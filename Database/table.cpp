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

table::table()
{

}

table::table(pager *pgr)
{
	this->pgr = pgr;
}

int table::insert_row(data d)
{
	this->rows.push_back(d.serialize());
	return 0;
}

int table::select_row(data &out)
{
	for(int i = 0; i < this->rows.size(); i++) {
		data d = data(this->rows[i]);
		d.deserialize();
		if(d == out) {
			out = d;
		}
	}
	return 0;
}
