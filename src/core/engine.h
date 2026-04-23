#pragma once

#include "renderer.h"

class OGLEngine
{
public:
    OGLEngine();
    ~OGLEngine();

    void run();

private:
    Renderer renderer;
};