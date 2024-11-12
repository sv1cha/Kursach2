#include "ClientHandler.h"
#include "LoggerRefactored.h"
#include "CalculatorRefactored.h"
#include "Errors.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fstream>    
#include <stdexcept>  
#include <string>
#include <random>
#include <iomanip>
#include <sstream>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/variate_generator.hpp>

#define BUFFER_SIZE 1024

std::unique_ptr<char[]> buffer(new char[BUFFER_SIZE]);
std::map<std::string, std::string> client_registry;

std::string ClientHandler::create_salt()
{
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<uint64_t> dist;
    uint64_t salt_val = dist(rng);

    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << salt_val;
    return ss.str();
}

std::string ClientHandler::compute_md5(const std::string& input)
{
    using namespace CryptoPP;
    Weak::MD5 hasher;
    std::string output;

    StringSource source(input, true,
        new HashFilter(hasher,
            new HexEncoder(
                new StringSink(output)
            )
        )
    );

    return output;
}

void load_client_registry(const char* filepath)
{
    std::ifstream file(filepath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t sep = line.find(':');
            if (sep != std::string::npos) {
                std::string username = line.substr(0, sep);
                std::string pwd = line.substr(sep + 1);
                client_registry[username] = pwd;
            }
        }
    } else {
        throw crit_err("Error opening client registry file");
    }
}

int ClientHandler::manage_connection(int port, const char* registry_path, const char* log_path, Logger* logger)
{
    try {
        load_client_registry(registry_path);
        logger->set_path(log_path);

        int connection_limit = 100;
        sockaddr_in *server_addr = new sockaddr_in;
        server_addr->sin_family = AF_INET;
        server_addr->sin_port = htons(port);
        inet_aton("127.0.0.1", &server_addr->sin_addr);
        int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd <= 0) {
            throw crit_err("Socket creation failed");
        } else {
            logger->writelog("Socket created");
        }
        
        auto bind_result = bind(socket_fd, (const sockaddr*)server_addr, sizeof(sockaddr_in));
        if (bind_result == -1) {
            throw crit_err("Binding socket failed");
        } else {
            logger->writelog("Bind successful");
        }

        auto listen_result = listen(socket_fd, connection_limit);
        if (listen_result == -1) {
            throw crit_err("Listening on socket failed");
        }

        while (true) {
            try {
                sockaddr_in *client_addr = new sockaddr_in;
                socklen_t addr_len = sizeof(sockaddr_in);
                int client_fd = accept(socket_fd, (sockaddr*)(client_addr), &addr_len);
                if (client_fd <= 0) {
                    throw no_crit_err("[Non-critical] Failed to accept client socket");
                }
                logger->writelog("Client socket accepted");

                char client_id_buffer[64] = {0};
                if (recv(client_fd, client_id_buffer, sizeof(client_id_buffer) - 1, 0) <= 0) {
                    close(client_fd);
                    throw no_crit_err("[Non-critical] Failed to receive client ID");
                }
                
                std::string client_id(client_id_buffer);
                logger->writelog("Received client ID: " + client_id);

                if (client_registry.find(client_id) == client_registry.end()) {
                    send(client_fd, "ERR", 3, 0);
                    close(client_fd);
                    throw no_crit_err("[Non-critical] Unknown client ID");
                }

                std::string salt = create_salt();
                if (send(client_fd, salt.c_str(), salt.length(), 0) <= 0) {
                    close(client_fd);
                    throw no_crit_err("[Non-critical] Failed to send salt");
                }
                logger->writelog("Salt sent: " + salt);

                char hash_buffer[64] = {0};
                if (recv(client_fd, hash_buffer, sizeof(hash_buffer) - 1, 0) <= 0) {
                    close(client_fd);
                    throw no_crit_err("[Non-critical] Failed to receive hash");
                }
                
                std::string client_hash(hash_buffer);
                logger->writelog("Received client hash: " + client_hash);

                std::string password = client_registry[client_id];
                std::string expected_hash = compute_md5(salt + password);

                logger->writelog("Salt: " + salt);
                logger->writelog("Password: " + password);
                logger->writelog("Expected hash: " + expected_hash);

                char reply[17] = {0};
                if (client_hash == expected_hash) {
                    std::strncpy(reply, "OK____________", 16);
                    logger->writelog("Authentication successful");
                } else {
                    std::strncpy(reply, "ERR___________", 16);
                    logger->writelog("Authentication failed");
                }

                if (send(client_fd, reply, 16, 0) <= 0) {
                    close(client_fd);
                    throw no_crit_err("[Non-critical] Failed to send response");
                }
                logger->writelog("Response sent: " + std::string(reply));

                if (client_hash != expected_hash) {
                    close(client_fd);
                    continue;
                }

                uint32_t vector_count;
                if (recv(client_fd, &vector_count, sizeof(vector_count), 0) <= 0) {
                    close(client_fd);
                    throw no_crit_err("[Non-critical] Failed to receive vector count");
                }
                logger->writelog("Vector count received: " + std::to_string(vector_count));

                for (uint32_t i = 0; i < vector_count; i++) {
                    uint32_t vector_size;
                    if (recv(client_fd, &vector_size, sizeof(vector_size), 0) <= 0) {
                        close(client_fd);
                        throw no_crit_err("[Non-critical] Failed to receive vector size");
                    }
                    std::vector<int64_t> vector_data(vector_size);
                    if (recv(client_fd, vector_data.data(), vector_size * sizeof(int64_t), 0) <= 0) {
                        close(client_fd);
                        throw no_crit_err("[Non-critical] Failed to receive vector data");
                    }
                    MathEngine engine(vector_data);
                    int64_t result = engine.retrieve_result();

                    if (send(client_fd, &result, sizeof(result), 0) <= 0) {
                        close(client_fd);
                        throw no_crit_err("[Non-critical] Failed to send computation result");
                    }
                    logger->writelog("Calculation result for vector " + std::to_string(i+1) + " sent");
                }

                close(client_fd);
                logger->writelog("Closed client connection");

            } catch (no_crit_err& e) {
                logger->writelog(e.what());
            }
        }
    } catch (crit_err& e) {
        logger->writelog(e.what());
    }
    return 0;
}
