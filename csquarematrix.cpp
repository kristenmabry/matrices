#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <string>
#include "csquarematrix.h"
using namespace std;
using namespace csquarematrix;

namespace csquarematrix
	{
	int NUM_MATRICES = 1;
	}

// type conversion
	CSquareMatrix::CSquareMatrix(int dimension, std::string name)
{
	m_dimension = dimension;
	m_matrix = new double*[m_dimension];
	if (name == "Matrix")
		{
		m_name = name + "(" + to_string(NUM_MATRICES) + ")";
		NUM_MATRICES++;
		}
	else
		{
		m_name = name;
		}
	for (int i = 0; i < m_dimension; i++)
		{
		m_matrix[i] = new double[m_dimension];
		for (int j = 0; j < m_dimension; j++)
			{
			int value;
			m_matrix[i][j] = static_cast<double>(rand() % 10) - 4.0;
			}
		}
}



// dim and num
	CSquareMatrix::CSquareMatrix(int dimension, int num, std::string name)
{
	m_dimension = dimension;
	m_matrix = new double*[m_dimension];
	if (name == "Matrix")
		{
		m_name = name + "(" + to_string(NUM_MATRICES) + ")";
		NUM_MATRICES++;
		}
	else
		{
		m_name = name;
		}
	for (int i = 0; i < m_dimension; i++)
		{
		m_matrix[i] = new double[m_dimension];
		for (int j = 0; j < m_dimension; j++)
			{
			m_matrix[i][j] = num;
			}
		}

}

// copy ctor
	CSquareMatrix::CSquareMatrix(const CSquareMatrix& other, std::string name)
{
	m_dimension = other.m_dimension;
	m_matrix = new double*[m_dimension];
	if (name == "Copy of ")
		{
		m_name = "Copy of " + other.m_name;
		NUM_MATRICES++;
		}
	else
		{
		m_name = name;
		}
	for (int i = 0; i < m_dimension; i++)
		{
		m_matrix[i] = new double[m_dimension];
		for (int j = 0; j < m_dimension; j++)
			{
			m_matrix[i][j] = other.m_matrix[i][j];
			}
		}

}

// dtor
	CSquareMatrix::~CSquareMatrix()
{
	for (int i = 0; i < m_dimension; i++)
		{
		delete[] m_matrix[i];
		}
	//cout << "[Deleting " << m_name << "] (dtor)" << endl;
	delete[] m_matrix;
}


CSquareMatrix& CSquareMatrix::operator=(const CSquareMatrix& rhs)
{
	if (this != &rhs)
		{
		if (m_dimension != rhs.m_dimension)
			{
			for (int i = 0; i < m_dimension; i++)
				{
				delete[] m_matrix[i];
				}
			delete[] m_matrix;
			}
		else
			{
			m_dimension = rhs.m_dimension;
			m_matrix = new double*[m_dimension];
			for (int i = 0; i < m_dimension; i++)
				{
				m_matrix[i] = new double[m_dimension];
				}
			}
		for (int i = 0; i < m_dimension; i++)
			{
			for (int j = 0; j < m_dimension; j++)
				{
				m_matrix[i][j] = rhs.m_matrix[i][j];
				}
			}
		}
	return *this;
}



bool operator==(const CSquareMatrix& lhs, const CSquareMatrix& rhs)
{
	if (&lhs == &rhs)
		{
		return true;
		}
	else if (lhs.m_dimension != rhs.m_dimension)
		{
		return false;
		}
	else
		{
		for (int i = 0; i < lhs.m_dimension; i++)
			{
			for (int j = 0; j < lhs.m_dimension; j++)
				{
				if ( lhs.m_matrix[i][j] != rhs.m_matrix[i][j] )
					{
					return false;
					}
				}
			}
		}
	return true;
}

ostream& operator<<(ostream& outStream, const CSquareMatrix& disp)
{
	cout << disp.m_name << ":" << endl;
	cout.precision(3);
	for (int i = 0; i < disp.m_dimension; i++)
		{
		for (int j = 0; j < disp.m_dimension; j++)
			{
			double num = round(disp.m_matrix[i][j]*1000)/1000;
			if (num == -0)
				{
				num = 0;
				}
			outStream << setw(2) << num << " ";
			}
		outStream << endl;
		}
	return outStream;
}


CSquareMatrix* CofactorMatrix(const CSquareMatrix& src)
{
	CSquareMatrix* copy = new CSquareMatrix(src);
	
	for (int row = 0; row < src.GetDimension(); row++)
		{
		for (int col = 0; col < src.GetDimension(); col++)
			{
			copy->SetMatrix(row, col, Cofactor(src, row, col));
			}
		}

	return copy;
}


double Cofactor(const CSquareMatrix& cmatrix, int findRow, int findCol)
{
	if (cmatrix.GetDimension() == 2)
		{
		return pow(-1, (findRow + findCol)) * cmatrix.GetMatrix()[(findRow+1)%2][(findCol+1)%2];
		}
	else
		{
		int subtractRow = 0;
		CSquareMatrix newMatrix = cmatrix.GetDimension() - 1;
		for (int row = 0; row < cmatrix.GetDimension(); row++)
			{
			if (row == findRow)
				{
				subtractRow++;
				}
			else
				{
				int subtractCol = 0;
				for (int col = 0; col < cmatrix.GetDimension(); col++)
					{
					if (col == findCol)
						{
						subtractCol++;
						}
					else
						{
						newMatrix.SetMatrix(row-subtractRow, col-subtractCol, 
								cmatrix.GetMatrix()[row][col]);
						}
					}
				}
			}
			return pow(-1, (findRow + findCol)) * newMatrix.Determinant();
		}
}



