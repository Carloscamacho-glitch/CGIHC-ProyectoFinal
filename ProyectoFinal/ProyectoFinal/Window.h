#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLfloat getarregloluz() { return arregloluz; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLfloat getarticulacionllantas() { return articulacionllantas; }
	GLfloat getdesplazamiento() { return desplazamiento; }
	//Agregado ejercicio1 de clase  P8
	GLboolean getlampara() { return lampara; }

	//ejercicio 02 P8 
	GLfloat getFaro() { return bandera; }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat articulacionllantas, desplazamiento,arregloluz, bandera;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	//Agregado ejercicio 8
	GLboolean lampara = true;
	//
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

