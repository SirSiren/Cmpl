#include <iostream>
#include <memory>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "include/Shader.hpp"
#include "include/Program.hpp"
#include "include/Texture.hpp"
#include "include/SpriteAtlas.hpp"
#include "include/Animation.hpp"
#include "include\Polygon.hpp"


#include "include/ErrorChecker.hpp"

#define PR() {std::cout << "Here!\n";}

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Cmpl", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Error loading glad!" << std::endl;
    }

    auto vs_source{ std::make_unique<std::string>("./shaders/vertex.shader") };
    auto fs_source{ std::make_unique<std::string>("./shaders/fragment.shader") };
    auto vs{ std::make_shared<Shader>(ShaderType::VERTEX_SHADER, std::move(vs_source)) };
    auto fs{ std::make_shared<Shader>(ShaderType::FRAGMENT_SHADER, std::move(fs_source)) };
    
    auto default_program = std::make_unique<Program>();
    default_program->attach_shader(*vs);
    default_program->attach_shader(*fs);
    default_program->link();

    
    auto poly{ std::make_shared<Polygon>(window, 81, 137) };
    auto the_link{ std::make_unique<Texture>("./data/textures/man.png") };
    auto spr_atl{ std::make_shared<SpriteAtlas>(std::move(the_link)) };
    unsigned int standing[] {
        2,   885, 81, 137,
        85,  885, 81, 137,
        168, 885, 81, 137,
        251, 885, 81, 137,
        334, 885, 81, 137,
        416, 885, 81, 137,
        500, 885, 81, 137,  
        583, 885, 81, 137,
        666, 885, 81, 137,
        749, 885, 81, 137,
        832, 885, 81, 137,
        915, 885, 81, 137,
    };

    spr_atl->attach_tileset(standing, 12);
    
//blending
//TODO: let the objects to be set up by their unique way
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    glm::vec4 offset {0.0, 0.5, 0.0, 0.0};


    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //This are fields, which emulate the game_object's initializtion fields
    unsigned int vao{ 0 };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /////////
    //Bind the polygon's vertices to the "binding point 0" in shader
    glVertexArrayVertexBuffer(vao, 0, poly->get_vbo(), 0, 2 * sizeof(float));
    glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);

    //Bind the texture coordinates to the "binding point 1" in shader
    glVertexArrayVertexBuffer(vao, 1, spr_atl->get_coordinates_array(), 0, 2 * sizeof(float));
    glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, 0);
    
    //Binding to the attribute index (left) the binding point (right)
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribBinding(vao, 1, 1);

    //Enabling attribute binding only for this "vao"
    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, 1);

    //Bind element array buffer to "vao"
    glVertexArrayElementBuffer(vao, poly->get_ebo());
    /////////
    glBindVertexArray(0);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    default_program->set_uniform_vec4f("object_offset", offset);

    int i{ 0 };
    //Loop until the user closes the window
    while ( !glfwWindowShouldClose(window) ) {
        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spr_atl->bind_texture();
        default_program->use();

        //Bind vertex array
        glBindVertexArray(vao);

        //Setup tile's switching for debug purposes (play animation)
        glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, i * 8 * sizeof(float));
        
        //Draw vertex array
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

        //Switch frame
        if (i == spr_atl->get_tile_count() - 1) {
            i = 0;
        } else {
            i++;
        }

        //Swap front and back buffers
        glfwSwapBuffers(window);
        //Poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}