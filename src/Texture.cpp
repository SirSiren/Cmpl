#include <iostream>
#include "glad/glad.h"
#include "include/Texture.hpp"
#include <stb_image/stb_image.hpp>


//TODO: delete glcall wrapper

//Every Texture must be unique! 
Texture::Texture(const std::string& path) :
   m_renderer_id{0}, m_file_path{path}, m_local_buffer{nullptr}, m_width{0}, m_height{0}, m_bit_per_pixel{0} {
   
   stbi_set_flip_vertically_on_load(1);
   m_local_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bit_per_pixel, 4);

   glGenTextures(1, &m_renderer_id);
   glBindTexture(GL_TEXTURE_2D, m_renderer_id);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);
   glBindTexture(GL_TEXTURE_2D, 0);

   //Maybe it must not be deleted
   if(m_local_buffer) {
      stbi_image_free(m_local_buffer);
   }
}

Texture::~Texture() {
   glDeleteTextures(1, &m_renderer_id);
}


void Texture::bind(unsigned int slot) const {
   glActiveTexture(GL_TEXTURE0 + slot);
   glBindTexture(GL_TEXTURE_2D, m_renderer_id);
}

void Texture::unbind() {
   glBindTexture(GL_TEXTURE_2D, 0);
}