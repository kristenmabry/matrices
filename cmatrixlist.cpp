#include <iostream>
#include "cmatrixlist.h"
#include "csquarematrix.h"
using namespace std;


	CMatrixList::CMatrixList()
{
	m_numItems = 0;
}

	CMatrixList::~CMatrixList()
{
	for (int i = 0; i < m_numItems; i++)
		{
		delete m_items[i];
		}
	delete []m_items;
}


void CMatrixList::CopyList(const CMatrixList* otherList)
{
	// if list exists, release it
	if (m_items)
		{
		DestroyList();
		}

	// copy list items until new list's numItems
	m_items = new *ListType[];
	for (int i = 0; i < m_numItems; i++)
		{
		m_items[i] = otherList.m_items[i];
		}

	return m_numItems;
}


void CMatrixList::DestroyList()
{
	// release the array
	delete []m_items;
}


int CMatrixList::GetIndex(const ListType&  newItem) const
{
	if ( IsEmpty() )
		{
		return -1;
		}
	else
		{
		for (int i = 0; i < m_numItems; i++)
			{
			if (m_items[i]->m_name == newItem.m_name)
				{
				return i;
				}
			}

		return -1;
		}
} 

void CMatrixList::Insert(const ListType  &newItem)
{
	SetListSize(m_numItems+1);

	// if not adding to end of list, shift items
	if (index < m_numItems)
		{
		MoveItems(index, MOVE_TO_BACK);
		}

	m_items[index] = newItem;
	m_numItems++;
	return L_SUCCESS;
} 
