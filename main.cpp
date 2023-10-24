#include <stdio.h>
#include <vector>

char grey[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

int main(){

	FILE *fptr;

	fptr = fopen("test.ppm", "r");
	
	char letter;

	std::vector<char> vec;

	for(int i = 0; i < 15; i++){
		letter = fgetc(fptr);
		vec.push_back(letter);
	}
	fclose(fptr);
	return 0;
}
