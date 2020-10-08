#include "elf_reader.h"

template<size_t size>
void print_byte_array(std::array<byte, size> arr)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%02x ", arr[i]);
	}

	printf("%02x\n", arr[size - 1]);
}

void print_string_vector(const std::vector<std::string>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		printf("%zu: %s\n", i, vec[i].c_str());
	}
}

int main()
{
	// The working directory for the program is the top folder

	elf_reader file("file/readelf");

	// Print ELF header
#pragma region Print ELF Header

	printf("Elf Header:\n");

	printf(" %-20s", "Magic:");
	print_byte_array(file.get_magic());

	print_string_vector(file.get_symbol_names());
	print_string_vector(file.get_dynsymbol_names());

	return 0;
}