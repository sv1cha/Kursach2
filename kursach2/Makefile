CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -I.

SOURCES = main.cpp CalculatorRefactored.cpp ClientHandler.cpp ConnectorRefactored.cpp InterfaceRefactored.cpp LoggerRefactored.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = my_project

LIBS = -lcryptopp -lboost_program_options

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
