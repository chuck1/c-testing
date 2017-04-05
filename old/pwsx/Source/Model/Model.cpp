#include <Model/Model.h>
#include <Model/ModelUtil.h>
#include <PW/PW.h>
#include <PW/CartSet/CartSet.h>
#include <PW/Block/Block.h>
#include <PW/BoundaryCondition/BoundaryCondition.h>
#include <PW/VolumeCondition/VolumeCondition.h>
#include <PW/ConnectionBoundaryCondition/ConnectionBoundaryCondition.h>
#include <MyLib/external/tinyxml.h>

			Model::Model(): m_BC_sym(NULL) {

}
void 		Model::SetVolumeCondition(PW::VolumeCondition* vc,IS iSel,IS jSel,IS kSel) {
	int n0 = m_cs->GetN(0);
	int n1 = m_cs->GetN(1);
	int n2 = m_cs->GetN(2);	
	
	for ( int i = 0; i < n0; i++ )
	{
		for ( int j = 0; j < n1; j++ )
		{
			for ( int k = 0; k < n2; k++ )
			{
				if ( iSel.Test(i,n0) && jSel.Test(j,n1) && kSel.Test(k,n2) )
				{
					shared_ptr<PW::Block> blk = m_cs->GetBlkArray()->Get(3,i,j,k);
					assert(blk);
					
					PW::VolumeCondition* vc_old = NULL;
					if ( ( vc_old = blk->GetVC() ) )
					{
						vc_old->Remove(blk);
					}
					
					blk->SetVC(vc);
					vc->Add(blk);
				}
			}
		}
	}
}
void 		Model::RemoveVolumeCondition(PW::VolumeCondition* vc,IS iSel,IS jSel,IS kSel) {
	int n0 = m_cs->GetN(0);
	int n1 = m_cs->GetN(1);
	int n2 = m_cs->GetN(2);	
	
	for ( int i = 0; i < n0; i++ )
	{
		for ( int j = 0; j < n1; j++ )
		{
			for ( int k = 0; k < n2; k++ )
			{
				if ( iSel.Test(i,n0) && jSel.Test(j,n1) && kSel.Test(k,n2) )
				{
					shared_ptr<PW::Block> blk = m_cs->GetBlkArray()->Get(3,i,j,k);
					assert(blk);
					
					if ( blk->GetVC() == vc )
					{
						blk->SetVC(NULL);
					}
					
					vc->Remove(blk);
				}
			}
		}
	}
}
void 		Model::SetBoundaryCondition(PW::BoundaryCondition* bc,int dir,IS aSel,IS iSel,IS jSel,IS kSel) {
	for ( int a = 0; a < 3; a++ )
	{
		int n0 = m_cs->GetN(0) + ((a==0)?1:0);
		int n1 = m_cs->GetN(1) + ((a==1)?1:0);
		int n2 = m_cs->GetN(2) + ((a==2)?1:0);
		
		for ( int i = 0; i < n0; i++ )
		{
			for ( int j = 0; j < n1; j++ )
			{
				for ( int k = 0; k < n2; k++ )
				{
					if ( aSel.Test(a,3) && iSel.Test(i,n0) && jSel.Test(j,n1) && kSel.Test(k,n2) )
					{
						int ind[] = {i,j,k};
						
						if (dir < 0)
						{
							ind[a] -= 1;
						}
						
						shared_ptr<PW::Block> blk = m_cs->GetBlkArray()->Get(3,ind[0],ind[1],ind[2]);
						assert(blk);
						
						shared_ptr<PW::domain> dom = m_cs->GetDomArray(a)->Get(3,i,j,k);
						assert(dom);
						
						bc->AddPair(blk,dom);
					}
				}
			}
		}
	}
}
void 		Model::SetConnectionBoundaryConditionAuto(PW::ConnectionBoundaryCondition* cbc, PW::VolumeCondition* vc1, PW::VolumeCondition* vc2) {
	for ( int a = 0; a < 3; a++ )
	{
		int n0 = m_cs->GetN(0);
		int n1 = m_cs->GetN(1);
		int n2 = m_cs->GetN(2);
		
		int s0 = ((a==0)?1:0);
		int s1 = ((a==1)?1:0);
		int s2 = ((a==2)?1:0);
		
		for ( int i = s0; i < n0; i++ )
		{
			for ( int j = s1; j < n1; j++ )
			{
				for ( int k = s2; k < n2; k++ )
				{
					
					int ind[] = {i,j,k};
					
					shared_ptr<PW::Block> blk1 = m_cs->GetBlkArray()->Get(3,ind[0],ind[1],ind[2]);
					assert(blk1);
					
					ind[a] -= 1;
					
					shared_ptr<PW::Block> blk2 = m_cs->GetBlkArray()->Get(3,ind[0],ind[1],ind[2]);
					assert(blk2);
					
					shared_ptr<PW::domain> dom = m_cs->GetDomArray(a)->Get(3,i,j,k);
					assert(dom);
					
					if ( ( ( blk1->GetVC() == vc1 ) && ( blk2->GetVC() == vc2 ) ) || ( ( blk1->GetVC() == vc2 ) && ( blk2->GetVC() == vc1 ) ) )
					{
						AddTripleToConnection(cbc,a,i,j,k);
					}
				}
			}
		}
	}
}
void 		Model::SetConnectionBoundaryCondition( PW::ConnectionBoundaryCondition* cbc, IS aSel, IS iSel, IS jSel, IS kSel ) {
	for ( int a = 0; a < 3; a++ )
	{
		int n0 = m_cs->GetN(0) + ((a==0)?1:0);
		int n1 = m_cs->GetN(1) + ((a==1)?1:0);
		int n2 = m_cs->GetN(2) + ((a==2)?1:0);
		
		for ( int i = 0; i < n0; i++ )
		{
			for ( int j = 0; j < n1; j++ )
			{
				for ( int k = 0; k < n2; k++ )
				{
					if ( aSel.Test(a,3) && iSel.Test(i,n0) && jSel.Test(j,n1) && kSel.Test(k,n2) )
					{
						AddTripleToConnection(cbc,a,i,j,k);
					}
				}
			}
		}
	}
}
void 		Model::AddTripleToConnection(PW::ConnectionBoundaryCondition* cbc,int a,int i,int j,int k) {
	assert(a<3);
	assert(a>=0);
	
	shared_ptr<PW::domain> dom = m_cs->GetDomArray(a)->Get(3,i,j,k);
	assert(dom);
	
	int ind_opp[] = {i,j,k};
	
	ind_opp[a] -= 1;
	
	shared_ptr<PW::Block> same = m_cs->GetBlkArray()->Get(3,i,j,k);
	assert(same);
	
	shared_ptr<PW::Block> opposite = m_cs->GetBlkArray()->Get(3,ind_opp[0],ind_opp[1],ind_opp[2]);
	assert(opposite);
	   
	assert(same!=opposite);
	
	if (a==1)
	{
		cbc->AddTriple(opposite,same,dom);
	}
	else
	{
		cbc->AddTriple(same,opposite,dom);
	}
}
void 		Model::Print(ofstream& ofs) {
	m_cs->DefaultPrint(ofs);
	
	m_VC_solid->Print(ofs);
	m_VC_fluid->Print(ofs);
	
	m_BC_inlet->Print(ofs);
	m_BC_outlet->Print(ofs);
	
	PRNTLOC;
	cout << "m_BC_sym=" << m_BC_sym << endl;
	if ( m_BC_sym )
	{
		m_BC_sym->Print(ofs);
	}
	PRNTLOC;
	
	m_BC_heated->Print(ofs);
	
	m_BC_int_wall->Print(ofs);
	
	// save and export
	
	PW::PW::Save(ofs,m_root + m_title + "/pointwise_file_" + m_title );
	
	//ExportFluid(ofs);
	
	Export(ofs);
}
void 		Model::Export(ofstream& ofs) {
	vector<shared_ptr<PW::Block> >* blocks = new vector<shared_ptr<PW::Block> >();
	
	blocks->insert(blocks->end(),m_VC_fluid->GetBlockVector()->begin(),m_VC_fluid->GetBlockVector()->end());
	blocks->insert(blocks->end(),m_VC_solid->GetBlockVector()->begin(),m_VC_solid->GetBlockVector()->end());
	
	PW::PW::Export(ofs,blocks,m_root + m_title + "/casefile_conjugate_" + m_title );
}
void 		Model::ExportFluid(ofstream& ofs) {	
	PW::PW::Export(ofs,m_VC_fluid->GetBlockVector(),m_root + m_title + "/casefile_fluid_" + m_title );
}
bool 		Model::XMLParse(string XMLFile) {
	boost::regex e ("(.*)(/)(\\w+)(\\.xml)");
	boost::smatch sm;
	
	boost::regex_match (XMLFile,sm,e);
	//assert( sm.size() == 5 );
	/*
	cout << sm[0] << endl;
	cout << sm[1] << endl;
	cout << sm[2] << endl;
	cout << sm[3] << endl;
	cout << sm[4] << endl;
	*/
	m_title = sm[3];
	cout << "title=\"" << m_title << "\"" << endl;
	
	map<string,ftoid_parser*> mapParseFunc;
	
	mapParseFunc["Parameter"] = 	new ftoid_parser_parameter();
	mapParseFunc["Spacing"] = 		new ftoid_parser_spacing();
	mapParseFunc["IntVector"] = 	new ftoid_parser_intvector();
	mapParseFunc["Pattern"] = 		new ftoid_parser_pattern();
	
	PopulateVariableMap();
	
	PRNTLOC;
	
	int state = 0;
	
	TiXmlDocument document( XMLFile.c_str() );
	if ( !document.LoadFile() )
	{
		cout << "XML file not found" << endl;
		return false;
	}
	
	TiXmlElement* root = document.FirstChildElement( "Case" );
	TiXmlElement* element = NULL;
	
	const char* c = NULL;
	string value;
	if ( root )
	{
		element = root->FirstChildElement();
		
		while ( element )
		{
			c = element->Value();
			assert(c);
			if ( c )
			{
				value = c;
				ftoid_parser* f = NULL;
				if ( ( f = mapParseFunc[value] ) )
				{
					f->parse(this,element,state);
				}
				else
				{
					cout << "unable to parse \"" << value << "\" Element" << endl;
				}
			}
			
			element = element->NextSiblingElement();
		}
	}
	
	
	
	if ( ( state & m_condition ) != m_condition )
	{
		cout << "state = " << state << " does not equal condition = " << m_condition << endl;
		return false;
		
		
		
	}
	
	
	PRNTLOC;
	ProcessVariables();
	PRNTLOC;
	
	return true;
}
vector<int> Model::ConvertChannelCountToWallIndices(vector<int> v0,int first_channel_index) {
	vector<int> v1;
	
	assert( !v0.empty() );
	
	v1.push_back(v0.at(0));
	
	for ( unsigned int a = 1; a < (v0.size()-1); a++ )
	{
		v1.push_back(v1.back()+v0.at(a));
	}
	
	for ( unsigned int a = 0; a < v1.size(); a++ )
	{
		v1.at(a) *= 2;
		v1.at(a) -= 1;
		v1.at(a) += first_channel_index;
	}
	
	return v1;
}
int 		Model::S_GetModelID(string XMLFile) {
	TiXmlDocument document( XMLFile.c_str() );
	if ( !document.LoadFile() )
	{
		cout << "XML file not found" << endl;
		return false;
	}
	
	TiXmlElement* root = document.FirstChildElement( "Case" );
	
	const char* c = NULL;
	
	assert( c = root->Attribute("model") );
	
	map<string,int> m;
	
	m["1"] = 1;
	m["2"] = 2;
	m["3"] = 3;
	m["4"] = 4;
	m["5"] = 5;
	m["6"] = 6;
	
	int ret = m[c];
	
	assert( ret );
	
	return ret;
}







