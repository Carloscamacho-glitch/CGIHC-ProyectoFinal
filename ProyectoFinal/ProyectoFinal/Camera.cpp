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
	glm::vec3 movXZ = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

	//Camara en 3ra persona
	if (cameraID == 1.0f) {
		if (keys[GLFW_KEY_W])
		{
			position += movXZ * velocity;
		}

		if (keys[GLFW_KEY_S])
		{
			position -= movXZ * velocity;
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
		if (keys[GLFW_KEY_W] && position.z >= -1070.0f)
		{
			position += movXZ * velocity;
		}

		if (keys[GLFW_KEY_S] && 1070.0f >= position.z)
		{
			position -= movXZ * velocity;
		}

		if (keys[GLFW_KEY_A] && position.x >= -1302.0f)
		{
			position -= right * velocity;
		}

		if (keys[GLFW_KEY_D] && 1302.0f >= position.x)
		{
			position += right * velocity;
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
