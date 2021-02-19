#include <vector>
#include "Model.h"
#include "Solver.h"

Solver::Solver() {

}

Solver::~Solver() {

}

Solver::ModelScorePair Solver::solve(Model model, int depth, char playerColor) {
	Solver::ModelScorePair pair = dfsAlphaBeta(model, depth, true, playerColor);
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
Solver::ModelScorePair Solver::evaluate(Model model, char playerColor) {
	Solver::ModelScorePair evaluation;
	evaluation.model = model;
	evaluation.score = model.getScore(playerColor);
	return evaluation;
}

Solver::ModelScorePair Solver::dfsAlphaBeta(Model model, int depth, bool maximizingPlayer, char playerColor) {
	if (depth == 0) {
		return evaluate(model, playerColor);
	}
	else if (maximizingPlayer == true) {
		Solver::ModelScorePair  maximumEvalution;
		maximumEvalution.model = model;
		maximumEvalution.score = NEGATIVE_INFINITY;
		std::vector<Model> validMoves = model.getValidMoves();
		for (Model validMove : validMoves) {
			Solver::ModelScorePair  currentEvalution = dfsAlphaBeta(validMove, depth - 1, false, flipTurn(playerColor));
			if (currentEvalution.score > maximumEvalution.score) {
				maximumEvalution = currentEvalution;
			} 
		}
		return maximumEvalution;
	}
	else {
		Solver::ModelScorePair  minimumEvaluation;
		minimumEvaluation.model = model;
		minimumEvaluation.score = POSITIVE_INFINITY;
		std::vector<Model> validMoves = model.getValidMoves();
		for (Model validMove : validMoves) {
			Solver::ModelScorePair currentEvalution = dfsAlphaBeta(validMove, depth - 1, true, flipTurn(playerColor));
			if (currentEvalution.score < minimumEvaluation.score) {
				minimumEvaluation = currentEvalution; // TODO: Start here, note this is std::pair is not copyable if one of the asignment is not copiable.
			}
		}
		return minimumEvaluation;
	}
}


