#include "cl_reader.h"
cl_reader::cl_reader(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name) {
}
void cl_reader::handler_reader_from_app(string msg)
{
	string s_cmd;
	getline(cin, s_cmd);
	emit_signal(SIGNAL_D(cl_reader::signal_reader_to_remocon), s_cmd);
}
void cl_reader::signal_reader_to_remocon(string& msg)
{
}