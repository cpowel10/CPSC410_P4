#include <string>
#include <queue>
#include "stdlib.h"

#include "../includes/waiter.h"
#include "../includes/externs.h"

using namespace std;

//extern::bool b_WaiterIsFinished;
//extern::queue<ORDER> order_in_Q;

//ID is just a number used to identify this particular baker
//(used with PRINT statements)
//filename is what waiter reads in orders from
Waiter::Waiter(int id,std::string filename):id(id),myIO(filename)
{
}

Waiter::~Waiter()
{
}

//gets next Order from file_IO
//if return == SUCCESS then anOrder
//contains new order
//otherwise return contains fileIO error
int Waiter::getNext(ORDER &anOrder){
	int ret = myIO.getNext(anOrder);
	if (ret == SUCCESS)
		return SUCCESS;
	else{
		return ret;
	}
}

//contains a loop that will get orders from filename one at a time
//then puts them in order_in_Q then signals baker(s) using cv_order_inQ
//so they can be consumed by baker(s)
//when finished exits loop and signals baker(s) using cv_order_inQ that
//it is done using b_WaiterIsFinished
void Waiter::beWaiter() {
	int ret = SUCCESS;
	while (ret == SUCCESS){
		ORDER anOrder;
		ret = this->myIO.getNext(anOrder);
		if (ret == SUCCESS){
			order_in_Q.push(anOrder);
			cv_order_inQ.notify_all();
		}
	}
	b_WaiterIsFinished = true;
}

