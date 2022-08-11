#ifndef SHADER_HPP
#define SHADER_HPP

#include <string_view>
#include <memory>
#include <map>

#include "glad/glad.h"

enum ShaderType {
   NONE = 0,
   VERTEX_SHADER = GL_VERTEX_SHADER,
   GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
   TESSELATION_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
   TESSELATION_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
   FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
   COMPUTE_SHADER = GL_COMPUTE_SHADER,
};

static std::map<ShaderType, std::string_view> shader_descriptor {
   {VERTEX_SHADER, "VERTEX SHADER"},
   {GEOMETRY_SHADER, "GEOMETRY SHADER"},
   {TESSELATION_CONTROL_SHADER, "TESSELATION CONTROL SHADER"},
   {TESSELATION_EVALUATION_SHADER, "TESSELATION EVALUATION SHADER"},
   {FRAGMENT_SHADER, "FRAGMENT SHADER"},
   {COMPUTE_SHADER, "COMPUTE SHADER"}
};

enum class ShaderStatus {
   NOT_COMPILED,
   COMPILED
};

class Shader {
public:
   Shader() = delete;
   Shader(ShaderType type, std::unique_ptr<std::string> source_filename);
   ~Shader();

   ShaderType   get_type()   const;
   unsigned int get_id()     const;
   ShaderStatus get_status() const;

   const std::string_view type_to_string();
private:
   ShaderType   m_type{ShaderType::NONE};
   unsigned int m_id{0};
   ShaderStatus m_status{ShaderStatus::NOT_COMPILED};
};

#endif //SHADER_HPP