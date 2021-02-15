#include <vector>
#include "Model.h"
#include "Solver.h"

Solver::Solver() {

}

Solver::~Solver() {

}

std::pair<Model, int>  Solver::solve(Model model, int depth, char playerColor) {
	return dfsAlphaBeta(model, depth, true, playerColor);
}


char Solver::flipTurn(char playerColor) {
	if (playerColor == WHITE) {
		return BLACK;
	}
	else {
		return WHITE;
	}
}

std::pair<Model, int> Solver::evaluate(Model model, char playerColor) {
	std::pair<Model, int> evaluation = {model, model.getScore(playerColor)};
	return evaluation;
}


std::pair<Model, int> Solver::dfsAlphaBeta(Model model, int depth, bool maximizingPlayer, char playerColor) {
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


