#include <vector>;
#include "Model.h"

class Solver {

	public:

		Solver() {

		}


		~Solver() {

		}


		std::pair<Model, int> solve(Model model, int depth) {
			return dfsAlphaBeta(model, depth, true);
		}

	private:

		const int NEGATIVE_INFINITY = -1000000;
		const int POSITIVE_INFINITY = 1000000;

		std::pair<Model, int> dfsAlphaBeta(Model model, int depth, int maximizingPlayer) {
			if (depth == 0) {
				return evaluate(model);
			}
			else if (maximizingPlayer == true) {
				int maximumEvalution = NEGATIVE_INFINITY;
				std::vector<Model> validMoves = model.getValidMoves();
				for (Model validMove : validMoves) {
					std::pair<Model, int> currentEvalution = dfsAlphaBeta(validMove, depth - 1, false);
					maximumEvalution = std::max(maximumEvalution, currentEvalution.second);
				}
			}
			else {
				int minimumEvaluation = POSITIVE_INFINITY;
				std::vector<Model> validMoves = model.getValidMoves();
				for (Model validMove : validMoves) {
					std::pair<Model, int> currentEvalution = dfsAlphaBeta(validMove, depth - 1, true);
					minimumEvaluation = std::min(minimumEvaluation, currentEvalution.second);
				}
			}
		}



};
