#pragma once

#include <vector>
#include "Model.h"

class Solver {

	public:
	
		Solver();
		~Solver();

		virtual Model solve(Model, int, char);

		virtual Model dfsAlphaBeta(Model, int, bool, char);

		virtual int evaluate(Model model, char);


};