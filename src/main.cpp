#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Vertex.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "Shader.hpp"
#include "camera/PerspectiveCamera.hpp"

#include <glm/gtc/type_ptr.hpp>

float velocityF;
float velocityR;

float lastX = 400.0f, lastY = 300.0f;
bool firstMouse = true;

iris::PerspectiveCamera camera = iris::PerspectiveCamera(45.0f, 1280.0f / 720.0f, 0.01, 1000);

void processInput(GLFWwindow* window) 
{
    const float cameraSpeed = 0.05f;
    glm::vec3 pos = camera.getPosition();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.setPosition(pos + camera.getForward() * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.setPosition(pos - camera.getForward() * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.setPosition(pos - camera.getRight() * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.setPosition(pos + camera.getRight() * cameraSpeed);
}

// GLFW mouse callback
void mouse_callback(GLFWwindow* window, double xpos, double ypos) 
{
    if (firstMouse) {
        lastX = float(xpos);
        lastY = float(ypos);
        firstMouse = false;
    }

    float xoffset = float(xpos) - lastX;
    float yoffset = lastY - float(ypos); // reversed since y-coordinates range from bottom to top
    lastX = float(xpos);
    lastY = float(ypos);

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    float pitch = camera.getPitch() + yoffset;
    float yaw = camera.getYaw() + xoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    // Update camera rotation based on mouse movement
    camera.setYaw(yaw);
    camera.setPitch(pitch);
}

   // Define the vertices of a cube
    std::vector<iris::Vertex> cubeVertices = {
        // Vertex 1
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        // Vertex 2
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        // Vertex 3
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        // Vertex 4
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        // Vertex 5
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        // Vertex 6
        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        // Vertex 7
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        // Vertex 8
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    };

    std::vector<GLuint> cubeIndices = {
        0, 1, 2, 2, 3, 0,   // Front face
        4, 5, 6, 6, 7, 4,   // Back face
        0, 3, 7, 7, 4, 0,   // Left face
        1, 2, 6, 6, 5, 1,   // Right face
        0, 1, 5, 5, 4, 0,   // Bottom face
        2, 3, 7, 7, 6, 2    // Top face
    };

int main()
{
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Window", nullptr, nullptr);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    iris::Shader shader = iris::Shader("../shaders/default.vs", "../shaders/default.fs");
    shader.activate();

    iris::VAO vao = iris::VAO();
    vao.bind();

    iris::VBO vbo = iris::VBO(cubeVertices);
    iris::EBO ebo = iris::EBO(cubeIndices);

    vao.linkAttribute(vbo, 0, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));
    vao.linkAttribute(vbo, 1, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    vao.linkAttribute(vbo, 2, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    vao.linkAttribute(vbo, 3, 2, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(9 * sizeof(GL_FLOAT)));

    camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    glm::mat4 model = glm::mat4(1.0f);

    GLuint mvpLoc = glGetUniformLocation(shader.getID(), "mvp");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.activate();


        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 0.0f)); // Rotate around the y-axis
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewProjectionMatrix() * model));
        vao.bind();
        glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}