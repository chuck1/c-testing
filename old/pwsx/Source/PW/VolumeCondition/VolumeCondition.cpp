#include <PW/VolumeCondition/VolumeCondition.h>

void PW::VolumeCondition::Print(ofstream& ofs)
{
	int PW = PW::NextPW();
	
	ofs << "set _TMP(PW_" << PW << ") [PW::VolumeCondition create]" << endl;
	ofs << "  PW::Application markUndoLevel {Create VC}" << endl;
	ofs << endl;
	ofs << "  $_TMP(PW_" << PW << ") setName \"" << m_name << "\"" << endl;
	ofs << "  PW::Application markUndoLevel {Name VC}" << endl;
	ofs << endl;
	ofs << "  $_TMP(PW_" << PW << ") setPhysicalType {" << GetVCTypeString(m_type) << "}" << endl;
	ofs << "  PW::Application markUndoLevel {Change VC Type}" << endl;
	ofs << endl;
	ofs << "  $_TMP(PW_" << PW << ") apply [list";
	for ( int a = 0; a < m_blocks.size(); a++ )
	{
		shared_ptr<block> blk = m_blocks.at(a);
		ofs << " $_BL(" << blk->GetBL() << ")";
	}
	ofs << "]" << endl;
	ofs << "  PW::Application markUndoLevel {Set VC}" << endl;
	ofs << endl;
	ofs << "unset _TMP(PW_" << PW << ")" << endl;
	ofs << endl;
	
	m_VC = PW::NextVC();
}

string PW::VolumeCondition::GetVCTypeString( VCType type )
{
	switch (type)
	{
	case e_FLUID:
		return "Fluid";
	case e_SOLID:
		return "Solid";
	default:
		assert(0);
		return "";
	}
}

void PW::VolumeCondition::Add(shared_ptr<block> blk)
{
	m_blocks.push_back(blk);
}

void PW::VolumeCondition::Remove(shared_ptr<block> blk)
{
	vector<shared_ptr<block> >::iterator it;
	
	for ( it = m_blocks.begin(); it != m_blocks.end(); ++it )
    {
		if ( (*it) == blk )
		{
			m_blocks.erase(it);
		}
	}
}
