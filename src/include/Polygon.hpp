#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <GLFW\glfw3.h>


//TODO: make apropriate enum consts
enum PolygonConst {
    indices_per_square    = 4,
    vertices_per_polygon  = 8,
    default_draw_method_p = (GL_DYNAMIC_DRAW),
};

//!!!!Square polygon!!!!
class Polygon {
public:
    Polygon(GLFWwindow* window, unsigned int width, unsigned int height);
    ~Polygon();
    unsigned int get_vbo() const;
    unsigned int get_ebo() const;
    unsigned int get_width() const;
    unsigned int get_height() const;
private:
    unsigned int m_vbo{ 0 };
    unsigned int m_ebo{ 0 };
    unsigned int m_width{ 0 };
    unsigned int m_height{ 0 };
};

#endif //POLYGON_HPP