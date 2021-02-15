
#include <string>;
#include <vector>;
#include <map>;

class Model {

public:

	Model() {
		board = {
			{"br",8,1},{"bk",8,2},{"bb",8,3},{"bq",8,4},{"b!",8,5},{"bb",8,6},{"bk",8,7},{"br",8,8},
			{"bp",7,1},{"bp",7,2},{"bp",7,3},{"bp",7,4},{"bp",7,5},{"bm",7,6},{"bp",7,7},{"bp",7,8},
			{EMPT,6,1},{EMPT,6,2},{EMPT,6,3},{EMPT,6,4},{EMPT,6,5},{EMPT,6,6},{EMPT,6,7},{EMPT,6,8},
			{EMPT,5,1},{EMPT,5,2},{EMPT,5,3},{EMPT,5,4},{EMPT,5,5},{EMPT,5,6},{EMPT,5,7},{EMPT,5,8},
			{EMPT,4,1},{EMPT,4,2},{EMPT,4,3},{EMPT,4,4},{EMPT,4,5},{EMPT,4,6},{EMPT,4,7},{EMPT,4,8},
			{EMPT,3,1},{EMPT,3,2},{EMPT,3,3},{EMPT,3,4},{EMPT,3,5},{EMPT,3,6},{EMPT,3,7},{EMPT,3,8},
			{"wp",2,1},{"wp",2,2},{"wp",2,3},{"wp",2,4},{"wp",2,5},{"wp",2,6},{"wp",2,7},{"wp",2,8},
			{"wr",1,1},{"wk",1,2},{"wb",1,3},{"wq",1,4},{"w!",1,5},{"wb",1,6},{"wk",1,7},{"wr",1,8}
		};

		pieceValues = {
			{"br",5},{"bk",3},{"bb",3},{"bq",9},{"b!",0},
			{"bp",1},
			{EMPT,0},
			{"wp",1},
			{"wr",5},{"wk",3},{"wb",3},{"wq",9},{"w!",0}
		};
	}

	~Model() {

	}

	std::vector<Model> getValidMoves() {
		std::vector<Model> models;
		for (std::tuple<std::string, int, int> piece : board) {
			if (isPiece(piece)) {
				std::vector<std::tuple<std::string, int, int>> moves = getPieceMoves(piece);
				// TODO: finish hear!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				std::vector<Model> generatedModels = generatEMPTodels(moves);
				for (Model generatedModel : generatedModels) {
					models.push_back(generatedModel);
				}
			}
		}
		return models;
	}


	bool isPiece(std::tuple<std::string, int, int> piece) {
		if (std::get<0>(piece) != EMPT) {
			return true;
		}
		else {
			return false;
		}
	}

	std::vector<Model> generatEMPTodels(std::vector<std::tuple<std::string, int, int>> moves) {
		std::vector<Model> models;
		for (std::tuple<std::string, int, int> move : moves) {
			Model model = Model();
			model.movePieceToLocation(std::get<0>(move), std::get<1>(move), std::get<2>(move));
			models.push_back(model);
		}
		return models;
	}

	std::vector<std::tuple<std::string, int, int>> getPieceMoves(std::tuple<std::string, int, int> piece) {
		char pieceType = getPieceType(piece);
		if (pieceType == 'p') {
			return getPawnMoves(piece);
		}
		else if (pieceType == 'r') {
			return getRookMoves(piece);
		}
		else if (pieceType == 'k') {
			return getKnightMoves(piece);
		}
		else if (pieceType == 'b') {
			return getBishopMoves(piece);
		}
		else if (pieceType == 'q') {
			return getQueenMoves(piece);
		}
		else if (pieceType == '!') {
			return getKingMoves(piece);
		}
	};

	char getPieceType(std::tuple<std::string, int, int> piece) {
		std::string pieceType = std::get<0>(piece);
		return pieceType[1];
	}

