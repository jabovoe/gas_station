#ifndef __CL_OUTPUT__H
#define __CL_OUTPUT__H
#include "cl_base.h"
class cl_output : public cl_base
{
public:
	cl_output(cl_base* p_head_object, string s_object_name);
	void handler_output_from_remocon(string msg);
};
#endif