#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "include\Polygon.hpp"

Polygon::Polygon(GLFWwindow* window, unsigned int width, unsigned int height) :
    m_vbo{ 0 }, m_ebo{ 0 }, m_width{ width }, m_height{ height } {
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    int win_width{ 0 };
    int win_height{ 0 };
    glfwGetWindowSize(window, &win_width, &win_height);

    float width_temp = static_cast<float>(width) / static_cast<float>(win_width);
    float height_temp = static_cast<float>(height) / static_cast<float>(win_height);

    float coordinates[vertices_per_polygon]{ 0 };
    coordinates[0] = coordinates[2] = -width_temp;
    coordinates[1] = coordinates[7] = -height_temp;
    coordinates[3] = coordinates[5] =  height_temp;
    coordinates[4] = coordinates[6] =  width_temp;

    glNamedBufferData(m_vbo, vertices_per_polygon * sizeof(float), coordinates, default_draw_method_p);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    unsigned int indices[]{
        0, 1, 2, 3
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_per_square * sizeof(unsigned int), indices, default_draw_method_p);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Polygon::~Polygon() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

unsigned int Polygon::get_vbo() const {
    return m_vbo;
}

unsigned int Polygon::get_ebo() const {
    return m_ebo;
}

unsigned int Polygon::get_width() const {
    return m_width;
}
unsigned int Polygon::get_height() const {
    return m_height;
}