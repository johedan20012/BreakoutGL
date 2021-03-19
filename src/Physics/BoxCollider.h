#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.h"


#include "../Graphics/Texture2D.h"
#include "../Graphics/Shader.h"
#include "../Graphics/SpriteRenderer.h"
#include "../Graphics/SpriteManager.h"

class BoxCollider : public Collider{
    private:
        glm::vec2 min;
        glm::vec2 max;

    public:
        BoxCollider() = default;
        BoxCollider(glm::vec2 position,glm::vec2 size);

        glm::vec2 getMin();
        glm::vec2 getMax();

        glm::vec2 calculateCenter() override;
        glm::vec2 calculateDimensions() override;
        void moveTo(glm::vec2 newPosition) override;
        
        Texture2D debugSprite;
        void render(Shader& shader) override;
        
};

#endif