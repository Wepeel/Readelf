#pragma once

#include <stdio.h>
#include <vector>
#include <array>
#include <stdint.h>

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

	uint16_t read_uint16();

	uint32_t read_uint32();

	int32_t read_int32();

	void seek(long offset, int origin);


private:

	FILE* m_ptr;

};