#include <vector>
#include <string>

class Scan {
public:
	Scan(int id, int count);
	~Scan();
	void player();
	void world(int type);
	enum type {
		PLAYER = 1,
		DROP,
		VAULT,
		DBOX
	};
private:
	int item_id = 0;
	int item_count = 0;
	int found = 0;
	std::vector<std::pair<std::string, int>> data;
};