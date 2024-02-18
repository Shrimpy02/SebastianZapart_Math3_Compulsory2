
// GL Components
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C++ specific components
#include "iostream"

// Class includes
#include "Main.h"

int main()
{
	// ------------------- Initialization ------------------- 
	// GLFW
	GLFInitialization();

	// Window
	GLFWwindow* window = initializeWindow("MainScreen");
	if (!window) return -1;

	// GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Faild to initialize GLAD" << std::endl;
		return -1;
	}

	// Shaders
	Shader normalShader("ShaderSourceCode/normalVertexShader.vs", "ShaderSourceCode/normalFragmentShader.fs", &myCamera, SCR_WIDTH, SCR_HEIGHT);

	// Camera
	myCamera.SetMovementMode(FLYING);

	// Geometry
		// -----------------------------------------------
	// CHANGE THIS TO ENUM TO TEST EACH ASSIGNMENT CODE:
	CurrentAssignment = AssignmentOne;
	// -----------------------------------------------
	if (CurrentAssignment == AssignmentOne)
		Graph.Initialize(Graph.generateNormalGeometryFromFile("Assignment1VertexFile.txt"), 6);
	else if (CurrentAssignment == AssignmentTwo)
		Graph.Initialize(Graph.generateNormalGeometryFromFile("Assignment2VertexFile.txt"), 6);
	

	// ------------------- Render loop ------------------- 

	while (!glfwWindowShouldClose(window))
	{
		// ---------- Input ----------
		updateDeltaTime();

		// ProcessInput
		processInput(window);

		// ---------- Rendering options ----------
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ---------- Drawing ----------

		// Rendering
		Graph.drawGraphGeometry(&normalShader, vec3(0.0, 0.0, -3.0), vec3(1, 1, 1));

		// GLFW: swap buffers and process events
		// -------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Graph.~Geometry();

	glfwTerminate();
	return 0;
}
