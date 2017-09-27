/*
 * node.h
 *
 *
 *      Author: johnb
 */

#ifndef NODE_H_
#define NODE_H_
#include <string>
#include <iostream>


class Node
{
private:
	int index;

public:
	Node();
	Node(int num);
	Node(int num, Node* n);
	Node(int num, Node* n, Node* p);
	Node* next;
	int getIndex();

};


#endif /* NODE_H_ */
