#include <iostream>
#include <chrono>
#include <ctime>
#include "csquarematrix.h"
#include "clist.h"
using namespace std;

void Commands();
void DisplayGUI();
void AddMatrices(LNode* head);
LNode* NewMatrix(LNode** head);
void EditMatrix(LNode* head);
void FindDet(LNode* head);
void GetInverse(LNode* head);
void MultiplyMatrices(LNode* head);
LNode* RemoveMatrix(LNode* head);
void ScalarMultiplication(LNode* head);
void GetTranspose(LNode* head);
void SolveSystem(LNode* head);
LNode* SelectMatrix(LNode* head);



int main()
{
	srand ( time(NULL) );
	int dim;
	cout << "Dimension: ";
	cin >> dim;
	cin.ignore();
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

	double array[3] = {1, 2, 3};
	double* answers = CramersRule(m1, array);
	for (int i = 0; i < dim; i++)
		{
		cout << "Answer #" << i << ": " << answers[i] << endl;
		}

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
		cin.ignore();

		switch (toupper(response))
			{
			case 'A':
				AddMatrices(list);
				break;
			case 'C':
				list = NewMatrix(&list);
				break;
			case 'D':
				if (list)
					{
					DisplayList(list);
					}
				else
					{
					cout << "List is empty...\n";
					}
				break;
			case 'E':
				EditMatrix(list);
				break;
			case 'F':
				FindDet(list);
				break;
			case 'I':
				GetInverse(list);
				break;
			case 'M':
				MultiplyMatrices(list);
				break;
			case 'N':
				cout << FreeNodes(&list) << " item(s) released.\n";
				break;
			case 'R':
				list = RemoveMatrix(list);
				break;
			case 'S':
				ScalarMultiplication(list);
				break;
			case 'T':
				GetTranspose(list);
				break;
			case 'O':
				SolveSystem(list);
				break;
			case 'Q':
				quit = true;
				cout << FreeNodes(&list) << " item(s) released.\n";
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
	cout << "F) Find the determinant\n";
	cout << "I) Inverse\n";
	cout << "M) Matrix multiplication\n";
	cout << "N) Release list\n";
	cout << "O) Solve system of equations\n";
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
	cin.ignore();
	string name;
	cout << "Choose a name: ";
	cin.clear();
	getline(cin, name);

	CSquareMatrix* newMatrix = new CSquareMatrix(dimension, name);

	char response;
	cout << "M)anual or R)andom: ";
	cin >> response;
	cin.ignore();

	if (toupper(response) == 'M')
		{
		newMatrix->EnterElements();
		}
	*head = InsertItem(*head, newMatrix);
	cout << *newMatrix << endl;

	return *head;
} // end of "NewMatrix"



LNode* RemoveMatrix(LNode* head)
{
	if (!head)
		{
		cout << "List is empty...\n";
		return head;
		}

	string name;
	cout << "Enter the name of the matrix to remove: ";
	getline(cin, name);

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
	if (!head)
		{
		cout << "List is empty...\n";
		return;
		}
	LNode* chosen = SelectMatrix(head); 
	if (chosen)
		{
		CSquareMatrix* inverse = Inverse(*(chosen->item));
		if (inverse)
			{
			cout << *inverse << endl;
			InsertItem(head, inverse);	
			}
		else
			{
			cout << "Matrix is invertible...\n";
			}
		}
} // end of "GetInverse"

void ScalarMultiplication(LNode* head)
{
	if (!head)
		{
		cout << "List is empty...\n";
		return;
		}
	LNode* chosen = SelectMatrix(head);

	if (chosen)
		{
		double multiplier;
		cout << "Enter a scalar: ";
		cin >> multiplier;
		cin.ignore();
		CSquareMatrix* newMatrix = new CSquareMatrix(*(chosen->item));
		newMatrix->Scalar(multiplier);
		string name = to_string(multiplier) + " * ( " 
					+ chosen->item->GetName() + " )";
		newMatrix->SetName(name);
		cout << *newMatrix << endl;
		InsertItem(head, newMatrix);
		}
} // end of "ScalarMultiplication"



void GetTranspose(LNode* head)
{
	if (!head)
		{
		cout << "List is empty...\n";
		return;
		}
	LNode* chosen = SelectMatrix(head);

	if (chosen)
		{
		CSquareMatrix* transpose = Transpose(*(chosen->item));
		cout << *transpose;
		InsertItem(head, transpose);
		}
}	

LNode* SelectMatrix(LNode* head)
{
	string name;
	cout << "Choose a matrix: ";
	getline(cin, name);
	
	bool success;
	LNode* chosen = GetItem(head, name, success);

	if (!success)
		{
		cout << "Matrix not found...\n";
		}

	return chosen;

} // end of "SelectMatrix"



void MultiplyMatrices(LNode* head)
{
	if (!head)
		{
		cout << "List is empty...\n";
		return;
		}

	cout << "Matrix 1: \n";
	LNode* matrix1 = SelectMatrix(head);
	cout << "Matrix 2: \n";
	LNode* matrix2 = SelectMatrix(head);

	if (matrix1 && matrix2)
		{
		CSquareMatrix* result = Multiply(*(matrix1->item), *(matrix2->item));
		if (result)
			{
			cout << *result << endl;
			InsertItem(head, result);
			}
		else
			{
			cout << "Matrices are different dimensions...\n";
			}
		}
	else
		{
		cout << "One or more matrices missing...\n";
		}

} // end of "MultiplyMatrices"



void AddMatrices(LNode* head)
{
	if (!head)
		{
		cout << "List is empty...\n";
		return;
		}

	LNode* m1 = SelectMatrix(head);
	LNode* m2 = SelectMatrix(head);
	if (m1 && m2)
		{
		CSquareMatrix* added = AddMatrix(*(m1->item), *(m2->item));
		if (added)
			{
			cout << *added << endl;
			InsertItem(head, added);
			}
		else
			{
			cout << "The matrices have different dimensions...\n";
			}
		}
	else
		{
		cout << "One or more matrices not found...\n";
		}
		
} // end of "AddMatrices"



void EditMatrix(LNode* head)
{
	if (!head)
		{
		cout << "List is empty...\n";
		return;
		}

	LNode* chosen = SelectMatrix(head);
	
	if (chosen)
		{
		chosen->item->EnterElements();
		}

} // end of "Edit Matrix"



void FindDet(LNode* head)
{
	if (!head)
		{
		cout << "List is empty...\n";
		return;
		}
	
	LNode* chosen = SelectMatrix(head);

	if (chosen)
		{
		cout << "Determinant of " << chosen->item->GetName() << ": " <<
			chosen->item->Determinant() << endl;
		}

} // end of "Find Determinant"



void SolveSystem(LNode* head)
{
	if (!head)
		{
		cout << "List is empty...\n";
		return;
		}
	
	LNode* chosen = SelectMatrix(head);
	if (chosen)
		{
		int dim = chosen->item->GetDimension();
		double array[dim];
		for (int i = 0; i < dim; i++)
			{
			cout << "Enter b_" << i + 1 << ": ";
			cin >> array[i];
			}
		double* answers = CramersRule(*(chosen->item), array);
		if (answers)
			{
			for (int i = 0; i < dim; i++)
				{
				cout << "x_" << i+1 << " = " << answers[i] << endl;
				}
			delete []answers;
			}
		else
			{
			cout << "Dependent solutions currently unavailable...\n";
			}
		}

} // end of "Solve System"
