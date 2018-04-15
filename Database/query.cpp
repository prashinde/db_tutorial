#include <iostream>

#include "query.h"

#define INSERT_LEN 6
#define SELECT_LEN 6
query::query(std::string s)
{
	this->command = s;
}

int query::parse_statement()
{
	size_t where;
	data d;

	where = this->command.find("insert");
	if(where != std::string::npos) {
		this->qc = CREATE;
		d.put_blob(this->command.substr(where+INSERT_LEN, this->command.length()-INSERT_LEN));
	} else {
		where = this->command.find("select");
		this->qc = SELECT;
		d.put_blob(this->command.substr(where+SELECT_LEN, this->command.length()-SELECT_LEN));
	}

	this->d = d;
	return 0;
}

int query::execute()
{
	int res;
	res = parse_statement();

	std::cout << this->d.serialize() << std::endl;

	switch(this->qc) {
		CREATE:
		res = this->table->insert_row(this->data);
		break;

		SELECT:
		res = this->table->select_row(this->data);
		break;
	}
	return res;
}
