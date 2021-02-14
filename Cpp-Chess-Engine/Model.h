#pragma once


class Model {

	public:
	
		Model();
		~Model();

		virtual int getValue(int, int);
		virtual int setValue(int, int);

};