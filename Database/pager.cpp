#include <stdio.h>
#include <fcntl.h>
#include "pager.h"

pager::pager() {}

pager::pager(unsigned long page_size, std::string fname)
{
	this->page_size = page_size;
	this->fname = fname;
}

off_t pager::file_size(std::string const& filename)
{
	/* C, because C++ file I/O is a bull-shit
	 * Its so fucking stupid that it cannot gaurantee 
	 * the actual file size.. Seriosly? After a great STL,
	 * how the file I/O can be so shitty!
	 **/
	FILE * pFile;
	off_t size;

	pFile = fopen(filename.c_str(),"rb");
    fseek (pFile, 0, SEEK_END);
    size = ftell(pFile);
    fclose (pFile);
    return size;
}

off_t pager::fsize()
{
	return file_size(this->fname);
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
	std::cout << "For closing file suze:" << file_size(this->fname) << std::endl;
	this->pfstream.close();
	std::cout << "After closing file suze:" << file_size(this->fname) << std::endl;
	return 0;
}

void * pager::read_page(int page_no)
{
	off_t fsize = file_size(this->fname);
	unsigned long tpages = fsize/this->page_size;

	std::cout << "Fsize:" << fsize << " Total pages:" << tpages << "pnp:" << page_no << std::endl;
	if(page_no > tpages) {
		return nullptr;
	}

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
	std::cout << "Write offset = " << foffset << " " << page_size << std::endl;
	this->pfstream.seekg(foffset, std::ios::beg);
	this->pfstream.write((char *)page, page_size);
	this->pfstream.flush();
}
