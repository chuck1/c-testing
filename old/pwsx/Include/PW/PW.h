#ifndef _PW_H
#define _PW_H

#include <stdio.h>
#include <fstream>
#include <vector>
#include <memory>


#ifdef _MY_DEBUG
#define PRNTLOC printf("%s\n",__PRETTY_FUNCTION__);
#else
#define PRNTLOC
#endif


using namespace std;


namespace PW
{
	
	class Connector;
	class domain;
	class Block;
	class CartSet;
	class RectangularExtrusion;
	class BoundaryCondition;
	class VolumeCondition;
	
	enum VCType {
		e_FLUID,
		e_SOLID,
		e_NB_VC_TYPES
	};
	
	enum BCType {
		/*
		e_INFLOW,
		e_OUTFLOW,
		e_SYMMETRY_PLANE,
		e_WALL,
		e_UNSPECIFIED,
		*/
		e_MASS_FLOW_INLET,
		e_PRESSURE_OUTLET,
		e_SYMMETRY,
		e_WALL,
		e_INTERFACE,
		e_NB_BC_TYPES
	};
	
	
	class PW {
	
	public:
		static void PrintHeader(ofstream& ofs);
		static void Save(ofstream& ofs,string path);
		static void Export(ofstream& ofs,vector<shared_ptr<Block>>* blocks,string path);
		static int NextPW();
		static int NextMode();
		static int NextCN();
		static int NextDM();
		static int NextBL();
		static int NextBC();
		static int NextVC();
		
		
		void PrintConditions(ofstream& ofs);
	private:
		vector<BoundaryCondition*>	m_boundaryConditions;
		vector<VolumeCondition*>	m_volumeConditions;
		
	public:
		static int s_PW;
		static int s_mode;
		static double s_space;
		
		static int s_CN;
		static int s_DM;
		static int s_BL;
		static int s_BC;
		static int s_VC;
		
		static int s_nb_connector[3];
		static int s_nb_domain[3];
		static int s_nb_block;
	
	};
	
	
};

/*
#include "Spacing/Spacing.h"
#include "Pattern/Pattern.h"
#include "Connector/Connector.h"
#include "domain/domain.h"
#include "Block/Block.h"

#include "VolumeCondition/VolumeCondition.h"
#include "BoundaryCondition/BoundaryCondition.h"
#include "ConnectionBoundaryCondition/ConnectionBoundaryCondition.h"

#include "CartSet/CartSet.h"
*/



#endif

