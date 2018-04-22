#include "db.h"
#include <errno.h>

DB::DB()
{
	this->db_name = std::string("");
}

DB::DB(std::string fname)
{
	this->tl = NULL;
	this->db_name = fname;
}

int DB::db_open()
{
	this->pgr = new pager(4096, this->db_name);
	this->tl = new table(this->pgr);
	return this->pgr->open_pager();
}

table* DB::get_table_by_name(std::string table_name) const
{
	return this->tl;
}

int DB::db_close()
{
	this->pgr->close_pager();
	delete this->pgr;
	delete this->tl;
	return 0;
}
