#ifndef SPRITE_ATLAS_HPP
#define SPRITE_ATLAS_HPP

#include <memory>
#include <vector>
#include <map>

#include "Texture.hpp"

enum TileConst {
   vertices_per_entire_tile = 8,
   vertices_per_input_tile  = 4,
   default_draw_method      = (GL_DYNAMIC_DRAW | GL_DYNAMIC_COPY),
   tile_offset              = 4,
};

enum RawTileArraySpec {
   x = 0,
   y = 1,
   width  = 2,
   height = 3,
   param_stride = 4,
};

class SpriteAtlas {
public:
   SpriteAtlas();
   SpriteAtlas(std::unique_ptr<Texture> texture);
   ~SpriteAtlas();

   void attach_texture(std::unique_ptr<Texture> texture, bool delete_old_tileset);

   //Tileset data format:
   //   -pixels are counted from left-down corner of a texture;
   //   -all the values are number of the pixels; 
   //   -numbers in array is laid out as follow:
   //   -[x, y, width, height],
   //   -where "x" and "y" are coordinates of left-down corner of the TILE;
   //   -all tiles must be drawn by only m_draw_method;
   //   -all tiles must be rectangle now;
   //   -first 2 value are polygon vertices, next 2 are texture coordinates;
   void attach_tileset(unsigned int raw_data[], size_t length);

   //Debug now
   void bind_texture();
   unsigned int get_coordinates_array();
   unsigned int get_tile_count() const;

private:
   //Adds single tile
   void add_tile(float* vertices);
   void compute_vertices(float* destination, unsigned int raw_data[], size_t length, size_t start_index);

private:
   std::unique_ptr<Texture> m_texture{nullptr};
   unsigned int m_coordinates_array{ 0 };
   unsigned int m_tile_count{ 0 };
};


#endif //SPRITE_ATLAS_HPP