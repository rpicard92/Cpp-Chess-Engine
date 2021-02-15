// Cpp-Chess-Engine.cpp : Defines the entry point for the application.
//

#include "Cpp-Chess-Engine.h"
#include "Solver.h"
#include "Model.h"

using namespace std;

int main()
{
	Model model = Model();
	Solver solver = Solver();
	model = solver.solve(model, 1, 'w');
	cout << "Hello CMake." << endl;
	return 0;
}
