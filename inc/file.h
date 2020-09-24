#pragma once

#include <stdio.h>
#include <vector>
#include <array>

using byte = unsigned char;

class file
{

public:

	file(const char* path, const char* perm);

	~file();

	void reset();

	template<size_t bytes_to_read>
	std::array<byte, bytes_to_read> read()
	{
		std::array<byte, bytes_to_read> ret;

		for (size_t i = 0; i < bytes_to_read; ++i)
		{
			size_t bytes_read = fread(&ret[i], sizeof(byte), 1, m_ptr);

			if (1 != bytes_read)
			{
				break;
			}
		}

		return ret;
	}

	std::vector<byte> read(size_t bytes_to_read);

	byte read_byte();

	void seek(long offset, int origin);


private:

	FILE* m_ptr;

};