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
	GLfloat getCamara() { return Camara; }
	GLfloat getLucesspot() { return Lucesspot; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	//Transformacion
	GLfloat getAlien1() { return Alien1; }
	GLfloat getAlien2() { return Alien2; }
	GLfloat getDestransformar() { return Destransformar; }

	~Window();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLfloat Camara, Lucesspot;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	//Transformacion
	GLfloat Alien1, Alien2, Destransformar;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

