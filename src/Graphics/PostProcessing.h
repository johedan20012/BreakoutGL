#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "GlMemory.hpp"
#include "Shader.h"

class PostProcessing{
    private:
        static unsigned int framebuffer;
        
        static unsigned int colorBuffers[2];
        static unsigned int depthBuffer;

        static unsigned int pingPongFramebuffers[2];

        static unsigned int pingPongColorBuffers[2];

        static ArrayObject QuadVAO;

        static Shader blurShader;
        static Shader bloomShader;
    public:
        static void init();

        static void bindFramebuffer();

        static void renderFramebuffer();

        static void cleanup();

    private:
        PostProcessing();
};

#endif