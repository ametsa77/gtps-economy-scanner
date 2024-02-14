#include <iostream>
#include "Scan.hpp"

int main() {
	int item_id = 0, count = 0, type = 0;
	printf_s("[1] Player\n[2] Dropped Items\n[3] Safe Vault\n[4] Donation Box\n");
	printf_s("Select Scan Type: "), scanf_s("%d", &type);
	system("CLS");
	printf_s("Item ID: "), scanf_s("%d", &item_id);
	printf_s("Minumum Count: "), scanf_s("%d", &count);
	system("CLS");
	auto find = new Scan(item_id, count);
	if (type == find->PLAYER) find->player(), delete find;
	else find->world(type), delete find;
}