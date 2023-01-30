/*
Name: Cooper Earls
netID: cce114
Compiler: Visual Studios 2019
Program Description: This program takes input strings from the user, puts them in a linked list, and when they type STOP
					 it reverses their list and outputs it.

NOTES: Yeah there aren't going to be alot of comments in this program because I feel like I could write this blindfolded
	   at this point. I had alot of trouble getting this to compile in my linux terminal(that's why I am doing this 
	   program in Visual Studios). Any help on whey I couln't get it to compile would be great. It gave me an unreferenced
	   error or something. 
*/

#include <iostream>
#include <string>
#include "List.h"
using namespace std;

int main()
{
	string input;
	LinkedList linked;
	bool contin = true;
	int count = 1;

	cout << "This program takes a bunch of strings and reverses them!" << endl;
	cout << "Don't believe me? Try it!" << endl;
	cout << endl;

	while (contin)
	{
		cout << "Word" << count << ": ";
		cin >> input;

		if (input == "STOP")
		{
			contin = false;
		}
		else
		{
			linked.append(input);
			count++;
		}
	}

	linked.display();
	cout << endl;

	linked.displayreverse();

	return 0;
}