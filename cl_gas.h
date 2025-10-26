#ifndef __CL_GAS__H
#define __CL_GAS__H
#include "cl_base.h"
#include "cl_car.h"
class cl_gas : public cl_base
{
	cl_car* current = nullptr;
public:
	string mark = "";
	int volume = 0;
	cl_gas(cl_base* p_head_object, string s_object_name);
	void signal_gas_to_output(string& msg);
	void handler_gas_from_remocon(string msg);
	queue<cl_car*> cars_order;
	vector<string> done;
};
#endif