void AddRow(double** array, int dim, int src, int dest, double mult)
{
	for (int i = 0; i < dim; i++)
		{	
		array[dest][i] += array[src][i] * mult;
		}
}


void PermuteRows(double** array, int row1, int row2)
{
	double* row1Holder = array[row1];
	array[row1] = array[row2];
	array[row2] = row1Holder;
}


double CSquareMatrix::Determinant() const
{
	CSquareMatrix copy = *this;
	double det = 1.0;

	for (int col = 0; col < m_dimension-1; col++)
		{
		for (int row = col+1; row < m_dimension; row++)
			{
			if (copy.m_matrix[row][col] != 0.0)
				{
				if (!copy.m_matrix[col][col])
					{
					PermuteRows(copy.m_matrix, col, row);
					det *= -1.0;
					}
				double cancel = -copy.m_matrix[row][col];
				double multiplier = cancel / copy.m_matrix[col][col];
				AddRow(copy.m_matrix, m_dimension, col, row, multiplier);
				}
			}
		}
	for (int i = 0; i < m_dimension; i++)
		{
		det *= copy.m_matrix[i][i];
		}
	return det;
}


CSquareMatrix* Multiply(const CSquareMatrix& mat1, const CSquareMatrix& mat2)
{
	if (mat1.GetDimension() != mat2.GetDimension())
		{
		return NULL;
		}
	else
		{
		int dim = mat1.GetDimension();
		string newName = mat1.GetName() + " X " + mat2.GetName();
		CSquareMatrix* product = new CSquareMatrix(dim, 0, newName);
		for (int row = 0; row < dim; row++)
			{
			for (int col = 0; col < dim; col++)
				{
				for (int rep = 0; rep < dim; rep++)
					{
					product->GetMatrix()[row][col] += mat1.GetMatrix()[row][rep]
													* mat2.GetMatrix()[rep][col];
					}
				}
			}
		return product;
		}
}

void CSquareMatrix::Scalar(double mult)
{
	for (int row = 0; row < m_dimension; row++)
		{
		for (int col = 0; col < m_dimension; col++)
			{
			m_matrix[row][col] *= mult;
			}
		}
}

CSquareMatrix* Transpose(const CSquareMatrix& src) 
{
	int dim = src.GetDimension();
	string newName = src.GetName() + "-T";
	CSquareMatrix* trans = new CSquareMatrix(dim, newName);

	for (int row = 0; row < dim; row++)
		{
		for (int col = 0; col < dim; col++)
			{
			trans->GetMatrix()[row][col] = src.GetMatrix()[col][row];
			}
		}
	
	return trans;
}

CSquareMatrix* Inverse(const CSquareMatrix& src)
{
	double det = src.Determinant();
	if (!det)
		{
		return NULL;
		}
	else
		{
		CSquareMatrix* cofactor = CofactorMatrix(src); 
		CSquareMatrix* adjoint = Transpose(*cofactor);
		delete cofactor;
		adjoint->Scalar(1/det);
		string name = src.GetName() + "-1";
		adjoint->SetName(name);
		return adjoint;
		}

} // end of "Inverse"



void CSquareMatrix::EnterElements()
{
	int value;
	for (int i = 0; i < m_dimension; i++)
		{
		for (int j = 0; j < m_dimension; j++)
			{
			cout << "Set value " << i+1 << ", " << j+1 << ": ";
			cin >> value;
			m_matrix[i][j] = value;
			}
		}
} // end of "Enter Elements"



CSquareMatrix* AddMatrix(const CSquareMatrix& mat1, const CSquareMatrix& mat2)
{
	int dim = mat1.GetDimension();
	if (dim != mat2.GetDimension())
		{
		return NULL;
		}
	string newName = mat1.GetName() + " + " + mat2.GetName();
	CSquareMatrix* result = new CSquareMatrix(dim, newName);

	for (int row = 0; row < dim; row++)
		{
		for (int col = 0; col < dim; col++)
			{
			result->GetMatrix()[row][col] = mat1.GetMatrix()[row][col]
										+ mat2.GetMatrix()[row][col];
			}
		}
	
	return result;

} // end of "Add Matrix"



double* CramersRule(const CSquareMatrix& mat, double solutions[])
{
	double det = mat.Determinant();
	if (!det)
		{
		return NULL;
		}
	else
		{
		int dim = mat.GetDimension();
		double* array = new double[dim];
		for (int i = 0; i < dim; i++)
			{
			// replace column i
			CSquareMatrix replaced = mat;
			for (int row = 0; row < dim; row++)
				{
				replaced.GetMatrix()[row][i] = solutions[row];
				}
			// divide new det by original and add to array of solutions
			array[i] = replaced.Determinant() / det;	
			}

		return array;
		}
} // end of "Cramer's Rule"
