#include <iostream>
#include "BinaryHeap.h"
#include "Simulation.h"

using namespace std;

//This method determines whether the network is fixed by checking if there's at least 1 compromised PC
bool Simulation::isNetworkFixed() {
	for (int i = 1; i < number_of_computers; i++) {
		if (network[i] != 0) {
			return false;
		}
	}
	return true;
}

//This method determines whether the network has at least 50% of its computers are compromised
bool Simulation::isNetworkCompromised() {
	int count = 0;
	for (int i = 0; i < number_of_computers; i++) {
		if (network[i] != 0)
			count++;
	}
	if (count >= ((number_of_computers / 2) + 1)) {
		return true;
	}
	return false;
}

//generate a random integer
int Simulation::random_pc() {
	random_device rd;
	int pc = rd() % number_of_computers + 1;
	return pc;
}

//set the percent success
void Simulation::setPS(int ps) {
	percent_success = ps;
}

//set the percent detect
void Simulation::setPD(int pd) {
	percent_detect = pd;
}

/*
* Sets the number of computers for the network array and initializes the array to zeros.
* network[0] = Attacker
* network [1 to numOfComputers] = PC's
* network[i] = 0 - Clean PC
* network[i] = 1 - Compromised
* network[i] = 2 - Fix scheduled
*/
void Simulation::setNum(int num) {
	number_of_computers = num;
	network = new int[number_of_computers + 1];
	network[0] = 1;
	for (int i = 1; i < number_of_computers + 1; i++) {
		network[i] = 0;
	}
}

//returns the global clock
int Simulation::getClock() {
	return global_clock;
}

/*
* Attack method
* Determines whether an attack is successful
* Handles IDS crossings
*/
void Simulation::Attack(Event e) {
	random_device rd;
	int succeed = rd() % 99 + 1;
	//if check if attack is successful and the pc in the network array is compromised
	if (succeed <= percent_success && network[e.getSource()] != 0) {
		Event nextAttack(global_clock + 11, e.getSource(), random_pc());
		heap.Insert(nextAttack);
		match_start = true;

		if (network[e.getTarget()] == 0) {
			network[e.getTarget()] = 1;
			Event pcAttack(global_clock + 10, e.getTarget(), rd() % number_of_computers + 1);
			heap.Insert(pcAttack);
		}

		//Even numbers = switch1
		//Odd numbers = switch2
		//When the source and target are not the same switch, check IDS detection and run Notify
		if (e.getTarget() % 2 == 0 && e.getSource() % 2 == 1) {
			succeed = rd() % 99 + 1;
			if (succeed <= percent_detect) {
				Event notifyEvent(global_clock, e);
				heap.Insert(notifyEvent);
			}
		}
		if ((e.getTarget() % 2 == 1 && e.getSource() % 2 == 0) | (e.getSource() == 0)) {
			succeed = rd() % 99 + 1;
			if (succeed <= percent_detect) {
				Event notifyEvent(global_clock, e);
				heap.Insert(notifyEvent);
			}
		}
	}
	//Even when attack isnt successful, create next attacks
	else {
		if (e.getSource() == 0) {
			Event nextAttack(global_clock + 11, 0, random_pc());
			heap.Insert(nextAttack);
		}
		else {
			Event nextAttack(global_clock + 10, e.getSource(), random_pc());
			heap.Insert(nextAttack);
		}
	}
}

void Simulation::Notify(Event e) {
	if ((global_clock >= last_fix + 100) | (last_fix == 0)) {
		//Create Fix for source as long as source isn't the Attacker and a Fix hasn't been already scheduled
		if (network[e.getSource()] != 2 && e.getSource() != 0) {
			Event fix_source(global_clock + 100, e.getSource());
			last_fix = global_clock + 100;
			heap.Insert(fix_source);
			network[e.getSource()] = 2;
		}
		//Create Fix for target as long as a Fix hasn't already been scheduled for that PC
		if ((global_clock >= last_fix + 100) | (last_fix == 0)) {
			if (network[e.getTarget()] != 2) {
				Event fix_target(global_clock + 100, e.getTarget());
				last_fix = global_clock + 100;
				heap.Insert(fix_target);
				network[e.getTarget()] = 2;
			}
		}
		else {
			Event fix_target(last_fix + 100, e.getTarget());
			last_fix += 100;
			heap.Insert(fix_target);
			network[e.getTarget()] = 2;
		}
	}

	//global_clock < last_fix + 100, still on cooldown period
	else {
		if (network[e.getSource()] != 2 && e.getSource() != 0) {
			Event fix_source(last_fix + 100, e.getSource());
			heap.Insert(fix_source);
			last_fix += 100;
			network[e.getSource()] = 2;
		}
		if (network[e.getTarget()] != 2) {
			Event fix_target(last_fix + 100, e.getTarget());
			last_fix += 100;
			heap.Insert(fix_target);
			network[e.getTarget()] = 2;
		}
	}
}

void Simulation::Fix(Event e) {
	network[e.getTarget()] = 0;
}

int Simulation::checkEndGame() {
	if (match_start == true && isNetworkFixed()) {
		cout << "Sysadmin wins!" << endl;
		return 1;
	}

	if (match_start == true && isNetworkCompromised()) {
		cout << "Attacker wins!" << endl;
		return 2;
	}
	//game not over
	return 0;
}

int Simulation::run() {
	//first attacker's attack
	Event e(11, 0, random_pc());
	heap.Insert(e);

	while (global_clock < end_time) {
		//Check queue for events occurring now
		while (heap.ExtractMin().getTime() == global_clock) {
			Event e = heap.ExtractMin();
			heap.DeleteMin();

			if (e.getId() == 'a')
				Attack(e);
			if (e.getId() == 'n')
				Notify(e);
			if (e.getId() == 'f')
				Fix(e);
		}

		//if 0 is returned, continue, else stop game
		int result = checkEndGame();
		if (result != 0)
			return result;
		global_clock = heap.ExtractMin().getTime();
	}
	return 0;
}

int main() {
	Simulation sim;
	int ps;
	int pd;
	int num;

	cout << "Enter percent of success: ";
	std::cin >> ps;
	sim.setPS(ps);
	cout << "Enter percent of detect: ";
	std::cin >> pd;
	sim.setPD(pd);
	cout << "Enter number of computers: ";
	std::cin >> num;
	sim.setNum(num);

	if(sim.run() == 0)
		cout << "Tie" << endl;
	return 0;
}

