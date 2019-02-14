#include <iostream>
#include <chrono>
#include <ctime>
#include "csquarematrix.h"
#include "csortedlist.h"
using namespace std;

void Commands();
void DisplayGUI();
void AddMatrices() { }
void NewMatrix() { }
void EditMatrix() { }
void GetInverse() { }
void MultiplyMatrices() { }
void RemoveMatrix() { }
void ScalarMultiplication() { }
void GetTranspose() { }


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



void Commands()
{
	bool quit = false;
	while (!quit)
		{
		DisplayGUI();
		char response;
		cin >> response;

		switch (toupper(response))
			{
			case 'A':
				AddMatrices();
				break;
			case 'C':
				NewMatrix();
				break;
			case 'E':
				EditMatrix();
				break;
			case 'I':
				GetInverse();
				break;
			case 'M':
				MultiplyMatrices();
				break;
			case 'R':
				RemoveMatrix();
				break;
			case 'S':
				ScalarMultiplication();
				break;
			case 'T':
				GetTranspose();
				break;
			case 'Q':
				quit = true;
				break;
			default:
				cout << "That command was not recognized.\n";
				break;
			}

			cout << endl;
		}
}



void DisplayGUI()
{
	cout << "A) Add two matrices\n";
	cout << "C) Create new matrix\n";
	cout << "E) Edit a matrix\n";
	cout << "I) Inverse\n";
	cout << "M) Matrix multiplication\n";
	cout << "R) Remove a matrix\n";
	cout << "S) Scalar multiplication\n";
	cout << "T) Transpose\n";
	cout << "Q) Quit\n";
	cout << "Please enter a command: ";
}
