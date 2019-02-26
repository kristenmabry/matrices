#include    <iostream>
#include    <cstdlib>
#include    <cstdio>
#include    <cctype>
#include    "clist.h"
#include    "csquarematrix.h"
using namespace std;

// ==== DisplayList ===========================================================
// 
// This function displays the current contents of the list to stdout.
// 
// Input:
//      head [IN]   -- a pointer to the head of the linked list
// 
// Output:
//      The number of items written to stdout.
// 
// ============================================================================

int     DisplayList(const LNode  *head)
{
	int count = 0;
	//until the end of the list, output item and move to next position
	while (head != NULL)
   		{
		cout << *(head->item) << endl;
		head = head->next;
		count++;
		}

	return count;
}  // end of "DisplayList"



// ==== FreeNodes =============================================================
//
// This function releases all of the allocated nodes from the heap and returns
// the number of nodes released to the caller. It then sets the caller's head
// pointer to NULL to reflect the empty state of the list.
// 
//
// Input:
//      head [IN]       -- a pointer to a pointer to the first node in the
//                         linked list
// 
// Output:
//      An integer value that represents the number of nodes released.
//
// ============================================================================

int     FreeNodes(LNode  **head)
{
	LNode* nextNode;
	int counter = 0;
	
	while (*head != NULL)
		{
		// delete current node after saving location of next one
		nextNode = (*head)->next;
		delete (*head)->item;
		delete *head;
		// change current pointer to the next node
		*head = nextNode;
		counter++;
		}

	return counter;

}  // end of "FreeNodes"



// ==== InsertItem ============================================================
// 
// This function inserts a new item into the list. If the item is inserted
// successfully, the boolean parameter is set to true, otherwise it is set to
// false.
// 
// Input:
//      head [IN]       -- a pointer to the first node in the linked list
// 
//      index [IN]      -- the zero-based location index for the new item
// 
//      item [IN]       -- the integer value to insert into the list
// 
//      bSuccess [OUT]  -- the boolean result of the insert operation (true
//                         if successful, false if not)
// 
// Output:
//      A pointer to the (potentially new) head of the linked list.
// 
// ============================================================================

LNode*  InsertItem(LNode  *head, CSquareMatrix* item)
{
	if (head == NULL)
		{
		head = new LNode;
		head->item = item;
		head->next = NULL;
		return head;
		}
	LNode* tempNode = head;
	while (tempNode->next != NULL)
		{
		tempNode = tempNode->next;
		}
	LNode* newNode = new LNode;
	newNode->item = item;
	newNode->next = NULL;
	tempNode->next = newNode;
	return head;
	
}  // end of "InsertItem"



LNode*  DeleteItem(LNode  *head, std::string name, bool  &bSuccess)
{
	LNode* tempNode = head;
	int counter = 0;
	while (tempNode->item->GetName() != name && tempNode->next != NULL 
		&& name != tempNode->next->item->GetName())

		{
		tempNode = tempNode->next;
		counter++;
		}
	// if null and name not found, error
	if (tempNode->next == NULL 
		&& name != tempNode->item->GetName())
		{
		cout << "not found" << endl;
		bSuccess = false;
		return head;
		}
	// else if null and name found, delete node 
	else if (tempNode->next == NULL
		&& name == tempNode->item->GetName())
		{
		delete tempNode->item;
		delete tempNode;
		bSuccess = true;
		return NULL;
		}
	// else if not null and name found, save location
	// change node to next next node
	else if (tempNode->next->item->GetName() == name)
		{
		LNode* nextNode = tempNode->next->next;
		delete tempNode->next->item;
		delete tempNode->next;
		tempNode->next = nextNode;
		bSuccess = true;
		return head;
		}
	else 
		{
		LNode* newHead = tempNode->next;
		delete tempNode->item;
		delete tempNode;
		bSuccess = true;
		return newHead;
		}	

} // end of "DeleteItem"




LNode*	GetItem(LNode *head, std::string name, bool& bSuccess)
{
	if (head == NULL)
		{
		bSuccess = false;
		return NULL;
		}

	do
		{
		if (head->item->GetName() == name)
			{
			bSuccess = true;
			return head;
			}
		head = head->next;
		} while (head->next != NULL);

	bSuccess = false;
	return NULL;
}
