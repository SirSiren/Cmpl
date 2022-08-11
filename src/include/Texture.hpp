#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include "glad/glad.h"

class Texture {
public:
   Texture() = delete;
   Texture(const std::string& path);
   Texture(const Texture& texture) = delete;
   Texture& operator=(const Texture& texture) = delete;
   ~Texture();

   void bind(unsigned int slot = 0) const;
   void unbind();
   inline int  get_width()  const {return m_width;};
   inline int  get_height() const {return m_height;};

private:
      unsigned int   m_renderer_id{0};
      std::string    m_file_path{""};
      unsigned char* m_local_buffer{nullptr};
      int m_width{0};
      int m_height{0};
      int m_bit_per_pixel{0};
};



#endif //TEXTURE_HPP