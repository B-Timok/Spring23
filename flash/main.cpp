#include <vector>
#include <iostream>
#include <string>
#include "binTree.h"

int main() {
	binTree flash;
	std::vector<std::string> locations;
	std::string location;
	std::vector<std::string> path;

	std::cout << "\nFlash says Excelsior! Give the tree node names: ";
	std::cin >> location;

	while (location != "-1")
	{
		locations.push_back(location);
		std::cin >> location;
	}

	flash.buildTree(locations);
	std::cout << '\n';
	flash.print();

	path = flash.zigzag();

	std::cout << "\n";

	if (!path.empty())
	{
		std::cout << "Longest Zig Zag path: ";

		for (std::string node : path)
			std::cout << node << " ";

		std::cout << "\n";
	}
	else
		std::cout << "The flash will need to find another "
				  << "way to troll the DC Universe\n";

	std::cout << "\n";

	return 0;
}
