#pragma once

#include <vector>;
#include "Model.h"

class Solver {

	public:
	
		Solver();
		~Solver();

		virtual Model solve(Model, int);

	private:

		virtual private Model dfsAlphaBeta(Model, int, int);

		private int evaluate(Model model);

		private std::vector<Model> findValideMoves(Model model);

};