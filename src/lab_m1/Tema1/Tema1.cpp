#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include <cstdlib> 

using namespace std;
using namespace m1;



Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}




void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    center = glm::vec3(0, 0, 0);
    objectSide = 50;
    posx = -100;
    poxy = -100;
    angularStep = 0;
    moveTurret = false;
    time = 0;
    type = -1;
    timebonustar = 0;
    reducetime = 4;
    timebonus = rand() % 3  + 3;
    dificulty = 0;
    timeSpawnEnemy = rand() % reducetime + reducetime;
    lives = 3;
    resurse = 5;
    

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j].exist = 0;
            matrix[i][j].type = 0;
            matrix[i][j].posx = 0;
            matrix[i][j].posy = 0;
            matrix[i][j].scaleX = 1;
            matrix[i][j].scaleY = 1;
            matrix[i][j].hit = 0;
            matrix[i][j].delet = 0;
            matrix[i][j].timebulet = 0;
            matrix[i][j].nrenemy = 0;
            matrix[i][j].radius = objectSide;
        }
    }

    Mesh* square1 = object2D::CreateSquare("square1", center, objectSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);
        
    Mesh* healthbar = object2D::CreateSquare("healthbar", center, objectSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(healthbar);

    Mesh* square2 = object2D::CreateSquare("square2", center, objectSide, glm::vec3(1,0, 0), false);
    AddMeshToList(square2);

    glm::vec3 center2 = glm::vec3(0, 0,2);
    Mesh* romb_portucaliu = object2D::CreateRomb("rombportucaliu", center2, objectSide,objectSide,objectSide/2 ,glm::vec3(1, 0.5, 0));
    AddMeshToList(romb_portucaliu);

    Mesh* romb_albastru = object2D::CreateRomb("rombalbastru", center2, objectSide, objectSide, objectSide / 2, glm::vec3(0, 0, 1));
    AddMeshToList(romb_albastru);

    Mesh* romb_galben = object2D::CreateRomb("rombgalben", center2, objectSide, objectSide, objectSide / 2, glm::vec3(1, 1, 0));
    AddMeshToList(romb_galben);

    Mesh* romb_mov = object2D::CreateRomb("rombmov", center2, objectSide, objectSide, objectSide / 2, glm::vec3(0.4, 0, 1));
    AddMeshToList(romb_mov);


    glm::vec3 center3 = glm::vec3(0, 0, 3);
    Mesh* hexagon_portucaliu = object2D::CreateHexagon("hexagon_portucaliu", center3, objectSide, objectSide / 2, glm::vec3(1, 0.5, 0), glm::vec3(0.1, 0.5, 0.5));
    AddMeshToList(hexagon_portucaliu);

    Mesh* hexagon_albastru = object2D::CreateHexagon("hexagon_albastru", center3, objectSide, objectSide / 2, glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.5));
    AddMeshToList(hexagon_albastru);

    Mesh* hexagon_galben = object2D::CreateHexagon("hexagon_galben", center3, objectSide, objectSide / 2, glm::vec3(1, 1, 0), glm::vec3(0.1, 0.5, 0.5));
    AddMeshToList(hexagon_galben);

    Mesh* hexagon_mov = object2D::CreateHexagon("hexagon_mov", center3, objectSide, objectSide / 2, glm::vec3(0.4, 0, 1), glm::vec3(0.1, 0.5, 0.5));
    AddMeshToList(hexagon_mov);

    Mesh* star_portucaliu = object2D::CreateStar("star_portucaliu", center2, objectSide , objectSide /2, glm::vec3(1, 0.5, 0));
    AddMeshToList(star_portucaliu);

    Mesh* star_albastru = object2D::CreateStar("star_albastru", center2, objectSide, objectSide / 2, glm::vec3(0, 0, 1));
    AddMeshToList(star_albastru);

    Mesh* star_galben = object2D::CreateStar("star_galben", center2, objectSide, objectSide / 2, glm::vec3(1, 1, 0));
    AddMeshToList(star_galben);

    Mesh* star_mov = object2D::CreateStar("star_mov", center2, objectSide, objectSide / 2, glm::vec3(0.4, 0, 1));
    AddMeshToList(star_mov);

    Mesh* star_gri = object2D::CreateStar("star_gri", center2, objectSide, objectSide / 2, glm::vec3(0.4, 0.4, 0.4));
    AddMeshToList(star_gri);

    Mesh* heart = object2D::CreateHeart("heart", center2, objectSide/2, glm::vec3(1, 0, 0));
    AddMeshToList(heart);

    Mesh* circle = object2D::CreateCircle("circle", center2, objectSide, glm::vec3(1, 0, 0), 100);
    AddMeshToList(circle);


    Mesh* redX = object2D::CreateRedX("redX", center2, objectSide);
    AddMeshToList(redX);



     resolution = window->GetResolution();
     directionx = resolution.x + 20;
  

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::checktype(int type,int forma)
{
    if (type == 0)
    {
        if (forma == 0)
        {
            RenderMesh2D(meshes["hexagon_portucaliu"], shaders["VertexColor"], modelMatrix);
        }
        else if (forma == 2)
        {
            RenderMesh2D(meshes["star_portucaliu"], shaders["VertexColor"], modelMatrix);
        }
        else 
            RenderMesh2D(meshes["rombportucaliu"], shaders["VertexColor"], modelMatrix);
    }
    else if (type == 1)
    {
        if (forma == 0)
        {
            RenderMesh2D(meshes["hexagon_albastru"], shaders["VertexColor"], modelMatrix);
        }
        else if (forma == 2)
        {
            RenderMesh2D(meshes["star_albastru"], shaders["VertexColor"], modelMatrix);
        }
        else
            RenderMesh2D(meshes["rombalbastru"], shaders["VertexColor"], modelMatrix);
    }
    else if (type == 2)
    {
        if (forma == 0)
        {
            RenderMesh2D(meshes["hexagon_galben"], shaders["VertexColor"], modelMatrix);
        }
        else if (forma == 2)
        {
            RenderMesh2D(meshes["star_galben"], shaders["VertexColor"], modelMatrix);
        }
        else
            RenderMesh2D(meshes["rombgalben"], shaders["VertexColor"], modelMatrix);
    }
    else if (type == 3)
    {
        if (forma == 0)
        {
            RenderMesh2D(meshes["hexagon_mov"], shaders["VertexColor"], modelMatrix);
        }
        else if (forma == 2)
        {
           RenderMesh2D(meshes["star_mov"], shaders["VertexColor"], modelMatrix);
        }
        else
            RenderMesh2D(meshes["rombmov"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::RenderScene()
{
    if (lives == 0)
    {
        exit(0);
    }

    //final redzone
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(0.5f, 4.3f);
    modelMatrix *= transform2D::Translate(75, 55);
    RenderMesh2D(meshes["healthbar"], shaders["VertexColor"], modelMatrix);

    // Create a 3x3 grid of squares with gaps
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Scale(1.2f, 1.2f);
            modelMatrix *= transform2D::Translate(130.0f + row * 130.0f, 70.0f + col * 130.0f);
            RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
        }
        row_grid[row] = 80.0f + row * 160.0f;
    }

    //turets
    for (int row = 0; row < 4; ++row)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(150.0f + 150.0f * row, 650.0f);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix *= transform2D::Scale(0.9f, 0.9f);
        if (row == 0)
        {
            if (resurse >= 1)
            {
				RenderMesh2D(meshes["rombportucaliu"], shaders["VertexColor"], modelMatrix);
			}
            else
            {
				RenderMesh2D(meshes["redX"], shaders["VertexColor"], modelMatrix);
			}
            
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(120.0f + 150.0f * row, 575.0f);
            modelMatrix *= transform2D::Scale(0.3f, 0.3f);
            modelMatrix *= transform2D::Rotate(-1.0f);
            RenderMesh2D(meshes["star_gri"], shaders["VertexColor"], modelMatrix);
        }
        else if (row == 1)
        {
            if (resurse >= 2)
            {
                RenderMesh2D(meshes["rombalbastru"], shaders["VertexColor"], modelMatrix);
            }
            else
            {
                RenderMesh2D(meshes["redX"], shaders["VertexColor"], modelMatrix);
            }
            for (int i = 0; i < 2; i++)
            {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(120.0f+ 30.0f*i + 150.0f * row, 575.0f);
                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                modelMatrix *= transform2D::Rotate(-1.0f);
                RenderMesh2D(meshes["star_gri"], shaders["VertexColor"], modelMatrix);
            }
            


        }
        else if (row == 2)
        {
            if (resurse >= 2)
            {
				RenderMesh2D(meshes["rombgalben"], shaders["VertexColor"], modelMatrix);
			}
            else
            {
				RenderMesh2D(meshes["redX"], shaders["VertexColor"], modelMatrix);
			}

            for (int i = 0; i < 2; i++)
            {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(120.0f + 30.0f * i + 150.0f * row, 575.0f);
                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                modelMatrix *= transform2D::Rotate(-1.0f);
                RenderMesh2D(meshes["star_gri"], shaders["VertexColor"], modelMatrix);
            }
        }
        else if (row == 3)
        {
            if (resurse >= 3)
            {
                RenderMesh2D(meshes["rombmov"], shaders["VertexColor"], modelMatrix);
            }
            else
            {
				RenderMesh2D(meshes["redX"], shaders["VertexColor"], modelMatrix);
			}
            for (int i = 0; i < 3; i++)
            {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(120.0f + 30.0f * i + 150.0f * row, 575.0f);
                modelMatrix *= transform2D::Scale(0.3f, 0.3f);
                modelMatrix *= transform2D::Rotate(-1.0f);
                RenderMesh2D(meshes["star_gri"], shaders["VertexColor"], modelMatrix);
            }
        }
    }

    for (int row = 0; row < lives; row++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(780.0f + 100.0f * row, 610.0f);
        modelMatrix *= transform2D::Scale(0.8f, 0.8f);

        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }
    for (int row = 0; row < resurse; row++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(780.0f + 50.0f * row, 580.0f);
        modelMatrix *= transform2D::Scale(0.4f, 0.4f);
        modelMatrix *= transform2D::Rotate(-1.0f);
        RenderMesh2D(meshes["star_mov"], shaders["VertexColor"], modelMatrix);

    }
}
void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    RenderScene();


    if (moveTurret)
    {
        modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(posx, poxy);
        checktype(type, 1);
	}

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (matrix[row][col].exist == 1)
            {
                float posx = matrix[row][col].posx;
                float poxy = matrix[row][col].posy;
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(posx, poxy);
                if (matrix[row][col].hit == 1 || matrix[row][col].delet == 1)
                {
					matrix[row][col].scaleX -= deltaTimeSeconds ;
					matrix[row][col].scaleY -= deltaTimeSeconds ;
					modelMatrix *= transform2D::Scale(matrix[row][col].scaleX, matrix[row][col].scaleY);
				}
                checktype(matrix[row][col].type, 1);
                if (matrix[row][col].scaleX < 0.1)
                {
                    matrix[row][col].exist = 0;
					matrix[row][col].type = 0;
					matrix[row][col].posx = 0;
					matrix[row][col].posy = 0;
					matrix[row][col].scaleX = 1;
					matrix[row][col].scaleY = 1;
					matrix[row][col].hit = 0;
                    matrix[row][col].delet = 0;
                    matrix[row][col].timebulet = 0;
                    matrix[row][col].nrenemy = 0;
                        

                }
            }
           
        }
    }
    time += deltaTimeSeconds;
    dificulty += deltaTimeSeconds;
    timebonustar += deltaTimeSeconds;

    if (dificulty >30)
    {
        reducetime -= 1;
        dificulty = 0;
	}
    if (time > timeSpawnEnemy)
    {
        int linie = rand() % 3;
        enemy_info newEnemy;
        newEnemy.type = rand() % 4;
        newEnemy.posx = (float)directionx;
        newEnemy.posy = row_grid[linie];
        newEnemy.life = 3;
        newEnemy.scaleX = 1;
        newEnemy.scaleY = 1;
        newEnemy.radius = objectSide;
        enemies[linie].push_back(newEnemy);
        time = 0;
        if (reducetime > 0)
        {
            timeSpawnEnemy = rand() % reducetime + reducetime;
        }
        for (int j = 0; j < 3; j++)
        {
            if (matrix[j][linie].type == newEnemy.type && matrix[j][linie].exist != 0)
            {
				matrix[j][linie].nrenemy += 1;
			}
		}

    }
    for (int i = 0; i < 3; i++) {
        for (int index = 0; index < enemies[i].size(); ++index) {
            auto& enemy = enemies[i][index];
            if (enemy.life != 0)
            {
                enemy.posx -= deltaTimeSeconds * 50.0f;
            }
            float posx = enemy.posx;

            float posy = enemy.posy;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(posx, posy);
            modelMatrix *= transform2D::Rotate(1.2f);
            if (enemy.life == 0)
            {
                enemy.scaleX -= deltaTimeSeconds * 0.9f;
                enemy.scaleY -= deltaTimeSeconds * 0.9f;
                modelMatrix *= transform2D::Scale(enemy.scaleX,enemy. scaleY);
                checktype(enemy.type, 0);
            }
            else
            {
                checktype(enemy.type, 0);
                
            }
            if (enemy.scaleX < 0.1)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (matrix[j][i].type == enemy.type && matrix[j][i].exist != 0)
                    {
                        matrix[j][i].nrenemy -= 1;
                    }
                }
                enemies[i].erase(enemies[i].begin() + index);
                continue;
            }
            if (enemy.posx < 50)
            {
                lives -= 1;
                for (int j = 0; j < 3; j++)
                {
                    if (matrix[j][i].type == enemy.type)
                    {
                        matrix[j][i].nrenemy -= 1;
                    }
                }
				enemies[i].erase(enemies[i].begin() + index);
				continue;
            }
        }
    }
    angularStep -= deltaTimeSeconds * 5;
    for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++)
          {
              if (matrix[j][i].exist != 1)
              {
                  continue;
              }
              int enemyTypeExist = 0;
              for (int index = 0; index < enemies[i].size(); ++index) {
                  auto& enemy = enemies[i][index];

                  float posx = enemy.posx;
             
                  float posy = enemy.posy;

                  float pos2x = matrix[j][i].posx;
                  float pos2y = matrix[j][i].posy;

                  float dist = sqrt((posx - pos2x) * (posx - pos2x) + (posy - pos2y) * (posy - pos2y));

                  if (dist < matrix[j][i].radius+enemy.radius && enemy.life != 0)
                  {
                      matrix[j][i].hit = 1;

                      if (matrix[j][i].bulet.size() > 0)
                      {
                          for (int i = 0; i < matrix[j][i].bulet.size(); i++)
                          {
                              
                              bulets.push_back(matrix[j][i].bulet[i]);
                          }
                          matrix[j][i].bulet.clear();
                      }
                      break;
                     
                  }
                  if (matrix[j][i].type == enemy.type && enemyTypeExist != 1)
                  {
                      enemyTypeExist = 1;
                      matrix[j][i].timebulet += deltaTimeSeconds;
                      if (matrix[j][i].timebulet > 2)
                      {
                          bulet_info newBulet;
                          newBulet.posx = matrix[j][i].posx;
                          newBulet.exist = 1;
                          newBulet.shoot = 1;
                          newBulet.enemy = 1;
                          newBulet.type = matrix[j][i].type;
                          newBulet.posy = matrix[j][i].posy;
                          newBulet.radius = objectSide;
                        
                          if (enemy.life != 0)
                          {
                              matrix[j][i].bulet.push_back(newBulet);
                              matrix[j][i].timebulet = 0;
                          }

                      }
                  }

                  for (int index2 = 0; index2 < matrix[j][i].bulet.size(); ++index2) {
                      auto& bulet = matrix[j][i].bulet[index2];
                      float pos3x = bulet.posx;
                      float pos3y = matrix[j][i].posy;
                      if (pos3x > posx && matrix[j][i].nrenemy == 1 && matrix[j][i].type == enemy.type && enemy.life != 0)
                      {
                         
                          bulet.shoot = 0;
                          
                          
                      }
                      if (pos3x < posx  && matrix[j][i].nrenemy > 1)
                      {
                         
						  bulet.shoot = 1;

					  }
                      if (pos3x < posx && matrix[j][i].type == enemy.type && matrix[j][i].hit != 1 && enemy.life != 0)
                      {  
                             dist = sqrt((pos3x - posx) * (pos3x - posx) + (pos3y - posy) * (pos3y - posy));
                          
                             if (dist < enemy.radius + bulet.radius && enemy.life != 0 )
                             {
                                 
                                  enemy.life -= 1;
                               

                                  matrix[j][i].bulet.erase(matrix[j][i].bulet.begin() + index2);

                             }

                          
                      }
           



                  }
               

              }
              if (matrix[j][i].hit == 1 || matrix[j][i].delet == 1)
              {
                  continue;
              }
              for (int index = 0; index < matrix[j][i].bulet.size(); ++index ) {
                  if ( matrix[j][i].delet == 1)
                  {
                      break;
                  }
                  auto& bulet = matrix[j][i].bulet[index];
                  bulet.posx += deltaTimeSeconds * 300;
                  float pos2x = bulet.posx;
                  float pos2y = matrix[j][i].posy;
                  modelMatrix = glm::mat3(1);
                  modelMatrix *= transform2D::Translate(pos2x + 30, pos2y);
                  modelMatrix *= transform2D::Scale(0.5, 0.5);
                  modelMatrix *= transform2D::Rotate(angularStep);
                 
                  if (bulet.shoot == 1)
                  {
                      
                      checktype(matrix[j][i].type, 2);
                  
                  }
                  if (pos2x > 1300)
                  {
                      matrix[j][i].bulet.erase(matrix[j][i].bulet.begin() + index);
                  }

              }
          }
    }

    for (int index = 0; index < bulets.size(); ++index) {
		auto& bulet = bulets[index];
		bulet.posx += deltaTimeSeconds * 300;
		float pos2x = bulet.posx;
		float pos2y = bulet.posy;
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(pos2x + 30, pos2y);
        modelMatrix *= transform2D::Scale(0.5, 0.5);
		modelMatrix *= transform2D::Rotate(angularStep);
        if (bulet.shoot == 1)
        {
			checktype(bulet.type, 2);
		}
        if (pos2x > 1300)
        {
			bulets.erase(bulets.begin() + index);
		}
        for (int i = 0; i < 3; i++)
        {
            for (int index2 = 0; index2 < enemies[i].size(); ++index2) {
               auto& enemy = enemies[i][index2];
				float posx = enemy.posx;
				float posy = enemy.posy;
                if (bulet.type == enemy.type && enemy.life != 0)
                {
                    float dist = sqrt((pos2x - posx) * (pos2x - posx) + (pos2y - posy) * (pos2y - posy));
                    if (dist < 100 && enemy.life != 0)
                    {
                        enemy.life -= 1;
                        bulets.erase(bulets.begin() + index);
                    }
                }
            }
        }
	}
    

    if (timebonustar > timebonus )
    {
        int number = rand() % 4 ;
        for (int i = 0; i < number; i++)
        {
            float x = (float)(rand() % window->GetResolution().x);
            float y =(float) (rand() % window->GetResolution().y);
            bonus newbonus;
            newbonus.posx = x;
            newbonus.posy = y;
            bonusuri.push_back(newbonus);
        }
        timebonus = rand() % 4 + 4;
        timebonustar = 0;
    }
    if (bonusuri.size() > 10)
    {
        for (int i = 0; i < 5; i++)
        {
            bonusuri.erase(bonusuri.begin() + i);
        }
    }
    for (int index = 0; index < bonusuri.size(); ++index) {
		auto& bonus = bonusuri[index];
		float posx = bonus.posx;
		float posy = bonus.posy;
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(posx, posy);
		modelMatrix *= transform2D::Scale(0.5, 0.5);
		RenderMesh2D(meshes["star_portucaliu"], shaders["VertexColor"], modelMatrix);



   
	}
  



  
  
    
  





   
  
    
}


