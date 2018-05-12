#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <time.h>

#include "query.h"
#include "db.h"

void read_input(std::string &line)
{
	std::getline(std::cin, line);
}

int main(int argc, char* argv[])
{
	std::string iline;
	int res = 0;

	if(argc < 2) {
		std::cout << "<exec> <filename>" << std::endl;
		return -EINVAL;
	}

	std::string fname = std::string(argv[1]);
	DB db = DB(fname);
	if(db.db_open() != 0) {
		std::cout << "Unable to open database file:" << fname << std::endl;
		return -EINVAL;
	}

	srand(time(NULL));
	while (true) {
		std::cout << "> ";
		read_input(iline);

		if(iline == "quit")
			break;
		try {
			query q = query(iline, &db);
			res = q.execute();
		} catch(std::exception const &exc) {
			std::cerr << "Exception caught " << exc.what() << "\n";
		}
		std::cout << std::endl;
	}

	db.db_close();
	return 0;
}
