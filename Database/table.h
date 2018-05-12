#ifndef __TABLE_H_
#define __TABLE_H_
#include <string>
#include <vector>

#include "common.h"
#include "pager.h"

class cursor;

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
	pager *pgr;
	int nr_rows;
	int line_sz;
	std::vector<std::string> rows;
public:
	table();
	pager *get_pager();
	table(pager *pgr, minfo_t mdata);
	minfo_t prepare_mdata();

	int get_lsize();
	int get_nr_rows();
	int insert_row(data d, cursor const &cur);
	int select_row(data &d, cursor const &cur);
};
#endif
