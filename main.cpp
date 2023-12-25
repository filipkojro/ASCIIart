#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

char grey[10] = {'@', '%', '#', '*', '+', '=', '-', ':', '.', ' '};


double gammaExpr(int c){
	double cl = c / 255.0;

	if(cl <= 0.04045) return cl/12.92;
	
	return pow((cl+0.055)/1.055,2.4);
}

int main(int argc, char** argv){

	std::string filePath = "123.ppm";
	std::ifstream in(filePath);
	

	std::string word;
	int w, h;

	in >> word >> w >> h >> word;

	int r, g, b;

	//system("clear");

	for(int i = 0; i < 10; i++){

		std::string outName = "output0.txt";
		outName[6] = char(i + 48);

		auto start = std::chrono::high_resolution_clock::now();

		std::ofstream out(outName);

		for(int y = 0; y < h; y++){
			for(int x = 0; x < w; x++){
				in >> r >> g >> b;

				double gama = gammaExpr(r)*0.2126+gammaExpr(g)*0.7152+gammaExpr(b)*0.0722;

				//std::cout << grey[int(gama * 10)] << " ";
				out << grey[int(gama * 10)] << " ";



				//out << int(gama * 255) <<"\n"<< int(gama * 255) <<"\n"<< int(gama * 255) <<"\n";
				//out << r << "\n" << g << "\n" << b << "\n";

			}
			//std::cout << "\n";
			out << "\n";
		}

		out.close();

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		std::cout << i << " done in " << duration.count() / 1000000.0 << "\n";
	}

	//std::cout << pow(2.0, 10.0);
	//out << pow(2.0, 10.0);
	
	
	in.close();
	return 0;
}
