
#include <string>;
#include <vector>;
#include <map>;

class Model {

public:

	Model() {
		model = {
	   "br1","bk1","bb1","bq1","bk1","bb2","bk2","br2",
	   "bp1","bp2","bp3","bp4","bp5","bm6","bp7","bp8",
	   "emp","emp","emp","emp","emp","emp","emp","emp",
	   "emp","emp","emp","emp","emp","emp","emp","emp",
	   "emp","emp","emp","emp","emp","emp","emp","emp",
	   "emp","emp","emp","emp","emp","emp","emp","emp",
	   "wp1","wp2","wp3","wp4","wp5","em6","wp7","wp8",
	   "wr1","wk1","wb1","wq1","wk1","wb2","wk2","wr2",
		};

		values = {
		{"br1",5},{"bk1",3},{"bb1",3},{"bq1",9},{"bk!",0},{"bb2",3},{"bk2",3},{"br2",5},
		{"bp1",1},{"bp2",1},{"bp3",1},{"bp4",1},{"bp5",1},{"bm6",1},{"bp7",1},{"bp8",1},
		{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},
		{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},
		{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},
		{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},{"emp",0},
		{"wp1",1},{"wp2",1},{"wp3",1},{"wp4",1},{"wp5",1},{"em6",1},{"wp7",1},{"wp8",1},
		{"wr1",5},{"wk1",3},{"wb1",3},{"wq1",9},{"wk!",0},{"wb2",3},{"wk2",3},{"wr2",5}
		};
	}
	~Model() {

	}

	std::string getPiece(int location) {
		return model.at(location);
	}

	int getValue(std::string piece) {
		return values[piece];
	}



private:

	std::vector<std::string> model;
	std::map<std::string, int> values;
};
