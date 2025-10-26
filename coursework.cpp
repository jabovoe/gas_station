#include "cl_application.h"
int main()
{
	cl_application ob_cl_application(nullptr); // declaring application object
	ob_cl_application.build_tree_objects(); // system building
	return ob_cl_application.exec_app(); // launching the system
}