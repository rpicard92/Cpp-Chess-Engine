#pragma once

#include <vector>;
#include "Model.h"

class Solver {

	public:
	
		Solver();
		~Solver();

		virtual Model solve(Model, int);

	private:

		virtual Model dfsAlphaBeta(Model, int, int);

		virtual int evaluate(Model model);

		vitural std::vector<Model> findValideMoves(Model model);

};