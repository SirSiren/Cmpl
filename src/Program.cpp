#include <iostream>

#include "include/Shader.hpp"
#include "include/Program.hpp"

#include "glm/glm.hpp"

#include "include/ErrorChecker.hpp"

Program::Program() :
   m_id{glCreateProgram()}, m_status{ProgramStatus::NOT_COMPILED} {
}

Program::~Program() {
   glDeleteProgram(m_id);
}


void Program::attach_shader(const Shader& shader) {
   glAttachShader(m_id, shader.get_id());
}

void Program::link() {
   glLinkProgram(m_id);

   int program_linked;
   glGetProgramiv(m_id, GL_LINK_STATUS, &program_linked);
   if (program_linked != GL_TRUE)
   {
      int info_log_length{0};
      glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &info_log_length);
      char* message = new char[info_log_length * sizeof(char)];

      glGetProgramInfoLog(m_id, info_log_length, &info_log_length, message);
      
      //TODO: redirect to the log file
      std::cout << "Program linking error!\n" << message << std::endl;
      // Write the error to a log
      delete [] message;
      glDeleteProgram(m_id);
   }
   glValidateProgram(m_id);

}

void Program::use() {
   glUseProgram(m_id);
}

unsigned int Program::get_id() const {
   return m_id;
}

ProgramStatus Program::get_status() const {
   return m_status;
}

void Program::set_uniform_vec4f(const char* name, const glm::vec4& vector) {
   int location = glGetUniformLocation(this->get_id(), name);
   glUniform4fv(location, 1, &vector.x);
}