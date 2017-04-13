#pragma once

namespace Graphics
{
    ///
    /// Check for OpenGL error and write it to log if any
    ///
    void checkGLError(const char *fileName, int line);
}

