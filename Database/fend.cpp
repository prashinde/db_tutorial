#include <iostream>
#include <string>
#include <fstream>

#include "query.h"

void read_input(std::string &line)
{
	std::getline(std::cin, line);
}

int main(int argc, char* argv[])
{
	std::string iline;
	int res = 0;

	while (true) {
		std::cout << "> ";
		read_input(iline);
		query q = query(iline);
		res = q.execute();
		std::cout << std::endl;
	}

	return 0;
}
