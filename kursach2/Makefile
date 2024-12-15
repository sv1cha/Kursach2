CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -I.

SOURCES = CalculatorRefactored.cpp ConnectorRefactored.cpp \
          ClientHandler.cpp InterfaceRefactored.cpp \
          LoggerRefactored.cpp Errors.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = my_project

TEST_SOURCES = tests.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_EXECUTABLE = test_project

LIBS = -lcryptopp -lboost_program_options
TEST_LIBS = -lUnitTest++

.PHONY: all clean test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) main.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

$(TEST_EXECUTABLE): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(TEST_OBJECTS) $(OBJECTS) $(LIBS) $(TEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TEST_OBJECTS) $(TEST_EXECUTABLE) main.o

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)
