#ifndef __PAGER_H_
#define __PAGER_H_

#include <string>
#include <fstream>

class pager {
private:
	unsigned long page_size;
	std::ofstream pfstream;
	std::string fname;
public:
	pager();
	pager(unsigned long page_size, std::string fname);
	int open_pager();
	unsigned long get_page_size();
	void *read_page(int page_no);
	void write_page(void *page);
	int close_pager();
};
#endif
