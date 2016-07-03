

 
#include <Stdlib.h>
#include <String.h>
#include <math.h>
//#include <Psim.h>
#include <stdio.h>
 
// PLACE GLOBAL VARIABLES OR USER FUNCTIONS HERE...

struct MyData
{
	FILE *out, *fp2, *node1fp;
	FILE *flag,*other_node_flag;
	int read_true = 0;
	//Add your variables here .....

};


 
/////////////////////////////////////////////////////////////////////
// FUNCTION: SimulationStep
//   This function runs at every time step.
//double t: (read only) time
//double delt: (read only) time step as in Simulation control
//double *in: (read only) zero based array of input values. in[0] is the first node, in[1] second input...
//double *out: (write only) zero based array of output values. out[0] is the first node, out[1] second output...
//int *pnError: (write only)  assign  *pnError = 1;  if there is an error and set the error message in szErrorMsg
//    strcpy(szErrorMsg, "Error message here..."); 
void SimulationStep(
		double t, double delt, double *in, double *out,
		 int *pnError, char * szErrorMsg,
		 void ** ptrUserData, int nThreadIndex, void * pAppPtr)
{
// ENTER YOUR CODE HERE...
	MyData * data = (MyData *)(*ptrUserData);
	float buf,node1time=-1,node1buf;
	int time_fixer=-1;
	
	//data->flag = fopen("c:\\temp\\node2flag.dat", "w");  //set the read others flag to -1
	//fprintf(data->flag, "0");
	//fclose(data->flag); //close the file
	data->out = fopen("z:\\NODE2_out.dat", "w");  //open the output file and write the time data to it
	if (data->out == NULL)
	{
		*pnError = 1;
		strcpy(szErrorMsg, "Could not open file.");
	}
	fscanf(data->fp2, " %f", &buf);  //read from the sample data file for output
    fprintf(data->out,"%f %f 0",t,buf);
	fclose(data->out);  //close the output file
	out[0] = buf;  //put the sample data written on the output 1 pin
	while (time_fixer != int((t+.000005)*100000))  //check for the right time on the other node's file
	{
		look:
		data->node1fp = fopen("z:\\NODE1_out.dat", "r");
		if (data->node1fp == NULL)
			goto look;
		fscanf(data->node1fp, " %f %f %d", &node1time, &node1buf);
		fclose(data->node1fp);
		time_fixer = (int)((node1time+.000005) * 100000);
	}
	out[1] = node1buf;  //when you get synchronized read the file data from the other node and write it to a pin
	data->flag = fopen("z:\\NODE2flag.dat", "w");  //open the read others flag file and set the flag to t
	if (data->flag == NULL)
	{
		*pnError = 1;
		strcpy(szErrorMsg, "Could not open file.");
	}
	fprintf(data->flag, "%d",time_fixer);
	fclose(data->flag);  //close the read others flag file

	while (data->read_true !=time_fixer)
	{
		data->other_node_flag = fopen("z:\\NODE1flag.dat", "r");
		fscanf(data->other_node_flag, " %d", &data->read_true);
		fclose(data->other_node_flag);
	}



	
	*pnError = 0; //Success
 
}
 
////////////////////////////////////////////////////////////////////////////////////////
/////////////////            Simulation Functions            ///////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION: SimulationBegin
//   Initialization function. This function runs once at the beginning of simulation
//   For parameter sweep or AC sweep simulation, this function runs at the beginning of each simulation cycle.
//   Use this function to initialize user data  structure and record the parameters And input/output nodes.
//const char *szId: (read only) Name of the DLL-block 
//int nInputCount: (read only) Number of input nodes
//int nOutputCount: (read only) Number of output nodes
//int nParameterCount: (read only) Number of parameters 
//int *pnError: (write only)  assign  *pnError = 1;  if there is an error and set the error message in szErrorMsg
//    strcpy(szErrorMsg, "Error message here..."); 
void SimulationBegin(
		const char *szId, int nInputCount, int nOutputCount,
		 int nParameterCount, const char ** pszParameters,
		 int *pnError, char * szErrorMsg,
		 void ** ptrUserData, int nThreadIndex, void * AppPtr)
{

	// Allocate	memory and initialize all variables here.
	MyData * data = new MyData;
	// ptrUserData will carry the data pointer to the right function and allows multiple instances of the same DLL to have their own data->
	*ptrUserData = data;																							   
    
	

	data->fp2 = fopen("c:\\temp\\square.dat", "r");
	if (data->fp2 == NULL)
	{
		*pnError = 1;
		strcpy(szErrorMsg, "Could not open file.");
	}



	*pnError = 0; //Success
}





/////////////////////////////////////////////////////////////////////
// FUNCTION: SimulationEnd
//   Termination function. This function runs once at the end of simulation
//   For parameter sweep or AC sweep simulation, this function runs at the end of each simulation cycle.
//   Use this function to de-allocate any allocated memory or to save the result of simulation in an alternate file.
void SimulationEnd(const char *szId, void ** ptrUserData, int nThreadIndex, void * pAppPtr)
{
	// data allocated in OPENSIMUSER is provided.
	MyData * data = (MyData *)(*ptrUserData);
	fclose(data->fp2);
    //fclose(data->out);
	// Free all allocated memory here.
	if( data != NULL )
	{
		delete data;
	}


	*ptrUserData = NULL;

}
