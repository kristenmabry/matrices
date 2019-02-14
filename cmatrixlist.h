#ifndef MatrixList
#define MatrixList

const int MOVE_TO_BACK = 0;
const int MOVE_TO_FRONT = 1;

class CMatrixList
{
public:
	CMatrixList();

	void Insert(int index);
	void Remove(int index);
	void DestroyList();
	void IsEmpty() { return !m_numItems; }
	void SetListSize(int numItems);

private:
	int m_numItems;
	CSquareMatrix** m_items;
	
	void CopyList(const CMatrixList* otherList);
	void MoveItems(int index, int direction);
	int GetIndex(const ListType&  newItem) const;
}

#endif
