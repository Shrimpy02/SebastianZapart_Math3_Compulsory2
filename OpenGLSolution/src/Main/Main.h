#pragma once

// Class includes
#include "Shader.h"
#include "Camera.h"
#include "Geometry.h"
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h" // Image loader file

enum Assignment { AssignmentOne, AssignmentTwo };


// ------------------- Global Variable`s ------------------- 
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

double deltaTime = 0.0;
double lastFrame = 0.0;

// Bool`s
bool firstMouse = true;
Assignment CurrentAssignment = AssignmentOne;


// Object`s
Camera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));\
Geometry Graph;

// ------------------- Function`s -------------------

// Calculations`s

inline void updateDeltaTime()
{
	// Calculate`s the delta time between each frame
	// for a smooth and constant user experience
	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

}

// Callback`s

inline void mouse_callback(GLFWwindow* window, double _xPos, double _yPos)
{
	float xpos = static_cast<float>(_xPos);
	float ypos = static_cast<float>(_yPos);

	// First move check makes sure camera does not jerk on first mouse movement
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	myCamera.ProcessMouseMovement(xoffset, yoffset);
}

inline void scroll_callback(GLFWwindow* window, double _xOffset, double _yOffset)
{
	myCamera.ProcessMouseScroll(static_cast<float>(_yOffset));
}

inline void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Callback to glViewport called each frame for dynamic window re-sizing. 
	glViewport(0, 0, width, height);
}

// Input processing 

inline void processInput(GLFWwindow* window)
{

	// GLFW input management
	// -------------------------

	// Usability
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Camera Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		myCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		myCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		myCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		myCamera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		myCamera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		myCamera.ProcessKeyboard(DOWN, deltaTime);
}

// Initialization`s

inline void initializeCallbacks(GLFWwindow* _window)
{
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glfwSetCursorPosCallback(_window, mouse_callback);
	glfwSetScrollCallback(_window, scroll_callback);
}

inline GLFWwindow* initializeWindow(const char* _windowName)
{
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, _windowName, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	initializeCallbacks(window);

	return window;
}

inline void GLFInitialization()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}