#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>
#include <string>
using std::string;
#include <sstream>
#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"
#include "helper/texture.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "helper/scenerunner.h"


using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

GLuint mountain;

GLuint fire;

float camSpeed = 2.5f;
glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);
/*
float camSpeed = 2.5f;
glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Position = glm::vec3(0.0f, 0.0f, 2.0f);*/
//

/*
SceneBasic_Uniform::SceneBasic_Uniform() :
	tPrev(0){

	//plane(50.0f, 50.0f, 1, 1),
	//teapot(14, glm::mat4(1.0f)){
	
	mesh = ObjMesh::load("media/pig_hide.obj", true);
	//
}
*/

SceneBasic_Uniform::SceneBasic_Uniform() : plane(10.0f, 10.f, 100, 100) {
	mesh = ObjMesh::load("media/mountain/testing.obj", true);
	//mesh = ObjMesh::load("media/pig_triangulated.obj", true);
}


void SceneBasic_Uniform::initScene()
{
    compile();
	glEnable(GL_DEPTH_TEST);
	model = mat4(1.0f);
	
    view = glm::lookAt(vec3(1.0f, 1.25f, 3.25f ), vec3(0.0f, 0.2f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(-35.0f), vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(15.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(45.0, 4.0 / 3.0, 1.0, 50.0);
	angle = 0.0f;
	
	

    //prog.setUniform("Light.Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 1.0f));
    prog.setUniform("Light.L", vec3(1.0f));
    prog.setUniform("Light.La", vec3(0.05f));
	prog.setUniform("ModelMatrix", model);
	prog.setUniform("ViewMatrix", view);
	prog.setUniform("ProjectionMatrix", projection);

	prog.setUniform("Fog.MaxDist", 10.0f);
	prog.setUniform("Fog.MinDist", 1.0f);
	prog.setUniform("Fog.Color", vec3(0.5f, 0.5f, 0.5f));


	mountain = Texture::loadTexture("media/texture/snow_02_diff_2k.jpg");
	fire = Texture::loadTexture("media/texture/fire.png");

	
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
	
	float deltaT = t - tPrev;
	if (tPrev == 0.0f)
	{
		deltaT = 0.0f;
	}
	tPrev = t;
	angle += 0.1f * deltaT;
	if (angle > glm::two_pi<float>())angle -= glm::two_pi<float>();
	view = glm::rotate(view, 0.1f * deltaT, glm::vec3(0, 1, 0));
	prog.setUniform("ViewMatrix", view);
	//view = glm::lookAt(Position, Position + Orientation, Up);
	/*
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += camSpeed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += camSpeed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += camSpeed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += camSpeed * glm::normalize(glm::cross(Orientation, Up));
	}
	*/

}

void SceneBasic_Uniform::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec4 lightPos = vec4(10.0f * cos(angle), 10.0f, 10.0f * sin(angle), 1.0f);
	prog.setUniform("Light.Position", vec4(view * lightPos));

	prog.setUniform("Material.Kd", vec3(0.2f, 0.55f, 0.9f));
	prog.setUniform("Material.Ks", vec3(0.95f, 0.95f, 0.95f));
	prog.setUniform("Material.Ka", vec3(0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f));
	prog.setUniform("Material.Shininess", 100.0f);

	model = mat4(1.0f);
	model = glm::rotate(model, glm::radians(-90.f), vec3(1.0f, 0.0f, 0.0f));
	setMatrices();
	//cube.render();

		/*float dist = 0.0f;

	for (int i = 0; i < 5; i++)
	{
		model = mat4(1.0f);
		model = glm::translate(model, vec3(dist * 0.6f - 1.0f, 0.0f, -dist));
		model = glm::rotate(model, glm::radians(-90.f), vec3(1.0f, 0.0f, 0.0f));
		setMatrices();
		teapot.render();
		dist += 7.0f;
	}*/

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fire);
	prog.setUniform("Material.Kd", vec3(0.1f, 0.1f, 0.1f));
	prog.setUniform("Material.Ks", vec3(0.1f, 0.1f, 0.1f));
	prog.setUniform("Material.Ka", vec3(0.9f, 0.9f, 0.9f));
	prog.setUniform("Material.Shininess", 180.0f);
	model = mat4(1.0f);
	model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
	setMatrices();
	plane.render();


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mountain);
	prog.setUniform("Material.Kd", vec3(0.7f, 0.7f, 0.7f));
	prog.setUniform("Material.Ks", vec3(0.0f, 0.0f, 0.0f));
	prog.setUniform("Material.Ka", vec3(0.2f, 0.2f, 0.2f));
	prog.setUniform("Material.Shininess", 180.0f);
	model = mat4(1.0f);
	model = glm::rotate(model, glm::radians(90.f), vec3(0.0f, 1.0f, 0.0f));
	setMatrices();
	mesh -> render();
	
}


void SceneBasic_Uniform::resize(int w, int h)
{
	glViewport(0, 0, w, h);
    width = w;
    height = h;
    
    
	projection = glm::perspective(glm::radians(70.0f), (float) w / h, 0.3f, 100.0f);
}


void SceneBasic_Uniform::setMatrices() 
{
	mat4 mv = view * model;
	prog.setUniform("ModelViewMatrix",mv);
	prog.setUniform("NormalMatrix",glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	prog.setUniform("MVP", projection * mv);

}





void SceneBasic_Uniform::pressW()
{
	Position += camSpeed * Orientation;
}

void SceneBasic_Uniform::pressA()
{
	Position+= camSpeed * -glm::normalize(glm::cross(Orientation, Up));
}

void SceneBasic_Uniform::pressS()
{
	Position += camSpeed * -Orientation;
}

void SceneBasic_Uniform::pressD()
{
	Position += camSpeed* glm::normalize(glm::cross(Orientation, Up));
}
