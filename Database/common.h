#ifndef __COMMON_H
#define __COMMON_H
#include "table.h"
#include "pager.h"
typedef struct metainfo {
	int nr_rows;
} minfo_t;


enum CURSOR_POS {
	START = 1,
	END,
};

class table;
class cursor {
private:
	table *tl;
	pager *pgr;
	int rnum;
	bool is_end;
public:
	cursor();
	cursor(table *t);
	bool cursor_end() const;
	int move_cursor(CURSOR_POS pos);
	void *cursor_value() const;
	void cursor_advance();
};

class table {
private:
	pager *pgr;
	int nr_rows;
	int line_sz;
public:
	table();
	pager *get_pager();
	table(pager *pgr, minfo_t mdata);
	minfo_t prepare_mdata();

	int get_lsize();
	int get_nr_rows();
	int insert_row(data d, cursor const &cur);
	int select_row(data &d, cursor &cur);
};

#endif
