#ifndef ERROR_CHECKER_HPP
#define ERROR_CHECKER_HPP

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "glad/glad.h"

#define ASSERT(x) if (!(x)) { std::exit(EXIT_FAILURE); }
#define GLCall(x) GL_CLEAR_ERROR();\
   x;\
   ASSERT(GL_LOG_CALL_ERROR(__FILE__, #x, __LINE__))
 
inline void GL_CLEAR_ERROR() {
   while (glGetError() != GL_NO_ERROR);
}

inline bool GL_LOG_CALL_ERROR(const char* file, const char* function, int line) {
   while(GLenum error = glGetError()) {
      std::cout << "[OpenGL Error]\n" <<
      std::setw(15) << std::left << "error code:" << error    << "\n" <<
      std::setw(15) << std::left << "filename:"   << file     << "\n" <<
      std::setw(15) << std::left << "function: "  << function << "\n" <<
      std::setw(15) << std::left << "line: "      << line << std::endl;
      return false;
   }
   return true;
}

#endif //ERROR_CHECKER_HPP