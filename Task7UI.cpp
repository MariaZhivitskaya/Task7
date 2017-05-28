#include <iostream>
#include <fstream>

using namespace std;

double mainElement(double** matr, int n, int position, int &row, int &column)
{
	double mainElem = 0;

	for (int i = position; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (fabs(matr[i][j]) > mainElem)
			{
				mainElem = matr[i][j];
				row = i;
				column = j;
			}
		}
	}

	return mainElem;
}

void changeRows(double** matr, int n, int row, int &inverse, int index)
{
	double currElem;

	for (int i = 0; i < n; i++)
	{
		currElem = matr[row][i];
		matr[row][i] = matr[index][i];
		matr[index][i] = currElem;
	}

	inverse++;
}

void changeColumns(double** matr, int n, int column, int &inverse, int index)
{
	double currElem;

	for (int i = 0; i < n; i++)
	{
		currElem = matr[i][column];
		matr[i][column] = matr[i][index];
		matr[i][index] = currElem;
	}

	inverse++;
}

void division(double** matr, int n, double mainElem, int index)
{
	for (int i = index; i < n; i++)
		matr[index][i] /= mainElem;

	double elem;

	for (int i = index + 1; i < n; i++)
	{
		elem = matr[i][index];
		if (elem != 0)
		{
			for (int j = index; j < n; j++)
			{
				matr[i][j] -= matr[index][j] * elem;
			}
		}
	}
}

double determinant(double** matr, int n)
{
	double det = 1;
	int inverse;
	int row;
	int column;
	double mainElem;
	
	for (int i = 0; i < n; i++)
	{
		mainElem = mainElement(matr, n, i, row, column);

		if (row != i)
			changeRows(matr, n, row, inverse, i);
		if (column != i)
			changeColumns(matr, n, column, inverse, i);

		division(matr, n, mainElem, i);

		det *= mainElem;
	}

	return pow(-1.0, inverse) * det;
}

int main()
{
	ifstream fin;
	int n;
	double** matr;
	
	fin.open("In.txt");
	fin >> n;

	matr = new double*[n];
	for (int i = 0; i < n; i++)
	{
		matr[i] = new double[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fin >> matr[i][j];
		}
	}

	fin.close();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matr[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << "The determinant of matrix: " << determinant(matr, n) << endl;

	for (int i = 0; i < n; i++)
	{
		delete matr[i];
	}
	delete matr;
	
	system("pause");
	return 0;
}