#include <iostream>
#include <fstream>
#include <memory>
#include "include/Shader.hpp"

Shader::Shader(ShaderType type, std::unique_ptr<std::string> source_filename) :
   m_type{type}, m_id{glCreateShader(type)}, m_status{ShaderStatus::NOT_COMPILED} {

   //Trying to open source file
   std::ifstream shader_file{*source_filename};
   if(!shader_file) {
      //TODO: redirect to log-file
      std::cout << "Error! File hasn't been opened!" << std::endl;
   } else {
      //Seek for the end and get the length for the string
      shader_file.seekg(0, std::ios::end);
      int string_length = shader_file.tellg();
      
      //Allocating memory
      char* shader_source = new char[string_length + 1];
      shader_file.seekg(0, std::ios::beg);
      
      //Filling the array with file content
      for(int i{0}; i < string_length; ++i) {
         shader_source[i] = shader_file.get();
      }
      shader_source[string_length] = '\0';

      glShaderSource(m_id, 1, &shader_source, nullptr);
      glCompileShader(m_id);

      //Don't forget to free array
      delete [] shader_source;

      GLint vertex_compiled;
      glGetShaderiv(m_id, GL_COMPILE_STATUS, &vertex_compiled);
      if (vertex_compiled != GL_TRUE) {
         m_status = ShaderStatus::NOT_COMPILED;
         
         int info_log_length{0};
         glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &info_log_length);
         char* message = new char[info_log_length * sizeof(char)];
         
         int log_length;
         glGetShaderInfoLog(m_id, info_log_length, &log_length, message);
         //TODO: redirect to the log file
         std::cout << this->type_to_string() << " wasn't compiled!\n" << message << std::endl;
         // Write the error to a log
         delete [] message;
         glDeleteShader(m_id);
      } else {
         m_status = ShaderStatus::COMPILED;
      }
   }
}

Shader::~Shader() {
   glDeleteShader(m_id);
};


ShaderType Shader::get_type() const {
   return m_type;
}

unsigned int Shader::get_id() const {
   return m_id;
}

ShaderStatus Shader::get_status() const {
   return m_status;
}


const std::string_view Shader::type_to_string() {
   return shader_descriptor.at(m_type);
};