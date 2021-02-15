
#include <string>;
#include <vector>;
#include <map>;

class Model {

public:

	Model() {
		board = {
			{"br1",8,1},{"bk1",8,2},{"bb1",8,3},{"bq1",8,4},{"b!!",8,5},{"bb2",8,6},{"bk2",8,7},{"br2",8,8},
			{"bp1",7,1},{"bp2",7,2},{"bp3",7,3},{"bp4",7,4},{"bp5",7,5},{"bm6",7,6},{"bp7",7,7},{"bp8",7,8},
			{"emp",6,1},{"emp",6,2},{"emp",6,3},{"emp",6,4},{"emp",6,5},{"emp",6,6},{"emp",6,7},{"emp",6,8},
			{"emp",5,1},{"emp",5,2},{"emp",5,3},{"emp",5,4},{"emp",5,5},{"emp",5,6},{"emp",5,7},{"emp",5,8},
			{"emp",4,1},{"emp",4,2},{"emp",4,3},{"emp",4,4},{"emp",4,5},{"emp",4,6},{"emp",4,7},{"emp",4,8},
			{"emp",3,1},{"emp",3,2},{"emp",3,3},{"emp",3,4},{"emp",3,5},{"emp",3,6},{"emp",3,7},{"emp",3,8},
			{"wp1",2,1},{"wp2",2,2},{"wp3",2,3},{"wp4",2,4},{"wp5",2,5},{"em6",2,6},{"wp7",2,7},{"wp8",2,8},
			{"wr1",1,1},{"wk1",1,2},{"wb1",1,3},{"wq1",1,4},{"wk!",1,5},{"wb2",1,6},{"wk2",1,7},{"wr2",1,8}
		};

		pieceValues = {
			{"br1",5},{"bk1",3},{"bb1",3},{"bq1",9},{"bk!",0},{"bb2",3},{"bk2",3},{"br2",5},
			{"bp1",1},{"bp2",1},{"bp3",1},{"bp4",1},{"bp5",1},{"bm6",1},{"bp7",1},{"bp8",1},
			{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},
			{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},
			{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},
			{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},
			{"wp1",1},{"wp2",1},{"wp3",1},{"wp4",1},{"wp5",1},{"em6",1},{"wp7",1},{"wp8",1},
			{"wr1",5},{"wk1",3},{"wb1",3},{"wq1",9},{"w!!",0},{"wb2",3},{"wk2",3},{"wr2",5}
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
				std::vector<Model> generatedModels = generateModels(moves);
				for (Model generatedModel : generatedModels) {
					models.push_back(generatedModel);
				}
			}
		}
		return models;
	}


	bool isPiece(std::tuple<std::string, int, int> piece) {
		if (std::get<0>(piece) != "emp") {
			return true;
		}
		else {
			return false;
		}
	}

	std::vector<Model> generateModels(std::vector<std::tuple<std::string, int, int>> moves) {
		std::vector<Model> models;
		for (std::tuple<std::string, int, int> move : moves) {
			Model model = Model();
			model.movePieceToLocation(std::get<0>(move),std::get<1>(move),std::get<2>(move));
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
	};

	char getPieceType(std::tuple<std::string, int, int> piece) {
		std::string pieceType = std::get<0>(piece);
		return pieceType[1];
	}

	// TODO: Account for Empassant, which required a temporal aspect
	std::vector<std::tuple<std::string, int, int>> getPawnMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::tuple<std::string, int, int>> moves;
		if (pieceColor == WHITE) {
			if (!hasPiece(row + 1, column) && isOnBaord(row+1, column)) {
				moves.push_back({pieceColorAndType, row + 1, column});
			}
			if (!hasPiece(row + 2, column) && !hasPiece(row + 1, column) && isOnBaord(row + 2, column)) { // tranistive property captured
				moves.push_back({pieceColorAndType, row + 2, column});
			}
			if (hasBlackPiece(row + 1, column + 1) && isOnBaord(row + 1, column + 1)) {
				moves.push_back({pieceColorAndType, row + 1, column + 1});
			}
			if (hasBlackPiece(row + 1, column - 1) && isOnBaord(row + 1, column - 1)) {
				moves.push_back({pieceColorAndType, row + 1, column - 1});
			}
		}
		else if (pieceColor == BLACK) {
			if (!hasPiece(row - 1, column) && isOnBaord(row - 1, column)) {
				moves.push_back({pieceColorAndType, row - 1, column});
			}
			if (!hasPiece(row - 2, column) && !hasPiece(row - 1, column) && isOnBaord(row - 2, column)) { // tranistive property captured
				moves.push_back({pieceColorAndType, row - 2, column});
			}
			if (hasWhitePiece(row - 1, column + 1) && isOnBaord(row + 1, column) && isOnBaord(row - 1, column + 1)) {
				moves.push_back({pieceColorAndType, row - 1, column + 1});
			}
			if (hasWhitePiece(row - 1, column - 1) && isOnBaord(row + 1, column) && isOnBaord(row - 1, column) + 1) {
				moves.push_back({pieceColorAndType, row - 1, column - 1});
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
			if ((!hasPiece(row + 1, column + 2) || hasBlackPiece(row + 1, column + 2)) && isOnBaord(row + 1, column + 2)) {
				moves.push_back({ pieceColorAndType, row + 1, column + 2});
			}
			if ((!hasPiece(row + 2, column + 1) || hasBlackPiece(row + 2, column + 1)) && isOnBaord(row + 2, column + 1)) {
				moves.push_back({ pieceColorAndType, row + 2, column + 1 });
			}
			// upper left quadrant
			if ((!hasPiece(row + 1, column - 2) || hasBlackPiece(row + 1, column - 2)) && isOnBaord(row + 1, column - 2)) {
				moves.push_back({ pieceColorAndType, row + 1, column - 2 });
			}
			if ((!hasPiece(row + 2, column - 1) || hasBlackPiece(row + 2, column - 1)) && isOnBaord(row + 2, column - 1)) {
				moves.push_back({ pieceColorAndType, row + 2, column - 1 });
			}
			// lower left quadrant
			if ((!hasPiece(row - 1, column - 2) || hasBlackPiece(row - 1, column - 2)) && isOnBaord(row - 1, column - 2)) {
				moves.push_back({ pieceColorAndType, row - 1, column - 2 });
			}
			if ((!hasPiece(row - 2, column - 1) || hasBlackPiece(row - 2, column - 1)) && isOnBaord(row - 2, column - 1)) {
				moves.push_back({ pieceColorAndType, row - 2, column - 1 });
			}
			// lower right quadrant
			if ((!hasPiece(row - 1, column + 2) || hasBlackPiece(row - 1, column + 2)) && isOnBaord(row - 1, column + 2)) {
				moves.push_back({ pieceColorAndType, row - 1, column + 2 });
			}
			if ((!hasPiece(row - 2, column + 1) || hasBlackPiece(row - 2, column + 1)) && isOnBaord(row - 2, column + 1)) {
				moves.push_back({ pieceColorAndType, row - 2, column + 1 });
			}
		}
		else if (pieceColor == BLACK) {
			// upper right quadrant
			if ((!hasPiece(row + 1, column + 2) || hasWhitePiece(row + 1, column + 2)) && isOnBaord(row + 1, column + 2)) {
				moves.push_back({ pieceColorAndType, row + 1, column + 2 });
			}
			if ((!hasPiece(row + 2, column + 1) || hasWhitePiece(row + 2, column + 1)) && isOnBaord(row + 2, column + 1)) {
				moves.push_back({ pieceColorAndType, row + 2, column + 1 });
			}
			// upper left quadrant
			if ((!hasPiece(row + 1, column - 2) || hasWhitePiece(row + 1, column - 2)) && isOnBaord(row + 1, column - 2)) {
				moves.push_back({ pieceColorAndType, row + 1, column - 2 });
			}
			if ((!hasPiece(row + 2, column - 1) || hasWhitePiece(row + 2, column - 1)) && isOnBaord(row + 2, column - 1)) {
				moves.push_back({ pieceColorAndType, row + 2, column - 1 });
			}
			// lower left quadrant
			if ((!hasPiece(row - 1, column - 2) || hasWhitePiece(row - 1, column - 2)) && isOnBaord(row - 1, column - 2)) {
				moves.push_back({ pieceColorAndType, row - 1, column - 2 });
			}
			if ((!hasPiece(row - 2, column - 1) || hasWhitePiece(row - 2, column - 1)) && isOnBaord(row - 2, column - 1)) {
				moves.push_back({ pieceColorAndType, row - 2, column - 1 });
			}
			// lower right quadrant
			if ((!hasPiece(row - 1, column + 2) || hasWhitePiece(row - 1, column + 2)) && isOnBaord(row - 1, column + 2)) {
				moves.push_back({ pieceColorAndType, row - 1, column + 2 });
			}
			if ((!hasPiece(row - 2, column + 1) || hasWhitePiece(row - 2, column + 1)) && isOnBaord(row - 2, column + 1)) {
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
		std::vector<std::tuple<std::string, int, int>> upRightDiagnolMoves = upRightDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(upRightDiagnolMoves, moves);
		std::vector<std::tuple<std::string, int, int>> upLeftDiagnolMoves = upRightDiagnalMoves(piece);
		std::vector<std::tuple<std::string, int, int>> moves = combineVectors(upLeftDiagnolMoves, moves);
		//TODO: start here!!
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

	std::vector<std::tuple<std::string, int, int>> upLefDiagnalMoves(std::tuple<std::string, int, int> piece) {
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
				iColumn++;
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
		for (std::vector<typename T> element : vector1) {
			vector2.push_back(element);
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
							moves.push_back({pieceColorAndType, iRow, column });
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


	bool isOnBaord(int row, int column) {
		if (row > 9 || row < 1 || column > 9 || column < 1) {
			return false;
		}
		else {
			return true;
		}
	}

	bool hasPiece(int row, int column) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<0>(square) != "emp" && std::get<1>(square) == row && std::get<2>(square) == column) {
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
		setLocationTo("emp", currentLocation.first, currentLocation.second); // remove piece
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

	//TODO: Might not need
	std::string getPieceAtLocation(int row, int column) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<1>(square) == row && std::get<2>(square) == column) {
				return std::get<0>(square);
			}
		}
	}

private:
	const char BLACK = 'b';
	const char WHITE = 'w';
	std::vector<std::tuple<std::string, int, int>> board;
	std::map<std::string, int> pieceValues;
};
