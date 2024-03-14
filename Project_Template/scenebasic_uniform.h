#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "helper/torus.h"
#include "helper/teapot.h"
#include "helper/plane.h"
#include "helper/objmesh.h"
#include "helper/cube.h"



class SceneBasic_Uniform : public Scene
{
private:
    Plane plane;
    //Teapot teapot;
    std::unique_ptr<ObjMesh> mesh;
    Cube cube;
    float tPrev;
    float angle;
    GLSLProgram prog;
    void setMatrices();
    void compile();
    

public:
    SceneBasic_Uniform();
    
    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
    void pressW();
    void pressA();
    void pressS();
    void pressD();
    void pressUp();
    void pressDown();
    void mouseClick();
    void mouseRelease();
};

#endif // SCENEBASIC_UNIFORM_H
