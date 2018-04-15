#ifndef __QUERY_H_
#define __QUERY_H_

#include <string>

#include "db.h"
#include "table.h"

enum qtype {
	CREATE = 1,
	SELECT
};

class query {
private:
	std::string command;
	table tl;
	enum qtype qc;
	/* This data should be different depending upon the table. */
	data record;
	const DB *db;
	int parse_statement();
	int insert_command();
	int select_command();
public:
	query(std::string s, const DB *db);
	int execute();
};
#endif
