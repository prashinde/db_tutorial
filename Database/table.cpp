#include <random>

#include "query.h"
#include "table.h"

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
	this->line_sz = 200;

	this->nr_rows = mdata.nr_rows; //this->pgr->fsize()/this->line_sz;

	//std::cout << this->nr_rows << " " << this->pgr->fsize();
}

minfo_t table::prepare_mdata()
{
	minfo_t mdata;
	mdata.nr_rows = this->nr_rows;
	return mdata;
}

int table::insert_row(data d)
{
	//this->rows.push_back(d.serialize());
	std::string row = d.serialize();
	if(row.length() != this->line_sz) {
		std::string t =	std::string(this->line_sz - row.length(), '\0');
		row = row+t;
	}

	char *page;

	int page_pos = (this->nr_rows*this->line_sz)%this->pgr->get_page_size();
	int page_n = (this->nr_rows*this->line_sz)/this->pgr->get_page_size();

	std::cout << "Page number:" << page_n << std::endl;

	if(page_pos == 0) {
		page = new char[this->pgr->get_page_size()];
	} else {
		page = (char *)this->pgr->read_page(page_n);
	}

	memcpy(page+page_pos, row.c_str(), this->line_sz);
	this->pgr->write_page(page, page_n);
	this->nr_rows++;
	return 0;
}

int table::select_row(data &out)
{
	char *page;
	int pgn = 0;
	int nkeys = 0;
	while((page = (char *)this->pgr->read_page(pgn)) != nullptr) {
		int kperpage = this->pgr->get_page_size()/this->line_sz;
		char t[this->line_sz];
		while(kperpage != 0 && nkeys < this->nr_rows) {
			memcpy(t, page, this->line_sz);
			std::string row = t;
			data d = data(row);
			d.deserialize();
			if(d == out) {
				out = d;
				return 0;
			}
			page = page+this->line_sz;
			kperpage--;
			nkeys++;
		}
		pgn++;
	}

	return -EINVAL;
}
