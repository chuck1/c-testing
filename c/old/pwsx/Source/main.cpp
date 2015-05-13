#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <assert.h>
#include <tuple>

#define _MY_DEBUG



using namespace std;


/*
double MyDouble( void* p )
{
	double* d = (double*)p;
	
	if (d)
	{
		cout << "Double: " << *d << endl;
		return *d;
	}
	else
	{
		return 0;
	}
}
*/

/*
#include "/nfs/stak/students/r/rymalc/cfs/code/cpp/mylib/mylib.h"

#include "pw/pw.h"
#include "Model/Model.h"
*/

int main( int argc, char* argv[] )
{
	const char* usage_str = "Usage is -x [xml filename]";
	
	string XMLFile;
	
	
	for ( int i = 0; i < argc; i++ )
	{
		//cout << argv[i] << endl;
	}
	
	if ( argc < 3 )
	{
		cout << usage_str << endl;
		return 0;
	}
	else
	{
		if ( strcmp( argv[1], "-x" ) == 0 )
		{
			XMLFile = argv[2];
		}
		else
		{
			cout << usage_str << endl;
			return 0;
		}
	}
	
	unitmanager::Init();
	
	Model* model = NULL;
	
	// determine model
	int modelID = Model::S_GetModelID(XMLFile);
	switch ( modelID )
	{
	case 1:
		model = new Model_1;
		break;
	case 2:
		model = new Model_2;
		break;
	case 3:
		model = new Model_3;
		break;
	case 4:
		model = new Model_4;
		break;
	case 5:
		model = new Model_5;
		break;
	case 6:
		model = new Model_6;
		break;
	}
	
	
	
	
	
	
	if ( !model->XMLParse(XMLFile) )
	{
		return 0;
	}
	
	model->Process();
	PRNTLOC;
	
	cout << "opening file" << endl;
	ofstream ofs;
	ofs.open("../data/scripts/script_" + model->GetTitle() + ".glf",ofstream::out);
	
	model->Print(ofs);
	
	cout << "connectors: " << pw::pw::s_nb_connector[0] + pw::pw::s_nb_connector[1] + pw::pw::s_nb_connector[2] << endl;
	cout << "domains:    " << pw::pw::s_nb_domain[0] + pw::pw::s_nb_domain[1] + pw::pw::s_nb_domain[2] << endl;
	cout << "blocks:     " << pw::pw::s_nb_block << endl;
	
	ofs.close();
	
	return 0;
}

