#include "elf.h"

int main()
{
	// The working directory for the program is the top folder

	elf file("file/readelf");

	// Print ELF header
#pragma region Print ELF Header

	printf("Elf Header:\n");

	printf(" %-20s", "Magic:");
	elf::print_magic(file.get_magic());

	printf(" %-20s %02x\n", "Class:", file.get_ei_class());
	printf(" %-20s %02x\n", "Data:", file.get_ei_data());
	printf(" %-20s %02x\n", "Version:", file.get_ei_version());
	printf(" %-20s %02x\n", "OS/ABI:", file.get_ei_osabi());
	printf(" %-20s %02x\n", "ABI Version:", file.get_ei_abiversion());

#pragma endregion

	return 0;
}