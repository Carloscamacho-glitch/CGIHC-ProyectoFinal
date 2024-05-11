/*
Proyecto Final
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <windows.h>
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
#include "Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include <time.h> //tiempo
const float toRadians = 3.14159265f / 180.0f;
bool* keys;
glm::vec3 peridotPos = glm::vec3(-200.0f, 12.0f, 0.0f);

//variable para guardar y manejar el tiempo
time_t contador, contador2;
double resta, tiempoguardado, resta2, tiempoguardado2;
float dia = 0.0f, intensidad = 0.2f, direccionx = -1.0f, direcciony = 0.0f;
int aux = 0;
float posnaveX = 1335.0f, posnaveY = 27.0f, posnaveZ = 450.5f;
float posCarroX = -1295.0f, posCarroY = 0.3f, posCarroZ = 60.0f;

//Variables para animaciones
//DX10------------
float movDX10 = 0.0f;
float movDX10z = 0.0f;
float movDX10Offset = 0.0f;
float rotllanta = 0.0f;
float rotllantaOffset = 0.0f;
float giroDX10 = 0.0;
float giroDX10Offset = 0.0f;
bool avanzaDX10 = true;
bool controlDX10 = true;
//-------
//Ben-----
float rotmano = 0.0f;
float rotmanoOffset = 0.0f;
float maxRotation = 0.0f;
float minRotation = 0.0f;
float escesferax = 0.0f;
float escesferay = 0.0f;
float escesferaz = 0.0f;
float escesferax2 = 0.0f;
float escesferay2 = 0.0f;
float escesferaz2 = 0.0f;
float escesferaOffset = 0.0f;
float maxEscale = 0.0f;
bool Dibujaresfera = false;
float Transformar = 0.0f;
bool Dibujaresfera2 = false;
float rotmanoD = 0.0f;
float rotbrazoD = 0.0f;
float rotbrazoDOffset = 0.0f;
float rotmanoDOffset = 0.0f;
float movAtaque = 0.0f;
float movAtaqueOffset = 0.0f;
float maxTraslation = 0.0f;
bool AtaqueDiamante = false;
bool Revertir = false;
bool Limite = true;
//Jetsky------------
float movJetskyXoffset = 0.0f;
float movJetskyYoffset = 0.0f;
float movJetskyZoffset = 0.0f;
float movJetskyX = 0.0f;
float movJetskyY = 0.0f;
float movJetskyZ = 0.0f;
float giroJetsky = 0.0f;
float giroJetskyOffset = 0.0f;
bool JetskyAni = true;
bool controlJetsky = true;
//Peridot-----------
float rotPeridotPiernas = 0.0f;
float rotPeridotPiernasOffset = 0.0f;
float rotPeridotBrazos = 0.0f;
float rotPeridotBrazosOffset = 0.0f;
bool movPeridot = true;
//Dona-----------
float rotDona = 0.0f;
float rotSoporte = 0.0f;
float movSoporte = 0.0f;
float rotDonaOffset = 0.0f;
float rotSoporteOffset = 0.0f;
float movSoporteOffset = 0.0f;
bool DonaAni = true;
//BlimpDuff---------
float rotHelice = 0.0f;
float rotHeliceOffset = 0.0f;
float subeBlimp = 0.0f;
float subeBlimpOffset = 0.0f;
float giroBlimp = 0.0f;
float giroBlimpOffset = 0.0f;
float movBlimpX = 0.0f;
float movBlimpXOffset = 0.0f;
bool sube = true;
bool avanza = false;
bool giro1 = false;
bool regresa = false;
bool giro2 =  false;
bool baja = false;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Camera camera2;
Camera camera3;
Camera* currentCamera;

Texture estatua;
Texture MesaLGR;
Texture pinoTex;

Model Prueba_M; 
//Ben10 ---------------------------------
Model SrSmoothy;
Model SrSmoothyVid;
Model Azmuth;
Model Omnitrix;
Model Khyber;
Model EcoEco;
//Ben
Model Ben;
Model BenAntebrazo;
//Diamante
Model Diamante;
Model DiamanteBrazoIzq;
Model DiamanteManoIzq;
Model ADiamante;
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
Model Helice1;

//Steven Universe -----------------------
Model LGR;
Model LGRVid;
Model Dona;
Model Soporte;
Model Portal;
Model Burbuja;
Model BurbujaBismuto;
Model BurbujaSquaridot;
Model BurbujaJasper;
Model GatoGalleta;
Model Flor1;
Model Flor2;
Model Flor3;
Model Flor4;
Model Flor5;
Model Donas;
Model Refri;
Model Refri2;
Model Refri3;
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
Model hongos1;
Model hongos2;
Model hongos3;
Model gompersPDD;
Model gompersPDI;
Model gompersPTD;
Model gompersPTI;
Model gompers;
Model estatuaBill;
Model trickster;
Model mysteryShack;
Model pato;
Model patoPDD;
Model patoPDI;
Model patoPTD;
Model patoPTI;
Model dipper;
Model dipperCabeza;
Model dipperBD;
Model dipperBI;
Model dipperPD;
Model dipperPI;
Model gorra;
Model libros;

//Extras --------------------------------
Model Piso;
Model Carriles;
Model Agua;
Model Invernadero;
Model VidrioInvernadero;
Model Pinos;
Model Bote;
Model Banca;
Model Jardinera;
Model Banca2;
Model Arboles3;
Model Poste;
Model FilaPostes;
Model FilaPostes2;
Model Coladera1;
Model Coladera2;
Model Arbusto;
Model Esfera;
Model Esfera2;
Model Semaforo;
Model Semaforo2;
Model Barrera;
Model Espectacular1;
Model Espectacular2;
Model EspectacularCocinado1;
Model EspectacularCocinado2;

Model Jetsky;
Model Lancha;

Model Reflector;

Model ArbolSolo1;
Model ArbolSolo2;
Model ArbolSolo3;
Model ArbolSolo4;
//Lamparas 
Model Candil; 
Model Lampara1;
Model Lampara2;
Model LamparaLago;


// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights2[MAX_SPOT_LIGHTS];


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
	obj2->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj2);

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

void CrearMesa()
{
	unsigned int mesaBajo_indices[] = {
		//FrenteB
		0, 1, 2,
		2, 3, 0,
		//DerechaB
		4, 5, 6,
		6, 7, 4,
		//IzquierdaB
		8, 9, 10,
		10, 11, 8,
		//AtrasB
		12, 13, 14,
		14, 15, 12,
		//AbajoB
		16, 17, 18,
		18, 19, 16,
		//ArribaB
		44,45,46,
		46,47,44,

		//FrenteA
		20, 21, 22,
		22, 23, 20,
		//DerechaA
		24, 25, 26,
		26, 27, 24,
		//IzquierdaA
		28, 29, 30,
		30, 31, 28,
		//AtrasA
		32, 33, 34,
		34, 35, 32,
		//AbajoA
		36, 37, 38,
		38, 39, 36,
		//ArribaA
		40, 41, 42,
		42, 43, 40,
	};

	GLfloat mesaBajo_vertices[] = {

		//FrenteB
		//x		y		z		S(H)	T(V)
		-1.0f, 0.0f, 1.0f,		0.0f,   0.0f,		1.0f,	0.0f,	0.0f,	//0
		-1.0f, 0.0f, -1.0f,		1.0f,	0.0f,		1.0f,	0.0f,	0.0f,	//1
		-1.0f, 2.0f, -1.0f,		1.0f,	0.8f,		1.0f,	0.0f,	0.0f,	//2
		-1.0f, 2.0f, 1.0f,		0.0f,	0.8f,		1.0f,	0.0f,	0.0f,	//3
		//DerechaB
		//x		y		z		S		T
		-1.0f, 0.0f, -1.0f,	    0.0f,   0.0f,		0.0f,	0.0f,	1.0f,
		1.0f, 0.0f, -1.0f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		1.0f, 2.0f, -1.0f,		1.0f,	0.8f,		0.0f,	0.0f,	1.0f,
		-1.0f, 2.0f, -1.0f,	    0.0f,	0.8f,		0.0f,	0.0f,	1.0f,
		//IzquierdaB
		//x		y		z		S		T
		1.0f, 0.0f, 1.0f,		0.0f,   0.0f,		0.0f,	0.0f,	-1.0f,
		-1.0f, 0.0f, 1.0f,		1.0f,	0.0f,		0.0f,	0.0f,	-1.0f,
		-1.0f, 2.0f, 1.0f,		1.0f,	0.8f,		0.0f,	0.0f,	-1.0f,
		1.0f, 2.0f, 1.0f,		0.0f,	0.8f,		0.0f,	0.0f,	-1.0f,
		//AtrasB
		//x		y		z		S		T
		1.0f, 0.0f, -1.0f,		0.0f,   0.0f,		-1.0f,	0.0f,	0.0f,
		1.0f, 0.0f, 1.0f,		1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		1.0f, 2.0f, 1.0f,		1.0f,	0.8f,		-1.0f,	0.0f,	0.0f,
		1.0f, 2.0f, -1.0f,		0.0f,	0.8f,		-1.0f,	0.0f,	0.0f,
		//AbajoB
		//x		y		z		S		T
		-1.0f, 0.0f, 1.0f,		0.0f,   0.2f,		0.0f,	1.0f,	0.0f,
		-1.0f, -0.0f, -1.0f,	1.0f,	0.2f,		0.0f,	1.0f,	0.0f,
		1.0f, 0.0f, -1.0f,		1.0f,	0.8f,		0.0f,	1.0f,	0.0f,
		1.0f, 0.0f, 1.0f,		0.0f,	0.8f,		0.0f,	1.0f,	0.0f,
		//ArribaB
		//x		y		z		S		T
		-1.0f, 2.0f , 1.0f,		0.0f,   0.2f,		0.0f,	-1.0f,	0.0f,
		-1.0f, 2.0f , -1.0f,	1.0f,	0.2f,		0.0f,	-1.0f,	0.0f,
		1.0f, 2.0f, -1.0f,		1.0f,	0.8f,		0.0f,	-1.0f,	0.0f,
		1.0f, 2.0f, 1.0f,		0.0f,	0.8f,		0.0f,	-1.0f,	0.0f,

		//FrenteA
		//x		y		z		S		T
		-1.5f, 2.0f, 1.0f,		0.92f,  0.92f,		1.0f,	0.0f,	0.0f,
		-1.5f, 2.0f, -1.5f,		0.92f,	0.92f,		1.0f,	0.0f,	0.0f,
		-1.5f, 2.5f, -1.5f,		0.92f,	1.0f,		1.0f,	0.0f,	0.0f,
		-1.5f, 2.5f, 1.0f,		0.92f,	1.0f,		1.0f,	0.0f,	0.0f,
		//DerechaA
		//x		y		z		S		T
		-1.5f, 2.0f, -1.5f,	    0.92f,  0.92f,		0.0f,	0.0f,	1.0f,
		1.5f, 2.0f, -1.5f,		0.92f,	0.92f,		0.0f,	0.0f,	1.0f,
		1.5f, 2.5f, -1.5f,		0.92f,	1.0f,		0.0f,	0.0f,	1.0f,
		-1.5f, 2.5f, -1.5f,	    0.92f,	1.0f,		0.0f,	0.0f,	1.0f,
		//IzquierdaA
		//x		y		z		S		T
		1.5f, 2.0f, 1.0f,		0.92f,   0.92f,		0.0f,	0.0f,	-1.0f,
		-1.5f, 2.0f, 1.0f,		0.92f,	0.92f,		0.0f,	0.0f,	-1.0f,
		-1.5f, 2.5f, 1.0f,		0.92f,	1.0f,		0.0f,	0.0f,	-1.0f,
		1.5f, 2.5f, 1.0f,		0.92f,	1.0f,		0.0f,	0.0f,	-1.0f,
		//AtrasA
		//x		y		z		S		T
		1.5f, 2.0f, -1.5f,		0.92f,   0.92f,		-1.0f,	0.0f,	0.0f,
		1.5f, 2.0f, 1.0f,		0.92f,	0.92f,		-1.0f,	0.0f,	0.0f,
		1.5f, 2.5f, 1.0f,		0.92f,	1.0f,		-1.0f,	0.0f,	0.0f,
		1.5f, 2.5f, -1.5f,		0.92f,	1.0f,		-1.0f,	0.0f,	0.0f,
		//AbajoA
		//x		y		z		S		T
		-1.5f, 2.0f, 1.0f,		0.92f,   0.92f,		0.0f,	1.0f,	0.0f,
		-1.5f, 2.0f, -1.5f,		1.0f,	0.92f,		0.0f,	1.0f,	0.0f,
		1.5f, 2.0f, -1.5f,		1.0f,	0.92f,		0.0f,	1.0f,	0.0f,
		1.5f, 2.0f, 1.0f,		0.92f,	0.92f,		0.0f,	1.0f,	0.0f,
		//ArribaA
		//x		y		z		S		T
		-1.5f, 2.5f, 1.0f,		0.92f,   0.92f,		0.0f,	-1.0f,	0.0f,
		-1.5f, 2.5f, -1.5f,		1.0f,	0.92f,		0.0f,	-1.0f,	0.0f,
		1.5f, 2.5f, -1.5f,		1.0f,	0.92f,		0.0f,	-1.0f,	0.0f,
		1.5f, 2.5f, 1.0f,		0.92f,	0.92f,		0.0f,	-1.0f,	0.0f,
	};

	Mesh* mesaBajo = new Mesh();
	mesaBajo->CreateMesh(mesaBajo_vertices, mesaBajo_indices, 768, 72);
	meshList.push_back(mesaBajo);
}


void crearPino()
{
	unsigned int pino_indices[] = {
		//FrenteB
		0, 1, 2,
		2, 3, 0,
		//DerechaB
		4, 5, 6,
		6, 7, 4,
		//IzquierdaB
		8, 9, 10,
		10, 11, 8,
		//AtrasB
		12, 13, 14,
		14, 15, 12,
		//AbajoB
		16, 17, 18,
		18, 19, 16,
		//ArribaB
		44,45,46,
		46,47,44,

		//FrenteA
		20, 21, 22,
		22, 23, 20,
		//DerechaA
		24, 25, 26,
		26, 27, 24,
		//IzquierdaA
		28, 29, 30,
		30, 31, 28,
		//AtrasA
		32, 33, 34,
		34, 35, 32,
		//AbajoA
		36, 37, 38,
		38, 39, 36,
		//ArribaA
		40, 41, 42,
		42, 43, 40,


		//		//ArribaB
				//44,45,46,
				//46,47,44,

				//Segundo Piso
				//FrenteA
				48, 49, 50,
				50, 51, 48,
				//DerechaA
				52, 53, 54,
				54, 55, 52,
				//IzquierdaA
				56, 57, 58,
				58, 59, 56,
				//AtrasA
				60, 61, 62,
				62, 63, 60,
				//AbajoA
				64, 65, 66,
				66, 67, 64,
				//ArribaA
				68, 69, 70,
				70, 71, 68,




	};

	GLfloat pino_vertices[] = {

		//FrenteTronco
		//x		y		z		S(H)	T(V)
		-1.0f, 0.0f, 1.0f,		0.0f,   0.0f,		1.0f,	0.0f,	0.0f,	//0
		-1.0f, 0.0f, -1.0f,		1.0f,	0.0f,		1.0f,	0.0f,	0.0f,	//1
		-1.0f, 5.0f, -1.0f,		1.0f,	0.8f,		1.0f,	0.0f,	0.0f,	//2
		-1.0f, 5.0f, 1.0f,		0.0f,	0.8f,		1.0f,	0.0f,	0.0f,	//3
		////DerechaTronco
		//x		y		z		S		T
		-1.0f, 0.0f, -1.0f,	    0.0f,   0.0f,		0.0f,	0.0f,	1.0f,
		1.0f, 0.0f, -1.0f,		1.0f,	0.0f,		0.0f,	0.0f,	1.0f,
		1.0f, 5.0f, -1.0f,		1.0f,	0.8f,		0.0f,	0.0f,	1.0f,
		-1.0f, 5.0f, -1.0f,	    0.0f,	0.8f,		0.0f,	0.0f,	1.0f,
		//IzquierdaTronco
		//x		y		z		S		T
		1.0f, 0.0f, 1.0f,		0.0f,   0.0f,		0.0f,	0.0f,	-1.0f,
		-1.0f, 0.0f, 1.0f,		1.0f,	0.0f,		0.0f,	0.0f,	-1.0f,
		-1.0f, 5.0f, 1.0f,		1.0f,	0.8f,		0.0f,	0.0f,	-1.0f,
		1.0f, 5.0f, 1.0f,		0.0f,	0.8f,		0.0f,	0.0f,	-1.0f,
		//AtrasTronco
		//x		y		z		S		T
		1.0f, 0.0f, -1.0f,		0.0f,   0.0f,		-1.0f,	0.0f,	0.0f,
		1.0f, 0.0f, 1.0f,		1.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		1.0f, 5.0f, 1.0f,		1.0f,	0.8f,		-1.0f,	0.0f,	0.0f,
		1.0f, 5.0f, -1.0f,		0.0f,	0.8f,		-1.0f,	0.0f,	0.0f,
		//AbajoTronco
		//x		y		z		S		T
		-1.0f, 0.0f, 1.0f,		0.0f,   0.2f,		0.0f,	1.0f,	0.0f,
		-1.0f, -0.0f, -1.0f,	1.0f,	0.2f,		0.0f,	1.0f,	0.0f,
		1.0f, 0.0f, -1.0f,		1.0f,	0.8f,		0.0f,	1.0f,	0.0f,
		1.0f, 0.0f, 1.0f,		0.0f,	0.8f,		0.0f,	1.0f,	0.0f,
		//ArribaTronco
		//x		y		z		S		T
		-1.0f, 5.0f , 1.0f,		0.0f,   0.2f,		0.0f,	-1.0f,	0.0f,
		-1.0f, 5.0f , -1.0f,	1.0f,	0.2f,		0.0f,	-1.0f,	0.0f,
		1.0f, 5.0f, -1.0f,		1.0f,	0.8f,		0.0f,	-1.0f,	0.0f,
		1.0f, 5.0f, 1.0f,		0.0f,	0.8f,		0.0f,	-1.0f,	0.0f,

		//FrenteA
		//x		y		z		S		T
		-3.5f, 5.0f, 3.0f,		0.92f,  0.92f,		1.0f,	0.0f,	0.0f,
		-3.5f, 5.0f, -3.5f,		0.92f,	0.92f,		1.0f,	0.0f,	0.0f,
		0.0f, 10.0f, 0.0f,		0.92f,	1.0f,		1.0f,	0.0f,	0.0f,
		0.0f, 10.0f, 0.0f,		0.92f,	1.0f,		1.0f,	0.0f,	0.0f,
		//DerechaA
		//x		y		z		S		T
		-3.5f, 5.0f, -3.5f,	    0.92f,  0.92f,		0.0f,	0.0f,	1.0f,
		3.5f, 5.0f, -3.5f,		0.92f,	0.92f,		0.0f,	0.0f,	1.0f,
		0.0f, 10.0f, 0.0f,		0.92f,	1.0f,		0.0f,	0.0f,	1.0f,
		0.0f, 10.0f, 0.0f,	    0.92f,	1.0f,		0.0f,	0.0f,	1.0f,
		//IzquierdaA
		//x		y		z		S		T
		3.5f, 5.0f, 3.0f,		0.92f,   0.92f,		0.0f,	0.0f,	-1.0f,
		-3.5f, 5.0f, 3.0f,		0.92f,	0.92f,		0.0f,	0.0f,	-1.0f,
		0.0f, 10.0f, 0.0f,		0.92f,	1.0f,		0.0f,	0.0f,	-1.0f,
		0.0f, 10.0f, 0.0f,		0.92f,	1.0f,		0.0f,	0.0f,	-1.0f,
		//AtrasA
		//x		y		z		S		T
		3.5f, 5.0f, -3.5f,		0.92f,   0.92f,		-1.0f,	0.0f,	0.0f,
		3.5f, 5.0f, 3.0f,		0.92f,	0.92f,		-1.0f,	0.0f,	0.0f,
		0.0f, 10.0f, 0.0f,		0.92f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.0f, 10.0f, 0.0f,		0.92f,	1.0f,		-1.0f,	0.0f,	0.0f,
		//AbajoA
		//x		y		z		S		T
		-3.5f, 5.0f, 3.0f,		0.92f,   0.92f,		0.0f,	1.0f,	0.0f,
		-3.5f, 5.0f, -3.5f,		1.0f,	0.92f,		0.0f,	1.0f,	0.0f,
		3.5f, 5.0f, -3.5f,		1.0f,	0.92f,		0.0f,	1.0f,	0.0f,
		3.5f, 5.0f, 3.0f,		0.92f,	0.92f,		0.0f,	1.0f,	0.0f,

		//Segundo piso hojas
		//FrenteA
		//x		y		z		S		T
		-3.5f, 8.0f, 3.0f,		0.92f,  0.92f,		1.0f,	0.0f,	0.0f,
		-3.5f, 8.0f, -3.5f,		0.92f,	0.92f,		1.0f,	0.0f,	0.0f,
		0.0f, 16.0f, 0.0f,		0.92f,	1.0f,		1.0f,	0.0f,	0.0f,
		0.0f, 16.0f, 0.0f,		0.92f,	1.0f,		1.0f,	0.0f,	0.0f,
		//DerechaA
		//x		y		z		S		T
		-3.5f, 8.0f, -3.5f,	    0.92f,  0.92f,		0.0f,	0.0f,	1.0f,
		3.5f, 8.0f, -3.5f,		0.92f,	0.92f,		0.0f,	0.0f,	1.0f,
		0.0f, 16.0f, 0.0f,		0.92f,	1.0f,		0.0f,	0.0f,	1.0f,
		0.0f, 16.0f, 0.0f,	    0.92f,	1.0f,		0.0f,	0.0f,	1.0f,
		//IzquierdaA
		//x		y		z		S		T
		3.5f, 8.0f, 3.0f,		0.92f,   0.92f,		0.0f,	0.0f,	-1.0f,
		-3.5f, 8.0f, 3.0f,		0.92f,	0.92f,		0.0f,	0.0f,	-1.0f,
		0.0f, 16.0f, 0.0f,		0.92f,	1.0f,		0.0f,	0.0f,	-1.0f,
		0.0f, 16.0f, 0.0f,		0.92f,	1.0f,		0.0f,	0.0f,	-1.0f,
		//AtrasA
		//x		y		z		S		T
		3.5f, 8.0f, -3.5f,		0.92f,   0.92f,		-1.0f,	0.0f,	0.0f,
		3.5f, 8.0f, 3.0f,		0.92f,	0.92f,		-1.0f,	0.0f,	0.0f,
		0.0f, 16.0f, 0.0f,		0.92f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.0f, 16.0f, 0.0f,		0.92f,	1.0f,		-1.0f,	0.0f,	0.0f,
		//AbajoA
		//x		y		z		S		T
		-3.5f, 8.0f, 3.0f,		0.92f,   0.92f,		0.0f,	1.0f,	0.0f,
		-3.5f, 8.0f, -3.5f,		1.0f,	0.92f,		0.0f,	1.0f,	0.0f,
		3.5f, 8.0f, -3.5f,		1.0f,	0.92f,		0.0f,	1.0f,	0.0f,
		3.5f, 8.0f, 3.0f,		0.92f,	0.92f,		0.0f,	1.0f,	0.0f,

	};

	Mesh* pino = new Mesh();
	pino->CreateMesh(pino_vertices, pino_indices, 1268, 122);
	meshList.push_back(pino);
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
	keys = mainWindow.getsKeys();

	CreateObjects();
	CreateShaders();
	CrearCubo();
	CrearMesa();
	crearPino();
	

	//Camara en 3ra persona
	camera = Camera(glm::vec3(-300.0f, 30.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.5f, 2.5f, peridotPos);
	//Camara aerea
	camera2 = Camera(glm::vec3(-300.0f, 500.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, -90.0f, 5.5f, 2.5f, peridotPos);
	//Camara libre temporal
	camera3 = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.5f, 2.5f, peridotPos);

	//Carga de texturas ///////////////////////////////////////////////////////////////////////////////////////////
	estatua = Texture("Textures/daiza1.png");
	estatua.LoadTextureA();
	MesaLGR = Texture("Textures/MesaLGR.tga");
	MesaLGR.LoadTextureA();

	//Carga de modelos ///////////////////////////////////////////////////////////////////////////////////////////
	Prueba_M = Model();
	Prueba_M.LoadModel("Models/ModeloPrueba.obj");
	pinoTex = Texture("Textures/pino.tga");
	pinoTex.LoadTextureA();
	//Ben 10 --------------------------------
	SrSmoothy = Model();
	SrSmoothy.LoadModel("Models/Ben10/mrsmoothie-3d-model/Mr_SmoothieCompleto.obj");
	SrSmoothyVid = Model();
	SrSmoothyVid.LoadModel("Models/Ben10/mrsmoothie-3d-model/Mr_SmoothieVidrios.obj");
	Omnitrix = Model();
	Omnitrix.LoadModel("Models/Ben10/Omnitrix/Omnitrix.obj");
	Azmuth = Model();
	Azmuth.LoadModel("Models/Ben10/Azmuth/Azmuth.obj");
	Khyber = Model();
	Khyber.LoadModel("Models/Ben10/Khyber/Khyber.obj");
	EcoEco = Model();
	EcoEco.LoadModel("Models/Ben10/Ultimate_EcoEco/U_EcoEco.obj");
	//Ben
	Ben = Model();
	Ben.LoadModel("Models/Ben10/Ben/Ben.obj");
	BenAntebrazo = Model();
	BenAntebrazo.LoadModel("Models/Ben10/Ben/Ben_Antebrazo.obj");
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
	ADiamante = Model();
	ADiamante.LoadModel("Models/Ben10/Diamondhead/Diamante_Ataque.obj");
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
	Letras.LoadModel("Models/Simpsons/Letras/LetrasMontana2.obj");
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
	Helice1 = Model();
	Helice1.LoadModel("Models/Simpsons/Blimp/Helice1.obj");


	//Steven Universe -----------------------
	LGR = Model();
	LGR.LoadModel("Models/Steven Universe/La Gran Rosquilla.obj");
	LGRVid = Model();
	LGRVid.LoadModel("Models/Steven Universe/La Gran Rosquilla V.obj");
	Dona = Model();
	Dona.LoadModel("Models/Steven Universe/Dona.obj");
	Soporte = Model();
	Soporte.LoadModel("Models/Steven Universe/Soporte.obj");
	Portal = Model();
	Portal.LoadModel("Models/Steven Universe/Portal.obj");
	Burbuja = Model();
	Burbuja.LoadModel("Models/Steven Universe/Burbuja.obj");
	BurbujaBismuto = Model();
	BurbujaBismuto.LoadModel("Models/Steven Universe/Burbuja Bismuto.obj");
	BurbujaSquaridot = Model();
	BurbujaSquaridot.LoadModel("Models/Steven Universe/Burbuja Squaridot.obj");
	BurbujaJasper = Model();
	BurbujaJasper.LoadModel("Models/Steven Universe/Burbuja Jasper.obj");
	GatoGalleta = Model();
	GatoGalleta.LoadModel("Models/Steven Universe/GatoGalleta.obj");
	Flor1 = Model();
	Flor1.LoadModel("Models/Steven Universe/Flor1.obj");
	Flor2 = Model();
	Flor2.LoadModel("Models/Steven Universe/Flor2.obj");
	Flor3 = Model();
	Flor3.LoadModel("Models/Steven Universe/Flor3.obj");
	Flor4 = Model();
	Flor4.LoadModel("Models/Steven Universe/Flor4.obj");
	Flor5 = Model();
	Flor5.LoadModel("Models/Steven Universe/Flor5.obj");
	Donas = Model();
	Donas.LoadModel("Models/Steven Universe/Donas.obj");
	Refri = Model();
	Refri.LoadModel("Models/Steven Universe/Refri.obj");
	Refri2 = Model();
	Refri2.LoadModel("Models/Steven Universe/Refri2.obj");
	Refri3 = Model();
	Refri3.LoadModel("Models/Steven Universe/Refri3.obj");
	//Leon
	Leon = Model();
	Leon.LoadModel("Models/Steven Universe/Leon.obj");
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
	hongos1 = Model();
	hongos1.LoadModel("Models/Gravity Falls/Hongos/Hongos1.obj");
	hongos2 = Model();
	hongos2.LoadModel("Models/Gravity Falls/Hongos/Hongos2.obj");
	hongos3 = Model();
	hongos3.LoadModel("Models/Gravity Falls/Hongos/Hongos3.obj");
	gompersPDD = Model();
	gompersPDD.LoadModel("Models/Gravity Falls/Gompers/Gompers PDD.obj");
	gompersPDI = Model();
	gompersPDI.LoadModel("Models/Gravity Falls/Gompers/Gompers PDI.obj");
	gompersPTD = Model();
	gompersPTD.LoadModel("Models/Gravity Falls/Gompers/Gompers PTI.obj");
	gompersPTI = Model();
	gompersPTI.LoadModel("Models/Gravity Falls/Gompers/Gompers PTD.obj");
	gompers = Model();
	gompers.LoadModel("Models/Gravity Falls/Gompers/Gompers.obj");
	estatuaBill = Model();
	estatuaBill.LoadModel("Models/Gravity Falls/Estatua Bill/Estatua Bill.obj");
	trickster = Model();
	trickster.LoadModel("Models/Gravity Falls/Trickster/trickster.obj");
	mysteryShack = Model();
	mysteryShack.LoadModel("Models/Gravity Falls/Mystery Shack/Mystery Shack.obj");
	pato = Model();
	pato.LoadModel("Models/Gravity Falls/Pato/Pato.obj");
	patoPDD = Model();
	patoPDD.LoadModel("Models/Gravity Falls/Pato/Pato PDD.obj");
	patoPDI = Model();
	patoPDI.LoadModel("Models/Gravity Falls/Pato/Pato PDI.obj");
	patoPTD = Model();
	patoPTD.LoadModel("Models/Gravity Falls/Pato/Pato PTD.obj");
	patoPTI = Model();
	patoPTI.LoadModel("Models/Gravity Falls/Pato/Pato PTD.obj");
	dipper = Model();
	dipper.LoadModel("Models/Gravity Falls/Dipper/Dipper.obj");
	dipperCabeza = Model();
	dipperCabeza.LoadModel("Models/Gravity Falls/Dipper/Dipper Cabeza.obj");
	dipperBD = Model();
	dipperBD.LoadModel("Models/Gravity Falls/Dipper/Dipper BD.obj");
	dipperBI = Model();
	dipperBI.LoadModel("Models/Gravity Falls/Dipper/Dipper BI.obj");
	dipperPD = Model();
	dipperPD.LoadModel("Models/Gravity Falls/Dipper/Dipper PD.obj");
	dipperPI = Model();
	dipperPI.LoadModel("Models/Gravity Falls/Dipper/Dipper PI.obj");
	gorra = Model();
	gorra.LoadModel("Models/Gravity Falls/Gorra Dipper/gorra dipper.obj");
	libros = Model();
	libros.LoadModel("Models/Gravity Falls/Libros/libros.obj");


	//Extras --------------------------------
	Piso = Model();
	Piso.LoadModel("Models/Extras/Piso.obj");
	Carriles = Model();
	Carriles.LoadModel("Models/Extras/Piso2.obj");
	Agua = Model();
	Agua.LoadModel("Models/Extras/Piso3.obj");
	Invernadero = Model();
	Invernadero.LoadModel("Models/Extras/InvernaderoSinVidrio.obj");
	VidrioInvernadero = Model();
	VidrioInvernadero.LoadModel("Models/Extras/VidrioInvernadero.obj");
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
	Coladera1 = Model();
	Coladera1.LoadModel("Models/Extras/Coladera1.obj");
	Coladera2 = Model();
	Coladera2.LoadModel("Models/Extras/Coladera2.obj");
	Poste = Model();
	Poste.LoadModel("Models/Extras/Poste.obj");
	Semaforo = Model();
	Semaforo.LoadModel("Models/Extras/Semaforo.obj");
	Barrera = Model();
	Barrera.LoadModel("Models/Extras/Barrera.obj");
	Espectacular1 = Model();
	Espectacular1.LoadModel("Models/Extras/Espectacular1.obj");
	Espectacular2 = Model();
	Espectacular2.LoadModel("Models/Extras/Espectacular2.obj");
	EspectacularCocinado1 = Model();
	EspectacularCocinado1.LoadModel("Models/Extras/EspectacularCocinado1.obj");
	EspectacularCocinado2 = Model();
	EspectacularCocinado2.LoadModel("Models/Extras/EspectacularCocinado2.obj");
	Semaforo2 = Model();
	Semaforo2.LoadModel("Models/Extras/Semaforo2.obj");
	FilaPostes = Model();
	FilaPostes.LoadModel("Models/Extras/Poste_Fila.obj");
	FilaPostes2 = Model();
	FilaPostes2.LoadModel("Models/Extras/Poste_Fila2.obj");
	Jetsky = Model();
	Jetsky.LoadModel("Models/Extras/Jetsky.obj");
	Lancha = Model();
	Lancha.LoadModel("Models/Extras/Lancha.obj");
	Arbusto = Model();
	Arbusto.LoadModel("Models/Extras/Arbusto.obj");
	ArbolSolo1 = Model();
	ArbolSolo1.LoadModel("Models/Extras/ArbolSolo1.obj");
	ArbolSolo2 = Model();
	ArbolSolo2.LoadModel("Models/Extras/ArbolSolo2.obj");
	ArbolSolo3 = Model();
	ArbolSolo3.LoadModel("Models/Extras/ArbolSolo3.obj");
	ArbolSolo4 = Model();
	ArbolSolo4.LoadModel("Models/Extras/ArbolSolo4.obj");
	Esfera = Model();
	Esfera.LoadModel("Models/Extras/Esfera.obj");
	Esfera2 = Model();
	Esfera2.LoadModel("Models/Extras/Esfera2.obj");
	Reflector = Model();
	Reflector.LoadModel("Models/Extras/Reflector.obj");
	//Lamparas
	Candil = Model();
	Candil.LoadModel("Models/Lamparas/candil.obj");
	Lampara1 = Model();
	Lampara1.LoadModel("Models/Lamparas/Lampara01.obj");
	Lampara2 = Model();
	Lampara2.LoadModel("Models/Lamparas/Lampara2.obj");
	LamparaLago = Model();
	LamparaLago.LoadModel("Models/Lamparas/LamparaLago.obj");

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

	////Luz puntual
	unsigned int pointLightCount = 0;
	//luz del omnitrix
	pointLights[0] = PointLight(0.0f, 1.0f, 0.0f,
		//INTENSIDADES
		5.0f, 5.0f,
		//POSICION
		620.0f, 15.0f, 0.0f,
		//Con /Lin /Exp
		1.0f, 0.005f, 0.005f);
	pointLightCount++;
	//luz de la linterna de los barcos
	pointLights[1] = PointLight(1.0f, 0.5f, 0.0f,
		//INTENSIDADES
		1.0f, 1.0f,
		//POSICION
		-1510.0f, -5.0f, 290.0f,
		//Con /Lin /Exp
		0.5f, 0.001f, 0.001f);
	pointLightCount++;
	//luz del letrero kwik-e-mart (se prendera en la noche y se apagara en el dia)
	pointLights[2] = PointLight(1.0f, 0.0f, 0.0f,
		//INTENSIDADES
		3.0f, 3.0f,
		//POSICION
		390.0f, 140.0f, 1010.0f,
		//Con /Lin /Exp
		1.0f, 0.01f, 0.01f);
	pointLightCount++;

	//Spothligth
	unsigned int spotLightCount = 0;
	//nave de xylene
	spotLights[0] = SpotLight(0.0f, 1.0f, 0.0f,
		//INTENSIDADES
		0.0f, 2.0f,
		//POSICION
		0.0f, 0.0f, 0.0f,
		//VECTOR DE DIRECCION
		0.0f, -1.0f, 0.0f,
		//Con /Lin /Exp
		1.0f, 0.0f, 0.0f,
		//VALOR DEL CONO (TAMAÑO)
		15.0f);
	spotLightCount++;
	//Carro
	spotLights[1] = SpotLight(1.0f, 1.0f, 0.0f,
		//INTENSIDADES
		0.0f, 2.0f,
		//POSICION
		0.0f, 0.0f, 0.0f,
		//VECTOR DE DIRECCION
		0.0f, 0.0f, 0.0f,
		//Con /Lin /Exp
		1.0f, 0.01f, 0.0f,
		//VALOR DEL CONO (TAMAÑO)
		10.0f);
	spotLightCount++;
	//Letras Springfield
	spotLights[2] = SpotLight(1.0f, 1.0f, 1.0f,
		//INTENSIDADES
		0.0f, 2.0f,
		//POSICION
		1150.0f, 8.0f, -495.0f,
		//VECTOR DE DIRECCION
		1.0f, 0.8f, -0.8f,
		//Con /Lin /Exp
		1.0f, 0.0f, 0.0f,
		//VALOR DEL CONO (TAMAÑO)
		20.0f);
	spotLightCount++; 
	 
	//Luces cocinadas 
	//spotLights[2] = SpotLight(1.0f, 0.0f, 0.0f,
	//	//INTENSIDADES
	//	4.0f, 2.0f,
	//	//POSICION
	//	-66.5f, 123.5f, -980.0f,
	//	//VECTOR DE DIRECCION
	//	0.0f, 0.0f, 1.780f,
	//	//Con /Lin /Exp
	//	1.0f, 0.01f, 0.0f,
	//	//VALOR DEL CONO (TAMAÑO)
	//	5.7f);
	//spotLightCount++;
	
	//spotLights[3] = SpotLight(0.0f, 1.0f, 1.0f,
	//	//INTENSIDADES
	//	3.0f, 2.0f,
	//	//POSICION
	//	-10.5f, 250.0f, -1310.0f,
	//	//VECTOR DE DIRECCION
	//	0.0f, 0.0f, 1.0f,
	//	//Con /Lin /Exp
	//	1.0f, 0.01f, 0.0f,
	//	//VALOR DEL CONO (TAMAÑO)
	//	8.5f);
	//spotLightCount++;

	spotLights2[0] = spotLights[0];
	spotLights2[1] = spotLights[1];


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	int contadorEspectacular = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	///Variables para animaciones
	//DX10
	movDX10 = 400.0f;
	movDX10z = 815.0f;
	movDX10Offset = 1.0f;
	rotllanta = 0.0f;
	rotllantaOffset = 1.5f;
	giroDX10 = 0.0f;
	giroDX10Offset = 0.8;

	//Ben
	rotmano = 0.0f;
	rotmanoOffset = 0.6f;
	maxRotation = 90.0f;
	minRotation = 0.0f;
	maxEscale = 200.0f;
	escesferax = escesferay = escesferaz = 6.5f;
	escesferax2 = escesferay2 = escesferaz2 = 6.5f;
	escesferaOffset = 0.8f;
	rotbrazoD = 0.0f;
	rotbrazoDOffset = 0.6f;
	rotmanoD = 0.0f;
	rotmanoDOffset = 0.6f;
	movAtaque = -35.0f;
	movAtaqueOffset = 0.3f;
	maxTraslation = 5.0f;
	Revertir = false;
	
	//Jetsky
	movJetskyXoffset = 3.0f;
	movJetskyYoffset = 3.0f;
	movJetskyZoffset = 3.0f;
	giroJetsky = 0;
	giroJetskyOffset = 0.8f;

	//Peridot
	rotPeridotPiernas = 0.0f;
	rotPeridotPiernasOffset = 1.0f;
	rotPeridotBrazos = 0.0f;
	rotPeridotBrazosOffset = 1.0f;

	//Dona
	rotDonaOffset = 0.1f;
	rotSoporteOffset = 0.1f;
	movSoporteOffset = 0.0001f;

	//Blimp Duff
	rotHeliceOffset = 20.0f;
	subeBlimpOffset = 0.5f;
	giroBlimpOffset = 0.6;
	movBlimpXOffset = 1.7f;
	
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		////////////////////// ANIMACIONES /////////////////////
		// Vehiculos Motorizados Obligatorios//------------------
		//DX10------
		if (avanzaDX10 && controlDX10) {
			if (giroDX10 >= 360) {
				giroDX10 = 0;
			}
			if (movDX10 < 990.0f)
			{
				movDX10 += movDX10Offset;
				rotllanta += rotllantaOffset;
			}
			else {
				if (giroDX10 < 90) {
					if (giroDX10 < 45) {
						giroDX10 += giroDX10Offset;
						movDX10 += movDX10Offset;
						rotllanta += rotllantaOffset;
					}
					else {
						movDX10z += movDX10Offset;
						rotllanta += rotllantaOffset;
						giroDX10 += giroDX10Offset;
					}
				}
				else {
					if (movDX10z < 2500.0f)
					{
						movDX10z += movDX10Offset;
						rotllanta += rotllantaOffset;
					}
					else {
						controlDX10 = !controlDX10;
					}
				}
			}
		}
		else if (avanzaDX10 && controlDX10 == false) {
			if (giroDX10 < 180) {
				if (giroDX10 < 135) {
					movDX10 -= movDX10Offset;
					rotllanta += rotllantaOffset;
					giroDX10 += giroDX10Offset;
				}
				else {
					giroDX10 += giroDX10Offset;
					movDX10z -= movDX10Offset;
					rotllanta += rotllantaOffset;
				}
			}
			else {
				if (movDX10 > 120.0f) {
					movDX10 -= movDX10Offset;
					rotllanta += rotllantaOffset;
				}
				else {
					if (giroDX10 < 270) {
						if (giroDX10 < 225) {
							giroDX10 += giroDX10Offset;
							movDX10 -= movDX10Offset;
							rotllanta += rotllantaOffset;
						}
						else {
							movDX10z += movDX10Offset;
							rotllanta += rotllantaOffset;
							giroDX10 += giroDX10Offset;
						}
					}
					else {
						if (movDX10z > 815.0f)
						{
							movDX10z -= movDX10Offset;
							rotllanta += rotllantaOffset;
						}
						else {
							avanzaDX10 = !avanzaDX10;
						}
					}
				}
			}
		}
		else {
			if (giroDX10 < 360) {
				if (giroDX10 < 315) {
					movDX10 += movDX10Offset;
					rotllanta += rotllantaOffset;
					giroDX10 += giroDX10Offset;
				}
				else {
					giroDX10 += giroDX10Offset;
					movDX10 += movDX10Offset;
					rotllanta += rotllantaOffset;
				}
			}
			else {
				controlDX10 = !controlDX10;
				avanzaDX10 = !avanzaDX10;
			}
		}
		//Jetsky------	
		if (JetskyAni && controlJetsky) {
			if (giroJetsky >= 360) {
				giroJetsky = 0;
			}
			if (movJetskyYoffset > 360.0f) {
				movJetskyYoffset = 0.0f;
			}
			if (movJetskyZ < 700.0f)
			{
				movJetskyY += movJetskyYoffset;
				movJetskyZ += movJetskyZoffset;
			}
			else {
				if (giroJetsky < 90) {
					if (giroJetsky < 45) {
						movJetskyY += movJetskyYoffset;
						giroJetsky += giroJetskyOffset;
						movJetskyZ += movJetskyZoffset;
					}
					else {
						movJetskyX -= movJetskyXoffset;
						movJetskyY += movJetskyYoffset;
						giroJetsky += giroJetskyOffset;
					}
				}
				else {
					if (movJetskyX > -250.0f)
					{
						movJetskyX -= movJetskyXoffset;
						movJetskyY += movJetskyYoffset;
					}
					else {
						controlJetsky = !controlJetsky;
					}
				}
			}
		}
		else if (JetskyAni && controlJetsky == false) {
			if (movJetskyYoffset > 360.0f) {
				movJetskyYoffset = 0.0f;
			}
			if (giroJetsky < 180) {
				if (giroJetsky < 135) {
					movJetskyX -= movJetskyXoffset;
					movJetskyY += movJetskyYoffset;
					giroJetsky += giroJetskyOffset;
				}
				else {
					movJetskyY += movJetskyYoffset;
					giroJetsky += giroJetskyOffset;
					movJetskyZ -= movJetskyZoffset;
				}
			}
			else {
				if (movJetskyZ > 150.0f) {
					movJetskyY += movJetskyYoffset;
					movJetskyZ -= movJetskyZoffset;
				}
				else {
					if (giroJetsky < 270) {
						if (giroJetsky < 225) {
							movJetskyY += movJetskyYoffset;
							giroJetsky += giroJetskyOffset;
							movJetskyZ -= movJetskyZoffset;
						}
						else {
							movJetskyX += movJetskyXoffset;
							movJetskyY += movJetskyYoffset;
							giroJetsky += giroJetskyOffset;
						}
					}
					else {
						if (movJetskyX < -100.0f)
						{
							movJetskyX += movJetskyXoffset;
							movJetskyY += movJetskyYoffset;
						}
						else {
							JetskyAni = !JetskyAni;
						}
					}
				}
			}
		}
		else {
			if (giroJetsky < 360) {
				if (giroJetsky < 315) {
					movJetskyX += movJetskyXoffset;
					movJetskyY += movJetskyYoffset;
					giroJetsky += giroJetskyOffset;
				}
				else {
					movJetskyY += movJetskyYoffset;
					giroJetsky += giroJetskyOffset;
					movJetskyZ += movJetskyZoffset;
				}
			}
			else {
				controlJetsky = !controlJetsky;
				JetskyAni = !JetskyAni;
			}
		}
		
		//Duuf Blimp
		if (sube && subeBlimp <= 200.0f) {
			subeBlimp += subeBlimpOffset;
			rotHelice -= rotHeliceOffset;
		}
		else if (sube) {
			avanza = !avanza;
			sube = !sube;
		}
		else if (avanza && movBlimpX >= -2500.0f) {
			movBlimpX -= movBlimpXOffset;
			rotHelice -= rotHeliceOffset;
		}
		else if (avanza) {
			giro1 = !giro1;
			avanza = !avanza;
		}
		else if (giro1 && giroBlimp <= 180.0f) {
			giroBlimp += giroBlimpOffset;
			rotHelice -= rotHeliceOffset;
		}
		else if (giro1) {
			regresa = !regresa;
			giro1 = !giro1;
		}
		else if (regresa && movBlimpX <= 3.0f) {
			movBlimpX += movBlimpXOffset;
			rotHelice -= rotHeliceOffset;
		}
		else if (regresa) {
			regresa = !regresa;
			giro2 = !giro2;
		}
		else if (giro2 && giroBlimp >= 0.0f) {
			giroBlimp -= giroBlimpOffset;
			rotHelice -= rotHeliceOffset;
		}
		else if (giro2) {
			baja = !baja;
			giro2 = !giro2;
		}
		else if (baja && subeBlimp >= 8.2f) {
			subeBlimp -= subeBlimpOffset;
			rotHelice -= rotHeliceOffset;
		}
		else if (baja) {
			sube = !sube;
			baja = !baja;
		}


		////// Fin Animaciones Obligatorias de vehiculos--------

		//Transformaciones----------
		//Eco Eco
		if (mainWindow.getAlien1() == 1.0f && Limite)
		{
			//Se activa animacion de mano
			rotmano += rotmanoOffset;
			//toca el reloj y comienza la transformacion
			if (rotmano >= maxRotation) {
				rotmano = maxRotation; 
				//Dibuja la esfera y la escala
				Dibujaresfera = true;
				escesferax += escesferaOffset;
				escesferay += escesferaOffset;
				escesferaz += escesferaOffset;
				//Llega al tope de crecimiento 
				if (escesferax == escesferay == escesferaz >= maxEscale) {
					escesferax = maxEscale;
					escesferay = maxEscale;
					escesferaz = maxEscale;
					Transformar = 1.0f;
					Dibujaresfera = false;
					escesferax2 = 6.5;
					escesferay2 = 6.5;
					escesferaz2 = 6.5;
					Limite = !Limite;
				}
			}
		}

		////Diamante (ANIMACION COMPLEJA)
		else if (mainWindow.getAlien2() == 1.0f && Limite)
		{
				//Se activa animacion de mano
				rotmano += rotmanoOffset;
				//toca el reloj y comienza la transformacion
				if (rotmano >= maxRotation) {
					rotmano = maxRotation;
					//Dibuja la esfera y la escala
					Dibujaresfera = true;
					escesferax += escesferaOffset;
					escesferay += escesferaOffset;
					escesferaz += escesferaOffset;
					//Llega al tope de crecimiento 
					if (escesferax == escesferay == escesferaz >= maxEscale) {
						escesferax = maxEscale;
						escesferay = maxEscale;
						escesferaz = maxEscale;
						Transformar = 2.0f;
						Dibujaresfera = false;
						if (Revertir == false) {
							rotbrazoD += rotbrazoDOffset;
							if (rotbrazoD >= maxRotation) {
								rotbrazoD = maxRotation;
								rotmanoD += rotmanoDOffset;
								if (rotmanoD >= maxRotation) {
									rotmanoD = maxRotation;
									AtaqueDiamante = true;
									movAtaque += movAtaqueOffset;
									if (movAtaque >= maxTraslation) {
										movAtaque = maxTraslation;
										Revertir = true;
									}
								}
							}
						}
						else {
							rotmanoD -= rotmanoDOffset;
							if (rotmanoD <= minRotation) {
								rotmanoD = minRotation;
								rotbrazoD -= rotbrazoDOffset;
								if (rotbrazoD <= minRotation) {
									rotbrazoD = minRotation;
									AtaqueDiamante = false;
									escesferax2 = 6.5;
									escesferay2 = 6.5;
									escesferaz2 = 6.5;
									rotmanoD = 0.0;
									rotbrazoD = 0.0;
									movAtaque = -35.0;
									Revertir = false;
									Limite = !Limite;
								}
							}
						}
					}
				}
		}

		//Destransformar
		if (mainWindow.getDestransformar() == 1.0f)
		{
			//Dibuja la esfera y la escala
			Dibujaresfera2 = true;
			escesferax2 += escesferaOffset;
			escesferay2 += escesferaOffset;
			escesferaz2 += escesferaOffset;
			//Llega al tope de crecimiento 
			if (escesferax2 == escesferay2 == escesferaz2 >= maxEscale) {
				escesferax2 = maxEscale;
				escesferay2 = maxEscale;
				escesferaz2 = maxEscale;
				Transformar = 0.0f;
				Dibujaresfera2 = false;
				rotmano = rotmano - 90.0f;
				if (rotmano <= minRotation) {
					rotmano = minRotation;
				}
				escesferax = 6.5;
				escesferay = 6.5;
				escesferaz = 6.5;
				Limite = true;
			}
		}

		////// ANIMACION AVATAR /////////-----------------
		//Caminata peridot------
		//Hacia adelante y atras
		if (keys[GLFW_KEY_W] && keys[GLFW_KEY_S]) {
			rotPeridotPiernas = rotPeridotPiernas;
			rotPeridotBrazos = rotPeridotBrazos;
		}
		else if (keys[GLFW_KEY_W] || keys[GLFW_KEY_S]) {
			if (movPeridot) {
				if (rotPeridotPiernas < 10.0f)
				{
					rotPeridotPiernas += rotPeridotPiernasOffset * deltaTime;
					rotPeridotBrazos += rotPeridotBrazosOffset * deltaTime;
				}
				else {
					movPeridot = !movPeridot;
				}
			}
			else {
				if (-10.0f < rotPeridotPiernas)
				{
					rotPeridotPiernas -= rotPeridotPiernasOffset * deltaTime;
					rotPeridotBrazos -= rotPeridotBrazosOffset * deltaTime;
				}
				else {
					movPeridot = !movPeridot;
				}
			}
		}
		//////////////--------------
		
		///////////// ANIMACIONES BASICAS //////////////--------
		//Dona
		if (DonaAni) {
			if (rotDona < 40) {
				rotDona += rotDonaOffset;
			}
			if (rotSoporte < 40) {
				rotSoporte += rotSoporteOffset;
				movSoporte -= rotSoporteOffset;
			}
			else {
				DonaAni = !DonaAni;
			}
		}
		else {
			if (rotDona > 0) {
				rotDona -= rotDonaOffset;
			}
			if (rotSoporte > 0) {
				rotSoporte -= rotSoporteOffset;
				movSoporte += rotSoporteOffset;
			}
			else {
				DonaAni = !DonaAni;
			}
		}
		// Animal
		

		////////---------------
		
		////// Animaciones de Vehiculos motorizados para punto extra ////////////-----



		///////// Fin animaciones punto extra /////////--------

		
 

		//Calculo de dia y noche
		contador = time(NULL);
		resta = contador - tiempoguardado;

		//cambio de variables
		if (resta >= 60) {
			if (dia == 1.0f) {
				//Noche
				dia = 0.0f;
			}
			else {
				//Dia
				dia = 1.0f;
			}
			//resetea el tiempo guardado al tiempo actual
			tiempoguardado = contador;
		}

		if (dia == 1.0f) {
			contador2 = time(NULL);
			resta2 = contador2 - tiempoguardado2;
			//calculo de intensidad y posicion del sol
			if (resta2 >= 1) {
				//control de la intensidad
				if (intensidad >= 0.21f && (59 >= aux && aux >= 40)) {
					intensidad -= 0.015f;
				}
				else if (0.5f >= intensidad && (19 >= aux && aux >= 0)) {
					intensidad += 0.015f;
				}
				//control de direccion
				if (direcciony >= -1.0f && (9 >= aux && aux >= 0)) {
					direcciony -= 0.1f;
				}
				else if (0.0f >= direccionx && (19 >= aux && aux >= 10)) {
					direccionx += 0.1f;
				}
				else if (1.0f >= direccionx && (49 >= aux && aux >= 40)) {
					direccionx += 0.1f;
				}
				else if (1.0f >= direcciony && (59 >= aux && aux >= 50)) {
					direcciony += 0.1f;
				}
				//aumenta la variable que cuenta los segundos
				if (aux == 59) {
					aux = 0;
				}
				else {
					aux += 1;
				}
				tiempoguardado2 = contador2;
			}
			//
			mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
				intensidad, intensidad,
				direccionx, direcciony, 0.0f);
		}
		else {
			contador2 = time(NULL);
			resta2 = contador2 - tiempoguardado2;
			//calculo de intensidad de la noche
			if (resta2 >= 1) {
				//control de la intensidad
				if (intensidad >= 0.1f && (9 >= aux && aux >= 0)) {
					intensidad -= 0.01f;
				}
				else if (0.2f >= intensidad && (59 >= aux && aux >= 50)) {
					intensidad += 0.01f;
					if (59 == aux) {
						direcciony = 0.0f;
						direccionx = -1.0f;
					}
				}
				//aumenta la variable que cuenta los segundos
				if (aux == 59) {
					aux = 0;
				}
				else {
					aux += 1;
				}
				tiempoguardado2 = contador2;
			}
			//
			mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
				intensidad, intensidad,
				0.0f, 0.0f, 0.0f);
		}

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
		currentCamera->keyControl(mainWindow.getCamara(), mainWindow.getsKeys(), deltaTime, peridotPos);
		currentCamera->mouseControl(mainWindow.getCamara(), mainWindow.getXChange(), mainWindow.getYChange(), peridotPos);

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

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);

		if (dia == 0.0f) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else {
			shaderList[0].SetPointLights(pointLights, pointLightCount-1);
		}

		if (mainWindow.getLucesspot() == 1.0f) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
			//luz de la nave de xilene
			spotLights[0].SetFlash(glm::vec3(posnaveX + 70, posnaveY + 25, posnaveZ + 70), glm::vec3(0.0f, -1.0f, 0.0f));
			//luz del rustbucket
			spotLights[1].SetFlash(glm::vec3(posCarroX, posCarroY - 0.3, posCarroZ), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (mainWindow.getLucesspot() == 0.0f) {
			shaderList[0].SetSpotLights(spotLights2, spotLightCount);
			//luz de la nave de xilene
			spotLights2[0].SetFlash(glm::vec3(posnaveX + 70, posnaveY + 25, posnaveZ + 70), glm::vec3(0.0f, -1.0f, 0.0f));
			//luz del rustbucket
			spotLights2[1].SetFlash(glm::vec3(posCarroX, posCarroY - 0.3, posCarroZ), glm::vec3(1.0f, 0.0f, 0.0f));
		}

		glm::mat4 model(1.0);
		glm::mat4 modelauxMark10(1.0);
		glm::mat4 modelauxRust(1.0);
		glm::mat4 modelauxBen(1.0);
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
		glm::mat4 ModelAuxLeon(1.0);
		glm::mat4 modelauxBlimp(1.0);
		glm::mat4 ModelBB(1.0);
		glm::mat4 ModelBJ(1.0);
		glm::mat4 ModelBS(1.0);
		glm::mat4 ModelBG(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		//Cuadrante 1-------------------------------------------------
		//Bancas//
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1220.0f, 0.0f, -240.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1220.0f, 0.0f, -370.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1480.0f, 0.0f, -180.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 18.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1700.0f, 0.0f, -180.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.5f, 15.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca2.RenderModel();
		//Terminan bancas

		//Hongos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1600, 10.0, -1000));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1300, 23.0, -900));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1645, 18.0, -480));
		model = glm::rotate(model, glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1300, 25.0, -555));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1450, 0.0, -330));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1600, 16.5, -700));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1290, 0.0, -1170));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1290, 0.0, -1235));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1290, 0.0, -1300));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1740, 0.0, -720));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1740, 8.0, -645));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1700, 0.0, -250));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1450, 30.0, -500));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1430, 25.0, -430));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1300, 28.0, -700));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1520, 8.0, -1160));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1740, 5.0, -795));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1740, 5.0, -860));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1740, 5.0, -925));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1630, 6.0, -250));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1630, 6.0, -340));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();

		//Pinos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1320.0f, 13.0f, -460.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1345.0f, -3.0f, -300.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1537.0f, -3.0f, -417.0f));
		model = glm::rotate(model, glm::radians(195.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.4f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1540.0f, -3.0f, -290.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1610.0f, -3.0f, -1117.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1440.0f, -3.0f, -1110.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1310.0f, 7.5f, -1080.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1420.0f, 0.0f, -1260.0f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1580.0f, 0.0f, -1265.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1740.0f, 0.0f, -1220.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1740.0f, 0.0f, -1020.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1705.0f, 0.0f, -395.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1750.0f, 8.0f, -540.0f));
		model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		//Coladera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1050.0, 0.0, -750.0));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coladera1.RenderModel();

		//leon
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1600.0f, 10.0f, -200.0f));
		model = glm::rotate(model, 75 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelAuxLeon = model;
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Leon.RenderModel();

		model = ModelAuxLeon;
		model = glm::translate(model, glm::vec3(1.3f, -3.4f, 1.7f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LeonPataDelDer.RenderModel();

		model = ModelAuxLeon;
		model = glm::translate(model, glm::vec3(-1.6f, -3.4f, 1.5f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LeonPataDelIzq.RenderModel();

		model = ModelAuxLeon;
		model = glm::translate(model, glm::vec3(1.5f, -2.4f, -5.2f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LeonPataTrasDer.RenderModel();

		model = ModelAuxLeon;
		model = glm::translate(model, glm::vec3(-1.6f, -2.6f, -5.2f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LeonPataTrasIzq.RenderModel();

		//Cuadrante 2 Jared ------------------------------------------------------
		//Sr Smoothie
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-680.5, 0.5, -1112.5));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SrSmoothy.RenderModel();

		////Transformaciones --------------
		//Ben-------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-525.0f, 0.0f, -1030.0f));
		model = glm::scale(model, glm::vec3(6.5f, 6.5f, 6.5f));
		modelauxBen = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if (Transformar == 0.0f)
		{
			Ben.RenderModel();
		}
		//Antebrazo
		model = modelauxBen;
		model = glm::translate(model, glm::vec3(-0.609f, 3.507f, 0.307f));
		model = glm::rotate(model, rotmano * toRadians, glm::vec3(0.0f, 0.0, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if (Transformar == 0.0f)
		{
			BenAntebrazo.RenderModel();
		}
		
		
		//EcoEco---------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-525.0f, 0.0f, -1030.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if(Transformar==1.0f){
			EcoEco.RenderModel();

		}
		
		//Diamante ----------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-525.0f, 0.0f, -1030.0f));
		model = glm::scale(model, glm::vec3(4.1f, 4.1f, 4.1f));
		modelauxDiamante = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if (Transformar == 2.0f) {
			Diamante.RenderModel();
		}
		//Brazo Izq
		model = modelauxDiamante;
		model = glm::translate(model, glm::vec3(-1.413f, 8.041f, -0.54f));
		model = glm::rotate(model, rotbrazoD * toRadians, glm::vec3(-1.0f, 0.0, 0.0f));
		modelauxDiamante = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if (Transformar == 2.0f) {
			DiamanteBrazoIzq.RenderModel();
		}
		//Mano Izq
		model = modelauxDiamante;
		model = glm::translate(model, glm::vec3(-1.166f, -4.551f, 0.0f));
		model = glm::rotate(model, rotmanoD * toRadians, glm::vec3(0.0f, 1.0, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if (Transformar == 2.0f) {
			DiamanteManoIzq.RenderModel();
		}

		//Ataque Diamante
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-525.0f, movAtaque, -920.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if (AtaqueDiamante == true){
			ADiamante.RenderModel();
		}
		//--------------------

		//Esfera para transformacion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-523.814f, 22.377f, -1026.459f));
		model = glm::scale(model, glm::vec3(escesferax, escesferay, escesferaz));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if (Dibujaresfera == true)
		{
			Esfera.RenderModel();
		}

		//Esfera para destransformacion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-523.814f, 22.377f, -1026.459f));
		model = glm::scale(model, glm::vec3(escesferax2, escesferay2, escesferaz2));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if (Dibujaresfera2 == true)
		{
			Esfera2.RenderModel();
		}
		//////---------------

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-886.5f, 7.0f, -912.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.5f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara1.RenderModel();

		//Semaforo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-156.5f, 0.0f, -910.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Semaforo.RenderModel();

		//Coladera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-310.5, 0.0, -1112.5));
		model = glm::rotate(model, glm::radians(117.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coladera2.RenderModel();

		//Botes de Basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-208.0f, 0.0f, -958.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-208.0f, 0.0f, -1290.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Arboles Jardinera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1700.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, -1600.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, 0.0f, -1500.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, 0.0f, -1400.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1320.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, -1240.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, 0.0f, -1180.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, 0.0f, -1090.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1010.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, -930.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo4.RenderModel();

		//Cuadrante 3 ------------------------------------------------------------------
		//Mesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(406.2f, 1.0f, -1080.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 22.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MesaLGR.UseTexture();
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(417.8f, 1.0f, -1109.2f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 22.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MesaLGR.UseTexture();
		meshList[3]->RenderMesh();

		//Refrigeradores
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(477.8f, -2.3f, -1109.5f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Donas.RenderModel();

		//Refri
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(426.0f, 24.0f, -1205.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Refri.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(486.0f, 24.0f, -1205.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Refri.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(538.0f, 24.0f, -1100.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Refri.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(634.0f, 0.0f, -1155.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Refri2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(634.0f, 0.0f, -1205.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Refri2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(406.2f, 19.0f, -1110.0f));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Refri3.RenderModel();

		//Gatogalleta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(420.0f, 21.0f, -1110.0f));
		ModelBG = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GatoGalleta.RenderModel();
		
		//La gran rosquilla
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(450.0f, 51.0f, -1050.0f));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LGR.RenderModel();

		//Dona
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(470.0f, 168.0f, -1040.0f));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		model = glm::rotate(model, glm::radians(rotDona), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dona.RenderModel();

		//Soporte
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(470.0f, 168.0f, -1072.0f + movSoporte));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		model = glm::rotate(model, glm::radians(rotSoporte), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Soporte.RenderModel();

		//Burbuja Gatogalleta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(700.0f, 20.0f, -1050.0f));
		ModelBG = model;
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		GatoGalleta.RenderModel();

		//Burbuja Jasper
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(750.0f, 30.0f, -1100.0f));
		ModelBJ = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BurbujaJasper.RenderModel();

		//Coladera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(600.5, 0.0, -1105.5));
		model = glm::rotate(model, glm::radians(117.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coladera2.RenderModel();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(163.5f, 7.0f, -913.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.5f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara1.RenderModel();

		//Cuadrante 4 -------------------------------------------------------------------
		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1216.5f, 7.0f, -163.5f));
		model = glm::scale(model, glm::vec3(10.0f, 10.5f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara1.RenderModel();

		//Coladera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1050.0, 0.0, -750.0));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coladera1.RenderModel();

		//Reflector
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1190.0, 10.0, -535.0));
		model = glm::rotate(model, -110 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Reflector.RenderModel();

		//Letras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1700.0f, 4.5f, -800.0f));
		model = glm::scale(model, glm::vec3(12.0f, 13.5f, 12.0f));
		model = glm::rotate(model, -145 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Letras.RenderModel();

		//Jefe Gorgory
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1400.0f, -15.5f, -450.0f));
		model = glm::scale(model, glm::vec3(0.52f, 0.52f, 0.52f));
		model = glm::rotate(model, -55 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		JefeGorgory.RenderModel();

		//Khyber
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1600.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
		model = glm::rotate(model, 225 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Khyber.RenderModel();

		//Escarabola---------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1350.0f, 0.0f, -250.0f));
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
		/////////////--------------------

		//Crabdozer-------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1250.0f, 0.1f, -500.0f));
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
		//////--------------------

		//Flores
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1475.0f, 20.0f, -525.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1460.0f, 90.0f, -630.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, -5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 55 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor5.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1635.0f, 120.0f, -488.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 5 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 48 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1530.0f, 65.0f, -525.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 50 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor5.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1375.0f, 65.0f, -725.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, -25 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -70 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1475.0f, 175.0f, -725.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, -25 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 60 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -27 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1630.0f, 70.0f, -450.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 50 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor5.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1590.0f, 155.0f, -560.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 20 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 70 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1510.0f, 105.0f, -580.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 55 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 152 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor4.RenderModel();

		//Cuadrante 5 -------------------------------------------------------------------
		//Jetsky
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1350.0f + movJetskyX, -10.0f + (4 * sin(glm::radians(movJetskyY))), 400.0f + movJetskyZ));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, giroJetsky * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(18.0f, 18.0f, 18.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jetsky.RenderModel();

		//Lanchas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1400.0f, -17.0f, 250.0f));
		model = glm::rotate(model, 195 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(18.0f, 18.0f, 18.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lancha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1630.0f, -17.0f, 270.0f));
		model = glm::rotate(model, 170 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(18.0f, 18.0f, 18.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lancha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1750.0f, -17.0f, 260.0f));
		model = glm::rotate(model, 185 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(18.0f, 18.0f, 18.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lancha.RenderModel();
		//
		//Lancha con Candil
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1510.0f, -15.0f, 300.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(18.0f, 18.0f, 18.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lancha.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1510.0f, -5.0f, 287.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Candil.RenderModel();

		//Semaforo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1160.5f, 0.0f, 165.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Semaforo.RenderModel();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1265.5f, 0.0f, 192.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.5f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LamparaLago.RenderModel();

		//Coladera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1050.0, 0.0, 750.0));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coladera1.RenderModel();

		//Arboles Jardinera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2100.0f, 0.0f, 3.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2000.0f, 0.0f, -17.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.4f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1900.0f, 0.0f, -17.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1800.0f, 0.0f, 3.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.0f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1720.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1640.0f, 0.0f, 3.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.2f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1580.0f, 0.0f, -17.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.4f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1490.0f, 0.0f, 3.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.1f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1410.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.25f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1330.0f, 0.0f, 3.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1250.0f, 0.0f, -17.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.4f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo1.RenderModel();

		//Cuadrante 6 -------------------------------------------------------------------
		//Mystery Shack
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-500.0f, 2.0f, 1120.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.8f, 8.8f, 8.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mysteryShack.RenderModel();
		glDisable(GL_BLEND);

		//Dipper
		glm::mat4 ModelAuxDipper1(1.0);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-475.0f, 20.0f, 950.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ModelAuxDipper1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dipper.RenderModel();

		//Pierna delantera derecha
		model = ModelAuxDipper1;
		model = glm::translate(model, glm::vec3(-0.15f, -0.9f, 0.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dipperPI.RenderModel();
		//Pierna delantera izquierda
		model = ModelAuxDipper1;
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));
		model = glm::translate(model, glm::vec3(0.3f, -1.0f, 0.1));
		model = glm::rotate(model, glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dipperPI.RenderModel();
		//Brazo derecho
		model = ModelAuxDipper1;
		model = glm::translate(model, glm::vec3(-0.3, -0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dipperBI.RenderModel();
		////Brazo izquierdo
		model = ModelAuxDipper1;
		model = glm::translate(model, glm::vec3(0.35, -0.1f, 0.1f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dipperBD.RenderModel();
		//Cabeza
		model = ModelAuxDipper1;
		model = glm::translate(model, glm::vec3(0.0, 0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dipperCabeza.RenderModel();

		//Hongos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-700, 5.0, 1100));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300, 5.0, 1100));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-500, 5.0, 1330));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hongos3.RenderModel();


		//Gorra
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-760.0f, 3.0f, 1100.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		gorra.RenderModel();

		//Libros
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-270.0f, 3.0f, 900.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		libros.RenderModel();

		//Pinos por código
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 3.0f, 1000.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.5f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-270.0f, 3.0f, 1000.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.2f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-340.0f, 3.0f, 1000.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.85f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-620.0f, 3.0f, 1000.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.9f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-690.0f, 3.0f, 1000.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.7f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-760.0f, 3.0f, 1000.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.1f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 3.0f, 1700.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.42f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-270.0f, 3.0f, 1700.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.12f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-340.0f, 3.0f, 1700.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.45f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-410.0f, 3.0f, 1700.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.966f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-480.0f, 3.0f, 1700.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.8f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-550.0f, 3.0f, 1700.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.856f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-620.0f, 3.0f, 1700.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.6f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-690.0f, 3.0f, 1700.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-760.0f, 3.0f, 1700.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.56f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 3.0f, 1600.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 6.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-270.0f, 3.0f, 1600.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.8f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-340.0f, 3.0f, 1600.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.23f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-410.0f, 3.0f, 1600.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.56f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-480.0f, 3.0f, 1600.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.389f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-550.0f, 3.0f, 1600.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-690.0f, 3.0f, 1600.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.189f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-760.0f, 3.0f, 1600.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.9f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.45f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-270.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.65f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-340.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.89f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-410.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.78f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-480.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 6.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-410.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.63f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-480.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.365f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-550.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.8f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-620.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 4.9f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-690.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 6.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-760.0f, 3.0f, 1500.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 5.31f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pinoTex.UseTexture();
		meshList[4]->RenderMesh();

		//Pinos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-270.0f, -3.0f, 1250.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-760.0f, -3.0f, 1250.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-168.0f, 0.0f, 912.0f));
		model = glm::scale(model, glm::vec3(3.5f, 4.0f, 3.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara2.RenderModel();

		//Bote de basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-836.5f, 0.0f, 958.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Cuadrante 7 ---------------------------------------------------------------------
		//KwikEmart
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(530.0f, -1.0f, 1116.6f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		KwikEmart.RenderModel();
		glDisable(GL_BLEND);

		//Letrero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(390.0f, 0.3f, 1010.0f));
		model = glm::scale(model, glm::vec3(15.5f, 17.0f, 15.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LetreroKwik.RenderModel();

		//Semaforo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(156.5f, 0.0f, 910.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Semaforo.RenderModel();

		//Coladera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(350.5, 0.0, 1116.6));
		model = glm::rotate(model, glm::radians(117.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coladera2.RenderModel();

		//Lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(888.5f, 0.0f, 912.0f));
		model = glm::scale(model, glm::vec3(3.5f, 4.0f, 3.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara2.RenderModel();

		//Botes de Basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(208.0f, 0.0f, 958.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(208.0f, 0.0f, 1240.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Apu 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(460.5f, 0.0f, 1000.5f));
		model = glm::scale(model, glm::vec3(1.8f, 1.7f, 1.8f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Apu.RenderModel();

		//Espectacular 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 0.3f, 1300.0f));
		model = glm::scale(model, glm::vec3(2.5f, 3.0f, 2.5f));
		//model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		if (dia == 1.0) {
			if (contadorEspectacular >= 0 && contadorEspectacular <= 600) {
				Espectacular1.RenderModel();
			}
			else if (contadorEspectacular > 600 && contadorEspectacular <= 1200) {
				Espectacular2.RenderModel();
			}
			contadorEspectacular++;
			if (contadorEspectacular > 1200) {
				contadorEspectacular = 0; // Reiniciar el contador
			}
		}
		else{
			if (contadorEspectacular >= 0 && contadorEspectacular <= 600) {
				EspectacularCocinado1.RenderModel();
			}
			else if (contadorEspectacular > 600 && contadorEspectacular <= 1200) {
				EspectacularCocinado2.RenderModel();
			}
			contadorEspectacular++;
			if (contadorEspectacular > 1200) {
				contadorEspectacular = 0; // Reiniciar el contador
			}
		}
		

		//Arboles Jardinera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1700.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 1600.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, 0.0f, 1500.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, 0.0f, 1400.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1320.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 1240.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, 0.0f, 1150.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo1.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, 0.0f, 1090.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1010.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 930.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolSolo4.RenderModel();

		//Cuadrante 8 -----------------------------------------------------------------
		//Coladera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1050.0, 0.0, 750.0));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Coladera1.RenderModel();

		//Blimp Duff
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1650 + movBlimpX, subeBlimp, 450.5f));
		model = glm::scale(model, glm::vec3(3.5f, 3.0f, 3.5f));
		model = glm::rotate(model, -75 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, giroBlimp * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelauxBlimp = model; 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BlimpDuff.RenderModel();
		model = modelauxBlimp;

		model = glm::translate(model, glm::vec3(-6.0f, 3.0f, -1.8f));
		model = glm::rotate(model, rotHelice * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helice1.RenderModel();
		model = modelauxBlimp;

		model = glm::translate(model, glm::vec3(6.0f, 3.0f, -1.8f));
		model = glm::rotate(model, rotHelice * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Helice1.RenderModel();
		model = modelauxBlimp;


		//Xylene Ship-----------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(posnaveX, posnaveY, posnaveZ));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		modelauxShip = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		XyleneShip.RenderModel();
		model = modelauxShip;

		//Arco
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -32.5f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		XyleneShip_Arco.RenderModel();
		model = modelauxShip;

		//Semaforo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1210.5f, 0.0f, 160.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Semaforo2.RenderModel();
		////---------------
		
		//Centro ----------------------------------------------------------------------
		//Piso
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso.RenderModel();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carriles.RenderModel();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Agua.RenderModel();

		//Invernadero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-700.0f, 1.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.015f, 0.0135f, 0.015f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Invernadero.RenderModel();
		glDisable(GL_BLEND);

		//Burbuja Bismuto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-685.0f, 15.0f, -62.0f));
		ModelBB = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BurbujaBismuto.RenderModel();

		//Burbuja Squaridot
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-715.0f, 35.0f, 48.0f));
		ModelBS = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		LGRVid.RenderModel();
		glDisable(GL_BLEND);

		//Invernadero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-700.0f, 1.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.015f, 0.0135f, 0.015f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		VidrioInvernadero.RenderModel();
		glDisable(GL_BLEND);
		////-----------

		BurbujaSquaridot.RenderModel();

		
		//Perimetro Postes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -650.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.4f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FilaPostes.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 640.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.4f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FilaPostes.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(938.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.4f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FilaPostes2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-945.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.4f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		FilaPostes2.RenderModel();

		//Portal
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Portal.RenderModel();

		//Ominitrix
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(620.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.5f, 5.0f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Omnitrix.RenderModel();

		// subcuadrante 1 -------
		//Pato
		glm::mat4 ModelAuxPato1(1.0);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-360.0f, 5.0f, -305.0f));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		ModelAuxPato1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pato.RenderModel();
		//Pierna delantera derecha
		model = ModelAuxPato1;
		model = glm::translate(model, glm::vec3(-0.04, -0.04, 0.047));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patoPDI.RenderModel();
		//Pierna delantera izquierda
		model = ModelAuxPato1;
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::translate(model, glm::vec3(0.02f, -0.04f, 0.028));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patoPDD.RenderModel();
		//Pierna trasera izquierda
		model = ModelAuxPato1;
		model = glm::translate(model, glm::vec3(0.035, -0.05f, -0.075f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patoPTD.RenderModel();
		//Pierna trasera derecha
		model = ModelAuxPato1;
		model = glm::translate(model, glm::vec3(-0.035, -0.05f, -0.061f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patoPTI.RenderModel();
		
		//Jardinera 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(360.0f, 0.0f, -350.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jardinera.RenderModel();

		//Pinos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(740.0f, 0.0f, -450.0f));
		model = glm::scale(model, glm::vec3(7.3f, 8.3f, 7.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(730.0f, 0.0f, -310.0f));
		model = glm::scale(model, glm::vec3(8.3f, 9.3f, 8.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(520.0f, 0.0f, -450.0f));
		model = glm::scale(model, glm::vec3(6.3f, 8.3f, 6.3f));
		model = glm::rotate(model, 245 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(500.0f, 0.0f, -310.0f));
		model = glm::scale(model, glm::vec3(7.3f, 10.3f, 7.3f));
		model = glm::rotate(model, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.0f, 0.0f, -450.0f));
		model = glm::scale(model, glm::vec3(6.3f, 9.5f, 6.3f));
		model = glm::rotate(model, 40 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.0f, 0.0f, -290.0f));
		model = glm::scale(model, glm::vec3(6.5f, 8.3f, 6.5f));
		model = glm::rotate(model, 75 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		//Banca 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(360.0f, 0.0f, -510.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		//basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(300.5f, 0.0f, -400.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Estatua Bill
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(350.0f, 25.0f, -250.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		estatuaBill.RenderModel();

		//trickster
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(450.0f, 0.0f, -150.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		trickster.RenderModel();
		
		//Flores
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(600.0f, 2.0f, -400.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 152 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor5.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(750.0f, 2.0f, -300.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 62 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 1.0f, -500.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 152 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, 2.0f, -275.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 34 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor4.RenderModel();
		///Terminan subcuadrante 1///

		// subcuadrante 2 --------
		//Jardinera 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-360.0f, 0.0f, -350.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jardinera.RenderModel();

		//Arboles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-730.0f, 0.0f, -400.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, -60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-740.0f, 0.0f, -280.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, -78 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-240.0f, 0.0f, -410.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-240.0f, 0.0f, -310.0f));
		model = glm::scale(model, glm::vec3(6.5f, 6.5f, 6.5f));
		model = glm::rotate(model, -145 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-520.0f, 0.0f, -380.0f));
		model = glm::scale(model, glm::vec3(6.5f, 6.5f, 6.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-520.0f, 0.0f, -260.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, -33 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		//Banca 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-360.0f, 0.0f, -510.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();
		
		//Azmuth
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-360.0f, 10.0f, -512.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Azmuth.RenderModel();

		//Basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.5f, 0.0f, -400.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Flores
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-600.0f, 2.0f, -400.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 142 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor5.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-750.0f, 2.0f, -300.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 42 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, 1.0f, -490.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 192 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor2.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 2.0f, -275.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 48 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor4.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-470.0f, 2.0f, -315.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor1.RenderModel();
		///Termina subcuadrante 2///

		// subcuadrante 3 -------
		//Jardinera 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-360.0f, 0.0f, 350.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jardinera.RenderModel();

		//Pinos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-710.0f, 0.0f, 410.0f));
		model = glm::scale(model, glm::vec3(7.5f, 10.3f, 7.5f));
		model = glm::rotate(model, -104 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-750.0f, 0.0f, 310.0f));
		model = glm::scale(model, glm::vec3(6.5f, 9.5f, 6.5f));
		model = glm::rotate(model, -64 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-520.0f, 0.0f, 450.0f));
		model = glm::scale(model, glm::vec3(6.3f, 8.3f, 6.3f));
		model = glm::rotate(model, -256 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-520.0f, 0.0f, 310.0f));
		model = glm::scale(model, glm::vec3(8.3f, 12.3f, 8.3f));
		model = glm::rotate(model, -148 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 0.0f, 430.0f));
		model = glm::scale(model, glm::vec3(7.0f, 8.5f, 7.0f));
		model = glm::rotate(model, -15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-190.0f, 0.0f, 300.0f));
		model = glm::scale(model, glm::vec3(7.3f, 9.3f, 7.3f));
		model = glm::rotate(model, -107 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinos.RenderModel();

		//Banca 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-360.0f, 0.0f, 510.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		//Basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.5f, 0.0f, 400.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Gompers
		glm::mat4 ModelAuxGompers1(1.0);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-360.0f, 10.0f, 450.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelAuxGompers1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		gompers.RenderModel();
		//Pierna delantera izquierda
		model = ModelAuxGompers1;
		model = glm::translate(model, glm::vec3(-0.2f, -0.75, -0.015));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		gompersPDD.RenderModel();
		//Pierna delantera derecha
		model = ModelAuxGompers1;
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::translate(model, glm::vec3(0.15f, -0.7f, -0.037));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		gompersPDI.RenderModel();
		//Pierna trasera derecha
		model = ModelAuxGompers1;
		model = glm::translate(model, glm::vec3(0.15, -0.65f, 0.855f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		gompersPTD.RenderModel();
		//Pierna trasera izquierda
		model = ModelAuxGompers1;
		model = glm::translate(model, glm::vec3(-0.22, -0.65f, 0.87f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		gompersPTI.RenderModel();

		//Arbustos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-640.0f, -8.0f, 410.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 142 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-725.0f, -4.0f, 285.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 25 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 42 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, -1.0f, 490.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 4 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 192 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, -2.0f, 255.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, -17 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 48 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();
		///Terminan subcuadrante 3///

		// subcuadrante 4 -------
		//Jardinera 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(360.0f, 0.0f, 350.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Jardinera.RenderModel();

		//Arboles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(710.0f, 0.0f, 470.0f));
		model = glm::scale(model, glm::vec3(6.5f, 6.5f, 6.5f));
		model = glm::rotate(model, -15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(720.0f, 0.0f, 310.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 10 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(520.0f, 0.0f, 430.0f));
		model = glm::scale(model, glm::vec3(6.5f, 6.5f, 6.5f));
		model = glm::rotate(model, 109 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(520.0f, 0.0f, 310.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		model = glm::rotate(model, 33 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, 0.0f, 470.0f));
		model = glm::scale(model, glm::vec3(5.3f, 5.3f, 5.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, 0.0f, 310.0f));
		model = glm::scale(model, glm::vec3(5.3f, 6.5f, 5.3f));
		model = glm::rotate(model, 75 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arboles3.RenderModel();

		//Banca 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(360.0f, 0.0f, 510.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banca.RenderModel();

		//basura
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(300.5f, 0.0f, 400.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();

		//Pedestal estatua 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(340.5f, 13.0f, 260.0f));
		model = glm::scale(model, glm::vec3(27.0f, 26.0f, 27.0f));
		modelauxDuff = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		estatua.UseTexture();
		meshList[2]->RenderMesh();
		//Estatua Duff
		model = glm::translate(model, glm::vec3(0.0f, 0.51f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Duff.RenderModel();

		//Arbustos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(640.0f, -8.0f, 420.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 84 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(725.0f, -4.0f, 285.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 25 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 69 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(300.0f, -1.0f, 495.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 4 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 102 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, -2.0f, 275.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 17 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 37 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(510.0f, 2.0f, 265.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 25 * toRadians, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 81 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto.RenderModel();
		///Termina subcuadrante 4///

		//Semaforo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(163.5f, 0.0f, -583.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Semaforo2.RenderModel();

		//Semaforo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-156.5f, 0.0f, 583.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Semaforo2.RenderModel();

		//Semaforo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(920.5f, 0.0f, 160.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Semaforo2.RenderModel();

		//Semaforo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-920.5f, 0.0f, 160.0f));
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Semaforo2.RenderModel();

		//Botes de basura //
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 390.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -390.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bote.RenderModel();
		//Terminan botes de basura//

		//asignacion de la posicion del modelo
		peridotPos = glm::vec3(camera.getCameraPeridotPos().x, camera.getCameraPeridotPos().y, camera.getCameraPeridotPos().z);

		// Calcula el angulo de acuerdo a la direccion que apunta la camara
		float angle = atan2(camera.getCameraDirection().z, camera.getCameraDirection().x);
		
		//Peridot --------------------------------------------------------------------------------------------------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(peridotPos));
		model = glm::scale(model, glm::vec3(1.6f, 1.6f, 1.6f));

		// Calcula la rotación del objeto para que siempre mire hacia donde mira la cámara
		float objectAngle = angle + glm::radians(0.0f);
		model = glm::rotate(model, -objectAngle, glm::vec3(0.0f, 1.0f, 0.0f));

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
		model = glm::rotate(model, -rotPeridotBrazos * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		/*model = glm::rotate(model, -rotPeridotBrazos2 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));*/
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotBrazoDer.RenderModel();
		//Mano derecha
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -0.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotManoDer.RenderModel();
		//Brazo izquierdo
		model = ModelAuxPeridot2;
		model = glm::translate(model, glm::vec3(0.0f, 2.6f, 0.9f));
		model = glm::rotate(model, rotPeridotBrazos * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		/*model = glm::rotate(model, rotPeridotBrazos2 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));*/
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotBrazoIzq.RenderModel();
		//Mano izquierda
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotManoIzq.RenderModel();
		//Pierna derecha
		model = ModelAuxPeridot3;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.35f));
		model = glm::rotate(model, rotPeridotPiernas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		/*model = glm::rotate(model, rotPeridotPiernas2 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));*/
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotPiernaDer.RenderModel();
		//Pie derecho
		model = glm::translate(model, glm::vec3(0.0f, -2.3f, -0.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotPieDer.RenderModel();
		//Pierna izquierda
		model = ModelAuxPeridot4;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.35f));
		model = glm::rotate(model, -rotPeridotPiernas * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		/*model = glm::rotate(model, -rotPeridotPiernas2 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));*/
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotPiernaIzq.RenderModel();
		//Pie izquierdo
		model = glm::translate(model, glm::vec3(0.0f, -2.3f, 0.95f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeridotPieIzq.RenderModel();

		//Carretera -----------------------------------

		//Rustbucket//////
		//Carro posCarroX, posCarroY, posCarroZ
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(posCarroX, posCarroY, posCarroZ));
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

		//DonutVan
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 0.0f, -677.0f));
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
	
		//DX Mark 10 Inicio ///////
		//Carro 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movDX10, 0.2f, movDX10z));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, giroDX10 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.5f, 10.5f, 10.5f));
		modelauxMark10 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen.RenderModel();
		model = modelauxMark10;

		//Llanta delantera derecha
		model = glm::translate(model, glm::vec3(1.4f, 0.7f, 2.7f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen_RuedaDelDer.RenderModel();
		model = modelauxMark10;

		//Llanta delantera izquierda
		model = glm::translate(model, glm::vec3(-1.9f, 0.7f, 2.7f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen_RuedaDelIzq.RenderModel();
		model = modelauxMark10;

		//Llanta trasera derecha
		model = glm::translate(model, glm::vec3(1.4f, 0.7f, -1.7f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen_RuedaTrasDer.RenderModel();
		model = modelauxMark10;

		//Llanta trasera izquierda
		model = glm::translate(model, glm::vec3(-1.9f, 0.7f, -1.7f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheBen_RuedaTrasIzq.RenderModel();
		model = modelauxMark10;
		////////////////-------------------

		//Barreras entre cuadrante 7 y 8 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(998.0f, 0.0f, -938.5f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Barrera.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1058.0f, 0.0f, -938.5f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Barrera.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1118.0f, 0.0f, -938.5f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Barrera.RenderModel();
		//Terminan barreras 
		
		//Barreras entre cuadrante 1 y 2 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-998.0f, 0.0f, 938.5f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Barrera.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1058.0f, 0.0f, 938.5f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Barrera.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1118.0f, 0.0f, 938.5f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Barrera.RenderModel();

		//Barrera RustBucket
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1200.0f, 0.0f, 60.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Barrera.RenderModel();
		//Terminan barreras 

		//Vidrios
		//SrSmoothy------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-680.5, 0.5, -1112.5));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		SrSmoothyVid.RenderModel();
		glDisable(GL_BLEND);

		//La Gran Rosquilla
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(450.0f, 51.0f, -1050.0f));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		LGRVid.RenderModel();
		glDisable(GL_BLEND);

		//Burbujas
		model = ModelBG;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Burbuja.RenderModel();
		glDisable(GL_BLEND);

		model = ModelBB;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Burbuja.RenderModel();
		glDisable(GL_BLEND);

		model = ModelBS;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Burbuja.RenderModel();
		glDisable(GL_BLEND);

		model = ModelBJ;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Burbuja.RenderModel();
		glDisable(GL_BLEND);
		////-----------

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