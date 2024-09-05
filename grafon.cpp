// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <unistd.h>
// Include GLEW - The OpenGL Extension Wrangler Library
#include <GL/glew.h>

// Include GLFW - Graphics Library Framework
#include <GLFW/glfw3.h>
GLFWwindow *window;

// Include GLM - OpenGL Mathematics
#include <glm/glm.hpp>
#include <iostream>

#include "shader.cpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
// using namespace glm;

int main(void)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(640, 360, "okno", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // куп
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, -1.0f, // Треугольник 1 : начало
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // Треугольник 1 : конец

        1.0f, 1.0f, -1.0f, // Треугольник 2 : начало
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, // Треугольник 2 : конец

        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f

    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // тривогольнек
    static const GLfloat triangle_vertex_buffer_data[] = {
        -1.0f,
        -1.0f,
        0.0f,

        1.0f,
        -1.0f,
        0.0f,

        0.0f,
        1.0f,
        0.0f,
    };

    GLuint trianglevertexbuffer;
    glGenBuffers(1, &trianglevertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, trianglevertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertex_buffer_data), triangle_vertex_buffer_data, GL_STATIC_DRAW);

    // цвет
    static GLfloat g_color_buffer_data[3 * 36];
    float r = 0.0, g = 0.0, b = 0.0;

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 100);
    for (int i = 0; i < 36; i++)
    {
        r = distrib(gen) * 0.01;
        g = distrib(gen) * 0.01;
        b = distrib(gen) * 0.01;
        g_color_buffer_data[i * 3] = r;
        g_color_buffer_data[i * 3 + 1] = g;
        g_color_buffer_data[i * 3 + 2] = b;
    }
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    // static GLfloat tri_color_buffer_data[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    // GLuint tricolorbuffer;
    // glGenBuffers(1, &tricolorbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, tricolorbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(tri_color_buffer_data), tri_color_buffer_data, GL_STATIC_DRAW);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.4f, 0.4f, 0.0f);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("vertex_shader.vert", "fragment_shader.frag");

    // Projection matrix: 45° Field of View, 16:9 ratio, display range: 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);

    // Camera (View) matrix, glm::lookAt(camera_position, where_camera_looks, orientation)
    glm::mat4 View = glm::lookAt(glm::vec3(3, 3, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    // Model matrix: an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection (MVP): multiplication of our 3 matrices
    // Remember, matrix multiplication is the other way around
    glm::mat4 mvp = Projection * View * Model;

    glm::mat4 mvp_tri = Projection * View * glm::translate(Model, glm::vec3(3.0f, 0.0f, 0.0f));

    // TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
    // !!! BEWARE!!! This lines actually performs the scaling FIRST, and THEN the rotation, and THEN the translation. This is how matrix multiplication works.

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    do
    {
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        // Use our shader
        glUseProgram(programID);

        // Cube
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,        // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0,        // stride
            (void *)0 // array buffer offset
        );

        // Colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

        // Triangle
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp_tri[0][0]);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, trianglevertexbuffer);
        glVertexAttribPointer(
            2,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glDisableVertexAttribArray(0);
        // glDisableVertexAttribArray(1);
        // glDisableVertexAttribArray(2);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
