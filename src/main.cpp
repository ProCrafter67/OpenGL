#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main()
{
    GLFWwindow* window;

    glfwInit();

    window = glfwCreateWindow(800, 600, "Hello", nullptr, nullptr);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}