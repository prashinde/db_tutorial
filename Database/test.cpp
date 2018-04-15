#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>

int main(int argc, char *argv[])
{
	if(argc < 2) {
		std::cout << "./exec <data file>" << std::endl;
		return -EINVAL;
	}

	std::ifstream in(argv[1]);
    
    if(!in.is_open()) {
        std::cout << "Failed to open file:" << argv[1] << std::endl;
        return -EINVAL;
    }

    unsigned long long len = 0;
    int total = 0;
	std::string line;
	while(in.good()) {
		std::getline(in, line);
		//std::cout << line << std::endl;
        len += line.length();
        total++;
	}
   
    std::cout << "Total lines:" << total << std::endl; 
    std::cout << "Total length:" << len << std::endl; 
    std::cout << "Average length is:" << ((float)len)/((float)total) << std::endl;
    in.close();
	return 0;
}
