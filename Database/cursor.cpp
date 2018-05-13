#include "common.h"

#include "cursor.h"
cursor::cursor() { }

cursor::cursor(table *tl)
{
	this->tl = tl;
	this->pgr = tl->get_pager();
}

int cursor::move_cursor(CURSOR_POS pos)
{
	if(pos == START) {
		this->rnum = 0;
		this->is_end = (this->tl->get_nr_rows() == 0);
	} else if(pos == END) {
		this->rnum = this->tl->get_nr_rows();
		this->is_end = true;
	}

	return 0;
}

void *cursor::cursor_value() const
{
	unsigned long pgsize = this->pgr->get_page_size();
	unsigned long page_num = (this->rnum*this->tl->get_lsize())/pgsize;
	unsigned long page_pos = (this->rnum*this->tl->get_lsize())%pgsize;

	void *addr = this->pgr->get_page(page_num);
	printf("Pager address in cursoe:%p, pagepos=%lu\n", addr, page_pos);
	return ((char*)addr)+page_pos;
}

void cursor::advance_cursor()
{
	this->rnum += 1;
	if(this->rnum >= this->tl->get_nr_rows())
		this->is_end = true;
}
