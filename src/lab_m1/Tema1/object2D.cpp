#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 center = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3( - length, - length, 0), color),
        VertexFormat(center + glm::vec3( length, - length, 0), color),
        VertexFormat(center + glm::vec3(length,  length, 0), color),
        VertexFormat(center + glm::vec3(- length, length, 0), color)
    };


    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRomb(
    const std::string& name,
    glm::vec3 center,
    float sideLength,
    float rectangleWidth,
    float rectangleHeight,
    glm::vec3 color)
{



    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, sideLength, 0), color),
        VertexFormat(center + glm::vec3(sideLength / 2, 0, 0) , color),
        VertexFormat(center + glm::vec3(0, -sideLength, 0) , color),
        VertexFormat(center + glm::vec3(-sideLength / 2, 0, 0), color),

        VertexFormat(center + glm::vec3(rectangleWidth,rectangleHeight / 2, 0) , color),
        VertexFormat(center + glm::vec3(rectangleWidth, -rectangleHeight / 2, 0), color),
        VertexFormat(center + glm::vec3(0, -rectangleHeight / 2, 0), color),
        VertexFormat(center + glm::vec3(0, rectangleHeight / 2, 0), color)
    };

    Mesh* rhombus = new Mesh(name);

    std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 2, 4, 5, 7, 6, 5, 7 };


    rhombus->InitFromData(vertices, indices);
    return rhombus;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float radius,
    float smallRadius,
    glm::vec3 color,
    glm::vec3 color2)
{
    std::vector<VertexFormat> vertices;
    for (int i = 0; i < 6; i++) {
        float angle = i * (M_PI / 3.0);  
        glm::vec3 vertexPosition(
            center.x + radius * cos(angle),
            center.y + radius * sin(angle),
            center.z
        );
        vertices.push_back(VertexFormat(vertexPosition, color));
        
    }

    for (int i = 0; i < 6; i++) {
        float angle = i * (M_PI / 3.0);
        glm::vec3 vertexPosition(
            center.x + smallRadius * cos(angle),
            center.y + smallRadius * sin(angle),
            center.z
        );
        vertices.push_back(VertexFormat(vertexPosition, color2));
    }

    Mesh* hexagon = new Mesh(name);

    
    std::vector<unsigned int> indices = { 
										  6, 7, 8,
										  6, 8, 9,
										  6, 9, 10,
										  6, 10, 11,
                                          0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5
	};

    hexagon->InitFromData(vertices, indices);

    return hexagon;
}
Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float outerRadius,
    float innerRadius,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices;

    for (int i = 0; i < 5; ++i) {
        float angle = i * glm::two_pi<float>() / 5;
        glm::vec3 outerPoint(
            center.x + outerRadius * cos(angle),
            center.y + outerRadius * sin(angle),
            center.z
        );
        glm::vec3 innerPoint(
            center.x + innerRadius * cos(angle),
            center.y + innerRadius * sin(angle),
            center.z
        );

        vertices.push_back(VertexFormat(outerPoint, color));
        vertices.push_back(VertexFormat(innerPoint, color));
    }

    std::vector<unsigned int> indices = {
        4,7,3,
        2,5,1,
        0,3,9,
        8,1,7,
        6,9,5,
        7,3,9
    };

    Mesh* star = new Mesh(name);
    star->InitFromData(vertices, indices);

    return star;
}


Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color)
{
    glm::vec3 center = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0,0, 0), color),
        VertexFormat(center + glm::vec3(length, length, 0), color),
        VertexFormat(center + glm::vec3(2*length,2*length, 0), color),
        VertexFormat(center + glm::vec3(length,3*length, 0), color),
        VertexFormat(center + glm::vec3(-length,length, 0), color),
        VertexFormat(center + glm::vec3(-length,3*length, 0), color),
        VertexFormat(center + glm::vec3(-2*length,2*length, 0), color)
    };


    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices = { 0,6,5,
                                          0,2,3,
            							  5,1,0,
                                          4,3,2
    };

     
    
   
    heart->InitFromData(vertices, indices);
    return heart;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    int numSegments)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    float angleIncrement = glm::two_pi<float>() / static_cast<float>(numSegments);

    for (int i = 0; i < numSegments; ++i) {
        float angle = i * angleIncrement;
        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, y, center.z), color));

        // Create triangles using center vertex and two adjacent points.
        indices.push_back(i);
        indices.push_back((i + 1) % numSegments);
        indices.push_back(0);  // Center vertex
    }

    Mesh* circle = new Mesh(name);
    circle->InitFromData(vertices, indices);

    return circle;
}

Mesh* object2D::CreateRedX(const std::string& name, glm::vec3 center, float length) {
    glm::vec3 redColor = glm::vec3(1.0f, 0.0f, 0.0f); // Red color

    std::vector<VertexFormat> vertices = {
        VertexFormat(center + glm::vec3(-length, -length, 0), redColor),
        VertexFormat(center + glm::vec3(length, length, 0), redColor),
        VertexFormat(center + glm::vec3(-length, length, 0), redColor),
        VertexFormat(center + glm::vec3(length, -length, 0), redColor)
    };

    Mesh* redX = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 1 }; // Indices for drawing two crossed lines

    redX->SetDrawMode(GL_LINES);
    redX->InitFromData(vertices, indices);
    return redX;
}



