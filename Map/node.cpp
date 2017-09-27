/*
 * node.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: johnb
 */
#include "node.h"
using namespace std;

Node::Node(int number, Node* n)
{
	index = number;
	next = n;

}


