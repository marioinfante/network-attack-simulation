#include "Event.h"
#include "Attack.h"
#include <iostream>

using namespace std;

Attack::Attack (int tm, int src, int tgt) {
	time = tm;
	source = src;
	target = tgt;
	cout << "Attack (" << time << ',' << source << ',' << target << ')' << endl;
}

int Attack::getSource() {
	return source;
}

int Attack::getTarget() {
	return target;
}

int Attack::getTime() {
	return time;
}

char Attack::getId() {
	return id;
}

//next attack
//check if source still infected when attack occurs
