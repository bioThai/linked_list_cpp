// bioThai
// Manage a list of inventory items using a linked list.  Operations include adding a new inventory item at the end of the list, adding a new inventory item at the beginning of the list, removing an inventory item from the beginning of the list, removing an inventory item from the end of the list, removing an inventory item by name, and displaying the current list of inventory items.

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

/*******************************************************
* InventoryNode
* A class to establish a node for each linked list item.
********************************************************/
class InventoryNode
{
private:
	string item;
	InventoryNode* next;

	friend class LinkedInventory;
public:
	InventoryNode(string, InventoryNode*);     //constructor
};

/*******************************************************
* LinkedInventory
* A class for the linked list of inventory items.
********************************************************/
class LinkedInventory
{
private:
	InventoryNode* head;
	int choice = 0;

	void displayMenu();
	void getChoice();
	void validateChoice(int&);
	string getItemName(int);
	void addAtBegin(string);
	void addAtEnd(string);
	void removeFromBegin();
	void removeFromEnd();
	void removeByName(string);
	void displayInventory();
	void pause();

public:
	LinkedInventory();      //constructor
	~LinkedInventory();     //destructor
	void driver();
};

/****************************InventoryNode methods*****************************/
/*******************************************************
* InventoryNode::InventoryNode(string s, InventoryNode* nodePtr)
* Constructor to initialize each node
*******************************************************/
InventoryNode::InventoryNode(string s, InventoryNode* nodePtr)
{
	item = s;
	next = nodePtr;
}

/****************************** LinkedInventory methods*****************************/
/*******************************************************
* LinkedInventory::LinkedInventory()
* Constructor
*******************************************************/
LinkedInventory::LinkedInventory()
{
	head = NULL;    //head starts off pointing to null
}

/*******************************************************
* LinkedInventory::displayMenu()
* Display menu options so user can pick what to do
*******************************************************/
void LinkedInventory::displayMenu()
{
	cout << "================ Main Menu ================\n" << endl;
	cout << "Add new item to inventory:\n"
		<< "  (1) Add item to beginning of list\n"
		<< "  (2) Add item to end of list"
		<< endl;
	cout << "Remove item from inventory:\n"
		<< "  (3) Remove item from beginning of list\n"
		<< "  (4) Remove item from end of list\n"
		<< "  (5) Remove item by name"
		<< endl;
	cout << "Other:\n"
		<< "  (6) See current inventory\n"
		<< "  (7) Exit program\n"
		<< endl;
	cout << "-------------------------------------------" << endl;
}

/*******************************************************
* LinkedInventory::getChoice()
* Get user input on menu choice
*******************************************************/
void LinkedInventory::getChoice()
{
	fseek(stdin, 0, SEEK_END); //clear the input buffer starting at the beginning (0) and going to the end

	cout << "What would you like to do?" << endl;
	cout << "Please enter an option from 1-7: ";
	cin >> choice;
	validateChoice(choice);
}

/*******************************************************
* LinkedInventory::validateChoice(int& option)
* Validate user input of their menu choice
*******************************************************/
void LinkedInventory::validateChoice(int& option)
{
	//test for invalid input less than 1, or greater than 7, or not an int (eg, characters)
	while (option < 1 || option > 7 || !cin)
	{
		cout << "    Invalid choice, try again: ";
		cin.clear(); //reset the flag back to a goodread
		fseek(stdin, 0, SEEK_END); //clear the input buffer starting at the beginning (0) and going to the end
		cin >> option;
	}
}

/*******************************************************
* LinkedInventory::getItemName(int option)
* Prompt user for an item name to add or remove
*******************************************************/
string LinkedInventory::getItemName(int option)
{
	string itemName;

	if (option <= 2)
		cout << "\nEnter the item you'd like to add: ";
	else if (option == 5)
		cout << "\nEnter the item you'd like to remove: ";

	fseek(stdin, 0, SEEK_END); //clear the input buffer starting at the beginning (0) and going to the end
	getline(cin, itemName);
	return itemName;
}

/*******************************************************
* LinkedInventory::addAtBegin(string itemName)
* Add new item at beginning of list
*******************************************************/
void LinkedInventory::addAtBegin(string itemName)
{
	head = new InventoryNode(itemName, head);
	cout << "\nItem added.\n" << endl;
}

/*******************************************************
* LinkedInventory::addAtEnd(string itemName)
* Add new item at end of list
*******************************************************/
void LinkedInventory::addAtEnd(string itemName)
{
	InventoryNode* nodePtr = head;

	//if item is being added to an empty list:
	if (head == NULL)
	{
		addAtBegin(itemName);
		return;
	}
	//if item is being added to list that's not empty:
	else
	{
		//use ptr to walk through the linked list until last item is reached
		while (nodePtr->next != NULL)
		{
			nodePtr = nodePtr->next;
		}
		//at this point, nodePtr points to last item and nodePtr->next=NULL (no item after last item)

		//a new node is created with a user-provided itemName and it has a pointer pointing to NULL (nodePtr->next=NULL) bc it's the new last item in list
		nodePtr->next = new InventoryNode(itemName, nodePtr->next);

		//now, nodePtr->next points to the newly-created last item in the list instead of to NULL

		cout << "\nItem added.\n" << endl;
	}
}

