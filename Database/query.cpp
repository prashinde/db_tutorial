#include <iostream>

#include "query.h"

#define INSERT_LEN 6
#define SELECT_LEN 6
query::query(std::string s, const DB *db)
{
	this->tl = NULL;
	this->command = s;
	this->db = db;
}

int query::parse_statement()
{
	size_t where;
	data d;

	this->tl = this->db->get_table_by_name(std::string("default"));
	where = this->command.find("insert");
	if(where != std::string::npos) {
		this->qc = CREATE;
		d.put_blob(this->command.substr(where+INSERT_LEN, this->command.length()-INSERT_LEN));
	} else {
		where = this->command.find("select");
		this->qc = SELECT;
		d.put_blob(this->command.substr(where+SELECT_LEN, this->command.length()-SELECT_LEN));
	}

	this->record = d;
	return 0;
}

int query::execute()
{
	int res;
	res = parse_statement();

	switch(this->qc) {
		case CREATE:
		res = this->tl->insert_row(this->record);
		break;

		case SELECT:
		res = this->tl->select_row(this->record);
		break;
	}
	return res;
}
