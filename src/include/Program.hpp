#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "glad/glad.h"
#include "glm/matrix.hpp"
#include "Shader.hpp"


enum class ProgramStatus {
   NOT_COMPILED,
   COMPILED
};

class Program {
public:
   Program();
   ~Program();

   void          attach_shader(const Shader& shader);
   //TODO: detach_shader()
   void          link();
   void          use();
   unsigned int  get_id() const;
   ProgramStatus get_status() const;

   void set_uniform_vec4f(const char* name, const glm::vec4& vector);
private:
   unsigned int  m_id{};
   ProgramStatus m_status{ProgramStatus::NOT_COMPILED};
};


//TODO: glValidateProgram!!


#endif //PROGRAM_HPP