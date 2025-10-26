# gas_station
This is my coursework made for object-oriented programming on C++ class

Problem definition 
Simulation of a gas station operation with the following instructions.
The system contains of the following elements:
    • gas station operator;
    • control panel;
    • a multitude of fuel dispensers with a certain fuel type and initial volume;
    • a multitude of cars with a request for a certain fuel type and volume;
    • screen displaying information about system operations.

System Operating Rules:
    • Time is measured in clock cycles.
    • In one cycle, a car enters the gas station and sends a request to the operator to purchase fuel.
    • In one cycle, the operator processes the request. If the required fuel of the certain type in the required volume is available, the operator places the car in the queue for the fuel dispenser. If the required volume of fuel for the car is not available, the service is denied. The car leaves the gas station.
    • Each fuel dispenser has a unique number and dispenses only one type of fuel. There are no two dispensers with the same fuel type. The service time for one car depends on the volume of fuel purchased. A queue may form at a dispenser. In one cycle, one car from the queue can be moved to the dispenser to start refueling. In one cycle, a dispenser can dispense 10 liters of fuel. On the final cycle of refueling, the car leaves the gas station.
The request from cars for a fuel volume is a multiple of 10 liters. Within a single cycle, the operator can queue up or deny service to no more than one car. Within a cycle, no more than one car can arrive at the gas station.

System commands:

1. Fuel request from the car.
	Fill up the tank «car's license plate» «fuel type» «required volume»
This command simulates a car's request for fuel. Based on the fuel type and volume, the system determines if there is a enough quantity of unsold fuel. If there is enough fuel, the car is placed in the queue for the corresponding fuel dispenser. If there is not enough fuel, the service is denied.

2. Displaying the list of cars serviced by the fuel dispenser.
	Display the petrol filling station status «fuel dispenser number»
Upon this command, a list of serviced cars is output line by line. After the command is processed, the system elements perform actions according to the cycle.

3. System status.
	Display the system status
Upon this command, the system state at the beginning of the current cycle is output. The information includes a list of fuel dispensers, the volume of unsold fuel remaining, and the size of a queue of cars. The remaining fuel is calculated taking into account the cars in the queue. The number of a car refueled at each dispenser is also displayed. The fuel dispensers are ordered by their numbers. The following information is displayed: the total number of cars that have been refueled and how many are still standing in the queue. After the command is processed, the system elements perform actions according to the cycle.

4. Empty command (a line containing nothing).
The system elements perform actions according to the cycle.

5. System shutdown.
	Turn off the system

The system uses the following objects:

1. The System object. Manages the execution of cycles.

2. The command and data reader object. This object simulates the work of the operator. It reads data for system preparation and configuration. After reading each new line of initial data or a command, the object emits a signal with the text of the received data. All initial data and command data are syntactically correct. Each command line corresponds to one cycle. If a line is empty, the system executes one cycle.

3. The Control Panel object models the work of the operator and their control device for processing incoming commands (requests). The object emits an appropriate signal or signals. It contains a list of fuel dispenser numbers, manages the distribution of cars to the dispensers, and determines the feasibility of a request. If the request can be fulfilled, it places the car in the queue for the corresponding dispenser; otherwise, it shows a denial message. It prepares data based on the system's state. The operator informs the car of the dispenser number. This action is performed within a single cycle.

4. The Fuel Dispenser object. It emits a signal indicating the start or completion of a car's refueling. It processes the contents of its queue. Upon the command to output the list of serviced cars, it emits signals to the output device with the text of the required information.
    
5. The Car object. This object is created (= enters the gas station) upon a request command. It contains the car's license plate, fuel type, and the required refueling volume. When a command is received, this object is added as a subordinate element to the Control Panel object. After assignment, the object is reassigned (re-parented) to the corresponding Fuel Dispenser object. After servicing is completed, the object is removed from the object tree and destroyed (= leaves the gas station). A method for removal from the hierarchy tree and object destruction is added to the base class.

6. The object for outputting the system state or command result to the console. This object receives the text for output via signals from other system objects. Each received message is output on a new line.

Algorithm:
1. Call the build_tree_objects() method of the System object.
	1.1. Building the object hierarchy tree. Object characteristics are initialized.
	1.2. Loop for processing input data and loading the initial system state.
		1.2.1. Sending a signal to the reader object to input data.
		1.2.2. Executing the operation to load the next portion of data.
    		1.2.3. Establishing signal and handler connections for the new object.
    	1.3. Establishing signal and handler connections between objects.
2. Call the exec_app() method of the System object.
	2.1. Bringing all objects to a ready state.
 	2.2. Loop for processing input commands.
    		2.2.1. Sending a signal to the object for command input.
    		2.2.2. Executing the command.
	2.3. After receiving the "Turn off the system" command, turn off the system.

A request from an object means sending a signal. All messages to the console are output on a new line.

1.1 Input data description
Input of fuel dispenser information:
«dispenser number» «fuel type» «fuel volume in liters»
Completion of fuel dispenser information input:
	End of information about petrol filling station
Commands are entered. Each command is executed within a single cycle.
The last command is:
	Turn off the system

Input example:
PS_1 A-72 100
PS_2 A-76 1000
PS_3 AI-91 1000
PS_4 AI-93 1000
PS_5 AI-95 1000
End of information about petrol filling stations
Fill up the tank rus77-001 A-72 30

Fill up the tank rus77-002 AI-93 50
Fill up the tank rus77-003 AI-93 50
Fill up the tank rus77-004 AI-93 50





Display the petrol filling station status PS_1


Display the system status

Display the petrol filling station status PS_4






Display the petrol filling station status PS_4
Display the system status
Turn off the system

1.2 Output data description
After completing the construction of the object hierarchy tree and loading the initial data, the following is displayed:
	Ready to work
Template for outputting fuel dispenser status information:
	Petrol filling station status «dispenser number» «number of cars in the queue» «number of cars serviced»
Followed by line-by-line output:
	«license plate of a serviced car, according to the queue»
	. . . .
System status output template:
	Petrol station «dispenser number» «unsold fuel volume» «queue length»
	. . . .
	Operator «number of cars refueled» «cars in queue»
Service denial message:
	Denial of service «car's license plate»
System shutdown message:
	Turn off the system

Output example:
Ready to work
Petrol filling station status PS_1 0 1
rus77-001
Petrol station PS_1 70 0
Petrol station PS_2 1000 0
Petrol station PS_3 1000 0
Petrol station PS_4 850 1
Petrol station PS_5 1000 0
Operator 3 1
Petrol filling station status PS_4 0 2
rus77-002
rus77-003
Petrol filling station status PS_4 0 3
rus77-002
rus77-003
rus77-004
Petrol station PS_1 70 0
Petrol station PS_2 1000 0
Petrol station PS_3 1000 0
Petrol station PS_4 850 0
Petrol station PS_5 1000 0
Operator 4 0
Turn off the system
