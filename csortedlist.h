// ============================================================================
// File: csortedlist.h (Spring 2019)
// ============================================================================
// Header file for the CSortedList class.
// ============================================================================

#ifndef DYNAMIC_CSORTED_LIST_HEADER
#define DYNAMIC_CSORTED_LIST_HEADER

// enable this #define symbol to see debug output
#define DEBUG_LIST

// type definitions
class CSquareMatrix;
typedef CSquareMatrix ListType;
enum    LStatus  { L_FULL
                  , L_EMPTY
                  , L_ERROR
                  , L_SUCCESS
                  , L_INVALID_INDEX
                  , L_DUPLICATE
                  , L_NOT_EXIST
                };


// constants
const   int     DEFAULT_LISTSIZE = 5;
const   int     MOVE_TO_BACK = 0;
const   int     MOVE_TO_FRONT  = 1;

class   CSortedList
{
public:
    // constructor and destructor
    CSortedList();
    CSortedList(const CSortedList  &other);
    ~CSortedList() { DestroyList(); }

    // member functions
    void       DestroyList();
    void       DispRetVal(const char*  szMessage, LStatus  value) const;
    LStatus    GetItem(int  index, ListType  &item) const;
    int        GetNumItems() const { return m_numItems; }
    LStatus    Insert(const ListType  &newItem);
    bool       IsEmpty() const { return (0 == m_numItems); }
    bool       IsFull() const { return (m_currMax == m_numItems); }
    LStatus    Remove(const ListType  &target);
    LStatus    SetListSize(int  numItems);

    // overloaded operators
    CSortedList&    operator=(const CSortedList  &otherList);

private:
    // data members
    int        m_currMax;
    int        m_numItems;
    ListType   *m_items;

    // member functions
    int        CopyList(const CSortedList  &otherList);
    bool       GetIndex(const ListType  &newItem
                                   , int  &index) const;
    int        MoveItems(int  index, int  direction);
};

#endif  // DYNAMIC_CSORTED_LIST_HEADER
