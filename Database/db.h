#ifndef __DB_H_
#define __DB_H_

#include <iostream>
#include <fstream>
#include <string>

#include "common.h"
#include "pager.h"
#include "table.h"

class DB {
private:
	std::string db_name;
	std::fstream pstream;
	/* This is not an active feature */
	//map<string, int> fhandles;
	//std::ofstream tl_fstream; //filename associated with table tl
	table *tl;
	pager *pgr;
public:
	DB();
	DB(const DB &db);
	DB(std::string fname);
	table* get_table_by_name(std::string table_name) const;
	int db_open(std::string fname);
	int db_close();	
	void open_metafile(std::string mfname);
	void close_metafile();
	minfo_t read_metafile();
	void write_metafile(minfo_t &mdata);
};

#endif
