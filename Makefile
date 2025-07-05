# SDL2 Makefile

CXX = g++
CXXFLAGS = -Wall -std=c++17 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
TARGET = sdl_app
SRC = main.cpp tile.cpp tile_manager.cpp pulse.cpp pulse_manager.cpp UIElement.cpp #SDL_FontCache.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)