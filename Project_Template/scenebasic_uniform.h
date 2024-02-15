#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "helper/torus.h"





class SceneBasic_Uniform : public Scene
{
private:
    /*glm::mat4 RotationMatrix;
    glm::mat4 Ld;
    glm::mat4 Kd;
    glm::mat4 mv;
    GLuint vaoHandle;
    GLSLProgram prog;
    Torus torus;
    void SetMatrices();
    void compile();*/
    Torus torus;
    GLSLProgram prog;
    void setMatrices();
    void compile();
    

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
