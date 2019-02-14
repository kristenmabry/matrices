// ============================================================================
// File: csortedlist.cpp (Spring 2019)
// ============================================================================
// This is the implementation file for the list ADT "CSortedList".  This
// particular implementation uses an array to store a list of type
// "ListType" items.
// ============================================================================

#include    <iostream>
using namespace std;
#include    "csortedlist.h"
#include    "csquarematrix.h"



// ==== CSortedList::CSortedList ============================================
//
// This the default constructor.
//
// Input:
//      Nothing.
//
// Output:
//      Nothing.
//
// ============================================================================

	CSortedList::CSortedList()
{
	// create default empty list
	m_currMax = DEFAULT_LISTSIZE;
	m_numItems = 0;
	m_items = new ListType[m_currMax];
} // end of "CSortedList::CSortedList"



// ==== CSortedList::CSortedList ============================================
//
// This the copy constructor, which performs a deep copy of the parameter.
//
// Input:
//      otherList   -- a reference to an existing CSortedList object
//
// Output:
//      Nothing.
//
// ============================================================================

	CSortedList::CSortedList(const CSortedList& other)
{
	// copy each individual element
	m_currMax = other.m_currMax;
	m_numItems = other.m_numItems;
	m_items = new ListType[m_currMax];
	for (int i = 0; i < m_numItems; i++)
		{
		m_items[i] = other.m_items[i];
		}
} // end of "CSortedList::CSortedList"


// ==== CSortedList::CopyList =================================================
//
// This function copies the contents of one CSortedList object to another
// CSortedList object.  If the destination object already contains a list, then
// that list is first released.
//
// Input:
//      otherList   -- a const reference to an existing CSortedList object
//
// Output:
//      The total number of items copied from the source object to the
//      destination object.
//
// ============================================================================

int	CSortedList::CopyList(const CSortedList  &otherList)
{
	// if list exists, release it
	if (m_items)
		{
		DestroyList();
		}

	// copy list items until new list's numItems
	m_items = new ListType[m_currMax];
	for (int i = 0; i < m_numItems; i++)
		{
		m_items[i] = otherList.m_items[i];
		}

	return m_numItems;
} //end of "CSortedList::CopyList"



// ==== CSortedList::DestroyList =============================================
//
// This function destroys a list by releasing any memory allocated for the
// list.
//
// Input:  nothing
//
// Output: nothing
//
// ============================================================================

void CSortedList::DestroyList()
{
	// release the array
	delete []m_items;
} // end of "CSortedList::DestroyList"



// ==== CSortedList::DispRetVal ===============================================
//
// This function is used for debugging purposes.  If a value of type
// ListReturnCode needs to be displayed to stdout, you can call this function.
//
// Input:
//      szMessage   -- a null-terminated string to display to stdout (e.g., the
//                     name of the function calling this function)
//
//      value       -- the list error code to display
//
// Output:
//      nothing
//
// ============================================================================

void    CSortedList::DispRetVal(const char*  szMessage, LStatus  value) const
{
    #ifdef  DEBUG_LIST
    cerr << szMessage << ": ";
    switch (value)
        {
        case   L_FULL:
            cerr << "L_FULL\n";
            break;

        case   L_EMPTY:
            cerr << "L_EMPTY\n";
            break;

        case   L_ERROR:
            cerr << "L_ERROR\n";
            break;

        case   L_SUCCESS:
            cerr << "L_SUCCESS\n";
            break;

        case   L_INVALID_INDEX:
            cerr << "L_INVALID_INDEX\n";
            break;

		case L_DUPLICATE:
			cerr << "L_DUPLICATE\n";
			break;

		case L_NOT_EXIST:
			cerr << "L_NOT_EXIST\n";
			break;

        default:
            cerr << "Unrecognized error code\n";
            break;
        }
    #endif  // DEBUG_LIST

}  // end of "CSortedList::DispRetVal"



// ==== CSortedList::GetItem ==================================================
//
// This function fetches the value of a target item from the list.
//
// Input:
//      index   -- the index location for the target item (zero-based).
//
//      item    -- a reference to a ListType object; this argument will
//                 contain the desired item after the function completes
//                 (assuming all goes well)
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned and the target
//      item is assigned to the reference parameter.  Else, an error code is
//      returned.
//
// ============================================================================

LStatus    CSortedList::GetItem(int  index, ListType  &item) const
{
	// if empty display error
	if ( IsEmpty() )
		{
		DispRetVal("Get Item", L_EMPTY);
		return L_EMPTY;
		}
	// if out of range display error
	else if (index > m_numItems-1)
		{
		DispRetVal("Get Item", L_INVALID_INDEX);
		return L_INVALID_INDEX;
		}
	// retrieve item
	else
		{
		item = m_items[index];
		return L_SUCCESS;
		}
} // end of "CSortedList::GetItem"



// ==== CSortedList::GetIndex =================================================
//
// This function determines the proper index location for the "newItem"
// parameter.  The proper index location is one that will maintain an ascending
// sorted order in the list.  If the "newItem" value is already in the list, a
// value of true is returned to alert the caller, otherwise a value of false is
// returned.
//
// NOTE: this function assumes the caller has already determined that there is
//       enough room in the array to add the new item.
//
// Input:
//
//      newItem     -- a const reference to the new item to insert into the list
//
//      index       -- the target index location for the new item (zero-based)
//
// Output:
//      A value of true if the "newItem" value is already in the list, false if
//      not.
//
// ============================================================================

