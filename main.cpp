#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdio>

const char* vs = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 model;
out vec3 vertexColor;
void main() {
    gl_Position = model * vec4(aPos, 1.0);
    vertexColor = aColor;
}
)";

const char* fs = R"(
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(vertexColor, 1.0);
}
)";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* w = glfwCreateWindow(800, 800,
        "Hello Triangle", nullptr, nullptr);
    glfwMakeContextCurrent(w);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    unsigned v = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v, 1, &vs, nullptr);
    glCompileShader(v);
    unsigned f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f, 1, &fs, nullptr);
    glCompileShader(f);
    unsigned p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);

    float verts[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts),
        verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT,
        GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT,
        GL_FALSE, 6 * sizeof(float),
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(w)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(p);

        float t = (float)glfwGetTime();
        float c = cosf(t);
        float s = sinf(t);

        float model[16] = {
            c, 0, -s, 0,
            0, 1,  0, 0,
            s, 0,  c, 0,
            0, 0,  0, 1
       };

        glUniformMatrix4fv(glGetUniformLocation(p, "model"),
            1, GL_FALSE, model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(w);
        glfwPollEvents();
    }
}
