#include "db.h"
#include <errno.h>

DB::DB()
{
	this->db_name = std::string("");
}

DB::DB(std::string fname)
{
	this->db_name = fname;
}

int DB::db_open()
{
	this->tl_fstream.open(this->db_name);
	if(this->tl_fstream.is_open())
		return 0;

	this->tl = table();
	return errno;
}

table DB::get_table_by_name(std::string table_name) const
{
	return this->tl;
}

int DB::db_close()
{
	this->tl_fstream.close();
	return 0;
}
