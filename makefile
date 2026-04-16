CC = g++
CFLAGS = -g -Wall -std=c++11
TARGET = P4
SRCS = main.cpp token.cpp scanner.cpp testScanner.cpp parser.cpp node.cpp semantics.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = token.h scanner.h testScanner.h parser.h node.h semantics.h

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)