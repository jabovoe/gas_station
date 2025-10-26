#include "cl_gas.h"
#include "cl_output.h"
cl_gas::cl_gas(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name) {
}
void cl_gas::signal_gas_to_output(string& msg)
{
}
void cl_gas::handler_gas_from_remocon(string msg)
{
	if (msg.substr(0, 18) == "Display the petrol")
	{
		int space = msg.find(" ", 19);
		string gas_num = msg.substr(19, space - 19);
		cl_gas* p_station = this;
		this->set_connection(SIGNAL_D(cl_gas::signal_gas_to_output),
			search_tree("Output"), HANDLER_D(cl_output::handler_output_from_remocon));
		for (int i = 0; i < p_station->done.size(); i++)
		{
			emit_signal(SIGNAL_D(cl_gas::signal_gas_to_output), p_station -> done[i]);
		}
	}
	else
	{
		if (current == nullptr)
		{
			if (!cars_order.empty())
			{
				current = cars_order.front();
				cars_order.pop();
			}
		}
		if (current != nullptr)
		{
			current->volume -= 10;
			if (current->volume == 0)
			{
				done.push_back(current->get_name());
				this->delete_sub_object(current->get_name());
				current = nullptr;
			}
		}
	}
}