void Tema1::FrameEnd()
{
}





void Tema1::OnInputUpdate(float deltaTime, int mods)
{
   
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (moveTurret)
    {
        posx = (float)mouseX;
        poxy = (float)(720 - mouseY);
    }
}
int Tema1::AABB(int mouseX, int mouseY, glm::mat3 modelMatrix2,int type)
{
    glm::vec3 stangajos(-objectSide, -objectSide, 1);
    glm::vec3 dreaptajos(objectSide, -objectSide, 1);
    glm::vec3 susdreapta(objectSide, objectSide, 1);

    stangajos = modelMatrix2 * stangajos;
    dreaptajos = modelMatrix2 * dreaptajos;
    susdreapta = modelMatrix2 * susdreapta;

    int scenaY = 720 - mouseY;
    int scenaX = mouseX;

    if (scenaX > stangajos.x && scenaX < dreaptajos.x && scenaY > stangajos.y && scenaY < susdreapta.y)
    {
        if (type == 1)
        {
            float latura = dreaptajos.x - stangajos.x;
            posx = dreaptajos.x - latura / 2;
            poxy = dreaptajos.y + latura / 2;
        }
        return 1;
    }
    return 0;

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == 1) {
        for (int row = 0; row < 4; row++) {
            glm::mat3 modelMatrix2 = glm::mat3(1);
            modelMatrix2 *= transform2D::Translate(150.0f + 150.0f * row, 650.0f); 
            int check = AABB(mouseX, mouseY, modelMatrix2,0);
            int resursenecesare = 0;
            if (row > 1)
            {
                resursenecesare = row;
            }
            else
                resursenecesare = row + 1;
            if (check == 1 && resurse >= resursenecesare)
            {
                moveTurret = true;
                posx = (float)mouseX;
                poxy = (float)(720 - mouseY);
                type = row;
            } 
        }
        for (int index = 0; index < bonusuri.size(); ++index) {
            auto& bonus = bonusuri[index];
            float posx = bonus.posx;
            float posy = bonus.posy;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(posx, posy);
            modelMatrix *= transform2D::Scale(0.5, 0.5);
            int check = AABB(mouseX, mouseY, modelMatrix,0);
            if (check == 1 )
            {
                resurse++;
                bonusuri.erase(bonusuri.begin() + index);
            }       
        }
    }
    if (button == 2)
    {   
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                glm::mat3 modelMatrix3 = glm::mat3(1);
                modelMatrix3 *= transform2D::Scale(1.2f, 1.2f);
                modelMatrix3 *= transform2D::Translate(130.0f + row * 130.0f, 70.0f + col * 130.0f);
                int check = AABB(mouseX, mouseY, modelMatrix3,0);
          
                if (check == 1)
                {     
                    if (matrix[row][col].exist == 1)
                    {
                       
                        matrix[row][col].delet = 1;
                        if (matrix[row][col].bulet.size() > 0)
                        {
                          
                            for (int i = 0; i < matrix[row][col].bulet.size(); i++)
                            {
                                bulets.push_back(matrix[row][col].bulet[i]);
                            }
                            matrix[row][col].bulet.clear();
                        }
                        matrix[row][col].timebulet = 0;
                      
                    }
                }
            }

        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_2 && moveTurret)
    {
        moveTurret = false;
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                glm::mat3 modelMatrix3 = glm::mat3(1);
                modelMatrix3 *= transform2D::Scale(1.2f, 1.2f);
                modelMatrix3 *= transform2D::Translate(130.0f + row * 130.0f, 70.0f + col * 130.0f);
                int check = AABB(mouseX, mouseY, modelMatrix3,1);
                int resursenecesare = 0;
                if (type > 1)
                {
                    resursenecesare = type;
                }
                else
                    resursenecesare = type + 1;

                if (check == 1 && matrix[row][col].exist != 1 )
                {
                    matrix[row][col].exist = 1;
                    matrix[row][col].posx = posx;
                    matrix[row][col].posy = poxy;
                    matrix[row][col].type = type;
                    resurse -= resursenecesare;
                    type = -1;
                    for (int index = 0; index < enemies[col].size(); ++index) {
                        auto& enemy = enemies[col][index];
                        if (enemy.type == matrix[row][col].type)
                        {
							matrix[row][col].nrenemy += 1;
						}

                    }
               

                    return;     
                }
            }
        }
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
