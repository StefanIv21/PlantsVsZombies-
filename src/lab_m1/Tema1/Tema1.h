#pragma once

#include "components/simple_scene.h"
#include <vector>
#include <iostream>

using namespace std;

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
         Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderScene();
        void checktype(int type,int forma);
        int AABB(int x, int y, glm::mat3 modelMatrix,int type);

     protected:
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float angularStep;
        int directionx;
        glm::ivec2 resolution;
        float posx;
        float poxy;
        int type;
        bool moveTurret;
        float time;
        float dificulty;
        int lives;
        int timebonus;
        int reducetime;
        int resurse;
        int timeSpawnEnemy;
        float objectSide;
        glm::vec3 center;
        float timebonustar;
        

        struct bulet_info {
            float posx;
            int exist;
            int shoot;
            int enemy;
            int type;
            float posy;
            float radius;

        };

    struct cell_info {
        int exist;
        int type;
        float posx;
        float posy;
        vector<bulet_info> bulet;
        float timebulet;
        float scaleX;
        float scaleY;
        int hit;
        int delet;
        int nrenemy;
        float radius;

    };
    struct enemy_info {
        int type;
        float posx;
        float posy;
        int life;
        float scaleX;
        float scaleY;
        float radius;



    };
    struct bonus {
        float posx;
        float posy;
    };
    
    

    vector<enemy_info> enemies[3];
    struct cell_info matrix[3][3];
    vector <bonus> bonusuri;
    vector <bulet_info> bulets;

    float row_grid[3];

    };
}   
