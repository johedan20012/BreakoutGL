#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Collider.h"

#ifdef MIDEBUG
    #include "../Graphics/Texture2D.h"
    #include "../Graphics/Shader.h"
    #include "../Graphics/SpriteRenderer.h"
#endif

class CircleCollider : public Collider{
    private:
        glm::vec2 center;
        float radius;

    public:
        CircleCollider() = default;
        CircleCollider(glm::vec2 position,float radius);

        glm::vec2 calculateCenter() override;
        glm::vec2 calculateDimensions() override;

        #ifdef MIDEBUG
            Texture2D debugSprite;
            void render(Shader& shader);
        #endif
};

#endif