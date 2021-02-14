
#include <map>;

class Model {

public:

	Model() {

	}
	~Model() {

	}

	virtual int getValue(int, int);
	virtual int setValue(int, int);

private:
		
	char model[64][4] = {
		"br1","bk1","bb1","bq1","bk1","bb2","bk2","br2",
		"bp1","bp2","bp3","bp4","bp5","bm6","bp7","bp8",
		"emp","emp","emp","emp","emp","emp","emp","emp",
		"emp","emp","emp","emp","emp","emp","emp","emp",
		"emp","emp","emp","emp","emp","emp","emp","emp",
		"emp","emp","emp","emp","emp","emp","emp","emp",
		"wp1","wp2","wp3","wp4","wp5","em6","wp7","wp8",
		"wr1","wk1","wb1","wq1","wk1","wb2","wk2","wr2",
	};

	std::map<char[4], int> values = {
		{"br1",5},{"bk1",3},{"bb1",3},{"bq1",9},{"bk1",3},{"bb2",3},"bk2","br2",
		"bp1","bp2","bp3","bp4","bp5","bm6","bp7","bp8",
		"emp","emp","emp","emp","emp","emp","emp","emp",
		"emp","emp","emp","emp","emp","emp","emp","emp",
		"emp","emp","emp","emp","emp","emp","emp","emp",
		"emp","emp","emp","emp","emp","emp","emp","emp",
		"wp1","wp2","wp3","wp4","wp5","em6","wp7","wp8",
		"wr1","wk1","wb1","wq1","wk1","wb2","wk2","wr2",
	};

};