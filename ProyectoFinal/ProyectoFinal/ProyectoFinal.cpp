/*
Proyecto Final
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
Texture estatua;

Model Prueba_M; 
//Ben10 ---------------------------------
Model SrSmoothy;
Model Ben;
Model Azmuth;
Model Omnitrix;
Model Khyber;
Model EcoEco;
//Diamante
Model Diamante;
Model DiamanteBrazoIzq;
Model DiamanteManoIzq;
//Escarabola
Model Escarabola;
Model EscarabolaPataDelDer;
Model EscarabolaPataDelIzq;
Model EscarabolaPataTrasDer;
Model EscarabolaPataTrasIzq;
//Crabdozer
Model Crabdozer;
Model CrabdozerPataDelDer;
Model CrabdozerPataDelIzq;
Model CrabdozerPataMedDer;
Model CrabdozerPataMedIzq;
Model CrabdozerPataTrasDer;
Model CrabdozerPataTrasIzq;
//DX Mark 10
Model CocheBen;
Model CocheBen_RuedaDelDer;
Model CocheBen_RuedaDelIzq;
Model CocheBen_RuedaTrasDer;
Model CocheBen_RuedaTrasIzq;
//Rustbucket
Model Rustbucket;
Model Rustbucket_RuedaDelDer;
Model Rustbucket_RuedaDelIzq;
Model Rustbucket_RuedaTrasDer;
Model Rustbucket_RuedaTrasIzq;
Model Rustbucket_RuedaMedDer;
Model Rustbucket_RuedaMedIzq;
//Xylene Ship
Model XyleneShip;
Model XyleneShip_Arco;

//Simpsons ------------------------------
Model KwikEmart;
Model LetreroKwik;
Model Letras;
Model Duff;
Model JefeGorgory;
Model Apu;
Model DonutVan;
Model DonutVanLlanta01;
Model DonutVanLlanta02;
Model BlimpDuff;


//Steven Universe -----------------------
Model Portal;
Model BurbujaBismuto;
Model BurbujaSquaridot;
Model BurbujaJasper;
Model GatoGalleta;
//Leon
Model Leon;
Model LeonPataDelDer;
Model LeonPataDelIzq;
Model LeonPataTrasDer;
Model LeonPataTrasIzq;
//Peridot
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
Model Pinos;
Model Bote;
Model Banca;
Model Jardinera;
Model Banca2;
Model Arboles3;
Model Buzon;
Model Parquimetro;
Model Poste;
Model Coladera1;
Model Coladera2;
//Lamparas 
Model Candil;
Model Lampara1;
Model Lampara2;


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

void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,

		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,

		// right
		4, 5, 6,
		6, 7, 4,
	};

	GLfloat cubo_vertices[] = {

		//front
		-0.5f, -0.5f,  0.5f,	0.0f,   0.5f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.5f,	0.5f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.5f,	1.0f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.0f,	1.0f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,   0.5f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.5f,	0.5f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.5f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	1.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.5f,   0.5f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.0f,	0.5f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.0f,	1.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.5f,	1.0f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,   0.5f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.5f,	0.5f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.5f,	1.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	1.0f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.5f,   0.0f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	1.0f,	0.0f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	1.0f,	0.5f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.5f,	0.5f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,   0.0f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.5f,	0.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.5f,	0.5f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	0.5f,		0.0f,	-1.0f,	0.0f,

	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 192, 36); 
	meshList.push_back(cubo); 
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
	CrearCubo();

	//Camara en 3ra persona
	camera = Camera(glm::vec3(-40.0f, 40.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 2.5f, 2.5f);
	//Camara aerea
	camera2 = Camera(glm::vec3(-200.0f, 750.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -90.0f, 2.5f, 2.5f);
	//Camara libre temporal
	camera3 = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 2.5f, 2.5f);

	//Carga de texturas ///////////////////////////////////////////////////////////////////////////////////////////
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	estatua = Texture("Textures/daiza1.png");
	estatua.LoadTextureA();

	//Carga de modelos ///////////////////////////////////////////////////////////////////////////////////////////
	Prueba_M = Model();
	Prueba_M.LoadModel("Models/ModeloPrueba.obj");

	//Ben 10 --------------------------------
	SrSmoothy = Model();
	SrSmoothy.LoadModel("Models/Ben10/mrsmoothie-3d-model/Mr_SmoothieCompleto.obj");
	Ben = Model();
	Ben.LoadModel("Models/Ben10/Ben/Ben.obj");
	Omnitrix = Model();
	Omnitrix.LoadModel("Models/Ben10/Omnitrix/Omnitrix.obj");
	Azmuth = Model();
	Azmuth.LoadModel("Models/Ben10/Azmuth/Azmuth.obj");
	Khyber = Model();
	Khyber.LoadModel("Models/Ben10/Khyber/Khyber.obj");
	EcoEco = Model();
	EcoEco.LoadModel("Models/Ben10/Ultimate_EcoEco/U_EcoEco.obj");
	//Escarabola
	Escarabola = Model();
	Escarabola.LoadModel("Models/Ben10/ball-weevil/BallWeevil.obj");
	EscarabolaPataDelDer = Model();
	EscarabolaPataDelDer.LoadModel("Models/Ben10/ball-weevil/BallWeevil_PataDelDer.obj");
	EscarabolaPataDelIzq = Model();
	EscarabolaPataDelIzq.LoadModel("Models/Ben10/ball-weevil/BallWeevil_PataDelIzq.obj");
	EscarabolaPataTrasDer = Model();
	EscarabolaPataTrasDer.LoadModel("Models/Ben10/ball-weevil/BallWeevil_PataTraDer.obj");
	EscarabolaPataTrasIzq = Model();
	EscarabolaPataTrasIzq.LoadModel("Models/Ben10/ball-weevil/BallWeevil_PataTraIzq.obj");
	//Crabdozer
	Crabdozer = Model();
	Crabdozer.LoadModel("Models/Ben10/Crabdozer/Crabdozer.obj");
	CrabdozerPataDelDer = Model();
	CrabdozerPataDelDer.LoadModel("Models/Ben10/Crabdozer/Crabdozer_PataDelDer.obj");
	CrabdozerPataDelIzq = Model();
	CrabdozerPataDelIzq.LoadModel("Models/Ben10/Crabdozer/Crabdozer_PataDelIzq.obj");
	CrabdozerPataMedDer = Model();
	CrabdozerPataMedDer.LoadModel("Models/Ben10/Crabdozer/Crabdozer_PataMediaDer.obj");
	CrabdozerPataMedIzq = Model();
	CrabdozerPataMedIzq.LoadModel("Models/Ben10/Crabdozer/Crabdozer_PataMediaIzq.obj");
	CrabdozerPataTrasDer = Model();
	CrabdozerPataTrasDer.LoadModel("Models/Ben10/Crabdozer/Crabdozer_PataTrasDer.obj");
	CrabdozerPataTrasIzq = Model();
	CrabdozerPataTrasIzq.LoadModel("Models/Ben10/Crabdozer/Crabdozer_PataTrasIzq.obj");
	//Diamante
	Diamante = Model();
	Diamante.LoadModel("Models/Ben10/Diamondhead/Diamante.obj");
	DiamanteBrazoIzq = Model();
	DiamanteBrazoIzq.LoadModel("Models/Ben10/Diamondhead/Diamante_BrazoIzq.obj");
	DiamanteManoIzq = Model();
	DiamanteManoIzq.LoadModel("Models/Ben10/Diamondhead/Diamante_ManoIzq.obj");
	//DX Mark 10
	CocheBen = Model();
	CocheBen.LoadModel("Models/Ben10/DX Mark 10/DX Mark 10.obj");
	CocheBen_RuedaDelDer = Model();
	CocheBen_RuedaDelDer.LoadModel("Models/Ben10/DX Mark 10/DX Mark 10_RuedaDer.obj");
	CocheBen_RuedaDelIzq = Model();
	CocheBen_RuedaDelIzq.LoadModel("Models/Ben10/DX Mark 10/DX Mark 10_RuedaIzq.obj");
	CocheBen_RuedaTrasDer = Model();
	CocheBen_RuedaTrasDer.LoadModel("Models/Ben10/DX Mark 10/DX Mark 10_RuedaDer.obj");
	CocheBen_RuedaTrasIzq = Model();
	CocheBen_RuedaTrasIzq.LoadModel("Models/Ben10/DX Mark 10/DX Mark 10_RuedaIzq.obj");
	//Rustbucket
	Rustbucket = Model();
	Rustbucket.LoadModel("Models/Ben10/rustbucket/Rustbucket.obj");
	Rustbucket_RuedaDelDer = Model();
	Rustbucket_RuedaDelDer.LoadModel("Models/Ben10/rustbucket/Rustbucket_LlantaDer.obj");
	Rustbucket_RuedaTrasDer = Model();
	Rustbucket_RuedaTrasDer.LoadModel("Models/Ben10/rustbucket/Rustbucket_LlantaDer.obj");
	Rustbucket_RuedaDelIzq = Model();
	Rustbucket_RuedaDelIzq.LoadModel("Models/Ben10/rustbucket/Rustbucket_LlantaIzq.obj");
	Rustbucket_RuedaTrasIzq = Model();
	Rustbucket_RuedaTrasIzq.LoadModel("Models/Ben10/rustbucket/Rustbucket_LlantaIzq.obj");
	Rustbucket_RuedaMedDer = Model();
	Rustbucket_RuedaMedDer.LoadModel("Models/Ben10/rustbucket/Rustbucket_LlantaDer.obj");
	Rustbucket_RuedaMedIzq = Model();
	Rustbucket_RuedaMedIzq.LoadModel("Models/Ben10/rustbucket/Rustbucket_LlantaIzq.obj");
	//Xylene Ship
	XyleneShip = Model();
	XyleneShip.LoadModel("Models/Ben10/Xylene_Ship/Xylene's Ship.obj");
	XyleneShip_Arco = Model();
	XyleneShip_Arco.LoadModel("Models/Ben10/Xylene_Ship/Xylene's Ship_Arco.obj");

	//Simpsons ------------------------------
	KwikEmart = Model();
	KwikEmart.LoadModel("Models/Simpsons/kwikEmart/KwikEMartUnido.obj");
	LetreroKwik = Model();
	LetreroKwik.LoadModel("Models/Simpsons/kwikEmart/letrero.obj");
	Letras = Model();
	Letras.LoadModel("Models/Simpsons/Letras/Letras.obj");
	Duff = Model();
	Duff.LoadModel("Models/Simpsons/Estatua/Estatua.obj");
	JefeGorgory = Model();
	JefeGorgory.LoadModel("Models/Simpsons/Personajes/Jefe_Gorgory.obj");
	DonutVan = Model();
	DonutVan.LoadModel("Models/Simpsons/DonutVan/DonutVan.obj");
	DonutVanLlanta01 = Model();
	DonutVanLlanta01.LoadModel("Models/Simpsons/DonutVan/DonutVanLlanta01.obj");
	DonutVanLlanta02 = Model();
	DonutVanLlanta02.LoadModel("Models/Simpsons/DonutVan/DonutVanLlanta02.obj");
	Apu = Model();
	Apu.LoadModel("Models/Simpsons/Personajes/Apu.obj");
	BlimpDuff = Model();
	BlimpDuff.LoadModel("Models/Simpsons/Blimp/BlimpDuff.obj");


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
	//Leon
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
	//Peridot
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
	Banca = Model();
	Banca.LoadModel("Models/Extras/bancajardin.obj");
	Jardinera = Model();
	Jardinera.LoadModel("Models/Extras/Jardinera2.obj");
	Banca2 = Model();
	Banca2.LoadModel("Models/Extras/Banca2.obj");
	Arboles3 = Model();
	Arboles3.LoadModel("Models/Extras/ArbolesConjunto3.obj");
	Bote = Model();
	Bote.LoadModel("Models/Extras/Bote.obj");
	Pinos = Model();
	Pinos.LoadModel("Models/Extras/ArbolesConjunto01.obj");
	Buzon = Model();
	Buzon.LoadModel("Models/Extras/Buzon.obj");
	Coladera1 = Model();
	Coladera1.LoadModel("Models/Extras/Coladera1.obj");
	Coladera2 = Model();
	Coladera2.LoadModel("Models/Extras/Coladera2.obj");
	Poste = Model();
	Poste.LoadModel("Models/Extras/Poste.obj");
	Parquimetro = Model();
	Parquimetro.LoadModel("Models/Extras/Parquimetro.obj");

	//Lamparas
	Candil = Model();
	Candil.LoadModel("Models/Lamparas/candil.obj");
	Lampara1 = Model();
	Lampara1.LoadModel("Models/Lamparas/Lampara01.obj");
	Lampara2 = Model();
	Lampara2.LoadModel("Models/Lamparas/Lampara2.obj");

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
		glm::mat4 modelauxMark10(1.0);
		glm::mat4 modelauxRust(1.0);
		glm::mat4 modelauxDiamante(1.0);
		glm::mat4 modelauxEscarabola(1.0);
		glm::mat4 modelauxCrab(1.0);
		glm::mat4 modelauxShip(1.0);
		glm::mat4 modelauxDuff(1.0); 
		glm::mat4 modelauxDonutVan(1.0);
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

		//Bancas//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-850.0f, 0.0f, -170.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-850.0f, 0.0f, -250.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-930.0f, 0.0f, -140.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1000.0f, 0.0f, -140.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();
		//Terminan bancas

		//Cuadrante 2 Jared ------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, -750.0f));
		model = glm::scale(model, glm::vec3(25.0f, 1.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Sr Smoothie
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-480.5, 0.5, -742.5));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		SrSmoothy.RenderModel();
		glDisable(GL_BLEND);

		//Ben
		model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(200.0f, 0.2f, 545.0f));
		model = glm::translate(model, glm::vec3(-325.0f, 0.0f, -660.0f));
		model = glm::scale(model, glm::vec3(6.5f, 6.5f, 6.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ben.RenderModel();

		/////Transformaciones////----------------
		////EcoEco
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-315.0f, 0.0f, -660.0f));
		//model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//EcoEco.RenderModel();

		////Diamante 
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-290.0f, 0.0f, -660.0f));
		//model = glm::scale(model, glm::vec3(4.1f, 4.1f, 4.1f));
		//modelauxDiamante = model;
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Diamante.RenderModel();
		//model = modelauxDiamante;
		////Brazo Izq
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//modelauxDiamante = model;
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//DiamanteBrazoIzq.RenderModel();
		//model = modelauxDiamante;
		////Mano Izq
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//DiamanteManoIzq.RenderModel();
		/////--------------------

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-591.5f, 7.0f, -608.5f));
		model = glm::scale(model, glm::vec3(10.0f, 10.5f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara1.RenderModel();

		//Botes de Basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-108.0f, 0.0f, -608.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-108.0f, 0.0f, -890.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Cuadrante 3 ------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(350.0f, 0.0f, -750.0f));
		model = glm::scale(model, glm::vec3(25.0f, 1.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(108.5f, 7.0f, -608.5f));
		model = glm::scale(model, glm::vec3(10.0f, 10.5f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara1.RenderModel();

		//Cuadrante 4 -------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1000.0f, 0.0f, -500.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(806.5f, 7.0f, -608.5f));
		model = glm::scale(model, glm::vec3(10.0f, 10.5f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara1.RenderModel();

		//Letras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1070.0f, 0.5f, -720.0f));
		model = glm::scale(model, glm::vec3(17.0f, 17.5f, 17.0f));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Letras.RenderModel();

		//Banca 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1150.0f, 0.0f, -510.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		//Banca 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1150.0f, 0.0f, -410.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		//Banca 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1150.0f, 0.0f, -310.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		//Banca 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(870.0f, 0.0f, -850.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		//Bote de Basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1150.0f, 0.0f, -460.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Bote de Basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(820.0f, 0.0f, -850.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Jefe Gorgory
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1000.0f, -15.5f, -750.0f));
		model = glm::scale(model, glm::vec3(0.52f, 0.52f, 0.52f));
		model = glm::rotate(model, -55 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JefeGorgory.RenderModel();

		//Khyber
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1100.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
		model = glm::rotate(model, 225 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Khyber.RenderModel();

		//Escarabola---------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(950.0f, 0.0f, -350.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, -55 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelauxEscarabola = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Escarabola.RenderModel();

		model = modelauxEscarabola;

		//Pata delantera derecha
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EscarabolaPataDelDer.RenderModel();
		model = modelauxEscarabola;

		//Pata delantera izquierda
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EscarabolaPataDelIzq.RenderModel();
		model = modelauxEscarabola;

		//Pata trasera derecha
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EscarabolaPataTrasDer.RenderModel();
		model = modelauxEscarabola;

		//Pata trasera izquierda
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EscarabolaPataTrasIzq.RenderModel();
		model = modelauxEscarabola;
		/////////////--------------------

		//Crabdozer-------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(950.0f, 0.1f, -500.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		modelauxCrab = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Crabdozer.RenderModel();
		model = modelauxCrab;

		//Pata delantera derecha
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CrabdozerPataDelDer.RenderModel();
		model = modelauxCrab;

		//Pata delantera izquierda
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CrabdozerPataDelIzq.RenderModel();
		model = modelauxCrab;

		//Pata media derecha
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CrabdozerPataMedDer.RenderModel();
		model = modelauxCrab;

		//Pata media izquierda
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CrabdozerPataMedIzq.RenderModel();
		model = modelauxCrab;

		//Pata trasera derecha
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CrabdozerPataTrasDer.RenderModel();
		model = modelauxCrab;

		//Pata trasera izquierda
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CrabdozerPataTrasIzq.RenderModel();
		model = modelauxCrab;
		//////--------------------

		//Cuadrante 5 -------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1000.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-810.5f, 0.0f, 109.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.5f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Candil.RenderModel();

		//Rustbucket//////
		//Carro 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-895.0f, 0.3f, 50.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		modelauxRust = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rustbucket.RenderModel();
		model = modelauxRust;

		//Llanta delantera derecha
		model = glm::translate(model, glm::vec3(1.3f, 0.55f, 2.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rustbucket_RuedaDelDer.RenderModel();
		model = modelauxRust;

		//Llanta delantera izquierda
		model = glm::translate(model, glm::vec3(-1.3f, 0.55f, 2.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rustbucket_RuedaDelIzq.RenderModel();
		model = modelauxRust;

		//Llanta media derecha
		model = glm::translate(model, glm::vec3(1.3f, 0.55f, -0.85f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rustbucket_RuedaDelDer.RenderModel();
		model = modelauxRust;

		//Llanta media izquierda
		model = glm::translate(model, glm::vec3(-1.3f, 0.55f, -0.85f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rustbucket_RuedaDelIzq.RenderModel();
		model = modelauxRust;

		//Llanta trasera derecha
		model = glm::translate(model, glm::vec3(1.3f, 0.55f, -1.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rustbucket_RuedaTrasDer.RenderModel();
		model = modelauxRust;

		//Llanta trasera izquierda
		model = glm::translate(model, glm::vec3(-1.3f, 0.55f, -1.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rustbucket_RuedaTrasIzq.RenderModel();
		model = modelauxRust;
		//////

		//Cuadrante 6 -------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, 750.0f));
		model = glm::scale(model, glm::vec3(25.0f, 1.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-108.5f, 0.0f, 608.5f));
		model = glm::scale(model, glm::vec3(3.5f, 4.0f, 3.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara2.RenderModel();

		//Bote de basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-591.5f, 0.0f, 608.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

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

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(578.5f, 0.0f, 608.5f));
		model = glm::scale(model, glm::vec3(3.5f, 4.0f, 3.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara2.RenderModel();

		
		//Botes de Basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(108.0f, 0.0f, 608.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(108.0f, 0.0f, 890.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Apu 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(360.5f, 0.0f, 650.5f));
		model = glm::scale(model, glm::vec3(1.8f, 1.7f, 1.8f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Apu.RenderModel();

		//Cuadrante 8 -----------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1000.0f, 0.0f, 500.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 40.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(806.5f, 0.0f, 118.5f));
		model = glm::scale(model, glm::vec3(3.5f, 4.0f, 3.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara2.RenderModel();


		//Blimp Duff
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1000.5f, 0.0f, 250.5f));
		model = glm::scale(model, glm::vec3(3.5f, 3.0f, 3.5f));
		model = glm::rotate(model, -75 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BlimpDuff.RenderModel();

		//Xylene Ship-----------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(935.0f, 15.0f, 660.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		modelauxShip = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		XyleneShip.RenderModel();
		model = modelauxShip;

		//Arco
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		XyleneShip_Arco.RenderModel();
		model = modelauxShip;
		////---------------

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

		//Ominitrix
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(520.0f, 0.0f, -50.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.0f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Omnitrix.RenderModel();

		//Invernadero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, 1.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.015f, 0.0135f, 0.015f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Invernadero.RenderModel();
		glDisable(GL_BLEND);

		//Jardinera 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(300.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jardinera.RenderModel();

		//Jardinera 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(300.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jardinera.RenderModel();

		//Jardinera 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jardinera.RenderModel();

		//Jardinera 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jardinera.RenderModel();

		//Arboles subcuadrante 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-190.0f, 0.0f, -260.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-440.0f, 0.0f, -230.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();
		///Terminan arboles subcuadrante 2///

		//Arboles subcuadrante 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(460.0f, 0.0f, 70.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(420.0f, 0.0f, 270.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(140.0f, 0.0f, 240.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();
		///Terminan arboles subcuadrante 4///

		//Pedestal estatua 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.5f, 13.0f, 110.0f));
		model = glm::scale(model, glm::vec3(27.0f, 26.0f, 27.0f));
		modelauxDuff = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		estatua.UseTexture();
		meshList[3]->RenderMesh();
		//Estatua Duff
		model = glm::translate(model, glm::vec3(0.0f, 0.51f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Duff.RenderModel();

		//Pinos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-508.0f, 0.0f, 190.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, 220 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-422.0f, 0.0f, 310.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, 0.0f, 290.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(435.0f, 0.0f, -310.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, 225 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(508.0f, 0.0f, -190.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(140.0f, 0.0f, -290.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, 40 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		//Banca 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, 0.0f, -300.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		//Banca 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(300.0f, 0.0f, -300.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		//Banca 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, 0.0f, 300.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		//Banca 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(300.0f, 0.0f, 300.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		//Botes de basura //
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.5f, 0.0f, 240.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-240.5f, 0.0f, 240.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-240.5f, 0.0f, -240.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.5f, 0.0f, -240.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 240.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -240.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Terminan botes de basura//

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

		//Carretera -----------------------------------

		//DonutVan
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 0.0f, -550.0f));
		model = glm::scale(model, glm::vec3(19.0f, 18.0f, 19.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelauxDonutVan = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DonutVan.RenderModel();

		//Llanta
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DonutVanLlanta01.RenderModel();
		model = modelauxDonutVan;

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.45f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DonutVanLlanta01.RenderModel();
		model = modelauxDonutVan;

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DonutVanLlanta02.RenderModel();
		model = modelauxDonutVan;
	
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.45f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DonutVanLlanta02.RenderModel();
	

		//DX Mark 10///////
		//Carro 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, 0.2f, 555.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.5f, 10.5f, 10.5f));
		modelauxMark10 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen.RenderModel();
		model = modelauxMark10;

		//Llanta delantera derecha
		model = glm::translate(model, glm::vec3(1.4f, 0.7f, 2.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen_RuedaDelDer.RenderModel();
		model = modelauxMark10;

		//Llanta delantera izquierda
		model = glm::translate(model, glm::vec3(-1.9f, 0.7f, 2.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen_RuedaDelIzq.RenderModel();
		model = modelauxMark10;

		//Llanta trasera derecha
		model = glm::translate(model, glm::vec3(1.4f, 0.7f, -1.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen_RuedaTrasDer.RenderModel();
		model = modelauxMark10;

		//Llanta trasera izquierda
		model = glm::translate(model, glm::vec3(-1.9f, 0.7f, -1.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen_RuedaTrasIzq.RenderModel();
		model = modelauxMark10;
		////////
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