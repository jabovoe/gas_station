#ifndef __CL_CAR__H
#define __CL_CAR__H
#include "cl_base.h"
class cl_car : public cl_base
{
public:
	int volume;
	string mark;
	cl_car(cl_base* p_head_object, string s_object_name);
};
#endif