#include "pager.h"

pager::pager() {}

pager::pager(unsigned long page_size, std::string fname)
{
	this->page_size = page_size;
	this->fname = fname;
}

unsigned long pager::get_page_size()
{
	return this->page_size;
}

int pager::open_pager()
{
	this->pfstream.open(this->fname);
	if(this->pfstream.is_open())
		return 0;
	return errno;
}

int pager::close_pager()
{
	this->pfstream.close();
	return 0;
}

void * pager::read_page(int page_no)
{
	return nullptr;
}

void pager::write_page(void *page)
{

}