/*******************************************************
* LinkedInventory::removeFromBegin()
* Remove item from beginning of list
*******************************************************/
void LinkedInventory::removeFromBegin()
{
	InventoryNode* nodePtr = head;

	if (head == NULL)   //if list is empty
	{
		cout << "\nItem cannot be removed from an empty list.\n" << endl;
		return;
	}
	else                //if non-empty list
	{
		head = head->next;      //assign new value to head of list before removing first item
		delete nodePtr;

		cout << "\nItem removed.\n" << endl;
	}
}

/*******************************************************
* LinkedInventory::removeFromEnd()
* Remove item from end of list
*******************************************************/
void LinkedInventory::removeFromEnd()
{
	InventoryNode* nodePtr = head;
	InventoryNode* previousNodePtr = head;

	if (head == NULL)   //if list is empty
	{
		cout << "\nItem cannot be removed from an empty list.\n" << endl;
		return;
	}
	else                //if non-empty list
	{
		if (nodePtr->next == NULL)  //if only one item in list
		{
			removeFromBegin();
			return;
		}
		else            //if multiple items in list
		{
			//use ptr to walk through the linked list until last item is reached
			while (nodePtr->next != NULL)
			{
				previousNodePtr = nodePtr;
				nodePtr = nodePtr->next;
			}
			//nodePtr->next now points to null, nodePtr points to last item, previousNodePtr points to second-to-last item

			//set previousNodePtr->next to point to null, then delete nodePtr;
			previousNodePtr->next = nodePtr->next;
			delete nodePtr;

			cout << "\nItem removed.\n" << endl;
		}
	}
}

/*******************************************************
* LinkedInventory::removeByName(string itemName)
* Remove item from list based on item name inputted by user
*******************************************************/
void LinkedInventory::removeByName(string itemName)
{
	InventoryNode* nodePtr = head;
	InventoryNode* previousNodePtr = head;

	if (head == NULL)   //if list is empty
	{
		cout << "\nItem cannot be removed from an empty list.\n" << endl;
		return;
	}

	//if the item to delete is in the first node (at beginning of list)
	if (head->item == itemName)
	{
		removeFromBegin();
		return;
	}
	else
	{
		//walk through list and skip nodes whose item != itemName
		//break out of loop once itemName is found in list or end of list is reached w/out finding itemName
		while (nodePtr != NULL && nodePtr->item != itemName)
		{
			previousNodePtr = nodePtr;
			nodePtr = nodePtr->next;
		}

		//if itemName was found before end of list was reached,
		//link previous node to the node after the one pointed to by nodePtr, then delete nodePtr
		if (nodePtr != NULL)
		{
			previousNodePtr->next = nodePtr->next;
			delete nodePtr;
			cout << "\nItem removed.\n" << endl;
		}

		//else if itemName not found before end of list was reached
		else if (nodePtr == NULL)
			cout << "\nItem was not found in list and could not be removed.\n" << endl;
	}
}

/*******************************************************
* LinkedInventory::displayInventory()
* Walk through linked list to display inventory
*******************************************************/
void LinkedInventory::displayInventory()
{
	//use ptr to walk through the linked list instead of head
	//head will stay the same
	InventoryNode* nodePtr = head;

	cout << "\nCurrent inventory:" << endl;

	while (nodePtr != NULL)
	{
		cout << "  " << nodePtr->item << endl;
		nodePtr = nodePtr->next;
	}
	cout << endl;
}

/*******************************************************
* LinkedInventory::pause()
* Pauses the program before re-displaying menu by prompting user to press Enter
*******************************************************/
void LinkedInventory::pause()
{
	cout << "Press Enter to return to main menu.";
	fseek(stdin, 0, SEEK_END); //clear the input buffer starting at the beginning (0) and going to the end
	cin.get();
	cout << '\n' << endl;
}

/*******************************************************
* LinkedInventory::driver()
* Handles the order of execution for the program
*******************************************************/
void LinkedInventory::driver()
{
	while (choice != 7)
	{
		displayMenu();
		getChoice();

		if (choice == 1)
			addAtBegin(getItemName(choice));
		else if (choice == 2)
			addAtEnd(getItemName(choice));
		else if (choice == 3)
			removeFromBegin();
		else if (choice == 4)
			removeFromEnd();
		else if (choice == 5)
			removeByName(getItemName(choice));
		else if (choice == 6)
			displayInventory();
		else if (choice == 7)
			exit(0);    //exit parameter "0" returns successful termination status to system

		pause();
	}
}

/*******************************************************
* LinkedInventory::~LinkedInventory()
* Destructor to destroy the list node pointers
*******************************************************/
LinkedInventory::~LinkedInventory()
{
	while (head != NULL)
	{
		InventoryNode* nodePtr = head;
		head = head->next;
		delete nodePtr;
	}
}

/********************** main() ************************/
int main()
{
	LinkedInventory list1;
	list1.driver();
	return 0;
}
