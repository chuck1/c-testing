#ifndef _VOLUME_CONDITION_H
#define _VOLUME_CONDITION_H

namespace PW
{
	
	class VolumeCondition
	{
	public:
		friend class Block;
	public:
		VolumeCondition(string name, VCType type):
			m_name(name), m_type(type)
		{
		}
		void							Print(ofstream& ofs);
		string							GetVCTypeString(VCType type);
		void							Add(	shared_ptr<Block> blk);
		void							Remove(	shared_ptr<Block> blk);
		vector<shared_ptr<Block> >*		GetBlockVector()
		{
			return &m_blocks;
		}
	private:
		int								m_VC;
		string							m_name;
		VCType							m_type;
		
		vector<shared_ptr<Block> >		m_blocks;
	};
	
};


#endif

