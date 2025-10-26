#ifndef __CL_REMOCON__H
#define __CL_REMOCON__H
#include "cl_base.h"
#include "cl_gas.h"
#include "cl_car.h"
class cl_remocon : public cl_base
{
public:
	vector<string> gas_stations;
	cl_remocon(cl_base* p_head_object, string s_object_name);
	void handler_remocon_from_reader(string msg);
	void signal_remocon_to_all(string& msg);
	void signal_remocon_to_output(string& msg);
	void signal_remocon_to_app(string& msg);
	void signal_remocon_to_gas(string& msg);
};
#endif