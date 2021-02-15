#include <vector>
#include "Model.h"
#include "Solver.h"

Solver::Solver() {

}

Solver::~Solver() {

}

std::pair<Model, int>  Solver::solve(Model model, int depth, char playerColor) {
	std::pair<Model, int> pair = dfsAlphaBeta(model, depth, true, playerColor);
	return pair;
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
		std::pair<Model, int>  maximumEvalution = { model, NEGATIVE_INFINITY };
		std::vector<Model> validMoves = model.getValidMoves();
		for (Model validMove : validMoves) {
			std::pair<Model, int> currentEvalution = dfsAlphaBeta(validMove, depth - 1, false, flipTurn(playerColor));
			if (currentEvalution.second > maximumEvalution.second) {
				maximumEvalution = currentEvalution; // TODO: Start here, note this is std::pair is not copyable if one of the asignment is not copiable.
			}
		}
		return maximumEvalution;
	}
	else {
		std::pair<Model, int>  minimumEvaluation = { model, POSITIVE_INFINITY };
		std::vector<Model> validMoves = model.getValidMoves();
		for (Model validMove : validMoves) {
			std::pair<Model, int> currentEvalution = dfsAlphaBeta(validMove, depth - 1, true, flipTurn(playerColor));
			if (currentEvalution.second < minimumEvaluation.second) {
				minimumEvaluation = currentEvalution; // TODO: Start here, note this is std::pair is not copyable if one of the asignment is not copiable.
			}
		}
		return minimumEvaluation;
	}
}


