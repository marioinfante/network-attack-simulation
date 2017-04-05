#ifndef ATTACK_H
#define ATTACK_H
#include "Event.h"

class Attack : public Event{
public:
	Attack(int tm,int src,int tgt);
	int getTime();
	char getId();
	int getSource();
	int getTarget();
private:
	char id = 'a';
	int source;
	int time;
	int target;
};

#endif