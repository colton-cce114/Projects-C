#pragma once
#include <string>
#include <iostream>
using namespace std;

class Node
{
public:
	string data;
	Node* next;
	Node* prev;
	Node() : data(), next(nullptr), prev(nullptr) {}
	Node(string data) : data(data), next(nullptr), prev(nullptr) {}
};

class LinkedList
{
private:
	Node* head;
	Node* tail;

public:
	LinkedList() : head(nullptr), tail(nullptr) {}
	~LinkedList();

	void append(string value);

	void display();
	void displayreverse();
};