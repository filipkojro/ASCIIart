#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <thread>
#include <vector>
#include "raylib.h"

bool startFlag = false;

char grey[10] = {'@', '%', '#', '*', '+', '=', '-', ':', '.', ' '};


double gammaExpr(int c){
	double cl = c / 255.0;

	if(cl <= 0.04045) return cl/12.92;
	
	return pow((cl+0.055)/1.055,2.4);
}


void job(int* tabIn, double* tabOut, int start, int end){
	
	while (!startFlag) {}
	
	for(int i = start; i < end; i++){
		tabOut[i] = gammaExpr(tabIn[i*3])*0.2126+gammaExpr(tabIn[i*3 + 1])*0.7152+gammaExpr(tabIn[i*3 + 2])*0.0722;
	}
}

int main(int argc, char** argv){

	char* fileName = "";
	std::string outFileName = "";
	int numOfThreads = 0;
	int width = 0;
	int height = 0;
	int testCount = 10;

	for(int i = 1; i < argc; i++){

		std::string arg = argv[i];

		if(arg == "--file"){
			i++;
			fileName = argv[i];
			std::cout << "file: " << fileName << "\n";
		}
		else if(arg == "--core"){
			i++;
			numOfThreads = std::atoi(argv[i]);
			std::cout << "thread count: " << numOfThreads << "\n";
		}
		else if(arg == "--test"){
			i++;
			testCount = std::atoi(argv[i]);
			std::cout << "test count: " << testCount << "\n";
		}
		else if(arg == "--size"){
			i++;
			width = std::atoi(argv[i]);
			i++;
			height = std::atoi(argv[i]);
			std::cout << "custom size: " << width << " " << height << "\n";
		}
		else if(arg == "--output"){
			i++;
			outFileName = argv[i];
			std::cout << "output file: " << outFileName << "\n";
		}
		else{
			std::cout << "unknown argument\n";
			exit(0);
		}
	}

	Image img;
	Color* colors;

	int* tabIn;
	int tabOutSize;
	double* tabOut;

	if(numOfThreads == 0) numOfThreads = std::thread::hardware_concurrency();

	if(width != 0 && height != 0){

		tabIn = new int[width * height * 3];

		tabOut = new double[width * height];

		for(int x = 0; x < width; x++){
			for(int y = 0; y < height; y++){
				tabIn[(y * width + x) * 3] = x * (255.0 / width);
				tabIn[(y * width + x) * 3 + 1] = y * (255.0 / height);
				tabIn[(y * width + x) * 3 + 2] = x * (255.0 / width) * y * (255.0 / height) / 255.0;
			}
		}
	}
	else{
		std::string fn = fileName;
		if(fn != ""){
			img = LoadImage(fileName);
		}
		else{
			img = LoadImage("test.png");
		}

		colors = LoadImageColors(img);

		width = img.width;
		height = img.height;

		tabIn = new int[width * height * 3];
		tabOut = new double[width * height];

		for(int i = 0; i < width * height; i++){
			tabIn[i*3] = colors[i].r;
			tabIn[i*3 + 1] = colors[i].g;
			tabIn[i*3 + 2] = colors[i].b;
		}
	}

	double average = 0;

	for(int test = 0; test < testCount; test++){

		std::vector<std::thread>jobs;

		for(int i = 0; i < numOfThreads;i++){
			int start = i * (width * height / numOfThreads);
			int end = start + (width * height / numOfThreads);

			jobs.push_back(std::thread(job, tabIn, tabOut, start, end));
		}

		auto timeStart = std::chrono::high_resolution_clock::now();
		startFlag = true;

		for(int i = 0; i < numOfThreads;i++) jobs[i].join();	

		auto timeStop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timeStop - timeStart);

		std::cout << test << " done in " << duration.count() / 1000000.0 << "\n";
		average += duration.count() / 1000000.0;
	}

	average /= testCount;

	std::cout << "average time: " << average << "\n";

	if(outFileName != ""){
		std::ofstream out(outFileName);
		for(int y = 0; y < height; y++){
			for(int x = 0; x < width; x++){
				out << grey[int(tabOut[y * width + x] * 10)] << " ";
			}
			out << "\n";
		}
		out.close();
	}

	return 0;
}
