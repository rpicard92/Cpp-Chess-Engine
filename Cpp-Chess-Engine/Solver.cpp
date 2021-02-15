#include <vector>;
#include "Model.h"

class Solver {

	public:

		Solver() {

		}

		~Solver() {

		}

		std::pair<Model, int> solve(Model model, int depth, char playerColor) {
			return dfsAlphaBeta(model, depth, true, playerColor);
		}

	private:

		const int NEGATIVE_INFINITY = -1000000;
		const int POSITIVE_INFINITY = 1000000;

		// TODO: figure out how to pull these from Model.h
		const char BLACK = 'b';
		const char WHITE = 'w';

		char flipTurn(char playerColor) {
			if (playerColor == WHITE) {
				return BLACK;
			}
			else {
				return WHITE;
			}
		}

		std::pair<Model, int> evaluate(Model model, char playerColor) {
			std::pair<Model, int> evaluation = {model, model.getScore(playerColor)};
			return evaluation;
		}


		std::pair<Model, int> dfsAlphaBeta(Model model, int depth, bool maximizingPlayer, char playerColor) {
			if (depth == 0) {
				return evaluate(model, playerColor);
			}
			else if (maximizingPlayer == true) {
				int maximumEvalution = NEGATIVE_INFINITY;
				std::vector<Model> validMoves = model.getValidMoves();
				for (Model validMove : validMoves) {
					std::pair<Model, int> currentEvalution = dfsAlphaBeta(validMove, depth - 1, false, flipTurn(playerColor));
					maximumEvalution = std::max(maximumEvalution, currentEvalution.second);
				}
			}
			else {
				int minimumEvaluation = POSITIVE_INFINITY;
				std::vector<Model> validMoves = model.getValidMoves();
				for (Model validMove : validMoves) {
					std::pair<Model, int> currentEvalution = dfsAlphaBeta(validMove, depth - 1, true, flipTurn(playerColor));
					minimumEvaluation = std::min(minimumEvaluation, currentEvalution.second);
				}
			}
		}



};
