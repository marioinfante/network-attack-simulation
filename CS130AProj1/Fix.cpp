#include "Event.h"
#include "Fix.h"
#include <iostream>

using namespace std;

Fix::Fix(int tm, int tgt) {
	time = tm;
	target = tgt;
	cout << "Fix (" << time << ',' << target << ')' << endl;
}

int Fix::getTarget() {
	return target;
}

//has a fix already been scheduled for the PC in question?
//if so, skip, if not then create fix event