#include "file.h"

file::file(const char* path, const char* perm)
{
	m_ptr = fopen(path, perm);
}

file::~file()
{
	fclose(m_ptr);
}

void file::reset()
{
	rewind(m_ptr);
}

byte file::read_byte()
{
	return fgetc(m_ptr);
}

std::vector<byte> file::read(size_t bytes_to_read)
{
	std::vector<byte> ret;

	for (size_t i = 0; i < bytes_to_read; ++i)
	{
		byte b;
		size_t bytes_read = fread(&b, sizeof(byte), 1, m_ptr);

		if (1 != bytes_read)
		{
			break;
		}

		ret.push_back(b);
	}

	return ret;
}

void file::seek(long offset, int origin)
{
	fseek(m_ptr, offset, origin);
}