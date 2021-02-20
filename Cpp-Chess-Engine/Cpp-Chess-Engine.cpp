// Cpp-Chess-Engine.cpp : Defines the entry point for the application.
//

#include "Cpp-Chess-Engine.h"
#include "Model.h"
#include "Solver.h"

using namespace std;

int main()
{
	Model model = Model();
	Solver solver = Solver();
	int searchDepth = 1;
	Solver::ModelScorePair pair = solver.solve(model, searchDepth, 'w');
	cout << "Score: " + std::to_string(pair.score) << endl << endl;
	pair.model.printBoard();
	return 0;
}
