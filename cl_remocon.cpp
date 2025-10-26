#include "cl_remocon.h"
#include "cl_output.h"
cl_remocon::cl_remocon(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name) {}
void cl_remocon::handler_remocon_from_reader(string msg)
{
	if (msg == "Turn off the system" || msg == "End of information about petrol filling stations")
	{
		emit_signal(SIGNAL_D(cl_remocon::signal_remocon_to_output), msg);
		emit_signal(SIGNAL_D(cl_remocon::signal_remocon_to_app), msg);
	}
	else if (msg.substr(0, 16) == "Fill up the tank")
	{
		string car_name, car_mark;
		int car_volume, space_1, space_2;
		space_1 = msg.find(" ", 17);
		car_name = msg.substr(17, space_1 - 17);
		space_2 = msg.find(" ", space_1 + 1);
		car_mark = msg.substr(space_1 + 1, space_2 - space_1 - 1);
		car_volume = stoi(msg.substr(space_2));
		cl_car* p_sub = nullptr;
		p_sub = new cl_car(this, car_name);
		p_sub->volume = car_volume;
		p_sub->mark = car_mark;
		for (int i = 0; i < this->gas_stations.size(); i++)
		{
			cl_base* p_st = this->get_sub_object(gas_stations[i]);
			cl_gas* p_station = static_cast<cl_gas*>(p_st);
			if ((p_station->mark == car_mark) && (p_station->volume >= car_volume))
			{
				p_station->volume -= car_volume;
				p_station->cars_order.push(p_sub);
				p_sub->set_head_obj(p_station);
				emit_signal(SIGNAL_D(cl_remocon::signal_remocon_to_all), msg);
				return;
			}
		}
		msg = "Denial" + car_name;
		emit_signal(SIGNAL_D(cl_remocon::signal_remocon_to_all), msg);
		this->delete_sub_object(car_name);
	}
	else if (msg.substr(0, 18) == "Display the petrol")
	{
		string gas_num = msg.substr(42);
		cl_base* p_sub = this->get_sub_object(gas_num);
		cl_gas* p_station = static_cast<cl_gas*>(p_sub);
		msg = msg.substr(0, 18) + gas_num + " " + std::to_string(p_station -> cars_order.size()) + " " + std::to_string(p_station->done.size());
		this->set_connection(SIGNAL_D(cl_remocon::signal_remocon_to_gas), p_station, HANDLER_D(cl_gas::handler_gas_from_remocon));
		emit_signal(SIGNAL_D(cl_remocon::signal_remocon_to_output), msg);
		emit_signal(SIGNAL_D(cl_remocon::signal_remocon_to_gas), msg);
		this->delete_connection(SIGNAL_D(cl_remocon::signal_remocon_to_gas), p_sub, HANDLER_D(cl_gas::handler_gas_from_remocon));
	}
	else if (msg == "Display the system status")
	{
		int done = 0, queue = 0;
		for (int i = 0; i < this->gas_stations.size(); i++)
		{
			cl_base* p_sub = this->get_sub_object(gas_stations[i]);
			cl_gas* p_station = static_cast<cl_gas*>(p_sub);
			done += p_station->done.size();
			queue += p_station->cars_order.size();
			msg = "Petrol station " + gas_stations[i] + " " + std::to_string(p_station->volume) + " " + std::to_string(p_station -> cars_order.size());
			emit_signal(SIGNAL_D(cl_remocon::signal_remocon_to_output), msg);
		}
		msg = "Operator " + std::to_string(done) + " " + std::to_string(queue);
		emit_signal(SIGNAL_D(cl_remocon::signal_remocon_to_all), msg);
	}
	else if (msg == "")
	{
		emit_signal(SIGNAL_D(cl_remocon::signal_remocon_to_all), msg);
	}
	else
	{
		string mark;
		int volume, space_1, space_2;
		space_1 = msg.find(" ", 1);
		space_2 = msg.find(" ", space_1 + 1);
		mark = msg.substr(space_1 + 1, space_2 - space_1 - 1);
		volume = stoi(msg.substr(space_2 + 1));
		cl_gas* p_sub;
		p_sub = new cl_gas(this, msg.substr(0, space_1));
		p_sub->mark = mark;
		p_sub->volume = volume;
		this->gas_stations.push_back(msg.substr(0, space_1));
		this->set_connection(SIGNAL_D(cl_remocon::signal_remocon_to_all),
			p_sub, HANDLER_D(cl_gas::handler_gas_from_remocon));
	}
}
void cl_remocon::signal_remocon_to_all(string& msg) {}
void cl_remocon::signal_remocon_to_output(string& msg) {}
void cl_remocon::signal_remocon_to_app(string& msg) {}
void cl_remocon::signal_remocon_to_gas(string& msg) {}