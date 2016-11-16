#pragma once
#include <vector>
class Matrix
{
private:
	std::vector<std::vector<double>> data;
	int cols, rows;
	void checkData(std::vector<std::vector<double>>);
public:
	Matrix();
	Matrix(std::vector<std::vector<double>> data);
	Matrix(int n, int j);
	void setData(std::vector<std::vector<double>> data);
	std::vector<std::vector<double>> getData();
	std::vector<double>& operator[](const int n);
	int getCols();
	int getRows();
	~Matrix();
	Matrix operator*(Matrix matrix);
	friend std::istream &operator>> (std::istream  &input, Matrix &matrix);
	friend std::ostream &operator << (std::ostream  &output, Matrix &matrix);
};

