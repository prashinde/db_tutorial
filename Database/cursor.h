#ifndef __CURSOR_H_
#define __CURSOR_H_
#if 0
#include "pager.h"

enum CURSOR_POS {
	START = 1,
	END,
};

class cursor {
private:
	table *tl;
	pager *pgr;
	int rnum;
	bool is_end;
public:
	cursor();
	cursor(table *t);
	int move_cursor(CURSOR_POS pos);
	void *cursor_value() const;
	void advance_cursor();
};
#endif
#endif
