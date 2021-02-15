﻿// Cpp-Chess-Engine.cpp : Defines the entry point for the application.
//

#include "Cpp-Chess-Engine.h"

using namespace std;

int main()
{
	Model model = Model();
	Solver solver = Solver();
	int test = 1;
	std::pair<Model, int> pair = solver.solve(model, test, 'w');
	cout << "Score: " + std::to_string(pair.second) << endl;
	return 0;
}
