#pragma once

// C++ Components
#include <vector>
#include <iomanip>

// Namespaces
using namespace std;
using namespace Eigen;

class AssignmentOne
{
public:
	// ------------ Global Variables -------------

private:
	// ------------ Local Variables -------------


	float defMin = 0;
	float defMax = 9;
	float resolution = 0.25;

	float lastY = 1;

	struct Vertex
	{
		float x, y, z;
		float r, g, b;
	};

	vector<Vertex*> funcVertices;

public:
	// ------------ Global Functions -------------
	AssignmentOne() {}

	void GenerateVertices(MatrixXf _coefficients, bool _shouldWriteToConsole = false)
	{
		// Generates and pushes vertices into storage vector with function values
		for (float i = defMin; i <= defMax; i += resolution)
		{
			if (_shouldWriteToConsole)
			{
				// Prints function values for f(x) = y for each value.
				cout << setprecision(3) << "f(" << i << ") = " << f(i, _coefficients) << endl;
			}

			funcVertices.push_back(CreateVertex(i, f(i, _coefficients), 0, resolution, 1, 0));
			funcVertices.push_back(CreateVertex(i+resolution, f(i+resolution, _coefficients), 0, resolution, 1, 0));
		}
	}

	void WriteVerticesToFile(int _numVertexVariables, const char* fileName)
	{
		// takes the funcVertices vector and writes its values into a file.
		// Opens / creates the output file
		ofstream outputFile(fileName);

		if (outputFile.is_open()) {
			// writes the first line, witch is the number of lines in total
			outputFile << funcVertices.size() << "\n";
			// Writes the second line, witch is the number of vertex variables
			outputFile << _numVertexVariables << "\n";

			// Loops through all vertices generated and writes them their own line
			for (auto i = 0; i < funcVertices.size(); i++)
			{
				// There is one rule when writing to file,
				// each number must be followed by a ',' to indicate the number has ended.
				outputFile << "(" << funcVertices[i]->x << ", "
					<< funcVertices[i]->y << ", "
					<< funcVertices[i]->z << ",) "
					<< funcVertices[i]->r << ", "
					<< funcVertices[i]->g << ", "
					<< funcVertices[i]->b << ",\n";
			}
			// closes file when finished
			outputFile.close();
		}
		else {
			cerr << "Error opening file - Assignment 1";
		}
	}

	MatrixXf GenMatrixFrom7xPoints(vector<Vector2f> _points)
	{
		if (_points.empty()) {
			cerr << "Error: Vector of points is empty." << endl;
			return MatrixXf::Zero(7, 3);
		}
		if (_points.size() != 7) {
			cerr << "Error: Incorrect num points." << endl;
			return MatrixXf::Zero(7, 3);
		}

		MatrixXf temp(7, 3);
		for (int i = 0; i < 7; ++i) {
			temp.row(i) << pow(_points[i].x(), 2), _points[i].x(), 1;
		}

		return temp;
	}

	MatrixXf GenMatrixFrom7yPoints(vector<Vector2f> _points)
	{
		if (_points.empty()) {
			cerr << "Error: Vector of points is empty." << endl;
			return MatrixXf::Zero(7, 1);
		}
		if (_points.size() != 7) {
			cerr << "Error: Incorrect num points." << endl;
			return MatrixXf::Zero(7, 1);
		}

		MatrixXf temp(7, 1);
		for (int i = 0; i < 7; ++i) {
			temp.row(i) << _points[i].y();
		}

		return temp;
	}


private:
	// ------------ Local Functions -------------

	Vertex* CreateVertex(float _x, float _y, float _z = 0.0, float _r = 0, float _g = 0, float _b = 0)
	{
		Vertex* newVertex = new Vertex();
		newVertex->x = _x;
		newVertex->y = _y;
		newVertex->z = _z;
		newVertex->r = _r;
		newVertex->g = _g;
		newVertex->b = _b;
		return newVertex;
	}

	float f(float x, MatrixXf coefficients)
	{
		int degree = coefficients.size() - 1;
		float result = 0.0f;

		for (int i = 0; i <= degree; ++i) {
			result += coefficients(i) * pow(x, degree - i);
		}

		if (abs(result) < 0.0001)
			return 0;

		return result;
	}

public:
	// ------------ Getters and Setters -------------


};
