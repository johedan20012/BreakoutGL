#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <glm/glm.hpp>

namespace MathHelper{
    inline int taxiDistance(glm::vec2 a,glm::vec2 b){
        return (int)(abs(a.x-b.x)+abs(a.y-b.y));
    }
}


#endif