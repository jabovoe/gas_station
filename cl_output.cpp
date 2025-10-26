#include "cl_output.h"
cl_output::cl_output(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name) {
}
void cl_output::handler_output_from_remocon(string msg)
{
	if (msg == "End of information about petrol filling stations")
	{
		cout << "Ready to work";
	}
	else if (msg.substr(0, 6) == "Denial")
	{
		cout << '\n' << "Denial of service " << msg.substr(6);
	}
	else if (msg.substr(0, 18) == "Display the petrol")
	{
		cout << '\n' << "Petrol filling station status " << msg.substr(18);
	}
	else if (msg.substr(0, 16) == "Fill up the tank" || msg == "")
	{
	}
	else
	{
		cout << '\n' << msg;
	}
}