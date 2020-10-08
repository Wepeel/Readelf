#pragma once

#include "file.h"
#include <elf.h>
#include <vector>
#include <string>
#include <array>

// table of imported symbols
// table of exported symbols


class elf_reader
{

public:

	elf_reader(const char* path);

	Elf64_Ehdr get_elf_header();

	std::array<byte, 16> get_magic();

	Elf64_Shdr get_symbol_table();

	Elf64_Shdr get_dynsymbol_table();

	Elf64_Shdr get_string_table();

	Elf64_Shdr get_dynstring_table();

	std::vector<std::string> get_symbol_names();

	std::vector<std::string> get_dynsymbol_names();

	static const char* ei_class_text(byte ei_class);

	static const char* ei_data_text(byte ei_data);

	static const char* ei_version_text(byte ei_version);

	static const char* ei_osabi_text(byte ei_osabi);

	static const char* ei_abitversion_text(byte ei_abiversion);


private:

	bool verify_magic_numbers();


private:

	file m_file;
};