#include "elf_reader.h"

#define HEX_STRING " %-30s %u\n"
#define PRINT_STRING " %-30s %s\n"

int main()
{
	// The working directory for the program is the top folder

	elf_reader file("file/readelf");

	// Print ELF header
#pragma region Print ELF Header

	printf("Elf Header:\n");

	printf(" %-20s", "Magic:");
	elf_reader::print_magic(file.get_magic());

	printf(PRINT_STRING, "Class:", elf_reader::ei_class_text(file.get_ei_class()));
	printf(PRINT_STRING, "Data:", elf_reader::ei_data_text(file.get_ei_data()));
	printf(PRINT_STRING, "Version:", elf_reader::ei_version_text(file.get_ei_version()));
	printf(PRINT_STRING, "OS/ABI:", elf_reader::ei_osabi_text(file.get_ei_osabi()));
	printf(PRINT_STRING, "ABI Version:", elf_reader::ei_abitversion_text(file.get_ei_abiversion()));

	printf(PRINT_STRING, "Type:", file.elf_type_text(file.get_elf_type()));
	printf(PRINT_STRING, "Machine:", file.elf_machine_text(file.get_elf_machine()));
	printf(PRINT_STRING, "Version:", file.elf_version_text(file.get_elf_version()));

	elf_reader::off shoff = file.get_elf_shoff();

#pragma endregion

	return 0;
}