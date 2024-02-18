#ifndef CAMERA_H
#define CAMERA_H

// GL Components
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Namespaces
using namespace glm;

// Enums
enum Movement_Mode
{
	WALKING,
    FLYING
};

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:

	// ---------- Constants --------------
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

	// Euler Angles
    float Yaw;
    float Pitch;

	// Camera Variables
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Default Enums
    Movement_Mode ActiveMovementMode = FLYING;

    // ---------- Constructors --------------

    // Constructor with vectors
	Camera(vec3 _position = vec3(0.0f,0.0f,0.0f), vec3 _up = vec3(0.0f,1.0f,0.0f), float _yaw = YAW, float _pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
        Position = _position;
        WorldUp = _up;
        Yaw = _yaw;
        Pitch = _pitch;
        updateCameraVectors();
	}

    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

	// ---------- Global Functions --------------

    mat4 GetViewMatrix()
	{
        return glm::lookAt(Position, Position + Front, Up);
	}

    // Process inputs
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;

		if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;

        if (ActiveMovementMode == FLYING)
        {
            if (direction == UP)
                Position += Up * velocity;
            if (direction == DOWN)
                Position -= Up * velocity;
        }
    }

    void ProcessMouseMovement(float _xOffset, float _yOffset, GLboolean _constrainPitch = true)
    {
        _xOffset *= MouseSensitivity;
        _yOffset *= MouseSensitivity;

        Yaw += _xOffset;
        Pitch += _yOffset;

        // make sure that pitch stays in bounds
        if (_constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(float _yOffset)
    {
        Zoom -= (float) _yOffset;

        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:

    // ---------- Local Functions --------------

	void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

		// Re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp)); 
        Up = glm::normalize(glm::cross(Right, Front));
    }

public:

	// ---------- Setters and Getters --------------

    void SetMovementMode(Movement_Mode _moveMode)
    {
        ActiveMovementMode = _moveMode;
    }
};

#endif
