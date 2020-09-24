#pragma once

#include "file.h"

// table of imported symbols
// table of exported symbols

class elf
{

public:

	elf(const char* path);


private:

	bool verify_magic_numbers();


private:

	file m_file;
};