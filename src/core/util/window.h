#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "camera.h"

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_TITLE "OGLWindow"

class Window
{
public:    
    Window(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, const char *title = DEFAULT_TITLE)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(
            width,
            height,
            title,
            nullptr,
            nullptr);

        if (window == NULL)
        {
            std::cerr << "Failed to create GLFW window." << std::endl;
            glfwTerminate();
            exit(1);
        }

        glfwMakeContextCurrent(window);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    }
    ~Window()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void SetFramebufferSizeCallback(GLFWframebuffersizefun framebuffer_size_callback)
    {
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }
    void SetCursorPosCallback(GLFWcursorposfun mouse_callback)
    {
        glfwSetCursorPosCallback(window, mouse_callback);
    }
    void SetMouseButtonCallback(GLFWmousebuttonfun mouse_button_callback)
    {
        glfwSetMouseButtonCallback(window, mouse_button_callback);
    }
    void SetScrollCallback(GLFWscrollfun scroll_callback)
    {
        glfwSetScrollCallback(window, scroll_callback);
    }
    void SetVsync(bool key)
    {
        if (key)
            glfwSwapInterval(1);
    }

    GLFWwindow* GetWindow()
    {
        return window;
    }
    void Refresh()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    bool IsOpen()
    {
        return !glfwWindowShouldClose(window);
    }
        
private:
    GLFWwindow *window;
};