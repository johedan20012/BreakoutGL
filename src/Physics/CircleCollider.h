#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Collider.h"


#include "../Graphics/Texture2D.h"
#include "../Graphics/Shader.h"
#include "../Graphics/SpriteRenderer.h"
#include "../Graphics/SpriteManager.h"

class CircleCollider : public Collider{
    private:
        glm::vec2 center;
        float radius;

    public:
        CircleCollider() = default;
        CircleCollider(glm::vec2 position,float radius);

        glm::vec2 calculateCenter() override;
        glm::vec2 calculateDimensions() override;
        void moveTo(glm::vec2 newPosition) override;
        void changeDimensions(glm::vec2 newDimensions)override;

        Texture2D debugSprite;
        void render(Shader& shader) override;
};

#endif