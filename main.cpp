#include <iostream>
#include <fstream>

char grey[10] = {'@', '%', '#', '*', '+', '=', '-', ':', '.', ' '};


int main(int argc, char** argv){

	std::string filePath = "test.ppm";
	std::ifstream in(filePath);

	std::string word;
	int w, h;

	in >> word >> w >> h >> word;

	int value;

	system("clear");

	for(int y = 0; y < h; y++){
		for(int x = 0; x < w; x++){
			in >> value >> value >> value;
			std::cout << " " << grey[int(value/25.5)];
		}
		std::cout << "\n";
	}
	in.close();
	return 0;
}
