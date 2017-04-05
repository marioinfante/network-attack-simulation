#ifndef SIMULATION_H
#define SIMULATION_H
#include <random>

class Simulation {
public:
	bool isNetworkFixed();
	bool isNetworkCompromised();
	int random_pc();
	int getClock();
	void setPS(int ps);
	void setPD(int pd);
	void setNum(int num);
	int run();
	void Attack(Event e);
	void Fix(Event e);
	void Notify(Event e);
	int checkEndGame();
private:
	BinaryHeap heap;
	int percent_success;
	int percent_detect;
	bool match_start = false;
	int number_of_computers;
	int* network;
	int last_fix = 0;
	int global_clock = 0;
	int end_time = 86400000; //100 days
};

#endif 
