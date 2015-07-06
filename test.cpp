#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <map>
#include <vector>
#include "game.pb.h"
#include <dirent.h>
#include "Types.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define TILE_W      64
#define TILE_H      32

using namespace std;
struct {
    SDL_Surface* screen;
    map<string, SDL_Surface*> images;
} m;
namespace game {

    void project(float x, float y, float z, int* dx, int *dy) {
        *dx = x * (TILE_W/2) - y * (TILE_W/2);
        *dy = x * (TILE_H/2) + y * (TILE_H/2) - z;
    }
    void invProject(float x, float y, float z, int* dx, int* dy) {
        float tw = TILE_W/2, th = TILE_H/2;
        *dx = x / tw + ((y + z) / th - x / tw) / 2;
        *dy = ((y + z) / th - x / tw) / 2;
    }
    void mainLoop() {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            /* If a button on the mouse is pressed. */
            if (event.type == SDL_MOUSEBUTTONDOWN) {
            } else if (event.type == SDL_MOUSEMOTION) { 
            }
        }
        SDL_Surface* image = m.images["floor1"];
        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {
                SDL_Rect dst;
                dst.w = image->w;
                dst.h = image->h;

                project(x, y, 0, &dst.x, &dst.y);
                dst.x -= TILE_W/2;
                SDL_BlitSurface (image, NULL, m.screen, &dst);
            }
        }
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        SDL_Rect dst;
        int tx, ty;
        invProject(mx, my, 0, &tx, &ty);
        image = m.images["floor2"];
        project(tx, ty, 0, &dst.x, &dst.y);
        //dst.y -= image->h;
        dst.w = image->w;
        dst.h = image->h;

        dst.x -= TILE_W/2;
        SDL_BlitSurface(image, NULL, m.screen, &dst);

        SDL_Flip(m.screen); 
    }
}
bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
int loadImages() {
    struct dirent **entries;
    int rc = scandir("img", &entries, NULL, alphasort);
    if (rc < 0)
        return -1;
    for (int i = 0; i < rc; i++) {
        string n = string("./img/") + entries[i]->d_name;
        if (!has_suffix(n, ".png"))
            continue;
        printf("%s\n", entries[i]->d_name);
        SDL_Surface *image = IMG_Load(n.c_str());
        string id = entries[i]->d_name;
        id = id.substr(0, id.size() - 4);
        m.images[id] = image;
        if (!image) { 
            printf("IMG_Load: %s\n", IMG_GetError());
            return -1;
        }
        free(entries[i]);
    }
    free(entries);
    return 0;
}

extern "C" int main(int argc, char** argv) {

    SDL_Init(SDL_INIT_VIDEO);

    m.screen = SDL_SetVideoMode(1024,768, 32, SDL_SWSURFACE);
    if (loadImages()) 
        return -1;
    emscripten_set_main_loop(game::mainLoop, 0, true);
    return 0;
}

