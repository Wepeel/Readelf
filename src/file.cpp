#include "file.h"

file::file(const char* path, const char* perm)
{
	m_ptr = fopen(path, perm);
}

file::~file()
{
	fclose(m_ptr);
}

std::vector<byte> file::read(size_t bytes_to_read)
{
	std::vector<byte> ret;
	ret.reserve(bytes_to_read);

	for (size_t i = 0; i < bytes_to_read; ++i)
	{
		byte b;
		auto bytes_read = fread(&b, sizeof(byte), 1, m_ptr);

		if (bytes_read != 1)
		{
			break;
		}

		ret.push_back(b);
	}

	return ret;
}