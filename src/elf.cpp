#include "elf.h"
#include <assert.h>

bool elf::is_little_endian()
{
	return get_ei_data() == 1;
}

elf::half elf::get_little_endian(elf::half half)
{
	return (half >> 8) | (half << 8);
}

elf::word elf::get_little_endian(elf::word word)
{
	return ((word >> 24) & 0xff) |
		((word << 8) & 0xff0000) |
		((word >> 8) & 0xff00) |
		((word << 24) & 0xff000000);
}

elf::half elf::get_proper_endian(elf::half half)
{
	if (is_little_endian())
	{
		return get_little_endian(half);
	}

	return half;
}

elf::word elf::get_proper_endian(elf::word word)
{
	if (is_little_endian())
	{
		return get_little_endian(word);
	}

	return word;
}

elf::elf(const char* path)
	:m_file(path, "r")
{
	assert(verify_magic_numbers());
}

std::array<byte, 16> elf::get_magic()
{
	m_file.reset();
	return m_file.read<16>();
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
	m_file.seek(20, SEEK_SET);
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

void elf::print_magic(std::array<byte, 16> arr)
{
	for (size_t i = 0; i < 15; i++)
	{
		printf("%02x ", arr[i]);
	}

	printf("%02x\n", arr[15]);
}

const char* elf::ei_class_text(byte ei_class)
{
	switch (ei_class)
	{
	case 0:
		return "ELFNONE";
	case 1:
		return "ELF32";
	case 2:
		return "ELF64";
	default:
		return "";
	}
}

const char* elf::ei_data_text(byte ei_data)
{
	switch (ei_data)
	{
	case 0:
		return "Invalid Encoding";
	case 1:
		return "2's complement, little endian";
	case 2:
		return "2's complement, big endian";
	default:
		return "";
	}
}

const char* elf::ei_version_text(byte ei_version)
{
	switch (ei_version)
	{
	case 0:
		return "0 (invalid)";
	case 1:
		return "1 (current)";
	default:
		return "";
	}
}

const char* elf::ei_osabi_text(byte ei_osabi)
{
	switch (ei_osabi)
	{
	case 0:
	case 1:
		return "UNIX System V ABI";
	case 2:
		return "HP-UX ABI";
	case 3:
		return "NetBSD ABI";
	case 4:
		return "Linux ABI";
	case 5:
		return "Solaris ABI";
	case 6:
		return "IRIX ABI";
	case 7:
		return "FreeBSD ABI";
	case 8:
		return "TRU64 UNIX ABI";
	case 9:
		return "ARM architecture ABI";
	case 10:
		return "Stand-alone (embedded) ABI";
	default:
		return "";
	}
}

const char* elf::ei_abitversion_text(byte ei_abiversion)
{
	switch (ei_abiversion)
	{
	case 0:
		return "0";
	default:
		return "INVALID";
	}
}

const char* elf::elf_type_text(elf::half elf_type)
{

	elf_type = get_proper_endian(elf_type);

	switch (elf_type)
	{
	case 0:
		return "NONE";
	case 1:
		return "Relocatable File";
	case 2:
		return "Executable File";
	case 3:
		return "Shared Object File";
	case 4:
		return "Core File";
	case 0xff00:
		return "LoProc";
	case 0x00ff:
		return "HiProc";
	default:
		return "INVALID";
	}
}

const char* elf::elf_machine_text(elf::half elf_machine)
{
	elf_machine = get_proper_endian(elf_machine);

	if (elf_machine == 0x40)
	{
		return "Advanced Micro Devices X86-64";
	}

	return "INVALID";
}

const char* elf::elf_version_text(elf::word elf_version)
{
	if (elf_version == 1)
	{
		return "0x1";
	}

	return "INVALID";
}