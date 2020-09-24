#pragma once

#include <stdio.h>
#include <vector>

using byte = unsigned char;

class file
{

public:

	file(const char* path, const char* perm);

	~file();


	std::vector<byte> read(size_t bytes_to_read);


private:

	FILE* m_ptr;

};