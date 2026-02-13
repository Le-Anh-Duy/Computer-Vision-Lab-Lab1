CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include

# Lấy cflags + libs của OpenCV trên Linux/WSL
OPENCV_FLAGS := $(shell pkg-config --cflags --libs opencv4)

EXECUTABLE := main

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp,$(BIN)/%.o,$(SOURCES))

all: $(BIN)/$(EXECUTABLE)

$(BIN):
	mkdir -p $(BIN)

$(BIN)/%.o: $(SRC)/%.cpp | $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $(OPENCV_FLAGS) -c $< -o $@

$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(OPENCV_FLAGS)

.PHONY: clean run

run: all
	./$(BIN)/$(EXECUTABLE)

clean:
	rm -rf $(BIN)/*.o $(BIN)/$(EXECUTABLE)