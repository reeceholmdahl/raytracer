#include "Framebuffer.hpp"

namespace renderer
{
    void framebufferToGLPixelArray(const Framebuffer &fb, float *pixels)
    {
        // float *pixels = new float[3 * fb.m_width * fb.m_height];

        for (size_t i(0); i < fb.m_width; ++i)
        {
            // inner loop is inverted as per openGL texture standards
            for (size_t j(0); j < fb.m_height; ++j)
            {
                const size_t index_fb(fb.index(i, fb.m_height - j - 1));
                const size_t index_gl(fb.index(i, j));
                auto px(fb.m_pixelArray[index_fb]);
                pixels[3 * index_gl] = px[0];
                pixels[3 * index_gl + 1] = px[1];
                pixels[3 * index_gl + 2] = px[2];
            }
        }
    }
}