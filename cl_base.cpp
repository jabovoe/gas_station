#include "cl_base.h"
cl_base::cl_base(cl_base* p_head_object, string s_object_name)
{
	this->p_head_object = p_head_object; 
	this->s_object_name = s_object_name; 
	if (this->p_head_object)
	{
		p_head_object->subordinate_objects.push_back(this); 
	}
}
bool cl_base::set_name(string s_new_name)
{
	if (this->p_head_object)
	{
		for (int i = 0; i < p_head_object->subordinate_objects.size(); i++)
		{
			if (p_head_object->subordinate_objects[i]->get_name() == s_new_name)
			{
				return false;
			}
		}
	}
	this->s_object_name = s_new_name;
	return true;
}
string cl_base::get_name()
{
	return s_object_name;
}
cl_base* cl_base::get_head_obj()
{
	return p_head_object;
}
void cl_base::print_tree()
{
	cl_base* p_root = this;
	cout << '\n';
	while (p_root->get_head_obj() != nullptr)
	{
		p_root = p_root->get_head_obj();
		cout << " ";
	}
	cout << this->get_name();
	for (auto p_sub : this->subordinate_objects)
	{
		p_sub->print_tree();
	}
}
void cl_base::print_tree_and_state()
{
	cl_base* p_root = this;
	while (p_root->get_head_obj() != nullptr)
	{
		p_root = p_root->get_head_obj();
		cout << " ";
	}
	cout << this->get_name();
	if (this->status != 0)
	{
		cout << " is ready";
	}
	else
	{
		cout << " is not ready";
	}
	cout << '\n';
	for (auto p_sub : this->subordinate_objects)
	{
		p_sub->print_tree_and_state();
	}
}
cl_base* cl_base::get_sub_object(string s_name)
{
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		if (subordinate_objects[i]->get_name() == s_name)
		{
			return subordinate_objects[i];
		}
	}
	return nullptr;
}
cl_base::~cl_base()
{
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		delete subordinate_objects[i];
	}
}
cl_base* cl_base::search_current(string s_name)
{
	cl_base* p_found = nullptr;
	cl_base* p_front = nullptr;
	queue<cl_base*> q;
	q.push(this);
	while (!q.empty())
	{
		p_front = q.front();
		q.pop();
		if (p_front->get_name() == s_name)
		{
			if (p_found == nullptr)
			{
				p_found = p_front;
			}
			else
			{
				return nullptr;
			}
		}
		for (auto p_sub : p_front->subordinate_objects)
		{
			q.push(p_sub);
		}
	}
	return p_found;
}
cl_base* cl_base::search_tree(string s_name)
{
	cl_base* p_root = this;
	while (p_root->get_head_obj() != nullptr)
	{
		p_root = p_root->get_head_obj();
	}
	return p_root->search_current(s_name);
}
void cl_base::set_state(int state)
{
	cl_base* p_root = this;
	if (state != 0)
	{
		while (p_root->get_head_obj() != nullptr)
		{
			p_root = p_root->get_head_obj();
			if (p_root->status == 0)
			{
				return;
			}
		}
		this->status = state;
	}
	else
	{
		this->status = state;
		for (auto p_sub : this->subordinate_objects)
		{
			p_sub->set_state(0);
		}
	}
}
cl_base* cl_base::find_object_by_coord(string s_coord)
{
	cl_base* p_root = this;
	if (s_coord == "/")
	{
		while (p_root->get_head_obj() != nullptr)
		{
			p_root = p_root->get_head_obj();
		}
		return p_root;
	}
	else if (s_coord == ".")
	{
		return this;
	}
	else if (s_coord[0] == '/' && s_coord[1] == '/')
	{
		return this->search_tree(s_coord.substr(2));
	}
	else if (s_coord[0] == '.')
	{
		return this->search_current(s_coord.substr(1));
	}
	int i_slash_2 = s_coord.find("/", 1);
	string s_name;
	cl_base* p_obj;
	if (s_coord[0] == '/')
	{
		while (p_root->get_head_obj() != nullptr)
		{
			p_root = p_root->get_head_obj();
		}
		if (i_slash_2 != -1)
		{
			s_name = s_coord.substr(1, i_slash_2 - 1);
			p_obj = p_root->get_sub_object(s_name);
			if (p_obj != nullptr)
				return p_obj->find_object_by_coord(s_coord.substr(i_slash_2 + 1));
			else
				return nullptr;
		}
		else
		{
			return p_root->get_sub_object(s_coord.substr(1));
		}
	}
	else
	{
		if (i_slash_2 != -1)
		{
			s_name = s_coord.substr(0, i_slash_2);
			p_obj = this->get_sub_object(s_name);
			if (p_obj != nullptr)
				return p_obj->find_object_by_coord(s_coord.substr(i_slash_2 + 1));
			else
				return nullptr;
		}
		else
		{
			return this->get_sub_object(s_coord);
		}
	}
}
void cl_base::delete_sub_object(string s_name)
{
	for (int i = 0; i < subordinate_objects.size(); i++)
	{
		if (subordinate_objects[i]->get_name() == s_name)
		{
			subordinate_objects.erase(subordinate_objects.begin() + i);
			i--;
		}
	}
}
bool cl_base::set_head_obj(cl_base* p_new_head)
{
	cl_base* p_temp = p_new_head;
	if (p_new_head == nullptr)
	{
		return false;
	}
	else if (this->get_head_obj() == nullptr)
	{
		return false;
	}
	else if (p_new_head->get_sub_object(this->get_name()) != nullptr)
	{
		return false;
	}
	while (p_temp != nullptr)
	{
		if (p_temp == this)
		{
			return false;
		}
		else
			p_temp = p_temp->get_head_obj();
	}
	this->get_head_obj()->delete_sub_object(this->get_name());
	this->p_head_object = p_new_head;
	this->p_head_object->subordinate_objects.push_back(this);
	return true;
}
void cl_base::set_connection(TYPE_SIGNAL p_signal,
	cl_base* p_target,
	TYPE_HANDLER p_handler)
{
	o_sh* p_value;
	for (int i = 0; i < connects.size(); i++)
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_target == p_target &&
			connects[i]->p_handler == p_handler)
			return;
	}
	p_value = new o_sh();
	p_value->p_signal = p_signal;
	p_value->p_target = p_target;
	p_value->p_handler = p_handler;
	connects.push_back(p_value);
}
void cl_base::delete_connection(TYPE_SIGNAL p_signal,
	cl_base* p_target,
	TYPE_HANDLER p_handler)
{
	vector<o_sh*>::iterator p_it;
	for (p_it = connects.begin(); p_it != connects.end();)
	{
		if ((*p_it)->p_signal == p_signal && (*p_it)->p_target == p_target && (*p_it)->p_handler == p_handler)
		{
			p_it = connects.erase(p_it);
		}
		else
		{
			p_it++;
		}
	}
}
void cl_base::emit_signal(TYPE_SIGNAL p_signal, string s_message)
{
	(this->*p_signal)(s_message);
	for (auto connection : connects)
	{
		if (connection->p_signal == p_signal)
		{
			cl_base* p_target = connection->p_target;
			TYPE_HANDLER p_handler = connection->p_handler;
			(p_target->*p_handler)(s_message);
		}
	}
}
string cl_base::get_absolute_path()
{
	string s_abs_path = "";
	cl_base* p_object = this;
	if (p_object->get_head_obj() == nullptr)
	{
		string s_abs_path = "/";
		return s_abs_path;
	}
	while (p_object->get_head_obj() != nullptr)
	{
		s_abs_path = "/" + p_object->get_name() + s_abs_path;
		p_object = p_object->get_head_obj();
	}
	return s_abs_path;
}