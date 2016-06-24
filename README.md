# PSIM_NetworkDLL
PSIM multi-node network simulation block DLL basic template

This code is designed to work with Microsoft Visual Studio and PSIM power simulation software.

If you are familiar with PSIM, this code is designed for a PSIM general dll block. The purpose of the block is to enable a PSIM simulation on one computer to communicate to PSIM modules simulating simultaneously on other computers. The idea is that the computers will communicate over a shared file space. Each PSIM simulation has two files associated with it, a flag and a data file. The flag files are for synchronization between machines, they wait for all machines to catch up just in case other simulations are relying on data from other machines for the calculation of the next time step. The data files hold the relavent data points. These can be any inputs from the simulation, they are represented as input pins to the dll block. The output pins are any outputs that you want from other simulations.
