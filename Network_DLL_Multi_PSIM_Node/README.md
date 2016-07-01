# PSIM_NetworkDLL
PSIM multi-node network simulation block DLL basic template

This code is designed to work with Microsoft Visual Studio and PSIM power simulation software.

If you are familiar with PSIM, this code is designed for a PSIM general dll block. The purpose of the block is to enable a PSIM simulation on one computer to communicate to PSIM modules simulating simultaneously on other computers. The idea is that the computers will communicate over a shared file space. Each PSIM simulation has two files associated with it, a flag and a data file. The flag files are for synchronization between machines, they wait for all machines to catch up just in case other simulations are relying on data from other machines for the calculation of the next time step. The data files hold the relavent data points. These can be any inputs from the simulation, they are represented as input pins to the dll block. The output pins are any outputs that you want from other simulations.

Branches from this base are variations of this simulation platform for PSIM. Some include external devices.

PSIM_NET_FILE_SYNC:  Protocol description

Each occurrence of PSIM is a defined node.  Each occurrence of PSIM writes one file to a network location with the filename defining its network node name.

The file structure will be:

Time	Data1	Data2	Data3
.1	3423423	134214	23434

Where the first elements are the time cycle indicator and the next array elements will be the corresponding data points.

The node will write to the file at each time cycle erasing the file and restarting each time.

A second flag file will be created to tell the other nodes that it has successfully read all of their data at the given time step.

Other nodes of PSIM will access data asynchronously by opening and reading the file looking for their corresponding time period.  Necessarily, each node will loop until it gets to the correct time period and all nodes will be synchronized.

For this program you need to manually identify what you want to do with the data.  In the last section, you will specify what file you want to read from if any at each time step.  You can comment out these lines if you just want to get data from an input pin in PSIM.
For reading from other nodes we need to know what data is being written and in what order.  The first data point in the file will necessarily be the time step information.  The next data points will correspond to any output we want.
The next step is to program a multi-input, multi-output block. There should be one for each node relationship within PSIM. If there are multiple nodes each will have their own block operating in PSIM. I need to test if this will even work or not or if I have to program all the nodes into one block.

Potential problems:
1)	Depending on the file handling methods, will the network allow concurrent read and write to a file from multiple nodes. Only one node is writing while multiple may be reading.
a.	Possible fix give delay period
b.	Give error handling capacity when file is in use.
2)	If a node fails, the entire system will hang.
a.	`Need to add error handling capacity to drop nodes
b.	Need to add error handling capacity to restart the entire time cycle.
3)	The simulation settings need to be the same with the same time steps for each cycle

