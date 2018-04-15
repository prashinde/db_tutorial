#include <iostream>
#include <string>
#include <fstream>

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

	std::string fname = std::string(argv[1]);
	DB db = DB(fname);
	if(db.db_open() != 0) {
		std::cout << "Unable to open database file:" << fname << std::endl;
		return -EINVAL;
	}


	while (true) {
		std::cout << "> ";
		read_input(iline);
		query q = query(iline, &db);
		res = q.execute();
		std::cout << std::endl;
	}

	db.db_close();
	return 0;
}
