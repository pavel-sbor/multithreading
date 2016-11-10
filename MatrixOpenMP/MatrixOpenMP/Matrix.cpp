#include "stdafx.h"
#include "Matrix.h"
#include <iostream>
using namespace std;

void Matrix::checkData(vector<vector<double>> data) {
	int m = data[0].size();
	for each (vector<double> v in data) {
		if (v.size() != m)
		{
			throw exception("Matrix is not rectangle");
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

void Matrix::setData(vector<vector<double>> data) {
	checkData(data);
	Matrix::data = data;
	rows = data.size();
	cols = data[0].size();
}
vector<vector<double>> Matrix::getData() {
	return data;
}

double Matrix::operator()(int i, int j) {
	return data[i][j];
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
		vector<vector<double>> data;
		int n = 0, m = 0;
		input >> n >> m;
		if (n < 0) {
			throw exception("Nagative dimention of the matrix: " + n);
		}
		if (m < 0) {
			throw exception("Nagative dimention of the matrix: " + m);
		}
		for (int i = 0; i < n; i++) {
			vector<double> row;
			for (int j = 0; j < m; j++) {
				if (!input.eof()) {
					double var;
					input >> var;
					row.push_back(var);
				}
				else {
					break;
				}
			}
			data.push_back(row);

		}
		matrix.setData(data);
	}
	catch (exception& e) {
		cerr << "Unable to read matrix: " << e.what() << endl;
	}
	return input;
}

ostream &operator << (ostream  &output, Matrix &matrix) {
	for (int i = 0; i < matrix.getRows(); i++) {
		for (int j = 0; j < matrix.getCols(); j++) {
			//cout << matrix.getCell(i, j) << " ";
			output << matrix(i, j) << " ";
		}
		output << endl;
	}
	return output;
}

Matrix Matrix::operator*(Matrix matrix) {
	if (getCols() != matrix.getRows()) {
		throw exception("Dimensions does not match!");
	}
	vector<vector<double>> data;
	for (int i = 0; i < getRows(); i++) {
		vector<double> row;
		for (int j = 0; j < matrix.getCols(); j++) {
			double cellResult = 0;
			for (int k = 0; k < getCols(); k++) {
				cellResult += ((*this)(i, k)) * matrix(k, j);
			}
			row.push_back(cellResult);
		}
		data.push_back(row);
	}
	return Matrix(data);
}