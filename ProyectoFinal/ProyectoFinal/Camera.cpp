#include "Camera.h"
#include "Window.h"

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed, glm::vec3 PeridotPos)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	Pos = PeridotPos;

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(int cameraID, bool* keys, GLfloat deltaTime, glm::vec3 objectPosition)
{
	GLfloat velocity = moveSpeed * deltaTime;
	glm::vec3 movXZ = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

	//Camara en 3ra persona
	if (cameraID == 1) {
		if (keys[GLFW_KEY_W])
		{
			Pos += movXZ * velocity;
		}
		if (keys[GLFW_KEY_S])
		{
			Pos -= movXZ * velocity;
		}
		if (keys[GLFW_KEY_A])
		{
			Pos -= right * velocity;
		}
		if (keys[GLFW_KEY_D])
		{
			Pos += right * velocity;
		}
		//Camara aerea
	}
	else if (cameraID == 2.0f) {
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
	}

}

void Camera::mouseControl(int cameraID, GLfloat xChange, GLfloat yChange, glm::vec3 objectPosition)
{
	//Camara en 3ra persona
	if (cameraID == 1.0f) {
		xChange *= turnSpeed;
		yChange *= turnSpeed;

		// Actualizar los ángulos de yaw y pitch
		yaw += xChange;
		pitch += yChange;

		// Limitar el ángulo de pitch entre -89 y 89 grados
		if (pitch > 14.0f)
		{
			pitch = 14.0f;
		}
		if (pitch < -34.0f)
		{
			pitch = -34.0f;
		}

		// Calcular la nueva posición de la cámara alrededor del objeto
		// Considerando una distancia constante de 30 unidades
		glm::vec3 newPosition;
		newPosition.x = objectPosition.x - 30.0f * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		newPosition.y = objectPosition.y - 30.0f * sin(glm::radians(pitch));
		newPosition.z = objectPosition.z - 30.0f * sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		// Actualizar la posición de la cámara
		position.x = newPosition.x;
		position.y = newPosition.y + 13;
		position.z = newPosition.z;
		//Camara aerea
	}
	else if (cameraID == 2.0f) {

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

glm::vec3 Camera::getCameraPeridotPos()
{
	return Pos;
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
