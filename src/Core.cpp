#include "Core.hpp"

#include <GL/glew.h>

namespace iris
{
    bool init()
    {
        if (glewInit() != GLEW_OK)
            return false;

        return true;
    }
}