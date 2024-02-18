
// C++ Components 
#include <iostream>
#include <fstream>

// Eigen Includes
#include <Eigen/Dense>

// Classes
#include "AssignmentOne.h"
#include "AssignmentTwo.h"

// Name spaces
using namespace std;
using namespace Eigen;

int main()
{
	// Pointers to class objects
	shared_ptr<AssignmentOne> AOne = make_shared<AssignmentOne>();
	shared_ptr<AssignmentTwo> ATwo = make_shared<AssignmentTwo>();

	// Assignment 1 ------------------
	cout << "Assignment 1: " << endl;

	// points
	const vector<Vector2f> Points1 = { Vector2f(1,1), Vector2f(2,-0.5) ,Vector2f(3,-1) ,Vector2f(4,-2), Vector2f(5,-1), Vector2f(6,0.5),Vector2f(8,1) };

	// Maths
	MatrixXf A1 = AOne->GenMatrixFrom7xPoints(Points1);
	MatrixXf TransA1 = A1.transpose();
	MatrixXf Y1 = AOne->GenMatrixFrom7yPoints(Points1);
	MatrixXf B1 = TransA1 * A1;
	MatrixXf NegB1 = B1.inverse();
	MatrixXf C1 = TransA1 * Y1;
	MatrixXf X1 = NegB1*C1;
	AOne->GenerateVertices(X1,true);
	AOne->WriteVerticesToFile(6, "Assignment1VertexFile.txt");

	// Printing

	cout << "\n";
	cout << "Matrix A: \n";
	cout << A1 << "\n";
	cout << "\n";

	cout << "Matrix TransA: \n";
	cout << TransA1 << "\n";
	cout << "\n";

	cout << "Matrix Y: \n";
	cout << Y1 << "\n";
	cout << "\n";

	cout << "Matrix B: \n";
	cout << B1 << "\n";
	cout << "\n";

	cout << "Matrix NegB: \n";
	cout << NegB1 << "\n";
	cout << "\n";

	cout << "Matrix C: \n";
	cout << C1 << "\n";
	cout << "\n";

	cout << "Matrix X: \n";
	cout << X1 << "\n";
	cout << "\n";

	cout << "Interpolation function based on X: \n";
	cout << " + (" << X1(0, 0) << " * x^2) + (" << X1(1, 0) << " * x) + (" << X1(2, 0) << ")\n";
	cout << "\n";

	cout << endl;
	cout << endl;

	// Assignment 2 ------------------
	cout << "Assignment 2: " << endl;

	// points
	const vector<Vector2f> Points2 = {Vector2f(1,5), Vector2f(3,-2) ,Vector2f(4,0) ,Vector2f(5,1) };

	// Maths
	MatrixXf A2 = ATwo->GenMatrixFrom4xPoints(Points2);
	MatrixXf NegA2 = A2.inverse();
	MatrixXf Y2 = ATwo->GenMatrixFrom4yPoints(Points2);
	MatrixXf X2 = NegA2 * Y2;
	ATwo->GenerateVertices(X2);
	ATwo->WriteVerticesToFile(6, "Assignment2VertexFile.txt");

	// Printing
	cout << "\n";
	cout << "Matrix A: \n";
	cout << A2 << "\n";
	cout << "\n";

	cout << "Matrix NegA: \n";
	cout << NegA2 << "\n";
	cout << "\n";

	cout << "Matrix Y: \n";
	cout << Y2 << "\n";
	cout << "\n";

	cout << "Matrix X: \n";
	cout << X2 << "\n";
	cout << "\n";

	cout << "Interpolation function based on X: \n";
	cout << " + (" << X2(0, 0) << " * x^3) + (" << X2(1, 0) << " * x^2) + (" << X2(2, 0) << " * x) + (" << X2(3, 0) << ")\n";
	cout << "\n";

	cout << endl;
	cout << endl;

	return 0;
}
