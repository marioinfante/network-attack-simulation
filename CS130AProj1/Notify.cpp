#include "Event.h"
#include "Attack.h"
#include "Notify.h"
#include <iostream>

using namespace std;

Notify::Notify(int tm, Attack a) {
	time = tm;
	source = a.getSource();
	target = a.getTarget();
	cout << "Notify (" << time << ',' << source << ',' << target << ')' << endl;

}

int Notify::getSource() {
	return source;
}

int Notify::getTarget() {
	return target;
}