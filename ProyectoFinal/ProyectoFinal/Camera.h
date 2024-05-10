#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed, glm::vec3 Prueba);

	void keyControl(int cameraID, bool* keys, GLfloat deltaTime, glm::vec3 objectPosition);
	void mouseControl(int cameraID, GLfloat xChange, GLfloat yChange, glm::vec3 objectPosition);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraPeridotPos();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::vec3 Pos;
	int ID;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
};

