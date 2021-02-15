// Cpp-Chess-Engine.cpp : Defines the entry point for the application.
//

#include "Cpp-Chess-Engine.h"

using namespace std;

int main()
{
	Model model = Model();
	Solver solver = Solver();
	int searchDepth = 5;
	std::pair<Model, int> pair = solver.solve(model, searchDepth, 'w');
	cout << "Score: " + std::to_string(pair.second) << endl;
	return 0;
}
