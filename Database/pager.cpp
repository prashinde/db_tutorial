#include "pager.h"

pager::pager() {}

pager::pager(unsigned long page_size, std::string fname)
{
	this->page_size = page_size;
	this->fname = fname;
}

off_t pager::file_size(std::string const& filename)
{
    struct stat st;
    if (stat(filename.c_str(), &st) == -1)
        throw std::runtime_error(std::strerror(errno));
    return st.st_size;
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
	off_t fsize = file_size(this->fname);
	unsigned long tpages = fsize/this->page_size;

	if(page_no > tpages)
		return nullptr;

	char *page = new char[page_size];
	off_t foffset = page_no*page_size;
	
	this->pfstream.seekg(foffset, std::ios_base::beg);

	this->pfstream.read(page, page_size);
	return (void*)page;
}

int pager::write_page(void *page, int page_no)
{
	/* 1. Check if the */
	off_t foffset = page_no*page_size;
	this->pfstream.seekg(foffset, std::ios_base::beg);
	this->pfstream.write((char *)page, page_size);
}
