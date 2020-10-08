#include "elf_reader.h"
#include <assert.h>


template<size_t T>
bool equal_byte_array(std::array<byte, T> arr1, std::array<byte, T> arr2)
{
	for (size_t i = 0; i < T; ++i)
	{
		if (arr1[i] != arr2[i])
		{
			return false;
		}
	}

	return true;
}

elf_reader::elf_reader(const char* path)
	:m_file(path, "r")
{
	assert(verify_magic_numbers());
}

Elf64_Ehdr elf_reader::get_elf_header()
{
	m_file.reset();
	return m_file.read<Elf64_Ehdr>();
}

std::array<byte, 16> elf_reader::get_magic()
{
	Elf64_Ehdr hdr = get_elf_header();

	std::array<byte, 16> ret;

	std::copy(std::begin(hdr.e_ident), std::end(hdr.e_ident), std::begin(ret));

	return ret;
}

Elf64_Shdr elf_reader::get_symbol_table()
{
	Elf64_Ehdr elf_header = get_elf_header();

	m_file.seek(elf_header.e_shoff, SEEK_SET);

	for (size_t i = 0; i < elf_header.e_shnum; i++)
	{
		Elf64_Shdr section_header = m_file.read<Elf64_Shdr>();
		if (section_header.sh_type == SHT_SYMTAB)
		{
			return section_header;
		}
	}

	return Elf64_Shdr();
}

Elf64_Shdr elf_reader::get_dynsymbol_table()
{
	Elf64_Ehdr elf_header = get_elf_header();

	m_file.seek(elf_header.e_shoff, SEEK_SET);

	for (size_t i = 0; i < elf_header.e_shnum; i++)
	{
		Elf64_Shdr section_header = m_file.read<Elf64_Shdr>();
		if (section_header.sh_type == SHT_DYNSYM)
		{
			return section_header;
		}
	}

	return Elf64_Shdr();
}

Elf64_Shdr elf_reader::get_string_table()
{
	Elf64_Ehdr elf_header = get_elf_header();

	m_file.seek(elf_header.e_shoff, SEEK_SET);

	for (size_t i = 0; i < elf_header.e_shnum; i++)
	{
		Elf64_Shdr section_header = m_file.read<Elf64_Shdr>();
		if (section_header.sh_type == SHT_STRTAB)
		{
			return section_header;
		}
	}

	return Elf64_Shdr();
}

Elf64_Shdr elf_reader::get_dynstring_table()
{
	Elf64_Ehdr elf_header = get_elf_header();

	m_file.seek(elf_header.e_shoff, SEEK_SET);

	for (size_t i = 0; i < elf_header.e_shnum; i++)
	{
		Elf64_Shdr section_header = m_file.read<Elf64_Shdr>();
		if (section_header.sh_type == SHT_DYNSYM)
		{
			return section_header;
		}
	}

	return Elf64_Shdr();
}

std::vector<std::string> elf_reader::get_symbol_names()
{
	Elf64_Shdr symbol_table = get_symbol_table();

	if (0 != symbol_table.sh_size)
	{
		Elf64_Shdr string_table = get_string_table();


		std::vector<std::string> ret;

		for (size_t i = 0; i < symbol_table.sh_size / symbol_table.sh_entsize; i++)
		{
			m_file.seek(symbol_table.sh_offset + i * sizeof(Elf64_Sym), SEEK_SET);
			Elf64_Word sym_index = m_file.read<Elf64_Sym>().st_name;

			m_file.seek(string_table.sh_offset + sym_index, SEEK_SET);
			std::string symbol = m_file.read_string();

			ret.push_back(symbol);
		}

		return ret;
	}

	return std::vector<std::string>();
}

std::vector<std::string> elf_reader::get_dynsymbol_names()
{
	Elf64_Shdr symbol_table = get_dynsymbol_table();

	if (0 != symbol_table.sh_size)
	{

		Elf64_Shdr string_table = get_string_table();

		std::vector<std::string> ret;

		for (size_t i = 0; i < symbol_table.sh_size / symbol_table.sh_entsize; i++)
		{
			m_file.seek(symbol_table.sh_offset + i * sizeof(Elf64_Sym), SEEK_SET);
			Elf64_Word sym_index = m_file.read<Elf64_Sym>().st_name;

			m_file.seek(string_table.sh_offset + sym_index, SEEK_SET);
			std::string symbol = m_file.read_string();

			ret.push_back(symbol);
		}

		return ret;
	}

	return std::vector<std::string>();
}

bool elf_reader::verify_magic_numbers()
{
	std::array<byte, 16> magic = get_magic();

	std::array<byte, 4> check_bytes;
	std::copy(magic.begin(), magic.begin() + 4, check_bytes.begin());

	std::array<byte, 4> correct_magic_bytes = { ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3 };

	return equal_byte_array(correct_magic_bytes, check_bytes);
}

const char* elf_reader::ei_class_text(byte ei_class)
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

const char* elf_reader::ei_data_text(byte ei_data)
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

const char* elf_reader::ei_version_text(byte ei_version)
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

const char* elf_reader::ei_osabi_text(byte ei_osabi)
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

const char* elf_reader::ei_abitversion_text(byte ei_abiversion)
{
	switch (ei_abiversion)
	{
	case 0:
		return "0";
	default:
		return "INVALID";
	}
}

//const char* elf_reader::elf_type_text(elf_reader::half elf_type)
//{
//
//	//elf_type = get_proper_endian(elf_type);
//
//	switch (elf_type)
//	{
//	case 0:
//		return "NONE";
//	case 1:
//		return "Relocatable File";
//	case 2:
//		return "Executable File";
//	case 3:
//		return "Shared Object File";
//	case 4:
//		return "Core File";
//	case 0xff00:
//		return "LoProc";
//	case 0x00ff:
//		return "HiProc";
//	default:
//		return "INVALID";
//	}
//}
//
//const char* elf_reader::elf_machine_text(elf_reader::half elf_machine)
//{
//	//elf_machine = get_proper_endian(elf_machine);
//
//	if (elf_machine == 0x40)
//	{
//		return "Advanced Micro Devices X86-64";
//	}
//
//	return "INVALID";
//}
//
//const char* elf_reader::elf_version_text(elf_reader::word elf_version)
//{
//	if (elf_version == 1)
//	{
//		return "0x1";
//	}
//
//	return "INVALID";
//}