bool       CSortedList::GetIndex(const ListType  &newItem, int  &index) const
{
	// if empty return 0
	if ( IsEmpty() )
		{
		index = 0;
		return false;
		}
	else
		{
		// loop until found or current item is bigger than new one
		for (int i = 0; i < m_numItems; i++)
			{
			if (m_items[i] == newItem)
				{
				index = i;
				return true;
				}
			else if (m_items[i] > newItem)
				{
				index = i;
				return false;
				}
			}

		// if not found and newItem still bigger, set index to end of the list
		index = m_numItems;
		return false;
		}
} // end of "CSortedList::GetIndex"



// ==== CSortedList::Insert ===================================================
//
// This function inserts an item into the list.  If the new item is appended to
// the end of the list, the position of any other list item is unaffected.  If
// the new item is inserted before the last element, all elements after the
// target location are moved towards the back of the array one position to make
// room for the new element.
//
// Input:
//      newItem    -- a const reference to the new item to insert into the list
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned; else, an error
//      code is returned.
//
// ============================================================================
LStatus    CSortedList::Insert(const ListType  &newItem)
{
	int index;
	bool exists = GetIndex(newItem, index); 

	// if item exists display error
	if (exists)
		{
		DispRetVal("Insert", L_DUPLICATE);
		return L_DUPLICATE;
		}
	// if list is full, resize
	else if ( IsFull() )
		{
		SetListSize(m_currMax+1);
		}

	// if not adding to end of list, shift items
	if (index < m_numItems)
		{
		MoveItems(index, MOVE_TO_BACK);
		}

	m_items[index] = newItem;
	m_numItems++;
	return L_SUCCESS;
} // end of "CSortedList::Insert"



// ==== CSortedList::MoveItems ================================================
//
// This function moves the elements of the list forward or backward one
// position.  If an item is inserted before the last element in the list, the
// "trailing" elements must be moved towards the back of the array one position
// in order to make room for the new list item.  Similarly, if a list item is
// removed from the middle of the list, the trailing elements must be moved
// towards the front of the array one position to fill in the gap left by the
// deleted item.
//
// The caller of this function only needs to indicate the target location where
// an element is being inserted or removed, and the "direction" to move the
// trailing list elements (i.e., towards the front or back of the array).
//
// NOTE: This function assumes that the caller has already verified the
// validity of the index parameter.
//
// Input:
//      index           -- the index location for the target item (zero-based).
//
//      direction       -- the direction to move the trailing (i.e., those
//                         further down the list) list elements; this parameter
//                         should contain the value MOVE_TO_BACK if an item is
//                         being inserted into the list, or MOVE_TO_FRONT if 
//                         the item at targetIndex is being removed from the
//                         list.
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned and the target
//      item is assigned to the reference parameter.  Else, an errorcode is
//      returned.
//
// ============================================================================

int        CSortedList::MoveItems(int  index, int  direction)
{
	if (direction == MOVE_TO_FRONT)
		{
		for (int i = index; i < m_numItems; i++)
			{
			// move each item forward
			m_items[i] = m_items[i+1];
			}
		}
	else // if direction == MOVE_TO_BACK
		{
		for (int i = m_numItems -1; i >= index; i--)
			{
			// move each item back
			m_items[i+1] = m_items[i];
			}
		}
	return L_SUCCESS;
} // end of "CSortedList::MoveItems"



// ==== CSortedList::Remove ===================================================
//
// This function removes an item from the list.  If the target item is at the
// end of the list, the position of any other list item is unaffected.  If the
// target item is before the end of the list, all elements after the target
// location are moved towards the front of the array one position to fill in
// the gap left behind by the deleted item.
//
// Input:
//      target      -- a const reference to the item to remove
//
// Output:
//      If all goes well, a value of L_SUCCESS is returned; else, an error
//      code is returned.
//
// ============================================================================

LStatus    CSortedList::Remove(const ListType  &target)
{
	int index;
	bool exists = GetIndex(target, index);

	// if not in list, display error
	if (!exists)
		{
		DispRetVal("Remove", L_NOT_EXIST);
		return L_NOT_EXIST;
		}
	// if list empty, display error
	else if ( IsEmpty() )
		{
		DispRetVal("Remove", L_EMPTY);
		return L_EMPTY;
		}
	// if item not at end of list, shift items
	else if (index < m_numItems-1)
		{
		MoveItems(index, MOVE_TO_FRONT);
		}

	m_numItems--;
	if (m_currMax > DEFAULT_LISTSIZE)
		{
		SetListSize(m_currMax-1);
		}

	return L_SUCCESS;
} // end of "CSortedList::Remove"



// ==== CSortedList::SetListSize ==============================================
//
// This function is used to manage the allocated size of a list. The input 
// parameter indicates the number of elements to allocate for the list. If the 
// calling object already contains a list with data, it can be resized to 
// either increase or decrease its allocation. If the size of the existing list
// is being decreased, then the trailing items will be truncated.
// 
// Input:
//      numItems  -- the target number of items in the list
//
// Output:
//      Nothing.
// 
// ============================================================================

LStatus    CSortedList::SetListSize(int  numItems)
{
	// make copy list
	CSortedList temp = *this;

	m_currMax = numItems;
	// if items greater than max only take the max number of items
	if (m_numItems > m_currMax)
		{
		m_numItems = m_currMax;
		}
	// move original items back until max
	CopyList(temp);

	return L_SUCCESS;
} // end of "CSortedList::SetListSize"



// ==== CSortedList::operator= ================================================
//
// This is the overloaded assignment operator, copying the parameter's list to
// the calling object.
//
// Input:
//      rhs         -- a reference to a source CSortedList object
//
// Output:
//      A reference to the calling object.
//
// ============================================================================

CSortedList&    CSortedList::operator=(const CSortedList  &otherList)
{
	if (this != &otherList)
		{
		// copy each individual element
		m_numItems = otherList.m_numItems;
		m_currMax = otherList.m_currMax;
		CopyList(otherList);
		}

	return *this;
} // end of "CSortedList::operator="

