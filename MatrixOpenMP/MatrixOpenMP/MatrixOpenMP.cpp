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
	if (argc != 4) {
		cerr << "Wrong number of arguments!" << endl;
	}
	Matrix firstMatrix, secondMatrix;
#pragma omp parallel 
	{
#pragma omp sections
		{
#pragma omp section
			{
				ifstream matrixFile1;
				matrixFile1.open(argv[1]);
				if (matrixFile1.is_open()) {
					matrixFile1 >> firstMatrix;
				}
				else {
					cerr << "Unable to open file: " << argv[1] << endl;
				}
				matrixFile1.close();
			}
#pragma omp section
			{
				ifstream matrixFile2;
				matrixFile2.close();
				matrixFile2.open(argv[2]);
				if (matrixFile2.is_open()) {
					matrixFile2 >> secondMatrix;
				}
				else {
					cerr << "Unable to open file: " << argv[2] << endl;
				}
				matrixFile2.close();
			}
		}
	}
	cout << "Start multiplication of " << firstMatrix.getRows() << "x" << firstMatrix.getCols()
		<< " and " << secondMatrix.getRows() << "x" << secondMatrix.getCols() << " matrixes" << endl;
	ofstream outputFile;
	outputFile.open(argv[3]);
	Matrix multiplication = firstMatrix*secondMatrix;
	outputFile << multiplication;
	outputFile.close();
	endTime = omp_get_wtime();
	cout << "Overall time = " << endTime - startTime << " sec" << endl;
	return 0;
}


