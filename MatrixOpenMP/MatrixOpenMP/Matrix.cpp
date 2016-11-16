#include "stdafx.h"
#include "Matrix.h"
#include <omp.h>
#include <iostream>
using namespace std;

void Matrix::checkData(vector<vector<double>> data) {
	int m = data[0].size();
	int i = 0;
#pragma omp parallel for shared(data) private(i)
	for (i = 0; i < data.size(); i++) {
		//cout << "Thread " << num << " size: " << data[i].size() << " iteration: " << i << endl;
		if (data[i].size() != m)
		{
			cerr << "Matrix is not rectangle";
			exit(1);
		}
	}
}

Matrix::Matrix()
{

}

Matrix::Matrix(vector<vector<double>> data)
{
	setData(data);
}

Matrix::Matrix(int n, int m)
{
	vector<vector<double>> newData(n, vector<double>(m));
	rows = n;
	cols = m;
	data = newData;
}

void Matrix::setData(vector<vector<double>> data) {
	checkData(data);
	Matrix::data = data;
	rows = data.size();
	cols = data[0].size();
}
vector<vector<double>> Matrix::getData() {
	return data;
}

vector<double>& Matrix::operator[](const int n) {
	return data[n];
}

int Matrix::getCols() {
	return cols;
}

int Matrix::getRows() {
	return rows;
}

Matrix::~Matrix()
{
}

istream &operator >> (istream &input, Matrix &matrix) {
	try {
		int n = 0, m = 0;
		input >> n >> m;
		if (n < 0) {
			cerr << "Nagative dimention of the matrix: " << n;
			exit(1);
		}
		if (m < 0) {
			cerr << "Nagative dimention of the matrix: " << m;
			exit(1);
		}
		matrix = Matrix(n, m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (!input.eof()) {
					input >> matrix[i][j];
				}
				else {
					break;
				}
			}
		}
	}
	catch (exception& e) {
		cerr << "Unable to read matrix: " << e.what() << endl;
	}
	return input;
}

ostream &operator << (ostream  &output, Matrix &matrix) {
	for (int i = 0; i < matrix.getRows(); i++) {
		for (int j = 0; j < matrix.getCols(); j++) {
			output << matrix[i][j] << " ";
		}
		output << endl;
	}
	return output;
}

Matrix Matrix::operator*(Matrix matrix) {
	if (getCols() != matrix.getRows()) {
		cerr << "Dimensions does not match!";
		exit(1);
	}
	Matrix resultMatrix(getRows(), matrix.getCols());
	int i, j, ij;
#pragma omp parallel for shared(matrix, resultMatrix) private(i, j, ij)
	for (ij = 0; ij < getRows()*matrix.getCols(); ij++) {
		i = ij / matrix.getCols();
		j = ij % matrix.getCols();
		for (int k = 0; k < getCols(); k++) {
			resultMatrix[i][j] += ((*this)[i][k]) * matrix[k][j];
		}
	}
	return resultMatrix;
}