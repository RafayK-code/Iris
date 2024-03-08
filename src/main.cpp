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
#include "Texture.hpp"

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

// Vertices coordinates
std::vector<iris::Vertex> pyrVertices = { 
    {{-0.5f, 0.0f,  0.5f},     {0.83f, 0.70f, 0.44f},    {0.0f, -1.0f, 0.0f},  {0.0f, 0.0f}},  // Bottom side
    {{-0.5f, 0.0f, -0.5f},     {0.83f, 0.70f, 0.44f},    {0.0f, -1.0f, 0.0f},  {0.0f, 5.0f}},  // Bottom side
    {{ 0.5f, 0.0f, -0.5f},     {0.83f, 0.70f, 0.44f},    {0.0f, -1.0f, 0.0f},  {5.0f, 5.0f}},  // Bottom side
    {{ 0.5f, 0.0f,  0.5f},     {0.83f, 0.70f, 0.44f},    {0.0f, -1.0f, 0.0f},  {5.0f, 0.0f}},  // Bottom side
  
    {{-0.5f, 0.0f,  0.5f},     {0.83f, 0.70f, 0.44f},    {-0.8f, 0.5f, 0.0f},  {0.0f, 0.0f}}, // Left Side
    {{-0.5f, 0.0f, -0.5f},     {0.83f, 0.70f, 0.44f},    {-0.8f, 0.5f, 0.0f},  {5.0f, 0.0f}}, // Left Side
    {{ 0.0f, 0.8f,  0.0f},     {0.92f, 0.86f, 0.76f},    {-0.8f, 0.5f, 0.0f},  {2.5f, 5.0f}}, // Left Side
  
    {{-0.5f, 0.0f, -0.5f},     {0.83f, 0.70f, 0.44f},    {0.0f, 0.5f, -0.8f},  {5.0f, 0.0f}},  // Non-facing side
    {{ 0.5f, 0.0f, -0.5f},     {0.83f, 0.70f, 0.44f},    {0.0f, 0.5f, -0.8f},  {0.0f, 0.0f}},  // Non-facing side
    {{ 0.0f, 0.8f,  0.0f},     {0.92f, 0.86f, 0.76f},    {0.0f, 0.5f, -0.8f},  {2.5f, 5.0f}},  // Non-facing side
  
    {{ 0.5f, 0.0f, -0.5f},     {0.83f, 0.70f, 0.44f},    {0.8f, 0.5f,  0.0f},  {0.0f, 0.0f}},  // Right side
    {{ 0.5f, 0.0f,  0.5f},     {0.83f, 0.70f, 0.44f},    {0.8f, 0.5f,  0.0f},  {5.0f, 0.0f}},  // Right side
    {{ 0.0f, 0.8f,  0.0f},     {0.92f, 0.86f, 0.76f},    {0.8f, 0.5f,  0.0f},  {2.5f, 5.0f}},  // Right side
  
    {{ 0.5f, 0.0f,  0.5f},     {0.83f, 0.70f, 0.44f},    {0.0f, 0.5f,  0.8f},  {5.0f, 0.0f}},  // Facing side
    {{-0.5f, 0.0f,  0.5f},     {0.83f, 0.70f, 0.44f},    {0.0f, 0.5f,  0.8f},  {0.0f, 0.0f}},  // Facing side
    {{ 0.0f, 0.8f,  0.0f},     {0.92f, 0.86f, 0.76f},    {0.0f, 0.5f,  0.8f},  {2.5f, 5.0f}}  // Facing side
};

// Indices for vertices order
std::vector<GLuint> pyrIndices =
{
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
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
    
    iris::RenderObject mesh = iris::RenderObject(pyrVertices, pyrIndices);
    iris::RenderObject room = iris::RenderObject(roomVertices, roomIndices);
    iris::RenderObject axis = iris::RenderObject(axisVertices, axisIndices);
    iris::RenderObject light = iris::RenderObject(lightCubeVertices, lightCubeIndices);

    iris::Texture brickTex = iris::Texture("../assets/brick.png", "something", 0, GL_RGBA, GL_UNSIGNED_BYTE);
    brickTex.texUnit(shader, "tex0");

    camera.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    glm::mat4 model = glm::mat4(1.0f);

    lightShader.activate();
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

    lightShader.setUniform4f("lightColor", lightColor);

    shader.activate();
    shader.setUniform4f("lightColor", lightColor);
    shader.setUniform3f("lightPos", lightPos);

    mesh.identity();
    mesh.translate(glm::vec3(0.0f, 0.0f, -2.0f));
    mesh.scale(glm::vec3(2.0f, 2.0f, 2.0f));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        double currTime = glfwGetTime();
        static double lastTime = glfwGetTime();
        float dt = currTime - lastTime;
        processInput(window, dt);

        renderer.clear();

        shader.activate();

        mesh.rotate(1.0f * dt, glm::vec3(0, 1, 0));
        shader.setUniformMatrix4fv("vp", camera.getViewProjectionMatrix());
        shader.setUniformMatrix4fv("model", mesh.getModelMatrix());
        shader.setUniform3f("camPos", { camera.getPosition().x, camera.getPosition().y, camera.getPosition().z });

        renderer.draw(mesh);

        room.identity();
        room.scale(glm::vec3(20.0f, 20.0f, 30.0f));
        shader.setUniformMatrix4fv("model", room.getModelMatrix());

        //renderer.draw(room);

        light.identity();
        light.translate(lightPos);
        lightShader.activate();
        lightShader.setUniformMatrix4fv("vp", camera.getViewProjectionMatrix());
        lightShader.setUniformMatrix4fv("model", light.getModelMatrix());

        renderer.draw(light);

        glDisable(GL_DEPTH_TEST);

        axisShader.activate();

        axis.identity();
        glm::vec3 pos = camera.getPosition() + 1.0f * camera.getForward();
        axis.translate(pos);
        axisShader.setUniformMatrix4fv("vp", camera.getViewProjectionMatrix());
        axisShader.setUniformMatrix4fv("model", axis.getModelMatrix());

        renderer.draw(axis, GL_LINES);

        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);
        lastTime = currTime;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}