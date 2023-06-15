# Компилятор C++
CXX := g++

# Флаги компиляции
CXXFLAGS := -std=c++11 -Wall

# Имя исполняемого файла
TARGET := editor

# Правило для сборки исполняемого файла
$(TARGET): image.h main.cpp
  $(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp
