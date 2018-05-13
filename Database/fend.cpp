#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <time.h>
#include <algorithm>

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

	if(argc < 5) {
		std::cout << "<exec> <filename> <metafilename> <seed> <is_interactive>" << std::endl;
		return -EINVAL;
	}

	int seed = atoi(argv[3]);
	srand(seed);
	std::string fname = std::string(argv[1]);
	std::string metafilename = std::string(argv[2]);
	DB db = DB(fname);
	if(db.db_open(metafilename) != 0) {
		std::cout << "Unable to open database file:" << fname << std::endl;
		return -EINVAL;
	}

	bool interactive = atoi(argv[4]);
	if(!interactive) {
		int cnt = 0;
		while(cnt != argc-5) {
			iline += argv[5+cnt];
			iline += " ";
			cnt++;
		}

		iline.erase(std::remove(iline.begin(), iline.end(), '\"'), iline.end());
		query q = query(iline, &db);
		q.execute();
		db.db_close();
		return 0;
	}

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
