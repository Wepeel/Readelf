#include "elf.h"
#include <assert.h>

elf::elf(const char* path)
	:m_file(path, "r")
{
	assert(verify_magic_numbers());
}

byte elf::get_ei_class()
{
	m_file.seek(4, SEEK_SET);
	return m_file.read_byte();
}

byte elf::get_ei_data()
{
	m_file.seek(5, SEEK_SET);
	return m_file.read_byte();
}

byte elf::get_ei_version()
{
	m_file.seek(6, SEEK_SET);
	return m_file.read_byte();
}

byte elf::get_ei_osabi()
{
	m_file.seek(7, SEEK_SET);
	return m_file.read_byte();
}

byte elf::get_ei_abiversion()
{
	m_file.seek(8, SEEK_SET);
	return m_file.read_byte();
}

elf::half elf::get_elf_type()
{
	m_file.seek(15, SEEK_SET);
	return m_file.read_uint16();
}

elf::half elf::get_elf_machine()
{
	m_file.seek(31, SEEK_SET);
	return m_file.read_uint16();
}

elf::word elf::get_elf_version()
{
	m_file.seek(47, SEEK_SET);
	return m_file.read_int32();
}

elf::addr elf::get_elf_entry()
{
	m_file.seek(79, SEEK_SET);
	return m_file.read_uint32();
}

bool elf::verify_magic_numbers()
{
	std::array<byte, 4> arr = m_file.read<4>();

	if (0x7f != arr[0])
	{
		return false;
	}

	if ('E' != arr[1])
	{
		return false;
	}

	if ('L' != arr[2])
	{
		return false;
	}

	if ('F' != arr[3])
	{
		return false;
	}

	return true;
}