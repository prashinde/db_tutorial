#ifndef __PAGER_H_
#define __PAGER_H_

#include <iostream>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <fstream>
#include <map>

class pager {
private:
	unsigned long page_size;
	std::fstream pfstream;
	std::string fname;
	off_t file_size(std::string const& fname);
	std::map<int, void *> page_map;
	bool is_in_mem(int pagenum);
	void place_in_mem(int pagenum, void *ptr);
public:
	pager();
	pager(unsigned long page_size, std::string fname);
	int open_pager();	
	unsigned long get_page_size();
	off_t fsize();
	void sync_pages();
	void *get_page(int page_no);
	int write_page(void *page, int page_no);
	int close_pager();
};
#endif
