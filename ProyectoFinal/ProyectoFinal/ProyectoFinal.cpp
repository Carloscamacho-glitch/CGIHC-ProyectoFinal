/*
Práctica 7: Iluminación 1 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;
glm::vec3 peridotPos = glm::vec3(0.0f, 0.0f, 0.0f);

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Camera camera2;
Camera camera3;
Camera* currentCamera;

Texture pisoTexture;

Model Prueba_M;
//Ben10 ---------------------------------
Model SrSmoothy;

//Simpsons ------------------------------
Model KwikEmart;
Model LetreroKwik;

//Steven Universe -----------------------
Model Portal;
Model BurbujaBismuto;
Model BurbujaSquaridot;
Model BurbujaJasper;
Model GatoGalleta;
//leon
Model Leon;
Model LeonPataDelDer;
Model LeonPataDelIzq;
Model LeonPataTrasDer;
Model LeonPataTrasIzq;
//peridos
Model PeridotCuerpo;
Model PeridotCabeza;
Model PeridotBrazoDer;
Model PeridotBrazoIzq;
Model PeridotManoDer;
Model PeridotManoIzq;
Model PeridotPiernaDer;
Model PeridotPiernaIzq;
Model PeridotPieDer;
Model PeridotPieIzq;
//Gravity Falls -------------------------

//Extras --------------------------------
Model Invernadero;
//Lamparas 
Model Candil;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS]; //Incluye luz delantera del coche 
SpotLight spotLights2[MAX_SPOT_LIGHTS]; //Tendra la luz trasera del coche


// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;



//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	//Camara en 3ra persona
	camera = Camera(glm::vec3(-40.0f, 40.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 2.5f, 2.5f);
	//Camara aerea
	camera2 = Camera(glm::vec3(-200.0f, 750.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -90.0f, 2.5f, 2.5f);
	//Camara libre temporal
	camera3 = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 2.5f, 2.5f);

	//Carga de texturas ///////////////////////////////////////////////////////////////////////////////////////////
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();

	//Carga de modelos ///////////////////////////////////////////////////////////////////////////////////////////
	Prueba_M = Model();
	Prueba_M.LoadModel("Models/ModeloPrueba.obj");

	//Ben 10 --------------------------------
	SrSmoothy = Model();
	SrSmoothy.LoadModel("Models/Ben10/mrsmoothie-3d-model/Mr_SmoothieCompleto.obj");

	//Simpsons ------------------------------
	KwikEmart = Model();
	KwikEmart.LoadModel("Models/Simpsons/kwikEmart/KwikEMartUnido.obj");
	LetreroKwik = Model();
	LetreroKwik.LoadModel("Models/Simpsons/kwikEmart/letrero.obj");

	//Steven Universe -----------------------
	Portal = Model();
	Portal.LoadModel("Models/Steven Universe/Portal.obj");
	BurbujaBismuto = Model();
	BurbujaBismuto.LoadModel("Models/Steven Universe/Busbuja Bismuto.obj");
	BurbujaSquaridot = Model();
	BurbujaSquaridot.LoadModel("Models/Steven Universe/Burbuja Squaridot.obj");
	BurbujaJasper = Model();
	BurbujaJasper.LoadModel("Models/Steven Universe/Burbuja Jasper.obj");
	GatoGalleta = Model();
	GatoGalleta.LoadModel("Models/Steven Universe/GatoGalleta.obj");
	//leon
	Leon = Model();
	LeonPataDelDer.LoadModel("Models/Steven Universe/Leon.obj");
	LeonPataDelDer = Model();
	LeonPataDelDer.LoadModel("Models/Steven Universe/Leon Pata DelDer.obj");
	LeonPataDelIzq = Model();
	LeonPataDelIzq.LoadModel("Models/Steven Universe/Leon Pata DelIzq.obj");
	LeonPataTrasDer = Model();
	LeonPataTrasDer.LoadModel("Models/Steven Universe/Leon Pata TraDer.obj");
	LeonPataTrasIzq = Model();
	LeonPataTrasIzq.LoadModel("Models/Steven Universe/Leon Pata TraIzq.obj");
	//peridos
	PeridotCuerpo = Model();
	PeridotCuerpo.LoadModel("Models/Steven Universe/Peridot cuerpo.obj");
	PeridotCabeza = Model();
	PeridotCabeza.LoadModel("Models/Steven Universe/Peridot cabeza.obj");
	PeridotBrazoDer = Model();
	PeridotBrazoDer.LoadModel("Models/Steven Universe/Peridot brazo derecho.obj");
	PeridotBrazoIzq = Model();
	PeridotBrazoIzq.LoadModel("Models/Steven Universe/Peridot brazo izquierdo.obj");
	PeridotManoDer = Model();
	PeridotManoDer.LoadModel("Models/Steven Universe/Peridot mano derecha.obj");
	PeridotManoIzq = Model();
	PeridotManoIzq.LoadModel("Models/Steven Universe/Peridot mano izquierda.obj");
	PeridotPiernaDer = Model();
	PeridotPiernaDer.LoadModel("Models/Steven Universe/Peridot pierna derecha.obj");
	PeridotPiernaIzq = Model();
	PeridotPiernaIzq.LoadModel("Models/Steven Universe/Peridot pierna izquierda.obj");
	PeridotPieDer = Model();
	PeridotPieDer.LoadModel("Models/Steven Universe/Peridot pie derecho.obj");
	PeridotPieIzq = Model();
	PeridotPieIzq.LoadModel("Models/Steven Universe/Peridot pie izquierdo.obj");

	//Gravity Falls -------------------------

	//Extras --------------------------------
	Invernadero = Model();
	Invernadero.LoadModel("Models/Extras/Invernadero.obj");

	//Lamparas
	Candil = Model();
	Candil.LoadModel("Models/Lamparas/candil.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	////Luz puntual
	unsigned int pointLightCount = 0;

	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f,
		3.0f, 1.0f,
		20.0f, 3.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;
	

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		if (mainWindow.getCamara() == 1.0f) {
			currentCamera = &camera;
		}
		else if (mainWindow.getCamara() == 2.0f) {
			currentCamera = &camera2;
		}
		else {
			currentCamera = &camera3;
		}
		currentCamera->keyControl(mainWindow.getCamara(), mainWindow.getsKeys(), deltaTime);
		currentCamera->mouseControl(mainWindow.getCamara(), mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(currentCamera->calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(currentCamera->calculateViewMatrix()));
		glUniform3f(uniformEyePosition, currentCamera->getCameraPosition().x, currentCamera->getCameraPosition().y, currentCamera->getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount); 
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		glm::mat4 model(1.0);
		glm::mat4 ModelAuxPeridot1(1.0);
		glm::mat4 ModelAuxPeridot2(1.0);
		glm::mat4 ModelAuxPeridot3(1.0);
		glm::mat4 ModelAuxPeridot4(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		/*pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();*/

		//Dibujo de modelo de ejemplo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Prueba_M.RenderModel();

		//------------------------------------------------------------------Piso temporal-------------------------------------------------------------------
		//Cuadrante 1-------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1000.0f, 0.0f, -500.0f));
		model = glm::scale(model, glm::vec3(20.0f, 0.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Cuadrante 2 Jared ------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, -750.0f));
		model = glm::scale(model, glm::vec3(25.0f, 0.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Sr Smoothie
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-480.5, -0.5, -742.5));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		SrSmoothy.RenderModel();
		glDisable(GL_BLEND);

		//Cuadrante 3 ------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(350.0f, 0.0f, -750.0f));
		model = glm::scale(model, glm::vec3(25.0f, 1.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Cuadrante 4 -------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1000.0f, 0.0f, -500.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Cuadrante 5 -------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1000.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Cuadrante 6 -------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, 750.0f));
		model = glm::scale(model, glm::vec3(25.0f, 1.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Cuadrante 7 ---------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(350.0f, 0.0f, 750.0f));
		model = glm::scale(model, glm::vec3(25.0f, 1.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//KwikEmart
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(380.0f, -1.0f, 766.6f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		KwikEmart.RenderModel();
		glDisable(GL_BLEND);

		//Letrero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.0f, 0.3f, 660.0f));
		model = glm::scale(model, glm::vec3(15.5f, 17.0f, 15.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LetreroKwik.RenderModel();

		//Cuadrante 8 -----------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1000.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Centro ----------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(60.0f, 1.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Portal
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Portal.RenderModel();

		//Invernadero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, 1.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.015f, 0.0135f, 0.015f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Invernadero.RenderModel();
		glDisable(GL_BLEND);

		peridotPos = glm::vec3(camera.getCameraPosition().x+30.0f, camera.getCameraPosition().y-28.0f, camera.getCameraPosition().z);
		//Peridot ---------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(camera.getCameraPosition().x+30.0f, camera.getCameraPosition().y-28.0f, camera.getCameraPosition().z));
		model = glm::scale(model, glm::vec3(1.6f, 1.6f, 1.6f));
		ModelAuxPeridot1 = model;
		ModelAuxPeridot2 = model;
		ModelAuxPeridot3 = model;
		ModelAuxPeridot4 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotCuerpo.RenderModel();
		//cabeza
		model = glm::translate(model, glm::vec3(0.0f, 3.7f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotCabeza.RenderModel();
		//Brazo derecho
		model = ModelAuxPeridot1;
		model = glm::translate(model, glm::vec3(0.0f, 2.6f, -0.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotBrazoDer.RenderModel();
		//Mano derecha
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -0.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotManoDer.RenderModel();
		//Brazo izquierdo
		model = ModelAuxPeridot2;
		model = glm::translate(model, glm::vec3(0.0f, 2.6f, 0.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotBrazoIzq.RenderModel();
		//Mano izquierda
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotManoIzq.RenderModel();
		//Pierna derecha
		model = ModelAuxPeridot3;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.35f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotPiernaDer.RenderModel();
		//Pie derecho
		model = glm::translate(model, glm::vec3(0.0f, -2.3f, -0.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotPieDer.RenderModel();
		//Pierna izquierda
		model = ModelAuxPeridot4;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.35f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotPiernaIzq.RenderModel();
		//Pie izquierdo
		model = glm::translate(model, glm::vec3(0.0f, -2.3f, 0.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotPieIzq.RenderModel();

		//------------------------------------------------------------------Piso temporal-------------------------------------------------------------------

		//Prueba lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5, 15.5, 0.5));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Candil.RenderModel();
		
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
/*
//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		logofiTexture.UseTexture(); //textura con transparencia o traslucidez
		FIGURA A RENDERIZAR de OpenGL, si es modelo importado no se declara UseTexture
		glDisable(GL_BLEND);
*/