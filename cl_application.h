#ifndef __CL_APPLICATION__H
#define __CL_APPLICATION__H
#include "cl_base.h"
#include "cl_car.h"
#include "cl_gas.h"
#include "cl_output.h"
#include "cl_reader.h"
#include "cl_remocon.h"
class cl_application : public cl_base
{
	string s_cmd;
public:
	cl_application(cl_base* p_head_object);
	void build_tree_objects();
	void signal_app_to_reader(string& msg);
	void handler_app_from_remocon(string msg);
	int exec_app();
};
#endif