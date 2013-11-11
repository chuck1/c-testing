#include <PW/PW.h>

int 	PW::PW::s_PW = 0;
int 	PW::PW::s_mode = 0;
double 	PW::PW::s_space = -1.0; // negative so that it always gets reset on the first Connector creation
int 	PW::PW::s_CN = 0;
int 	PW::PW::s_DM = 0;
int 	PW::PW::s_BL = 0;
int		PW::PW::s_BC = 0;
int		PW::PW::s_VC = 0;
int		PW::PW::s_nb_connector[3];
int		PW::PW::s_nb_domain[3];
int		PW::PW::s_nb_block = 0;

void PW::PW::PrintConditions(ofstream& ofs) {
	for ( int a = 0; a < m_boundaryConditions.size(); a++ )
	{
		BoundaryCondition* bc = m_boundaryConditions.at(a);
		if (bc)
		{
			bc->Print(ofs);
		}
	}
	
	for ( int a = 0; a < m_volumeConditions.size(); a++ )
	{
		VolumeCondition* bc = m_volumeConditions.at(a);
		if (bc)
		{
			bc->Print(ofs);
		}
	}
}
void PW::PW::Export(ofstream& ofs,vector<shared_ptr<block> >* blocks,string path) {
	int mode = NextMode();
	
	fprintf(ofs,"puts \"exporting: %i.cas\"\n",path);
	fprintf(ofs,endl;
	fprintf(ofs,"set _TMP(mode_%i) [PW::Application begin CaeExport [PW::Entity sort [list",mode);
	for ( int a = 0; a < blocks->size(); a++ )
	{
		fprintf(ofs," $_BL(%i)",blocks->at(a)->GetBL());
	}
	fprintf(ofs,"]]]\n");
	fprintf(ofs,"  $_TMP(mode_%i) initialize -type CAE {%i.cas}\n",mode,path);
	fprintf(ofs,"  if {![$_TMP(mode_%i) verify]} {\n",mode);
	fprintf(ofs,"    error \"Data verification failed\"\n");
	fprintf(ofs,"  }\n");
	fprintf(ofs,"  $_TMP(mode_%i) write\n",mode);
	fprintf(ofs,"$_TMP(mode_%i) end\n",mode);
	fprintf(ofs,"unset _TMP(mode_%i)\n",mode);
	fprintf(ofs,endl;
}



void PW::PW::PrintHeader(ofstream& ofs) {
	fprintf(ofs,"package require PWI_Glyph 2.17.0\n\n");
	
	fprintf(ofs,"PW::Application setUndoMaximumLevels 5\n");
	fprintf(ofs,"PW::Application reset\n");
	fprintf(ofs,"PW::Application markUndoLevel {Journal Reset}\n\n");
	
	fprintf(ofs,"PW::Application clearModified\n\n");
	
	fprintf(ofs,"PW::Application setCAESolver {ANSYS FLUENT} 3\n");
	fprintf(ofs,"PW::Application markUndoLevel {Select Solver}\n\n");
	
}
void PW::PW::Save(ofstream& ofs,string path) {
	fprintf(ofs,"puts \"saving: %i.PW\"\n",path);
	fprintf(ofs,endl;
	fprintf(ofs,"PW::Application save {%i.PW}\n",path);
}
int PW::PW::NextPW() {
	return ++s_PW;

}
int PW::PW::NextMode() {
	return ++s_mode;

}
int PW::PW::NextCN() {
	return ++s_CN;
}
int PW::PW::NextDM() {
	return ++s_DM;
}
int PW::PW::NextBL() {
	return ++s_BL;
}
int PW::PW::NextBC() {
	return ++s_BC;
}
int PW::PW::NextVC() {
	return ++s_VC;
}

