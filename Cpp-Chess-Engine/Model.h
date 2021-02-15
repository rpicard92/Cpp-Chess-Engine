#pragma once

#include <string>
#include <vector>
#include <map>


class Model {

	public:
	
		Model();
		~Model();

		virtual std::vector<Model> getValidMoves();

		virtual bool isPiece(std::tuple<std::string, int, int>);

		virtual std::vector<Model> generatEMPTodels(std::vector<std::tuple<std::string, int, int>>);

		virtual std::vector<std::tuple<std::string, int, int>> getPieceMoves(std::tuple<std::string, int, int>);

		virtual char getPieceType(std::tuple<std::string, int, int>);

		// TODO: Account for EMPTpassant, which required a tEMPTporal aspect
		virtual std::vector<std::tuple<std::string, int, int>> getPawnMoves(std::tuple<std::string, int, int>);

		virtual std::vector<std::tuple<std::string, int, int>> getKnightMoves(std::tuple<std::string, int, int>);

		virtual std::vector<std::tuple<std::string, int, int>> getRookMoves(std::tuple<std::string, int, int>);

		virtual std::vector<std::tuple<std::string, int, int>> getBishopMoves(std::tuple<std::string, int, int>);
		
		virtual std::vector<std::tuple<std::string, int, int>> getQueenMoves(std::tuple<std::string, int, int>);
		
		virtual std::vector<std::tuple<std::string, int, int>> getKingMoves(std::tuple<std::string, int, int>);

		virtual std::vector<std::tuple<std::string, int, int>> upRightDiagnalMoves(std::tuple<std::string, int, int>);

		virtual std::vector<std::tuple<std::string, int, int>> downRightDiagnalMoves(std::tuple<std::string, int, int>);

		virtual std::vector<std::tuple<std::string, int, int>> downLeftDiagnalMoves(std::tuple<std::string, int, int>);
		
		virtual std::vector<std::tuple<std::string, int, int>> upLeftDiagnalMoves(std::tuple<std::string, int, int>);

		//TODO: move into helper class
		template<typename T>
		std::vector<typename T> combineVectors(std::vector<typename T> vector1, std::vector<typename T>);
	
		virtual std::vector<std::tuple<std::string, int, int>> getUpMoves(std::tuple<std::string, int, int>);

		virtual std::vector<std::tuple<std::string, int, int>> getDownMoves(std::tuple<std::string, int, int>);

		virtual std::vector<std::tuple<std::string, int, int>> getLeftMoves(std::tuple<std::string, int, int>);

		virtual std::vector<std::tuple<std::string, int, int>> getRightMoves(std::tuple<std::string, int, int>);

		virtual bool isOnBoard(int, int);

		virtual bool hasPiece(int, int); 

		virtual bool hasBlackPiece(int, int);

		virtual bool hasWhitePiece(int, int);

		virtual void movePieceToLocation(std::string, int, int);

		virtual std::pair<int, int> getLocationOfPiece(std::string);

		virtual void setLocationTo(std::string, int, int);

		virtual int getPieceValue(std::string);

		virtual int getScore(char);

};