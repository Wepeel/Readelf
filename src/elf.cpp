#include "elf.h"
#include <assert.h>

elf::elf(const char* path)
	:m_file(path, "r")
{
	assert(verify_magic_numbers());
}

bool elf::verify_magic_numbers()
{
	auto vec = m_file.read(4);

	if (0x7f != vec[0])
	{
		return false;
	}

	if ('E' != vec[1])
	{
		return false;
	}

	if ('L' != vec[2])
	{
		return false;
	}

	if ('F' != vec[3])
	{
		return false;
	}

	return true;
}