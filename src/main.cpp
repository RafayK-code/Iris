#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Vertex.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "camera/PerspectiveCamera.hpp"
#include "Core.hpp"
#include "Renderer.hpp"
#include "RenderObject.hpp"

#include <glm/gtc/type_ptr.hpp>

float velocityF;
float velocityR;

float lastX = 400.0f, lastY = 300.0f;
bool firstMouse = true;

iris::PerspectiveCamera camera = iris::PerspectiveCamera(45.0f, 1280.0f / 720.0f, 0.01, 1000);

void processInput(GLFWwindow* window, float dt)
{
    const float cameraSpeed = 5.0f * dt;
    glm::vec3 pos = camera.getPosition();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.setPosition(pos + camera.getForward() * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.setPosition(pos - camera.getForward() * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.setPosition(pos - camera.getRight() * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.setPosition(pos + camera.getRight() * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.setPosition(pos + glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.setPosition(pos - glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

glm::mat4 calculateCenteredAxisTransformationMatrix(const iris::PerspectiveCamera& camera) {
    glm::vec3 cameraPosition = camera.getPosition();

    // Use the camera's position to create a transformation matrix for the axes
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cameraPosition);
    // You can apply additional rotations or scaling if needed

    return model;
}


// Axis vertices and indices
std::vector<iris::Vertex> axisVertices = {
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // X-axis
    {{0.05f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // Y-axis
    {{0.0f, 0.05f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},

    {{0.0f, 0.0f, -0.05f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // Z-axis
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
};

std::vector<GLuint> axisIndices = {
    0, 1, 2, 3, 4, 5
};

std::vector<iris::Vertex> cubeVertices = {
    // Front face
    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

    // Back face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},

    // Left face
    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

    // Right face
    {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},

    // Top face
    {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

    // Bottom face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}
};

// Indices for a simple cube
std::vector<GLuint> cubeIndices = {
    0, 1, 2, 2, 3, 0,       // Front face
    4, 5, 6, 6, 7, 4,       // Back face
    8, 9, 10, 10, 11, 8,    // Left face
    12, 13, 14, 14, 15, 12, // Right face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20  // Bottom face
};

std::vector<iris::Vertex> roomVertices = {
    // Front face
    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, -1.0f}, {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, -1.0f},  {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, -1.0f},   {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, -1.0f},  {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},

    // Back face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f},  {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f},   {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f},  {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},

    // Left face
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f }, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f},  {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f},   {0.5f, 0.5f, 0.5f},{1.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},  {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},

    // Right face
    {{0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},
    {{0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},

    // Top face
    {{-0.5f, 0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},

    // Bottom face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}}
};

// Indices for a simple cube
std::vector<GLuint> roomIndices = {
    0, 1, 2, 2, 3, 0,       // Front face
    4, 5, 6, 6, 7, 4,       // Back face
    8, 9, 10, 10, 11, 8,    // Left face
    12, 13, 14, 14, 15, 12, // Right face
    16, 17, 18, 18, 19, 16, // Top face
    20, 21, 22, 22, 23, 20  // Bottom face
};

std::vector<iris::Vertex> lightCubeVertices = {
    // Front face
    {{-0.2f, -0.2f, 0.2f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.2f, -0.2f, 0.2f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.2f, 0.2f, 0.2f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.2f, 0.2f, 0.2f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

    // Back face
    {{-0.2f, -0.2f, -0.2f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.2f, -0.2f, -0.2f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{0.2f, 0.2f, -0.2f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.2f, 0.2f, -0.2f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
};

// Indices for a cube with shared vertices
std::vector<GLuint> lightCubeIndices = {
    0, 1, 2,  // Front face
    0, 2, 3,

    4, 5, 6,  // Back face
    4, 6, 7,

    0, 1, 5,  // Left face
    0, 5, 4,

    2, 3, 7,  // Right face
    2, 7, 6,

    0, 3, 7,  // Top face
    0, 7, 4,

    1, 2, 6,  // Bottom face
    1, 6, 5
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

    if (!iris::init())
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    iris::Renderer renderer;

    iris::Shader shader = iris::Shader("../shaders/default.vs", "../shaders/default.fs");
    shader.activate();

    iris::Shader axisShader = iris::Shader("../shaders/axis.vs", "../shaders/axis.fs");
    axisShader.activate();

    iris::Shader lightShader = iris::Shader("../shaders/light.vs", "../shaders/light.fs");
    lightShader.activate();

    /*
    iris::VAO vao = iris::VAO();
    vao.bind();

    iris::VBO vbo = iris::VBO(cubeVertices);
    iris::EBO ebo = iris::EBO(cubeIndices);

    vao.linkAttribute(vbo, 0, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));
    vao.linkAttribute(vbo, 1, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    vao.linkAttribute(vbo, 2, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    vao.linkAttribute(vbo, 3, 2, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(9 * sizeof(GL_FLOAT)));

    vbo.unbind();
    ebo.unbind();
    vao.unbind();
    */

    
    iris::RenderObject mesh = iris::RenderObject(cubeVertices, cubeIndices);

    iris::RenderObject room = iris::RenderObject(roomVertices, roomIndices);

    iris::RenderObject axis = iris::RenderObject(axisVertices, axisIndices);

    iris::RenderObject light = iris::RenderObject(lightCubeVertices, lightCubeIndices);

    /*
    iris::VAO vaoRoom = iris::VAO();
    vaoRoom.bind();

    iris::VBO vboRoom = iris::VBO(roomVertices);
    iris::EBO eboRoom = iris::EBO(roomIndices);

    vaoRoom.linkAttribute(vboRoom, 0, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));
    vaoRoom.linkAttribute(vboRoom, 1, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    vaoRoom.linkAttribute(vboRoom, 2, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    vaoRoom.linkAttribute(vboRoom, 3, 2, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(9 * sizeof(GL_FLOAT)));

    vboRoom.unbind();
    eboRoom.unbind();
    vaoRoom.unbind();

    iris::VAO vaoAxis = iris::VAO();
    vaoAxis.bind();


    iris::VBO vboAxis = iris::VBO(axisVertices);
    iris::EBO eboAxis = iris::EBO(axisIndices);

    vaoAxis.linkAttribute(vboAxis, 0, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));
    vaoAxis.linkAttribute(vboAxis, 1, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    vaoAxis.linkAttribute(vboAxis, 2, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    vaoAxis.linkAttribute(vboAxis, 3, 2, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(9 * sizeof(GL_FLOAT)));

    vboAxis.unbind();
    eboAxis.unbind();
    vaoAxis.unbind();

    iris::VAO vaoLight = iris::VAO();
    vaoLight.bind();

    iris::VBO vboLight = iris::VBO(lightCubeVertices);
    iris::EBO eboLight = iris::EBO(lightCubeIndices);

    vaoLight.linkAttribute(vboLight, 0, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));
    vaoLight.linkAttribute(vboLight, 1, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    vaoLight.linkAttribute(vboLight, 2, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    vaoLight.linkAttribute(vboLight, 3, 2, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(9 * sizeof(GL_FLOAT)));

    vboLight.unbind();
    eboLight.unbind();
    vaoLight.unbind();
    */

    camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    glm::mat4 model = glm::mat4(1.0f);

    lightShader.activate();
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(1.0f, 3.0f, 0.5f);

    glUniform4f(glGetUniformLocation(lightShader.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    GLuint vpLight = glGetUniformLocation(lightShader.getID(), "vp");
    GLuint modelLight = glGetUniformLocation(lightShader.getID(), "model");

    shader.activate();
    GLuint vpLoc = glGetUniformLocation(shader.getID(), "vp");
    GLuint modelLoc = glGetUniformLocation(shader.getID(), "model");
    glUniform4f(glGetUniformLocation(shader.getID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.getID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        double currTime = glfwGetTime();
        static double lastTime = glfwGetTime();
        float dt = currTime - lastTime;
        processInput(window, dt);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.activate();


        //model = glm::rotate(model, glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 0.0f)); // Rotate around the y-axis
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        //model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
        camera.setShaderMatrix(shader, "vp");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(shader.getID(), "camPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        //draw cube

        renderer.draw(mesh);
        
        //mesh.draw();

        /*
        vao.bind();
        ebo.bind();
        glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
        ebo.unbind();
        */

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(20.0f, 20.0f, 30.0f));
        camera.setShaderMatrix(shader, "vp");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(shader.getID(), "camPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        //draw cube

        renderer.draw(room);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        lightShader.activate();
        camera.setShaderMatrix(lightShader, "vp");
        glUniformMatrix4fv(modelLight, 1, GL_FALSE, glm::value_ptr(model));

        renderer.draw(light);

        glDisable(GL_DEPTH_TEST);

        axisShader.activate();
        model = glm::mat4(1.0f);
        glm::vec3 pos = camera.getPosition() + 1.0f * camera.getForward();
        model = glm::translate(model, pos);
        camera.setShaderMatrix(axisShader, "vp");
        glUniformMatrix4fv(glGetUniformLocation(axisShader.getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));

        renderer.draw(axis, GL_LINES);

        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);
        lastTime = currTime;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}