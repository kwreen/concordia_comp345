#include "Subject.h"

void Subject::attatch(vector<Player>& p) //points to the player list, as we are only storing player objects as listeners,views, polymorphism is not needed, simply use player array as observer list.
{
	observers = &p;

}
void Subject::notify()
{
	
	for (int i = 0; i < observers->size(); i++)
	{
		
		(*observers)[i].showStats();
	}
}
/*Not needed as observers points to something on stack not heap, so it will be deleted automatically as it goes out of scope
Subject::~Subject()
{
	delete observers;
	observers = nullptr;
}
*/

