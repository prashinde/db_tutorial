#include <random>

#include "query.h"
#include "table.h"

int data::generate_pkey()
{
	return rand();
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

std::string data::deserialize()
{
	return std::string("default");
}

int table::insert_row(data d)
{
	std::cout << d.serialize() << std::endl;
	return 0;
}

int table::select_row(data d)
{
	std::cout << d.serialize() << std::endl;
	return 0;
}
