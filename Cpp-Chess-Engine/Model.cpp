
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


	std::vector<Model> getValidMoves() {
		std::vector<Model> models;
		for (std::tuple<std::string, int, int> piece : board) {
			if (isPiece(piece)) {
				std::vector<std::pair<std::tuple<std::string, int, int>, std::tuple<std::string, int, int>>> moves = getPieceMoves(piece);
				// TODO: finish hear!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
		}
	}

	std::vector<std::pair<std::tuple<std::string, int, int>, std::tuple<std::string, int, int>>> getPieceMoves(std::tuple<std::string, int, int> piece) {
		char pieceType = getPieceType(piece);
		if (pieceType == 'p') {
			return getPawnMoves(piece);
		}
		else {
			// TODO: add the rest of the info hear!!!!!
		}
	};

	char getPieceType(std::tuple<std::string, int, int> piece) {
		std::string pieceType = std::get<0>(piece);
		return pieceType[1];
	}

	std::vector<std::pair<std::tuple<std::string, int, int>, std::tuple<std::string, int, int>>> getPawnMoves(std::tuple<std::string, int, int> piece) {
		std::string pieceColorAndType = std::get<0>(piece);
		char pieceColor = pieceColorAndType[0];
		char pieceType = pieceColorAndType[1];
		int row = std::get<1>(piece);
		int column = std::get<2>(piece);
		std::vector<std::pair<std::tuple<std::string, int, int>, std::tuple<std::string, int, int>>> candidateMoves;
		if (pieceColor == 'w') {
			if (!hasPiece(row + 1, column)) {
				candidateMoves.push_back({ {pieceColorAndType, row, column}, {pieceColorAndType, row + 1, column} });
			}
			else if (!hasPiece(row + 2, column)) {
				candidateMoves.push_back({ {pieceColorAndType, row, column}, {pieceColorAndType, row + 2, column} });
			}
			else if (hasBlackPiece(row + 1, column + 1)) {
				candidateMoves.push_back({ {pieceColorAndType, row, column}, {pieceColorAndType, row + 1, column + 1} });
			}
			else if (hasBlackPiece(row + 1, column - 1)) {
				candidateMoves.push_back({ {pieceColorAndType, row, column}, {pieceColorAndType, row + 1, column - 1} });
			}
		}
		else if (pieceColor == 'b') {
			std::vector<std::pair<std::tuple<std::string, int, int>, std::tuple<std::string, int, int>>> candidateMoves;
			if (!hasPiece(row - 1, column)) {
				candidateMoves.push_back({ {pieceColorAndType, row, column}, {pieceColorAndType, row - 1, column} });
			}
			else if (!hasPiece(row - 2, column)) {
				candidateMoves.push_back({ {pieceColorAndType, row, column}, {pieceColorAndType, row - 2, column} });
			}
			else if (hasWhitePiece(row - 1, column + 1)) {
				candidateMoves.push_back({ {pieceColorAndType, row, column}, {pieceColorAndType, row - 1, column + 1} });
			}
			else if (hasWhitePiece(row - 1, column - 1)) {
				candidateMoves.push_back({ {pieceColorAndType, row, column}, {pieceColorAndType, row - 1, column - 1} });
			}
		}
		return candidateMoves;
	}

	bool hasPiece(int row, int column) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<0>(square) != "emp" && std::get<1>(square) == row && std::get<2>(square) == column) {
				return true;
			}
		}
		return true;
	}

	bool hasBlackPiece(int row, int column) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<0>(square)[1] == 'w' && std::get<1>(square) == row && std::get<2>(square) == column) {
				return true;
			}
		}
		return true;
	}

	bool hasWhitePiece(int row, int column) {
		for (std::tuple<std::string, int, int> square : board) {
			if (std::get<0>(square)[1] == 'w' && std::get<1>(square) == row && std::get<2>(square) == column) {
				return true;
			}
		}
		return true;
	}

	bool isPiece(std::tuple<std::string, int, int> piece) {
		if (std::get<0>(piece) != "emp") {
			return true;
		}
		else {
			return false;
		}
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

	std::vector<std::tuple<std::string, int, int>> board;
	std::map<std::string, int> pieceValues;
};
