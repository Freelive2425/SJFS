#include <iostream>
#include "H_SJFS.hpp"
#include <iostream>
using namespace std;

int main() {

	C_SJFS *c = new C_SJFS();
	for (SWaiting* w : c->SJFS(5))
		cout << w->index << " - " << w->waiting << endl;
	system("pause");
	return 0;
}