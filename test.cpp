#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include "game.pb.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define TILE_W      64
#define TILE_H      32
struct Tile {
    uint16_t floor;
    uint16_t background;
    uint16_t foreground;
    uint16_t walls[6];
};

using namespace std;

struct Map {
    int w, h;
    vector< vector<Tile> > tiles;
     
};

void project(float x, float y, float z, int* dx, int *dy) {
    *dx = x * (TILE_W/2) - y * (TILE_W/2);
    *dy = x * (TILE_H/2) + y * (TILE_H/2) - z;
}

extern "C" int main(int argc, char** argv) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(1024,768, 32, SDL_SWSURFACE);

    SDL_Surface *image = IMG_Load("./img/floor1.png");
    if (!image)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        return 0;
    }
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            SDL_Rect dst;
            dst.w = image->w;
            dst.h = image->h;
            project(x, y, 0, &dst.x, &dst.y);
            dst.x += 512;
            SDL_BlitSurface (image, NULL, screen, &dst);
        }
    }

    SDL_Flip(screen); 

    SDL_Quit();

    return 0;
}

