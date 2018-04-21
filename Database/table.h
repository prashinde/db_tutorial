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
	data();
	data(std::string blob);

	int get_pkey();
	void set_pkey(int pkey);
	int put_blob(std::string blob);

	std::string get_blob();
	std::string serialize();
	void deserialize();
	bool operator ==(data &rhs) const;
	void operator =(data to);
};

class table {
private:
	std::vector<std::string> rows;
public:
	int insert_row(data d);
	int select_row(data &d);
};
#endif
