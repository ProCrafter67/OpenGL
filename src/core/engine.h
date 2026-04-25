#pragma once

#include "renderer.h"
#include "util/window.h"

class OGLEngine
{
public:
    OGLEngine() : window(SCR_WIDTH, SCR_HEIGHT)
    {
        window.SetFramebufferSizeCallback(framebuffer_size_callback);
        window.SetMouseButtonCallback(mouse_button_callback);
        window.SetCursorPosCallback(mouse_callback);
        window.SetScrollCallback(scroll_callback);

        window.SetVsync(false);

        renderer = new Renderer(window);
    }
    ~OGLEngine()
    {
        renderer->CleanUp();
    }

    void run()
    {
        while(window.IsOpen())
        {
            renderer->Render(window);
            window.Refresh();
        }
    }

private:
    static inline Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Window window;
    Renderer* renderer;

    static inline const unsigned int SCR_WIDTH = 800;
    static inline const unsigned int SCR_HEIGHT = 600;

    static inline float lastX = SCR_WIDTH / 2.0f;
    static inline float lastY = SCR_HEIGHT / 2.0f;
    static inline bool firstMouse = true;
    static inline bool rightMousePressed = false;
    static inline bool ignoreNextMouseEvent = false;

    // timing
    static inline float deltaTime = 0.0f;
    static inline float lastFrame = 0.0f;

    // lighting
    static inline glm::vec3 lightPos = glm::vec3(1.2f, 2.0f, 2.0f);

    static inline bool gamma_correct = false;
    static inline bool cull_back_faces = true;
    static inline bool texture_transparent = false;

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
    static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (!rightMousePressed)
        {
            lastX = xpos;
            lastY = ypos;
            return;
        }

        if (ignoreNextMouseEvent)
        {
            ignoreNextMouseEvent = false;
            lastX = static_cast<float>(SCR_WIDTH) / 2.0f;
            lastY = static_cast<float>(SCR_HEIGHT) / 2.0f;
            return;
        }

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
            return;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        camera.ProcessMouseMovement(xoffset, yoffset);

        lastX = static_cast<float>(SCR_WIDTH) / 2.0f;
        lastY = static_cast<float>(SCR_HEIGHT) / 2.0f;
        ignoreNextMouseEvent = true;
        glfwSetCursorPos(window, lastX, lastY);
    }
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            if (action == GLFW_PRESS)
            {
                rightMousePressed = true;
                firstMouse = true;
                ignoreNextMouseEvent = true;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetCursorPos(window, SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0);
            }
            else if (action == GLFW_RELEASE)
            {
                rightMousePressed = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }
    }
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }

    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (rightMousePressed)
        {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.ProcessKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.ProcessKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.ProcessKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.ProcessKeyboard(RIGHT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                camera.ProcessKeyboard(UP, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                camera.ProcessKeyboard(DOWN, deltaTime);
        }
    }
};