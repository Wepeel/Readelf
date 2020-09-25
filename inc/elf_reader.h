#pragma once

#include "file.h"

// table of imported symbols
// table of exported symbols


class elf_reader
{

public:

	using addr = uint32_t;
	using half = uint16_t;
	using off = uint32_t;
	using sword = uint32_t;
	using word = int32_t;

	elf_reader(const char* path);

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

	off get_elf_shoff();

	static void print_magic(std::array<byte, 16> arr);

	static const char* ei_class_text(byte ei_class);

	static const char* ei_data_text(byte ei_data);

	static const char* ei_version_text(byte ei_version);

	static const char* ei_osabi_text(byte ei_osabi);

	static const char* ei_abitversion_text(byte ei_abiversion);

	const char* elf_type_text(half elf_type);

	const char* elf_machine_text(half elf_machine);

	const char* elf_version_text(word elf_version);

	half get_proper_endian(half);

	word get_proper_endian(word);

	bool is_little_endian();

	static half get_little_endian(half);

	static word get_little_endian(word);


private:

	bool verify_magic_numbers();


private:

	file m_file;
};