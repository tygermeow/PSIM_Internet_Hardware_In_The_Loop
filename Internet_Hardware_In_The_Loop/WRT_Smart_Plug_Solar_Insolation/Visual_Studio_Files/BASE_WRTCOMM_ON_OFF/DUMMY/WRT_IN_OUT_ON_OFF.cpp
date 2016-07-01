

 
#include <Stdlib.h>
#include <String.h>
#include <math.h>
//#include <Psim.h>
#include <stdio.h>
#define TIMELAG
 
// PLACE GLOBAL VARIABLES OR USER FUNCTIONS HERE...

struct MyData
{
    FILE *fp,*fp2;
	float data_to_wrt, data_to_wrt2, data_from_wrt;
	int data_from_wrt_ON_OFF;
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

	MyData * data = (MyData *)(*ptrUserData);
#ifdef TIMELAG
	if ((int)(t / delt) % 100 == 0)
	{
#endif
		data->data_to_wrt = in[0];
		data->data_to_wrt2 = in[1];
		data->fp = fopen("z:\\PSIM_out.dat", "w");
		if (data->fp != NULL)
		{
			fprintf(data->fp, "%f\n%f", data->data_to_wrt, data->data_to_wrt2);
		}

		fclose(data->fp);

		data->fp2 = fopen("z:\\WRT_out.dat", "r");
		if (data->fp2 != NULL)
		{
			fscanf(data->fp2, " %f %d", &data->data_from_wrt,&data->data_from_wrt_ON_OFF);
		}

		fclose(data->fp2);
		out[0] = data->data_from_wrt;
		out[1] = data->data_from_wrt_ON_OFF;
		*pnError = 0; //Success
#ifdef TIMELAG
	}
#endif
 
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

 
	// Free all allocated memory here.
	if( data != NULL )
	{
		delete data;
	}

	*ptrUserData = NULL;
}
