#ifndef _types_h_
#define _types_h_
#include <vector>
#include <cstdint>
#include "game.pb.h"

namespace game {
    using namespace std;
    struct Tile {
        uint16_t floor;
        uint16_t background;
        uint16_t foreground;
        uint16_t walls[6];
        int8_t offsets[4];

        void load(const Game::Tile& tile) {
            floor = tile.floor();
            background = tile.background();
            foreground = tile.foreground();
            walls[0] = tile.wall1();
            walls[1] = tile.wall2();
            walls[2] = tile.wall3();
            walls[3] = tile.wall4();
            walls[4] = tile.wall5();
            walls[5] = tile.wall6();
            offsets[0] = tile.offset1();
            offsets[1] = tile.offset2();
            offsets[2] = tile.offset3();
            offsets[3] = tile.offset4();
        }
        void save(Game::Tile& tile) {
            tile.set_floor(floor);
            tile.set_background(background);
            tile.set_foreground(foreground);
            tile.set_wall1(walls[0]);
            tile.set_wall2(walls[1]);
            tile.set_wall3(walls[2]);
            tile.set_wall4(walls[3]);
            tile.set_wall5(walls[4]);
            tile.set_wall6(walls[5]);
            tile.set_offset1(offsets[0]);
            tile.set_offset2(offsets[1]);
            tile.set_offset3(offsets[2]);
            tile.set_offset4(offsets[3]);
        }
    };

    struct Map {
        int width, height, floors;
        vector<Tile> tiles;

        Tile& getTile(int x, int y, int z) {
            return tiles[z * width * height + y * width + x]; 
        }

        void load(Game::Map& map) {
            width  = map.width();
            height = map.height();
            floors = map.floors();
            tiles.clear();
            tiles.resize(width * height * floors);
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    const Game::TileStack& ts = map.tile_stacks(y * width + x);
                    for (int z = 0; z < ts.tiles_size(); z++) {
                        const Game::Tile& src = ts.tiles(z);
                        Tile& dst = getTile(x,y,z);
                        dst.load(src);
                    }
                }
            }
        }
        void save(Game::Map& map) {
            map.set_width(width);
            map.set_height(height);
            map.set_floors(floors);
            map.clear_tile_stacks();
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    Game::TileStack* ts = map.add_tile_stacks();
                    for (int z = 0; z < floors; z++) {
                        Tile& src = getTile(x,y,z);
                        if (src.floor) {
                            Game::Tile* dst = ts->add_tiles();
                            src.save(*dst);
                        }


                    }
                }
            }
        }
    };
}
#endif
