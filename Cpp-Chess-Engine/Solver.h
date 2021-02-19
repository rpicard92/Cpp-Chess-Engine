#pragma once

#include <vector>
#include "Model.h"

class Solver {

	public:
	
		Solver();
		~Solver();

		struct ModelScorePair {
			ModelScorePair() {

			}

			~ModelScorePair() {

			};
			Model model;
			int score;
		};

		virtual ModelScorePair solve(Model, int, char);

		virtual ModelScorePair dfsAlphaBeta(Model, int, bool, char);

		virtual ModelScorePair evaluate(Model , char);

		virtual char flipTurn(char);

		const int NEGATIVE_INFINITY = -1000000;
		const int POSITIVE_INFINITY = 1000000;

		// TODO: figure out how to pull these from Model.h
		const char BLACK = 'b';
		const char WHITE = 'w';

};