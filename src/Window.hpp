#pragma once
#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <string>

namespace iris
{
    struct WindowProps
    {
        std::string title;
        uint32_t width;
        uint32_t height;

        WindowProps(const std::string& title = "Iris", uint32_t width = 1280, uint32_t height = 720)
            : title(title), width(width), height(height)
        {
        }
    };

    class Window
    {
    public:
        Window();
        ~Window();



    private:
        GLFWwindow* _window;
    };

    }

#endif