
#include <iostream>

#include <python2.7/Python.h>

#include <string>

int main1(int argc, char** argv)
{
	std::string stdOutErr(
			"import sys\n"
			"class CatchOutErr:\n"
			"\tdef __init__(self):\n"
			"\t\tself.value = ''\n"
			"\tdef write(self, txt):\n"
			"\t\tself.value += txt\n"
			"catchOutErr = CatchOutErr()\n"
			"sys.stdout = catchOutErr\n"
			"sys.stderr = catchOutErr\n");
			//this is python code to redirect stdouts/stderr"

	//std::cout << stdOutErr << std::endl;

	Py_Initialize();
	PyObject *pModule = PyImport_AddModule("__main__"); //create main module
	PyRun_SimpleString(stdOutErr.c_str()); //invoke code to redirect
	PyRun_SimpleString("print(1+1)"); //this is ok stdout
	PyRun_SimpleString("1+a"); //this creates an error

	PyObject *catcher = PyObject_GetAttrString(pModule,"catchOutErr"); //get our catchOutErr created above

	PyErr_Print(); //make python print any errors

	PyObject *output = PyObject_GetAttrString(catcher,"value"); //get the stdout and stderr from our catchOutErr object

	printf("Here's the output:\n %s", PyString_AsString(output)); //it's not in our C++ portion

	Py_Finalize();


	return 0;

}

int main(int argc, char *argv[])
{

	return main1(argc,argv);

	PyObject *pValue;

	Py_SetProgramName(argv[0]);  /* optional but recommended */
	Py_Initialize();
	PyRun_SimpleString("from time import time,ctime\nprint('Today is', ctime(time()))\n");



	std::string istr;

	while(1) {
		std::cin >> istr;

		pValue = PyRun_String(istr.c_str(), Py_file_input, NULL, NULL);

		std::cout << "Result of call: " << PyLong_AsLong(pValue) << std::endl;
	}

	Py_Finalize();
	return 0;







}






