#ifndef _MODEL_H
#define _MODEL_H

#include <map>
#include <string>
#include <boost/regex.hpp>

using namespace std;

class TiXmlElement;

class Model;
class IS;
class Variable;

namespace PW {
	class CartSet;
	class Connector;
	class VolumeCondition;
	class BoundaryCondition;
	class ConnectionBoundaryCondition;
	class Spacing;
}


class Model {
public:
	friend class ftoid_parser;
	friend class ftoid_parser_parameter;
	friend class ftoid_parser_spacing;
	friend class ftoid_parser_intvector;
	friend class ftoid_parser_pattern;
	
	Model();
	
	virtual void Process(){ assert(0); }
	virtual void Print(ofstream& ofs);
	
	virtual void SetVolumeConditions(){ assert(0); }
	virtual void SetBoundaryConditions(){ assert(0); }
	
			bool 		XMLParse(string XMLFile);
			void 		ParseParameter(TiXmlElement* element,int& state);
			void 		ParseSpacing(TiXmlElement* element,int& state);
			void 		ParseIntVetor(TiXmlElement* element,int& state);
	
	
	
			vector<int>	ConvertChannelCountToWallIndices(vector<int> a,int first_channel_index);
	
	
	virtual void 		PopulateVariableMap(){ assert(0); }
	virtual void 		ProcessVariables(){ assert(0); }
	
			string 		GetTitle() { return m_title; }
	
			void 		Export(ofstream& ofs);
			void 		ExportFluid(ofstream& ofs);
	
	
			void 		SetVolumeCondition(PW::VolumeCondition* vc,IS iSel,IS jSel,IS kSel);
			void 		RemoveVolumeCondition(PW::VolumeCondition* vc,IS iSel,IS jSel,IS kSel);
			void 		SetBoundaryCondition(PW::BoundaryCondition* bc,int dir,IS aSel,IS iSel,IS jSel,IS kSel);
			void 		SetConnectionBoundaryCondition(PW::ConnectionBoundaryCondition* cbc,IS aSel,IS iSel,IS jSel,IS kSel);
			void 		SetConnectionBoundaryConditionAuto(PW::ConnectionBoundaryCondition* cbc, PW::VolumeCondition* vc1, PW::VolumeCondition* vc2);
	
	void AddTripleToConnection( PW::ConnectionBoundaryCondition* cbc, int a, int i, int j, int k );
	
	static int S_GetModelID(string XMLFile);
	
protected:
	
	// geometric variables
	double m_x_wall;
	double m_x_channel;
	double m_x_heated;
	double m_x_header_inlet_ext;
	double m_x_header_outlet_ext;
	double m_y_heated;
	double m_y_header_inlet;
	double m_y_header_outlet;
	double m_y_header_inlet_2;
	double m_y_header_outlet_2;
	double m_z_flux_plate;
	double m_z_channel;
	double m_z_header;
	int m_n;
	int m_nb_header_plates;
	
	bool m_y_neg_sym;
	
	// variables
	map<string,Variable*> m_mapVariables;
	int m_condition;
	
	
	int m_x_channelMod;
	int m_x_wallMod;
	
	PW::CartSet*						m_cs;
	
	PW::BoundaryCondition*				m_BC_inlet;
	PW::BoundaryCondition*				m_BC_outlet;
	PW::BoundaryCondition*				m_BC_sym;
	PW::BoundaryCondition*				m_BC_heated;
	
	PW::ConnectionBoundaryCondition*	m_BC_int_wall;
	
	PW::VolumeCondition*				m_VC_solid;
	PW::VolumeCondition*				m_VC_fluid;
	
	string m_title;
	string m_root;
	
	vector<int>			m_channel_groups_outlet;
	vector<int>			m_channel_groups_inlet;
	
	// spacings
	map<string,PW::Spacing*>			m_spacings;
	
	
};

#endif











