CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = program
OBJS = main.o SIGN.o Database.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Database.h SIGN.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Database.o: Database.cpp Database.h SIGN.h
	$(CXX) $(CXXFLAGS) -c Database.cpp

SIGN.o: SIGN.cpp SIGN.h
	$(CXX) $(CXXFLAGS) -c SIGN.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)