	// TODO: Account for EMPTpassant, which required a tEMPTporal aspect
	std::vector<std::tuple<std::string, int, int>> getPawnMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			if (!hasPiece(row + 1, column) && isOnBoard(row + 1, column)) {
				moves.push_back({ pieceColorAndType, row + 1, column });
			}
			if (!hasPiece(row + 2, column) && !hasPiece(row + 1, column) && isOnBoard(row + 2, column)) { // tranistive property captured
				moves.push_back({ pieceColorAndType, row + 2, column });
			}
			if (hasBlackPiece(row + 1, column + 1) && isOnBoard(row + 1, column + 1)) {
				moves.push_back({ pieceColorAndType, row + 1, column + 1 });
			}
			if (hasBlackPiece(row + 1, column - 1) && isOnBoard(row + 1, column - 1)) {
				moves.push_back({ pieceColorAndType, row + 1, column - 1 });
			}
		}
		else if (pieceColor == BLACK) {
			if (!hasPiece(row - 1, column) && isOnBoard(row - 1, column)) {
				moves.push_back({ pieceColorAndType, row - 1, column });
			}
			if (!hasPiece(row - 2, column) && !hasPiece(row - 1, column) && isOnBoard(row - 2, column)) { // tranistive property captured
				moves.push_back({ pieceColorAndType, row - 2, column });
			}
			if (hasWhitePiece(row - 1, column + 1) && isOnBoard(row + 1, column) && isOnBoard(row - 1, column + 1)) {
				moves.push_back({ pieceColorAndType, row - 1, column + 1 });
			}
			if (hasWhitePiece(row - 1, column - 1) && isOnBoard(row + 1, column) && isOnBoard(row - 1, column) + 1) {
				moves.push_back({ pieceColorAndType, row - 1, column - 1 });
			}
		}
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> getKnightMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			// upper right quadrant
			if ((!hasPiece(row + 1, column + 2) || hasBlackPiece(row + 1, column + 2)) && isOnBoard(row + 1, column + 2)) {
				moves.push_back({ pieceColorAndType, row + 1, column + 2 });
			}
			if ((!hasPiece(row + 2, column + 1) || hasBlackPiece(row + 2, column + 1)) && isOnBoard(row + 2, column + 1)) {
				moves.push_back({ pieceColorAndType, row + 2, column + 1 });
			}
			// upper left quadrant
			if ((!hasPiece(row + 1, column - 2) || hasBlackPiece(row + 1, column - 2)) && isOnBoard(row + 1, column - 2)) {
				moves.push_back({ pieceColorAndType, row + 1, column - 2 });
			}
			if ((!hasPiece(row + 2, column - 1) || hasBlackPiece(row + 2, column - 1)) && isOnBoard(row + 2, column - 1)) {
				moves.push_back({ pieceColorAndType, row + 2, column - 1 });
			}
			// lower left quadrant
			if ((!hasPiece(row - 1, column - 2) || hasBlackPiece(row - 1, column - 2)) && isOnBoard(row - 1, column - 2)) {
				moves.push_back({ pieceColorAndType, row - 1, column - 2 });
			}
			if ((!hasPiece(row - 2, column - 1) || hasBlackPiece(row - 2, column - 1)) && isOnBoard(row - 2, column - 1)) {
				moves.push_back({ pieceColorAndType, row - 2, column - 1 });
			}
			// lower right quadrant
			if ((!hasPiece(row - 1, column + 2) || hasBlackPiece(row - 1, column + 2)) && isOnBoard(row - 1, column + 2)) {
				moves.push_back({ pieceColorAndType, row - 1, column + 2 });
			}
			if ((!hasPiece(row - 2, column + 1) || hasBlackPiece(row - 2, column + 1)) && isOnBoard(row - 2, column + 1)) {
				moves.push_back({ pieceColorAndType, row - 2, column + 1 });
			}
		}
		else if (pieceColor == BLACK) {
			// upper right quadrant
			if ((!hasPiece(row + 1, column + 2) || hasWhitePiece(row + 1, column + 2)) && isOnBoard(row + 1, column + 2)) {
				moves.push_back({ pieceColorAndType, row + 1, column + 2 });
			}
			if ((!hasPiece(row + 2, column + 1) || hasWhitePiece(row + 2, column + 1)) && isOnBoard(row + 2, column + 1)) {
				moves.push_back({ pieceColorAndType, row + 2, column + 1 });
			}
			// upper left quadrant
			if ((!hasPiece(row + 1, column - 2) || hasWhitePiece(row + 1, column - 2)) && isOnBoard(row + 1, column - 2)) {
				moves.push_back({ pieceColorAndType, row + 1, column - 2 });
			}
			if ((!hasPiece(row + 2, column - 1) || hasWhitePiece(row + 2, column - 1)) && isOnBoard(row + 2, column - 1)) {
				moves.push_back({ pieceColorAndType, row + 2, column - 1 });
			}
			// lower left quadrant
			if ((!hasPiece(row - 1, column - 2) || hasWhitePiece(row - 1, column - 2)) && isOnBoard(row - 1, column - 2)) {
				moves.push_back({ pieceColorAndType, row - 1, column - 2 });
			}
			if ((!hasPiece(row - 2, column - 1) || hasWhitePiece(row - 2, column - 1)) && isOnBoard(row - 2, column - 1)) {
				moves.push_back({ pieceColorAndType, row - 2, column - 1 });
			}
			// lower right quadrant
			if ((!hasPiece(row - 1, column + 2) || hasWhitePiece(row - 1, column + 2)) && isOnBoard(row - 1, column + 2)) {
				moves.push_back({ pieceColorAndType, row - 1, column + 2 });
			}
			if ((!hasPiece(row - 2, column + 1) || hasWhitePiece(row - 2, column + 1)) && isOnBoard(row - 2, column + 1)) {
				moves.push_back({ pieceColorAndType, row - 2, column + 1 });
			}
		}
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> getRookMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		std::vector<std::tuple<std::string, int, int>> upMoves = getUpMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(upMoves, moves);
		std::vector<std::tuple<std::string, int, int>> downMoves = getDownMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(downMoves, moves);
		std::vector<std::tuple<std::string, int, int>> leftMoves = getLeftMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(leftMoves, moves);
		std::vector<std::tuple<std::string, int, int>> rightMoves = getRightMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(rightMoves, moves);
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> getBishopMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		std::vector<std::tuple<std::string, int, int>> upRightMoves = upRightDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(upRightMoves, moves);
		std::vector<std::tuple<std::string, int, int>> upLeftMoves = upLeftDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(upLeftMoves, moves);
		std::vector<std::tuple<std::string, int, int>> downRightMoves = downRightDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(downRightMoves, moves);
		std::vector<std::tuple<std::string, int, int>> downLeftMoves = downLeftDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(downLeftMoves, moves);
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> getQueenMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		std::vector<std::tuple<std::string, int, int>> upMoves = getUpMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(upMoves, moves);
		std::vector<std::tuple<std::string, int, int>> downMoves = getDownMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(downMoves, moves);
		std::vector<std::tuple<std::string, int, int>> leftMoves = getLeftMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(leftMoves, moves);
		std::vector<std::tuple<std::string, int, int>> rightMoves = getRightMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(rightMoves, moves);
		std::vector<std::tuple<std::string, int, int>> upRightMoves = upRightDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(upRightMoves, moves);
		std::vector<std::tuple<std::string, int, int>> upLeftMoves = upLeftDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(upLeftMoves, moves);
		std::vector<std::tuple<std::string, int, int>> downRightMoves = downRightDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(downRightMoves, moves);
		std::vector<std::tuple<std::string, int, int>> downLeftMoves = downLeftDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(downLeftMoves, moves);
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> getKingMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			// up
			if ((!hasPiece(row + 1, column) || hasBlackPiece(row + 1, column)) && isOnBoard(row + 1, column)) {
				moves.push_back({ pieceColorAndType, row + 1, column });
			}
			// down
			if ((!hasPiece(row - 1, column) || hasBlackPiece(row + 1, column)) && isOnBoard(row - 1, column)) {
				moves.push_back({ pieceColorAndType, row - 1, column });
			}
			// right
			if ((!hasPiece(row, column + 1) || hasBlackPiece(row + 1, column)) && isOnBoard(row, column + 1)) {
				moves.push_back({ pieceColorAndType, row, column + 1 });
			}
			// left
			if ((!hasPiece(row, column - 1) || hasBlackPiece(row + 1, column)) && isOnBoard(row, column - 1)) {
				moves.push_back({ pieceColorAndType, row, column - 1 });
			}
			// up right
			if ((!hasPiece(row + 1, column + 1) || hasBlackPiece(row + 1, column + 1)) && isOnBoard(row + 1, column + 1)) {
				moves.push_back({ pieceColorAndType, row + 1, column + 1 });
			}
			// up left
			if ((!hasPiece(row + 1, column - 1) || hasBlackPiece(row + 1, column - 1)) && isOnBoard(row + 1, column - 1)) {
				moves.push_back({ pieceColorAndType, row + 1, column - 1 });
			}
			// down left
			if ((!hasPiece(row - 1, column - 1) || hasBlackPiece(row - 1, column - 1)) && isOnBoard(row - 1, column - 1)) {
				moves.push_back({ pieceColorAndType, row - 1, column - 1 });
			}
			// down right
			if ((!hasPiece(row - 1, column + 1) || hasBlackPiece(row - 1, column + 1)) && isOnBoard(row - 1, column + 1)) {
				moves.push_back({ pieceColorAndType, row - 1, column + 1 });
			}
		}
		else if (pieceColor == BLACK) {
			// up
			if ((!hasPiece(row + 1, column) || hasWhitePiece(row + 1, column)) && isOnBoard(row + 1, column)) {
				moves.push_back({ pieceColorAndType, row + 1, column });
			}
			// down
			if ((!hasPiece(row - 1, column) || hasWhitePiece(row + 1, column)) && isOnBoard(row - 1, column)) {
				moves.push_back({ pieceColorAndType, row - 1, column });
			}
			// right
			if ((!hasPiece(row, column + 1) || hasWhitePiece(row + 1, column)) && isOnBoard(row, column + 1)) {
				moves.push_back({ pieceColorAndType, row, column + 1 });
			}
			// left
			if ((!hasPiece(row, column - 1) || hasWhitePiece(row + 1, column)) && isOnBoard(row, column - 1)) {
				moves.push_back({ pieceColorAndType, row, column - 1 });
			}
			// up right
			if ((!hasPiece(row + 1, column + 1) || hasWhitePiece(row + 1, column + 1)) && isOnBoard(row + 1, column + 1)) {
				moves.push_back({ pieceColorAndType, row + 1, column + 1 });
			}
			// up left
			if ((!hasPiece(row + 1, column - 1) || hasWhitePiece(row + 1, column - 1)) && isOnBoard(row + 1, column - 1)) {
				moves.push_back({ pieceColorAndType, row + 1, column - 1 });
			}
			// down left
			if ((!hasPiece(row - 1, column - 1) || hasWhitePiece(row - 1, column - 1)) && isOnBoard(row - 1, column - 1)) {
				moves.push_back({ pieceColorAndType, row - 1, column - 1 });
			}
			// down right
			if ((!hasPiece(row - 1, column + 1) || hasWhitePiece(row - 1, column + 1)) && isOnBoard(row - 1, column + 1)) {
				moves.push_back({ pieceColorAndType, row - 1, column + 1 });
			}
		}
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> upRightDiagnalMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			bool loopBroken = false;
			int iColumn = 1;
			for (int iRow = row; iRow <= 9; iRow++) {
				if (iColumn <= 8) {
					for (std::tuple<std::string, int, int> square : board) {
						if (std::get<1>(square) == iRow && std::get<2>(square) == column + iColumn) {
							if (std::get<0>(square)[0] == BLACK) {
								moves.push_back({ pieceColorAndType, iRow, column + iColumn });
								loopBroken = true;
								break;
							}
							else if (std::get<0>(square)[0] == WHITE) {
								loopBroken = true;
								break;
							}
						}
					}
				}
				else {
					loopBroken = true;
					break;
				}
				iColumn++;
				if (loopBroken) {
					break;
				}
			}
		}
		else if (pieceColor == BLACK) {
			bool loopBroken = false;
			int iColumn = 1;
			for (int iRow = row; iRow <= 9; iRow++) {
				if (iColumn <= 8) {
					for (std::tuple<std::string, int, int> square : board) {
						if (std::get<1>(square) == iRow && std::get<2>(square) == column + iColumn) {
							if (std::get<0>(square)[0] == WHITE) {
								moves.push_back({ pieceColorAndType, iRow, column + iColumn });
								loopBroken = true;
								break;
							}
							else if (std::get<0>(square)[0] == BLACK) {
								loopBroken = true;
								break;
							}
						}
					}
				}
				else {
					loopBroken = true;
					break;
				}
				iColumn++;
				if (loopBroken) {
					break;
				}
			}
		}
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> downRightDiagnalMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			bool loopBroken = false;
			int iColumn = 1;
			for (int iRow = row; iRow >= 0; iRow--) {
				if (iColumn <= 8) {
					for (std::tuple<std::string, int, int> square : board) {
						if (std::get<1>(square) == iRow && std::get<2>(square) == column + iColumn) {
							if (std::get<0>(square)[0] == BLACK) {
								moves.push_back({ pieceColorAndType, iRow, column + iColumn });
								loopBroken = true;
								break;
							}
							else if (std::get<0>(square)[0] == WHITE) {
								loopBroken = true;
								break;
							}
						}
					}
				}
				else {
					loopBroken = true;
					break;
				}
				iColumn++;
				if (loopBroken) {
					break;
				}
			}
		}
		else if (pieceColor == BLACK) {
			bool loopBroken = false;
			int iColumn = 1;
			for (int iRow = row; iRow >= 0; iRow--) {
				if (iColumn <= 8) {
					for (std::tuple<std::string, int, int> square : board) {
						if (std::get<1>(square) == iRow && std::get<2>(square) == column + iColumn) {
							if (std::get<0>(square)[0] == WHITE) {
								moves.push_back({ pieceColorAndType, iRow, column + iColumn });
								loopBroken = true;
								break;
							}
							else if (std::get<0>(square)[0] == BLACK) {
								loopBroken = true;
								break;
							}
						}
					}
				}
				else {
					loopBroken = true;
					break;
				}
				iColumn++;
				if (loopBroken) {
					break;
				}
			}
		}
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> downLeftDiagnalMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			bool loopBroken = false;
			int iColumn = 1;
			for (int iRow = row; iRow >= 0; iRow--) {
				if (iColumn >= 0) {
					for (std::tuple<std::string, int, int> square : board) {
						if (std::get<1>(square) == iRow && std::get<2>(square) == column - iColumn) {
							if (std::get<0>(square)[0] == BLACK) {
								moves.push_back({ pieceColorAndType, iRow, column - iColumn });
								loopBroken = true;
								break;
							}
							else if (std::get<0>(square)[0] == WHITE) {
								loopBroken = true;
								break;
							}
						}
					}
				}
				else {
					loopBroken = true;
					break;
				}
				iColumn--;
				if (loopBroken) {
					break;
				}
			}
		}
		else if (pieceColor == BLACK) {
			bool loopBroken = false;
			int iColumn = 1;
			for (int iRow = row; iRow >= 0; iRow--) {
				if (iColumn >= 0) {
					for (std::tuple<std::string, int, int> square : board) {
						if (std::get<1>(square) == iRow && std::get<2>(square) == column - iColumn) {
							if (std::get<0>(square)[0] == WHITE) {
								moves.push_back({ pieceColorAndType, iRow, column - iColumn });
								loopBroken = true;
								break;
							}
							else if (std::get<0>(square)[0] == BLACK) {
								loopBroken = true;
								break;
							}
						}
					}
				}
				else {
					loopBroken = true;
					break;
				}
				iColumn--;
				if (loopBroken) {
					break;
				}
			}
		}
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> upLeftDiagnalMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			bool loopBroken = false;
			int iColumn = 1;
			for (int iRow = row; iRow <= 9; iRow++) {
				if (iColumn >= 0) {
					for (std::tuple<std::string, int, int> square : board) {
						if (std::get<1>(square) == iRow && std::get<2>(square) == column - iColumn) {
							if (std::get<0>(square)[0] == BLACK) {
								moves.push_back({ pieceColorAndType, iRow, column - iColumn });
								loopBroken = true;
								break;
							}
							else if (std::get<0>(square)[0] == WHITE) {
								loopBroken = true;
								break;
							}
						}
					}
				}
				else {
					loopBroken = true;
					break;
				}
				iColumn--;
				if (loopBroken) {
					break;
				}
			}
		}
		else if (pieceColor == BLACK) {
			bool loopBroken = false;
			int iColumn = 1;
			for (int iRow = row; iRow <= 9; iRow++) {
				if (iColumn >= 0) {
					for (std::tuple<std::string, int, int> square : board) {
						if (std::get<1>(square) == iRow && std::get<2>(square) == column - iColumn) {
							if (std::get<0>(square)[0] == WHITE) {
								moves.push_back({ pieceColorAndType, iRow, column - iColumn });
								loopBroken = true;
								break;
							}
							else if (std::get<0>(square)[0] == BLACK) {
								loopBroken = true;
								break;
							}
						}
					}
				}
				else {
					loopBroken = true;
					break;
				}
				iColumn--;
				if (loopBroken) {
					break;
				}
			}
		}
		return moves;
	}

	//TODO: move into helper class
	template<typename T>
		std::vector<typename T> combineVectors(std::vector<typename T> vector1, std::vector<typename T> vector2) {
		for (std::vector<typename T> elEMPTent : vector1) {
			vector2.push_back(elEMPTent);
		}
		return vector2;
	}


	std::vector<std::tuple<std::string, int, int>> getUpMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			bool loopBroken = false;
			for (int iRow = row; iRow <= 9; iRow++) {
				for (std::tuple<std::string, int, int> square : board) {
					if (std::get<1>(square) == iRow && std::get<2>(square) == column) {
						if (std::get<0>(square)[0] == BLACK) {
							moves.push_back({ pieceColorAndType, iRow, column });
							loopBroken = true;
							break;
						}
						else if (std::get<0>(square)[0] == WHITE) {
							loopBroken = true;
							break;
						}
					}
				}
				if (loopBroken) {
					break;
				}
			}
		}
		else if (pieceColor == BLACK) {
			bool loopBroken = false;
			for (int iRow = row; iRow <= 9; iRow++) {
				for (std::tuple<std::string, int, int> square : board) {
					if (std::get<1>(square) == iRow && std::get<2>(square) == column) {
						if (std::get<0>(square)[0] == WHITE) {
							moves.push_back({ pieceColorAndType, iRow, column });
							loopBroken = true;
							break;
						}
						else if (std::get<0>(square)[0] == BLACK) {
							loopBroken = true;
							break;
						}
					}
				}
				if (loopBroken) {
					break;
				}
			}
		}
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> getDownMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			bool loopBroken = false;
			for (int iRow = row; iRow >= 1; iRow--) {
				for (std::tuple<std::string, int, int> square : board) {
					if (std::get<1>(square) == iRow && std::get<2>(square) == column) {
						if (std::get<0>(square)[0] == BLACK) {
							moves.push_back({ pieceColorAndType, iRow, column });
							loopBroken = true;
							break;
						}
						else if (std::get<0>(square)[0] == WHITE) {
							loopBroken = true;
							break;
						}
					}
				}
				if (loopBroken) {
					break;
				}
			}
		}
		else if (pieceColor == BLACK) {
			bool loopBroken = false;
			for (int iRow = row; iRow >= 1; iRow--) {
				for (std::tuple<std::string, int, int> square : board) {
					if (std::get<1>(square) == iRow && std::get<2>(square) == column) {
						if (std::get<0>(square)[0] == WHITE) {
							moves.push_back({ pieceColorAndType, iRow, column });
							loopBroken = true;
							break;
						}
						else if (std::get<0>(square)[0] == BLACK) {
							loopBroken = true;
							break;
						}
					}
				}
				if (loopBroken) {
					break;
				}
			}
		}
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> getLeftMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			bool loopBroken = false;
			for (int iCol = column; iCol >= 1; iCol--) {
				for (std::tuple<std::string, int, int> square : board) {
					if (std::get<1>(square) == row && std::get<2>(square) == iCol) {
						if (std::get<0>(square)[0] == BLACK) {
							moves.push_back({ pieceColorAndType, row, iCol });
							loopBroken = true;
							break;
						}
						else if (std::get<0>(square)[0] == WHITE) {
							loopBroken = true;
							break;
						}
					}
				}
				if (loopBroken) {
					break;
				}
			}
		}
		else if (pieceColor == BLACK) {
			bool loopBroken = false;
			for (int iCol = column; iCol >= 1; iCol--) {
				for (std::tuple<std::string, int, int> square : board) {
					if (std::get<1>(square) == row && std::get<2>(square) == iCol) {
						if (std::get<0>(square)[0] == WHITE) {
							moves.push_back({ pieceColorAndType, row, iCol });
							loopBroken = true;
							break;
						}
						else if (std::get<0>(square)[0] == BLACK) {
							loopBroken = true;
							break;
						}
					}
				}
				if (loopBroken) {
					break;
				}
			}
		}
		return moves;
	}

	std::vector<std::tuple<std::string, int, int>> getRightMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			bool loopBroken = false;
			for (int iCol = column; iCol <= 8; iCol++) {
				for (std::tuple<std::string, int, int> square : board) {
					if (std::get<1>(square) == row && std::get<2>(square) == iCol) {
						if (std::get<0>(square)[0] == BLACK) {
							moves.push_back({ pieceColorAndType, row, iCol });
							loopBroken = true;
							break;
						}
						else if (std::get<0>(square)[0] == WHITE) {
							loopBroken = true;
							break;
						}
					}
				}
				if (loopBroken) {
					break;
				}
			}
		}
		else if (pieceColor == BLACK) {
			bool loopBroken = false;
			for (int iCol = column; iCol <= 8; iCol++) {
				for (std::tuple<std::string, int, int> square : board) {
					if (std::get<1>(square) == row && std::get<2>(square) == iCol) {
						if (std::get<0>(square)[0] == WHITE) {
							moves.push_back({ pieceColorAndType, row, iCol });
							loopBroken = true;
							break;
						}
						else if (std::get<0>(square)[0] == BLACK) {
							loopBroken = true;
							break;
						}
					}
				}
				if (loopBroken) {
					break;
				}
			}
		}
		return moves;
	}


	bool isOnBoard(int row, int column) {
		if (row > 9 || row < 1 || column > 9 || column < 1) {
			return false;
		}
		else {
			return true;
		}
	}

	bool hasPiece(int row, int column) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<0>(square) != EMPT && std::get<1>(square) == row && std::get<2>(square) == column) {
				return true;
			}
		}
		return false
	}

	bool hasBlackPiece(int row, int column) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<0>(square)[1] == WHITE && std::get<1>(square) == row && std::get<2>(square) == column) {
				return true;
			}
		}
		return true;
	}

	bool hasWhitePiece(int row, int column) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<0>(square)[1] == WHITE && std::get<1>(square) == row && std::get<2>(square) == column) {
				return true;
			}
		}
		return true;
	}

	void movePieceToLocation(std::string piece, int row, int column) {
		std::pair<int, int> currentLocation = getLocationOfPiece(piece);
		setLocationTo(EMPT, currentLocation.first, currentLocation.second); // remove piece
		setLocationTo(piece, row, column); // set piece
	}

	std::pair<int, int> getLocationOfPiece(std::string piece) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<0>(square) == piece) {
				std::pair<int, int> location = { std::get<1>(square), std::get<2>(square) };
				return location;
			}
		}
	}

	void setLocationTo(std::string piece, int row, int column) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<1>(square) == row && std::get<2>(square) == column) {
				std::get<0>(square) = piece;
			}
		}
	}

	int getPieceValue(std::string piece) {
		return pieceValues[piece];
	}

	int getScore(char playerColor) {
		int score = 0;
		if (playerColor == WHITE) {
			for (std::tuple<std::string, int, int> square : board) {
				std::string pieceType = std::get<0>(square);
				if (pieceType[0] == WHITE) {
					score = score + getPieceValue(pieceType);
				}
			}
		}
	}

private:
	const char BLACK = 'b';
	const char WHITE = 'w';
	const std::string EMPT = "empty";
	std::vector<std::tuple<std::string, int, int>> board;
	std::map<std::string, int> pieceValues;
};
