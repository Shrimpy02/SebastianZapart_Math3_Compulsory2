#ifndef SHADER_H
#define SHADER_H

// GL Components
#include <glad/glad.h>

// C++ Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Class includes
#include "Camera.h"

// NameSpaces
using namespace std;
using namespace glm;

enum perspectiveMode
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class Shader
{
private:

	Camera* myCamera;
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;

public:

	// ---------- Global Constants --------------
	unsigned int ID;
	perspectiveMode activePerspectiveMode = PERSPECTIVE;

	// ---------- Constructors --------------
	Shader(const char* _vertexPath, const char* _fragmentPath, Camera* _camera,unsigned int _SCR_WIDTH, unsigned int _SCR_HEIGHT)
	{
		// Reads, compiles and links the Shader`s
		// --------------------------
		linkShaders(CreateVertexShader(_vertexPath), 
					CreateFragmentShader(_fragmentPath));

		glEnable(GL_DEPTH_TEST);

		myCamera = _camera;
		SCR_WIDTH = _SCR_WIDTH;
		SCR_HEIGHT = _SCR_HEIGHT;
	}

	// ---------- Global functions --------------

	void use()
	{
		glUseProgram(ID);
	}

	void setBool(const string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void setInt(const string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setfloat(const string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setVec3(const string& name, glm::vec3 vec) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()),1, &vec[0]);
	}

	void setMat4(const string& name, glm::mat4 mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void processTransformations(vec3 positionOffset = vec3(0.0f,0.0f,0.0f), vec3 scaleOffset = vec3(1.0f,1.0f,1.0f), float rotationInDegreesOffset = 0, vec3 rotationAxis = vec3(1.0f, 1.0f, 1.0f)) const
	{
		// Projection Matrix ----------------------------------
		mat4 projection = mat4(1.0f);
		if (activePerspectiveMode == PERSPECTIVE)
			projection = perspective(radians(myCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		else if(activePerspectiveMode == ORTHOGRAPHIC)
			projection = ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, 0.1f, 100.0f);

		setMat4("projection", projection);

		// View Matrix ----------------------------------
		mat4 view = myCamera->GetViewMatrix();
		setMat4("view", view);

		// Model Matrix ----------------------------------
		mat4 model = mat4(1.0f);

		model = translate(model, positionOffset);
		model = scale(model, scaleOffset);
		model = rotate(model, radians(rotationInDegreesOffset), rotationAxis);

		setMat4("model", model);

		// Normal Matrix ---------------------------------
		// very inneficient to tick inverse calulations!
	}


	// ---------- Local functions --------------
private:

	unsigned int CreateVertexShader( const char* _vertexPath)
	{
		// Reading Shader Source Code
		// --------------------------
		ifstream vShaderFile;
		stringstream vShaderStream;
		string vertexCode;

		// Checking exception rights
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

		// Reading shader source code from file
		try
		{
			// open files
			vShaderFile.open(_vertexPath);

			// read the files content into streams
			vShaderStream << vShaderFile.rdbuf();

			// close files
			vShaderFile.close();

			// convert stream into string
			vertexCode = vShaderStream.str();
		}
		catch (ifstream::failure e)
		{
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		
		// Vertex Shader
		// --------------------------
		unsigned int vertex;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		// Error Handling
		int success;
		char infoLog[512];
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}

		return vertex;
	}

	unsigned int CreateFragmentShader(const char* _fragmentPath)
	{
		// Reading Fragment source code
		// --------------------------
		ifstream fShaderFile;
		stringstream fShaderStream;
		string fragmentCode;

		// Checking exception rights
		fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

		// Reading shader source code from file
		try
		{
			// open files
			fShaderFile.open(_fragmentPath);

			// read the files content into streams
			fShaderStream << fShaderFile.rdbuf();

			// close files
			fShaderFile.close();

			// convert stream into string
			fragmentCode = fShaderStream.str();
		}
		catch (ifstream::failure e)
		{
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		}

		const char* fShaderCode = fragmentCode.c_str();


		// Vertex Shader
		// --------------------------
		unsigned int fragment;
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		// Error Handling
		int success;
		char infoLog[512];
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}

		return fragment;
	}

	void linkShaders(unsigned int _vertex, unsigned int _fragment)
	{
		// Linking Shader`s
		// --------------------------
		ID = glCreateProgram();
		glAttachShader(ID, _vertex);
		glAttachShader(ID, _fragment);
		glLinkProgram(ID);

		// Error Handling
		// -------------------------
		int success;
		char infoLog[512];
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}

		// Deleting Shader`s
		// --------------------------
		glDeleteShader(_vertex);
		glDeleteShader(_fragment);
	}

public:
	// ---------- Getters and setters --------------

	void SetPerspectiveMode(perspectiveMode _perspectiveMode)
	{
		activePerspectiveMode = _perspectiveMode;
	}

};

#endif