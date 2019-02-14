#include <iostream>
#include <chrono>
#include <ctime>
#include "csquarematrix.h"
using namespace std;


int main()
{
	srand ( time(NULL) );
	int dim;
	cout << "Dimension: ";
	cin >> dim;
	CSquareMatrix m1(dim);

	cout << m1 << endl;

	auto start1 = chrono::high_resolution_clock::now();
	int det = m1.Determinant();
	auto end1 = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> elapsed1 = end1 - start1;
	cout << det << endl;
	cout << elapsed1.count() << " ms" << endl;

	CSquareMatrix* inverse = Inverse(m1);
	CSquareMatrix* transpose = Transpose(m1);
	cout << "Transpose: " << endl << *transpose << endl << endl;
	cout << "Inverse: " << endl << *inverse << endl << endl;

	CSquareMatrix* product = Multiply(m1, *inverse);
	cout << "Product: " << endl << *product << endl << endl;

	delete product;
	delete inverse;
	delete transpose;

	return 1;
}
