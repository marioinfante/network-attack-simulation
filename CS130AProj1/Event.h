#ifndef EVENT_H
#define EVENT_H

class Event {
public:
	int getTime();
	char getId();
	int getTarget();
	int getSource();
	Event();
	Event(int tm, int src, int tgt);
	Event(int tm, Event e);
	Event(int tm, int tgt);
private:
	int eventTime;
	char id;
	int source;
	int target;
};

#endif