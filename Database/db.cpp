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

void DB::open_metafile()
{
	std::string mfname(".metafile");
	this->pstream.open(mfname, std::fstream::out);
}

void DB::close_metafile()
{
	this->pstream.close();
}

minfo_t DB::read_metafile()
{
	std::string nrows;
	minfo_t mdata;

	getline(this->pstream, nrows);
	mdata.nr_rows = atoi(nrows.c_str());
	return mdata;
}

void DB::write_metafile(minfo_t &mdata)
{
	this->pstream << mdata.nr_rows;
}

int DB::db_open()
{
	this->open_metafile();
	minfo_t mdata = this->read_metafile();

	this->pgr = new pager(4096, this->db_name);
	this->tl = new table(this->pgr, mdata);
	return this->pgr->open_pager();
}

table* DB::get_table_by_name(std::string table_name) const
{
	return this->tl;
}

int DB::db_close()
{
	minfo_t mdata = this->tl->prepare_mdata();
	std::cout << "Mdata:" << mdata.nr_rows << std::endl;
	this->write_metafile(mdata);
	this->close_metafile();
	this->pgr->close_pager();
	delete this->pgr;
	delete this->tl;
	return 0;
}
