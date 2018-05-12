#include <iostream>

#include "query.h"
#include "cursor.h"

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

	if(this->command.length() == 0)
		return -EINVAL;

	this->tl = this->db->get_table_by_name(std::string("default"));
	where = this->command.find("insert");
	if(where != std::string::npos) {
		this->qc = CREATE;
		d.put_blob(this->command.substr(where+INSERT_LEN, this->command.length()-INSERT_LEN));
	} else if((where = this->command.find("select")) != std::string::npos) {
		this->qc = SELECT;
		int pkey = std::stoi(this->command.substr(where+SELECT_LEN,\
					this->command.length()-SELECT_LEN), nullptr, 10);
		d.set_pkey(pkey);
	} else {
		return -EINVAL;
	}
	this->record = d;
	return 0;
}

int query::execute()
{
	int res;
	res = parse_statement();

	cursor cur(this->tl);

	switch(this->qc) {
		case CREATE:
		cur.move_cursor(END);
		res = this->tl->insert_row(this->record, cur);
		if(res == 0)
			std::cout << "Record is successfully inserted:" << this->record.get_pkey() << std::endl;
		break;

		case SELECT:
		cur.move_cursor(START);
		res = this->tl->select_row(this->record, cur);
		if(res == 0)
			std::cout << "Selected row is:" << this->record.get_blob() << std::endl;
		break;
	}
	return res;
}
