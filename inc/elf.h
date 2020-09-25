#pragma once

#include "file.h"

// table of imported symbols
// table of exported symbols


class elf
{

public:

	using addr = uint32_t;
	using half = uint16_t;
	using off = uint32_t;
	using sword = uint32_t;
	using word = int32_t;

	elf(const char* path);

	std::array<byte, 16> get_magic();

	byte get_ei_class();

	byte get_ei_data();

	byte get_ei_version();

	byte get_ei_osabi();

	byte get_ei_abiversion();

	half get_elf_type();

	half get_elf_machine();

	word get_elf_version();

	addr get_elf_entry();

	static void print_magic(std::array<byte, 16> arr);


private:

	bool verify_magic_numbers();


private:

	file m_file;
};