class CSquareMatrix;

// linked list structure
struct  LNode
{
    CSquareMatrix*	item;
    LNode*       	next;
};


// function prototypes
int     DisplayList(const LNode  *head);
int     FreeNodes(LNode  **head);
LNode*  InsertItem(LNode  *head, CSquareMatrix* item);
LNode*  DeleteItem(LNode  *head, std::string name, bool  &bSuccess);
LNode*	GetItem(LNode *head, std::string name, bool& bSuccess);



