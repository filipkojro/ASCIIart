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
	Image img;
	if(argc >= 2) img = LoadImage(argv[1]);
	else img = LoadImage("../test.png");

	Color* colors = LoadImageColors(img);

	//std::string word;
	//int w, h;

	//in >> word >> w >> h >> word;


	int* tabIn = new int[img.width * img.height * 3];
	double* tabOut = new double[img.width * img.height];

	for(int i = 0; i < img.width * img.height; i++){
		//in >> tabIn[i*3] >> tabIn[i*3 + 1] >> tabIn[i*3 + 2];

		tabIn[i*3] = colors[i].r;
		tabIn[i*3 + 1] = colors[i].g;
		tabIn[i*3 + 2] = colors[i].b;
	}



	int numOfThreads;

	if(argc == 3)numOfThreads = std::atoi(argv[2]);
	else numOfThreads = std::thread::hardware_concurrency();
	//

	for(int test = 0; test < 10; test++){

		std::vector<std::thread>jobs;

		for(int i = 0; i < numOfThreads;i++){
			int start = i * (img.width * img.height / numOfThreads);
			int end = start + (img.width * img.height / numOfThreads);

			jobs.push_back(std::thread(job, tabIn, tabOut, start, end));
		}

		auto timeStart = std::chrono::high_resolution_clock::now();
		startFlag = true;

		for(int i = 0; i < numOfThreads;i++) jobs[i].join();	

		auto timeStop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timeStop - timeStart);

		std::cout << test << " done in " << duration.count() / 1000000.0 << "\n";
	}
	

	/*
	for(int y = 0; y < img.height; y++){
		for(int x = 0; x < img.width; x++){
			std::cout << grey[int(tabOut[y * img.width + x] * 10)] << " ";
		}
		std::cout << "\n";
	}
	*/


	//in.close();
	return 0;
}
