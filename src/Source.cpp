#include "elf.h"
#include <stdlib.h>

int main()
{
	// The working directory for the program is the top folder

	elf file("file/readelf");

	printf("%u\n", file.get_ei_class());
	printf("%u\n", file.get_ei_data());
	printf("%u\n", file.get_ei_version());
	printf("%u\n", file.get_ei_osabi());
	printf("%u\n", file.get_ei_abiversion());

	//system("ls -al");

	return 0;
}