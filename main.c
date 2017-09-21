	


#include "functions.h"

int main(int argc, char const *argv[])
{
	processing_arguments(argc, argv); 

	fclose(output_f);
	if (input_f) fclose(input_f);
	return 0;
}