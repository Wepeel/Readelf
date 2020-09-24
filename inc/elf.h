#pragma once

#include "file.h"

// table of imported symbols
// table of exported symbols

class elf
{

public:

	elf(const char* path);

	byte get_ei_class();

	byte get_ei_data();

	byte get_ei_version();

	byte get_ei_osabi();

	byte get_ei_abiversion();


private:

	bool verify_magic_numbers();


private:

	file m_file;
};