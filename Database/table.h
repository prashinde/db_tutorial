#ifndef __TABLE_H_
#define __TABLE_H_
#include <string>
#include <vector>

class data {
private:
	int pkey;
	std::string blob;
	int generate_pkey();
public:
	int put_blob(std::string blob);
	std::string serialize();
	std::string deserialize();
};

class table {
private:
	std::vector<data> rows;
public:
	int insert_row(data d);
	int select_row(data d);
};
#endif
