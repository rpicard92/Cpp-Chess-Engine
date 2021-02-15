#pragma once

#include <vector>
#include "Model.h"

class Solver {

	public:
	
		Solver();
		~Solver();

		virtual std::pair<Model, int>  solve(Model, int, char);

		virtual std::pair<Model, int> dfsAlphaBeta(Model, int, bool, char);

		virtual std::pair<Model, int> evaluate(Model model, char);

		virtual char flipTurn(char);

		const int NEGATIVE_INFINITY = -1000000;
		const int POSITIVE_INFINITY = 1000000;

		// TODO: figure out how to pull these from Model.h
		const char BLACK = 'b';
		const char WHITE = 'w';

};