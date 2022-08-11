#include <iostream>
#include "include/SpriteAtlas.hpp"

#include "include/ErrorChecker.hpp"

SpriteAtlas::SpriteAtlas() :
   m_texture{ nullptr }, m_coordinates_array{ 0 }, m_tile_count{ 0 } {

   //Vertex array buffer initialization
   glGenBuffers(1, &m_coordinates_array);
   glBindBuffer(GL_ARRAY_BUFFER, m_coordinates_array);
   glBufferData(GL_ARRAY_BUFFER, 0, 0, default_draw_method);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SpriteAtlas::SpriteAtlas(std::unique_ptr<Texture> texture) :
   m_texture{ std::move(texture) }, m_coordinates_array{ 0 }, m_tile_count{ 0 } {
   
   //Vertex array buffer initialization
   glGenBuffers(1, &m_coordinates_array);
   glBindBuffer(GL_ARRAY_BUFFER, m_coordinates_array);
   glBufferData(GL_ARRAY_BUFFER, 0, 0, default_draw_method);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SpriteAtlas::~SpriteAtlas() {
   glDeleteBuffers(1, &m_coordinates_array);
}

void SpriteAtlas::attach_texture(std::unique_ptr<Texture> texture, bool delete_old_tileset) {
   if(texture) {
      m_texture = std::move(texture);
   }
   if(delete_old_tileset) {
      m_tile_count = 0;
      glDeleteBuffers(1, &m_coordinates_array);
   }
}

void SpriteAtlas::attach_tileset(unsigned int raw_data[], size_t length) {
   if(length > 0) {
      float tile_vertices[vertices_per_entire_tile] {0};
      for(size_t i{ 0 }; i < length; ++i) {
         compute_vertices(tile_vertices, raw_data, length, i);
         add_tile(tile_vertices);
      }
   }
}

void SpriteAtlas::compute_vertices(float* destination, unsigned int raw_data[], size_t length, size_t start_index) {
   if(start_index >= 0) {
      float width_temp = static_cast<float>(raw_data[RawTileArraySpec::width + start_index * RawTileArraySpec::param_stride]) / m_texture->get_width();
      float height_temp = static_cast<float>(raw_data[RawTileArraySpec::height + start_index * RawTileArraySpec::param_stride])/ m_texture->get_height();

      //Fill texture coordinate vertices
      float x_temp = static_cast<float>(raw_data[RawTileArraySpec::x + start_index * RawTileArraySpec::param_stride])  / m_texture->get_width();
      float y_temp = static_cast<float>(raw_data[RawTileArraySpec::y + start_index * RawTileArraySpec::param_stride])  / m_texture->get_height();
      destination[0] = destination[2] = x_temp;
      destination[1] = destination[7] = y_temp;
      destination[4] = destination[6] = x_temp + width_temp;
      destination[3] = destination[5] = y_temp + height_temp;
   }
}

void SpriteAtlas::add_tile(float* vertices) {
    ++m_tile_count;
    int old_buffer_size{ 0 };
    unsigned int new_vbo{ 0 };

    glGetNamedBufferParameteriv(m_coordinates_array, GL_BUFFER_SIZE, &old_buffer_size);
    //Create new extended buffer to store tileset->length + 1 tiles and fill it
    glGenBuffers(1, &new_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, new_vbo);
    glNamedBufferData(new_vbo, old_buffer_size + (vertices_per_entire_tile * sizeof(float)), nullptr, GL_DYNAMIC_DRAW);
    //Copies old tileset vertices
    if (old_buffer_size > 0) {
        glCopyNamedBufferSubData(m_coordinates_array, new_vbo, 0, 0, old_buffer_size);
    }
    //Free old buffer memory space
    glDeleteBuffers(1, &m_coordinates_array);
    //Bind old vbo to the new one
    m_coordinates_array = new_vbo;
    //Copies new tileset vertices in the end of new buffer
    glNamedBufferSubData(new_vbo, old_buffer_size, vertices_per_entire_tile * sizeof(float), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteAtlas::bind_texture() {
   m_texture->bind();
}

unsigned int SpriteAtlas::get_tile_count() const {
    return m_tile_count;
}

unsigned int SpriteAtlas::get_coordinates_array() {
   return m_coordinates_array;
}