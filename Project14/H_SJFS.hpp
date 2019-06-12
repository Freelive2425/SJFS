#ifndef __H_SJFS_HPP__
#define __H_SJFS_HPP__

#include<vector>
#include<queue>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>

using namespace std;

struct SProcess {
	int index;
	int burst;
	int arrive;


	SProcess(int index, int burst, int arrive) {
		this->index = index;
		this->burst = burst;
		this->arrive = arrive;
	}
};

struct SWaiting {

	int waiting;
	int index;
	int burst;

	SWaiting(int index, int waiting, int burst) {
		this->waiting = waiting;
		this->index = index;
		this->burst = burst;
	}
};

class ComparisonClass { public: bool operator() (SProcess* a, SProcess* b) { return (a->burst>b->burst); } };

class C_SJFS {

private:
	vector<SProcess*>process;
	int last_index;

public:  C_SJFS() { process = vector<SProcess*>(); last_index = 0; }

private:
	void generate_process(int n, vector<SWaiting*>&waiting) {
		int burst = 0;
		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			burst = int(rand() % 10 + 1);
			process.push_back(new SProcess(last_index, burst, int(0)));
			waiting.push_back(new SWaiting(last_index, 0, burst));
			++last_index;
		}
	}

	void sort_time(vector<SProcess*>&process) { sort(process.begin(), process.end(), [](SProcess *a, SProcess *b)->bool {return a->burst - b->burst; }); }
	void sort_burst(vector<SProcess*>&process) { sort(process.begin(), process.end(), [](SProcess *a, SProcess *b)->bool {return a->arrive - b->arrive; }); }


	void add_process(priority_queue<SProcess*, vector<SProcess*>, ComparisonClass>& _queue, int time) {
		for (int i = 0; i<process.size(); ++i) {
			if (process.at(i)->arrive <= time) {
				_queue.push(process.at(i));
				process.erase(process.begin() + i);
				--i;
			}
		}
	}

	int getMinorTime() {
		int aux = process.at(0)->arrive;
		for (int i = 0; i<process.size(); ++i) {
			if (aux>process.at(i)->arrive)
				aux = process.at(i)->arrive;
		}
		return aux;
	}

	int find_process(int _index, vector<SWaiting*> waiting) {
		int aux = 0;
		for (int i = 0; i<waiting.size(); ++i) {
			if (waiting.at(i)->index == _index) {
				aux = i;
				break;
			}
		}
		return aux;
	}


public:  vector<SWaiting*>  SJFS(int n) {
	int time = 0;
	priority_queue<SProcess*, vector<SProcess*>, ComparisonClass> _queue;
	vector<SWaiting*> waiting = vector<SWaiting*>();
	generate_process(n, waiting);

	for (SProcess *p : process)
		cout << "Index: " << p->index << " - " << "Burst: " << p->burst << " - " << "Arrive: " << p->arrive << endl;
	cout << endl;

	time = getMinorTime();
	add_process(_queue, time);

	bool flag = true;
	int index_aux = 0;
	int x = 0, y = 0, z = 0;
	while (!process.empty() || !_queue.empty()) {


		cout << "Time before process: " << time << endl;
		cout << "Index: " << _queue.top()->index << endl;
		cout << "Burst: " << _queue.top()->burst << endl;
		cout << "Arrive: " << _queue.top()->arrive << endl;

		--_queue.top()->burst;
		++time;

		cout << "Time after process: " << time << endl;
		cout << "Index: " << _queue.top()->index << endl;
		cout << "Burst: " << _queue.top()->burst << endl;
		cout << "Arrive: " << _queue.top()->arrive << endl;
		cout << endl;

		if (_queue.top()->burst == 0) {
			index_aux = find_process(_queue.top()->index, waiting);
			x = time;
			y = _queue.top()->arrive;
			z = waiting.at(index_aux)->burst;
			waiting.at(index_aux)->waiting = time - _queue.top()->arrive - waiting.at(index_aux)->burst;
			_queue.pop();
		}

		add_process(_queue, time);

		if (!process.empty() && _queue.empty()) {
			time += getMinorTime();
			add_process(_queue, time);
		}

	}


	return waiting;
}

};

#endif