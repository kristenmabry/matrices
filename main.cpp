#include <iostream>
#include <chrono>
#include <ctime>
#include "csquarematrix.h"
#include "clist.h"
using namespace std;

void Commands();
void DisplayGUI();
void AddMatrices() { }
LNode* NewMatrix(LNode** head);
void EditMatrix() { }
void GetInverse(LNode* head);
void MultiplyMatrices() { }
LNode* RemoveMatrix(LNode* head);
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
	cout << *transpose << endl << endl;
	cout << *inverse << endl << endl;

	CSquareMatrix* product = Multiply(m1, *inverse);
	cout << *product << endl << endl;

	delete product;
	delete inverse;
	delete transpose;

	Commands();
	return 1;
}



void Commands()
{
	LNode* list = new LNode();
	list->item = new CSquareMatrix(3, "Default");
	list->next = NULL;
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
				list = NewMatrix(&list);
				break;
			case 'D':
				DisplayList(list);
				break;
			case 'E':
				EditMatrix();
				break;
			case 'I':
				GetInverse(list);
				break;
			case 'M':
				MultiplyMatrices();
				break;
			case 'R':
				list = RemoveMatrix(list);
				break;
			case 'S':
				ScalarMultiplication();
				break;
			case 'T':
				GetTranspose();
				break;
			case 'Q':
				quit = true;
				FreeNodes(&list);
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
	cout << "D) Display your list\n";
	cout << "E) Edit a matrix\n";
	cout << "I) Inverse\n";
	cout << "M) Matrix multiplication\n";
	cout << "R) Remove a matrix\n";
	cout << "S) Scalar multiplication\n";
	cout << "T) Transpose\n";
	cout << "Q) Quit\n";
	cout << "Please enter a command: ";
}


LNode* NewMatrix(LNode** head)
{
	int dimension;
	cout << "Choose a dimension: ";
	cin >> dimension;
	string name;
	cout << "Choose a name: ";
	cin >> name;

	CSquareMatrix* newMatrix = new CSquareMatrix(dimension, name);
	*head = InsertItem(*head, newMatrix);

	return *head;
} // end of "NewMatrix"



LNode* RemoveMatrix(LNode* head)
{
	if (head == NULL)
		{
		cout << "List is empty...\n";
		return head;
		}

	string name;
	cout << "Enter the name of the matrix to remove: ";
	cin >> name;

	bool success;
	head = DeleteItem(head, name, success);

	if (!success)
		{
		cout << "Name not found..." << endl;
		}

	return head;

} // end of "RemoveMatrix"


void GetInverse(LNode* head)
{
	string name;
	cout << "Choose a matrix: ";
	cin >> name;

	bool success;
	LNode* chosen = GetItem(head, name, success);
	if (success)
		{
		CSquareMatrix* inverse = Inverse(*(chosen->item));
		cout << *inverse << endl;
		InsertItem(head, inverse);	
		}
	else
		{
		cout << "Name not found..." << endl;
		}
} // end of "GetInverse"
