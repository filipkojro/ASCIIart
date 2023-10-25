#include <iostream>
#include <fstream>
#include <math.h>

char grey[10] = {'@', '%', '#', '*', '+', '=', '-', ':', '.', ' '};


double gammaExpr(int c){
	double cl = c / 255.0;

	if(cl <= 0.04045) return cl/12.92;
	
	return pow((cl+0.055)/1.055,2.4);
}

int main(int argc, char** argv){

	std::string filePath = "test.ppm";
	std::ifstream in(filePath);

	std::string word;
	int w, h;

	in >> word >> w >> h >> word;

	int r, g, b;
	
	//std::ofstream out("output.ppm", std::ios_base::out | std::ios_base::binary);

	//out << "p3\n" << w << " " << h << "\n" << "255\n";

	system("clear");

	for(int y = 0; y < h; y++){
		for(int x = 0; x < w; x++){
			in >> r >> g >> b;
			
			double gama = gammaExpr(r)*0.2126+gammaExpr(g)*0.7152+gammaExpr(b)*0.0722;

			std::cout << grey[int(gama * 10)] << " ";

			//out << int(gama * 255) <<"\n"<< int(gama * 255) <<"\n"<< int(gama * 255) <<"\n";
			//out << r << "\n" << g << "\n" << b << "\n";

		}
		std::cout << "\n";
	}
	
	std::cout << pow(2.0, 10.0);
	
	//out.close();
	in.close();
	return 0;
}
