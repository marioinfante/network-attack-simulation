#ifndef NOTIFY_H
#define NOTIFY_H
#include "Event.h"
#include "Attack.h"

class Notify : public Event{
public:
	Notify(int tm, Attack a);
	int getSource();
	int getTarget();
private:
	char id = 'n';
	int source;
	int time;
	int target;
};

#endif