#ifndef CSM_HEADER
#define CSM_HEADER 

namespace csquarematrix
	{
	extern int NUM_MATRICES;
	}

class CSquareMatrix
{
public:
	CSquareMatrix(const CSquareMatrix& other, std::string name = "Copy of ");
	CSquareMatrix(int dimension, std::string name = "Matrix");
	CSquareMatrix(int dimension, int num, std::string name = "Matrix");
	~CSquareMatrix();

	CSquareMatrix& operator=(const CSquareMatrix& rhs);	
	friend bool operator==(const CSquareMatrix& lhs, const CSquareMatrix& rhs);
	friend std::ostream& operator<<(std::ostream& outStream, const CSquareMatrix& disp);

	std::string GetName() const { return m_name; }
	void SetName(std::string newName) { m_name = newName; }
	double** GetMatrix() const { return m_matrix; }
	int  GetDimension() const { return m_dimension; }
	void SetMatrix(int row, int col, double value) { m_matrix[row][col] = value; } 
	
	double Determinant() const;
	void Scalar(double mult);

private:
	int m_dimension;
	double** m_matrix;
	std::string m_name;

};

void AddRow(double** array, int dim, int src, int dest, long mult);
void PermuteRows(double** array, int row1, int row2);
CSquareMatrix* CofactorMatrix(const CSquareMatrix& src);
double Cofactor(const CSquareMatrix& cmatrix, int findRow, int findCol);
CSquareMatrix* Multiply(const CSquareMatrix& mat1, const CSquareMatrix& mat2);
CSquareMatrix* Transpose(const CSquareMatrix& src);
CSquareMatrix* Inverse(const CSquareMatrix& src);

#endif
