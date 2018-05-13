#include <stdio.h>
#include <fcntl.h>
#include "pager.h"

pager::pager() {}

int in_mem_pages;
	bool is_in_mem(int pagenum);
	void set_in_mem(int pagenum);

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
	this->sync_pages();
	this->pfstream.close();
	return 0;
}

bool pager::is_in_mem(int pagenum)
{
	return (this->page_map.count(pagenum) != 0);
}

void pager::place_in_mem(int pagenum, void *ptr)
{
	this->page_map[pagenum] = ptr;
}

void * pager::get_page(int page_no)
{
	off_t fsize = file_size(this->fname);
	unsigned long tpages = fsize/this->page_size;
	char *page;
	if(page_no > tpages) {
		page = new char[page_size];
		this->page_map[page_no] = page;
		this->place_in_mem(page_no, page);
	} else if(is_in_mem(page_no)) {
		page = (char *)this->page_map[page_no];
	} else {
		page = new char[page_size];
		off_t foffset = page_no*page_size;
		this->pfstream.seekg(foffset, std::ios_base::beg);
		this->pfstream.read(page, page_size);
		this->place_in_mem(page_no, page);
	}

	return (void*)page;
}

void pager::sync_pages()
{
	for(std::map<int, void *>::iterator it=this->page_map.begin();\
			it != this->page_map.end(); ++it) {
	   write_page(it->second, it->first);
	   //delete [] (char *)it->second;
	}
}

int pager::write_page(void *page, int page_no)
{
	/* 1. Check if the */
	this->pfstream.seekg(0, this->pfstream.beg);
	this->pfstream.clear();
	off_t foffset = page_no*page_size;
	this->pfstream.clear();
	this->pfstream.seekg(foffset, std::ios::beg);
	this->pfstream.clear();
	this->pfstream.write((char *)page, page_size);
	this->pfstream.flush();
}
