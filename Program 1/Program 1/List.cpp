#include "List.h"

LinkedList::~LinkedList()
{
	Node* tmp = head;
	while (tmp != nullptr)
	{
		head = head->next;
		delete tmp;
		tmp = head;
	}
	tail = nullptr;
	cout << endl << endl << endl;
	cout << "Memory Freed..." << endl;
}

void LinkedList::append(string value)
{
	Node* tmp = new Node(value);
	tmp->prev = tail;
	if (head == nullptr)
	{
		head = tmp;
	}
	else
	{
		tail->next = tmp;
	}
	tail = tmp;
}

void LinkedList::display()
{
	Node* tmp = head;
	while (tmp != nullptr)
	{
		cout << tmp->data << endl;
		tmp = tmp->next;
	}
}

void LinkedList::displayreverse()
{
	Node* tmp = tail;
	while (tmp != nullptr)
	{
		cout << tmp->data << endl;
		tmp = tmp->prev;
	}
}