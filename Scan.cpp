#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using std::filesystem::directory_iterator;
using json = nlohmann::json;

#include "Scan.hpp"

Scan::Scan(int id, int count) {
	printf_s("Scanning Item ID: %d\n", id);
	item_id = id, item_count = count;
}

Scan::~Scan() {
	std::sort(data.begin(), data.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
	for (const auto& entry : data) {
		if (found == 100) break;
		printf_s("Target: %d Count: %d\n", entry.first, entry.second);
		found++;
	}
	data.clear();
	system("PAUSE");
}

void Scan::player() {
	for (const auto& file : std::filesystem::directory_iterator("players")) {
		json db;
		int total = 0;
		std::ifstream player(file.path(), std::ifstream::binary);
		player >> db;
		for (const auto& get : db["inventory"]) {
			int id = get[0], count = get[1];
			if (id == item_id && count >= item_count) total += count;
		}
		if (total != 0) data.insert({ db["name"], total });
	}
}

void Scan::world(int type) {
	for (const auto& file : std::filesystem::directory_iterator("worlds")) {
		json db;
		int total = 0;
		std::ifstream world(file.path(), std::ifstream::binary);
		world >> db;
		switch (type) {
		case DROP:
		{
			for (const auto& get : db["drop_new"]) {
				int id = get[0], count = get[1];
				if (id == item_id && count >= item_count) total += count;
			}
			break;
		}
		case VAULT:
		{
			for (const auto& get : db["sbox1"]) {
				int id = get["i"], count = get["c"];
				if (id == item_id && count >= item_count) total += count;
			}
			break;
		}
		case DBOX:
		{
			for (const auto& get : db["dnt"]) {
				int id = get["item"], count = get["count"];
				if (id == item_id && count >= item_count) total += count;
			}
			break;
		}
		if (total != 0) data.insert({ file.path().string(), total });
		}
	}
}
