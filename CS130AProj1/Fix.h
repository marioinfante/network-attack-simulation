#ifndef FIX_H
#define FIX_H
#include "Event.h"

class Fix : public Event{
public:
	Fix(int tm, int tgt);
	int getTarget();
private:
	char id = 'f';
	int source;
	int time;
	int target;
};

#endif