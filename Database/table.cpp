#include <random>

#include "query.h"
#include "table.h"
#include "common.h"

data::data()
{

}

std::string data::get_blob()
{
	return this->blob;
}

int data::get_pkey()
{
	return this->pkey;
}

void data::set_pkey(int pkey)
{
	this->pkey = pkey;
}

bool data::operator ==(data &rhs) const
{
	return this->pkey == rhs.pkey;
}

void data::operator =(data from)
{
	this->pkey = from.pkey;
	this->blob = from.blob;
}

data::data(std::string blob)
{
	this->blob = blob;
}

int data::generate_pkey()
{
	int r = rand();
	return (r%100)+100;
}

int data::put_blob(std::string blob)
{
	this->pkey = generate_pkey();
	this->blob = blob;
	return 0;
}

std::string data::serialize()
{
	return std::string(std::to_string(this->pkey)+this->blob);
}

void data::deserialize()
{
	this->pkey = std::stoi(this->blob.substr(0, 3), nullptr, 10);
	this->blob = this->blob.substr(3, this->blob.length());
}

table::table() { }

table::table(pager *pgr, minfo_t mdata)
{
	this->pgr = pgr;
	this->line_sz = 256;
	this->nr_rows = mdata.nr_rows;
}

pager *table::get_pager()
{
	return this->pgr;
}

minfo_t table::prepare_mdata()
{
	minfo_t mdata;
	mdata.nr_rows = this->nr_rows;
	return mdata;
}

int table::get_lsize()
{
	return this->line_sz;
}

int table::get_nr_rows()
{
	return this->nr_rows;
}

int table::insert_row(data d, cursor const &cur)
{
	std::string row = d.serialize();
	if(row.length() != this->line_sz) {
		std::string t =	std::string(this->line_sz - row.length(), '\0');
		row = row+t;
	}

	void *addr = cur.cursor_value();
	memcpy(addr, row.c_str(), this->line_sz);
	this->nr_rows++;
	return 0;
}

int table::select_row(data &out, cursor &cur)
{

	while(!cur.cursor_end()) {
		char t[this->line_sz];
		void *addr = cur.cursor_value();
		memcpy(t, addr, this->line_sz);
		data d = data(std::string(t));
		d.deserialize();
		if(d == out) {
			out = d;
			return 0;
		}
		cur.cursor_advance();
	}
	return -EINVAL;
}
