CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -g

GTEST_INC := /opt/homebrew/Cellar/googletest/1.16.0/include
GTEST_LIB := /opt/homebrew/Cellar/googletest/1.16.0/lib

TARGET := hashmap_tests
SRCS := HashMap.cpp main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(GTEST_INC) $(SRCS) -L$(GTEST_LIB) -lgtest -lgtest_main -pthread -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
