#include <iostream>
#include "Event.h"

using namespace std;

Event::Event() {
	id = NULL;
	eventTime = NULL;
	source = NULL;
	target = NULL;
}

Event::Event(int tm, int src, int tgt) {
	id = 'a';
	eventTime = tm;
	source = src;
	target = tgt;
	cout << "Attack (" << eventTime << ',' << source << ',' << target << ')' << endl;
}

Event::Event(int tm, Event e) {
	id = 'n';
	eventTime = tm;
	source = e.getSource();
	target = e.getTarget();
	cout << "Notify (" << eventTime << ',' << source << ',' << target << ')' << endl;
}

Event::Event(int tm, int tgt) {
	id = 'f';
	eventTime = tm;
	target = tgt;
	source = NULL;
	cout << "Fix (" << eventTime << ',' << target << ')' << endl;
}

char Event::getId() {
	return id;
}

int Event::getTime() {
	return eventTime;
}

int Event::getSource() {
	return source;
}

int Event::getTarget() {
	return target;
}


//when creating an attack, schedule the next attack and
//check if computer is still compromised when generateAttack is called

//array based binary heap
//double size when out of space