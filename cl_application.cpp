#include "cl_application.h"
#include <iostream>
#include <windows.h>
using std::cin, std::cout;
cl_application::cl_application(cl_base* p_head_object) :
	cl_base(p_head_object) {
}
void cl_application::signal_app_to_reader(string& msg)
{
}
void cl_application::handler_app_from_remocon(string msg)
{
	s_cmd = msg;
}
void cl_application::build_tree_objects()
{
	cl_base* p_sub = nullptr;
	this->set_name("System");
	p_sub = new cl_reader(this, "Reader");
	p_sub = new cl_remocon(this, "Remote_control");
	p_sub = new cl_output(this, "Output");
	this->set_connection(SIGNAL_D(cl_application::signal_app_to_reader),
		get_sub_object("Reader"), HANDLER_D(cl_reader::handler_reader_from_app));
	get_sub_object("Reader") ->
		set_connection(SIGNAL_D(cl_reader::signal_reader_to_remocon),
			get_sub_object("Remote_control"),
			HANDLER_D(cl_remocon::handler_remocon_from_reader));
	get_sub_object("Remote_control") ->
		set_connection(SIGNAL_D(cl_remocon::signal_remocon_to_app), this,
			HANDLER_D(cl_application::handler_app_from_remocon));
	get_sub_object("Remote_control") ->
		set_connection(SIGNAL_D(cl_remocon::signal_remocon_to_output),
			get_sub_object("Output"),
			HANDLER_D(cl_output::handler_output_from_remocon));
	get_sub_object("Remote_control") ->
		set_connection(SIGNAL_D(cl_remocon::signal_remocon_to_all),
			get_sub_object("Output"), 
			HANDLER_D(cl_output::handler_output_from_remocon));
	string s_msg;
	s_cmd = "";
	while (s_cmd != "End of information about petrol filling stations")
	{
		emit_signal(SIGNAL_D(cl_application::signal_app_to_reader), s_msg);
	}
}
int cl_application::exec_app()
{
	string s_msg;
	s_cmd = "";
	while (s_cmd != "Turn off the system")
	{
		emit_signal(SIGNAL_D(cl_application::signal_app_to_reader), s_msg);
	}
	Sleep(10000);
	return 0;
}