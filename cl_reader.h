#ifndef __CL_READER__H
#define __CL_READER__H
#include "cl_base.h"
class cl_reader : public cl_base
{
public:
	cl_reader(cl_base* p_head_object, string s_object_name);
	void handler_reader_from_app(string msg);
	void signal_reader_to_remocon(string& msg);
};
#endif