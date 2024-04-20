#include "Camera.h"
#include "Window.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(int cameraID, bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
	glm::vec3 moveXY = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

	//Camara en 3ra persona
	if (cameraID == 1.0f) {
		if (keys[GLFW_KEY_W])
		{
			position += moveXY * velocity;
		}

		if (keys[GLFW_KEY_S])
		{
			position -= moveXY * velocity;
		}

		if (keys[GLFW_KEY_A])
		{
			position -= right * velocity;
		}

		if (keys[GLFW_KEY_D])
		{
			position += right * velocity;
		}
	//Camara aerea
	}else if (cameraID == 2.0f) {
		if (keys[GLFW_KEY_W])
		{
			position += moveXY * velocity;
		}

		if (keys[GLFW_KEY_S])
		{
			position -= moveXY * velocity;
		}

		if (keys[GLFW_KEY_A])
		{
			position -= right * velocity;
		}

		if (keys[GLFW_KEY_D])
		{
			position += right * velocity;
		}
		//Para bajar y subir la cámara
		if (keys[GLFW_KEY_LEFT_SHIFT]) {
			if (position.y > 500) {
				position.y -= velocity; // La cámara baja
			}
		}
		if (keys[GLFW_KEY_SPACE]) {
			if (position.y < 1000) {
				position.y += velocity; // La cámara sube
			}
		}
	//Camara en libre
	}else {
		if (keys[GLFW_KEY_W])
		{
			position += front * velocity;
		}

		if (keys[GLFW_KEY_S])
		{
			position -= front * velocity;
		}

		if (keys[GLFW_KEY_A])
		{
			position -= right * velocity;
		}

		if (keys[GLFW_KEY_D])
		{
			position += right * velocity;
		}
	}
	
}

void Camera::mouseControl(int cameraID,  GLfloat xChange, GLfloat yChange)
{
	//Camara en 3ra persona
	if (cameraID == 1.0f) {
		xChange *= turnSpeed;
		yChange *= turnSpeed;

		yaw += xChange;
		pitch += yChange;

		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}

		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
	//Camara aerea
	}else if (cameraID == 2.0f) {
		xChange *= turnSpeed;

		yaw += xChange;

	//Camara en libre
	}else {
		xChange *= turnSpeed;
		yChange *= turnSpeed;

		yaw += xChange;
		pitch += yChange;

		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}

		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
