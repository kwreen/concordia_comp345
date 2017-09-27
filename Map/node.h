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
	Node* next;
public:
	Node(int num);
	Node(int num, Node* n);
	Node(int num, Node* n, Node* p);

};


#endif /* NODE_H_ */
