#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left center, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRomb(const std::string& name, glm::vec3 leftBottomCorner, float length,float height,float width ,glm::vec3 color);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 center, float largeHexagonRadius, float smallHexagonRadius, glm::vec3 largeHexagonColor, glm::vec3 smallHexagonColor);
    Mesh* CreateStar(
        const std::string& name,
        glm::vec3 center,
        float outerRadius,
        float innerRadius,
        glm::vec3 color);
    Mesh* CreateCircle(
        const std::string& name,
        glm::vec3 center,
        float radius,
        glm::vec3 color,
        int numSegments);
    Mesh* CreateHeart(
        const std::string& name,
        glm::vec3 position,
        float size,
        glm::vec3 color);
    Mesh* CreateRedX(const std::string& name, glm::vec3 center, float length);
    
}
