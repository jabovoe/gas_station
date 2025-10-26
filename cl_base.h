#ifndef __CL_BASE__H
#define __CL_BASE__H
#include <vector>
#include <string>
#include <queue>
#include <iostream>
using std::string, std::vector, std::cout, std::cin, std::queue;
class cl_base;
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f)
typedef void (cl_base::* TYPE_SIGNAL)(string& msg);
typedef void (cl_base::* TYPE_HANDLER)(string msg);
struct o_sh
{
	TYPE_SIGNAL p_signal;
	cl_base* p_target;
	TYPE_HANDLER p_handler;
};
class cl_base
{
	cl_base* p_head_object;
	vector <cl_base*> subordinate_objects;
	string s_object_name;
	int status = 1;
	vector <o_sh*> connects;
public:
	cl_base(cl_base* p_head_object, string s_object_name = "Base_object");
	bool set_name(string s_new_name);
	string get_name();
	cl_base* get_head_obj();
	void print_tree();
	void print_tree_and_state();
	cl_base* search_current(string s_name);
	cl_base* search_tree(string s_name);
	void set_state(int state);
	cl_base* get_sub_object(string s_name);
	~cl_base();
	cl_base* find_object_by_coord(string s_coord);
	void delete_sub_object(string s_name);
	bool set_head_obj(cl_base* p_new_head);
	void set_connection(TYPE_SIGNAL p_signal,
		cl_base* p_target,
		TYPE_HANDLER p_handler);
	void delete_connection(TYPE_SIGNAL p_signal,
		cl_base* p_target,
		TYPE_HANDLER p_handler);
	void emit_signal(TYPE_SIGNAL p_signal, string s_message);
	string get_absolute_path();
};
#endif
