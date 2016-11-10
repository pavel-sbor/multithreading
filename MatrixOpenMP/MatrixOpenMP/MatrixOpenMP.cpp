#include "stdafx.h"

#include<iostream>
#include<fstream>
#include <string>
#include<omp.h>
#include"Matrix.h"
using namespace std;
int main(int argc, char *argv[])
{
	double endTime, startTime;
	startTime = omp_get_wtime();
	if (argc != 3) {
		cerr << "Wrong number of arguments!" << endl;
	}
	Matrix firstMatrix, secondMatrix;
	ifstream matrixFile; 
	matrixFile.open(argv[1]);
	if (matrixFile.is_open()) {
		matrixFile >> firstMatrix;
	}
	else {
		cerr << "Unable to open file: " << argv[1] << endl;
	}
	matrixFile.close();
	matrixFile.open(argv[2]);
	if (matrixFile.is_open()) {
		matrixFile >> secondMatrix;
	}
	else {
		cerr << "Unable to open file: " << argv[2] << endl;
	}
	matrixFile.close();
	ofstream outputFile;
	outputFile.open("output.txt");
	Matrix multiplication = firstMatrix*secondMatrix;
	outputFile << multiplication;
	outputFile.close();
	endTime = omp_get_wtime();
	cout << "Overall time = " << endTime - startTime << " sec" << endl;
	system("PAUSE");
    return 0;
}


