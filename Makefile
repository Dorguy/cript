CXX := g++

CXXFLAGS := -std=c++11 -Wall

TARGET := editor

$(TARGET): image.h main.cpp
  $(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp
