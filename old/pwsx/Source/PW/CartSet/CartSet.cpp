#include <PW/.h>

		PW::CartSet::CartSet(){
}
void 	PW::CartSet::ResetSpace( int a, int b, int n, ... ){
	assert( n == m_n[a] );
	
	m_space[a][b].clear();
	
	va_list args;
	
	va_start( args, n );
	for ( int c = 0; c < n; c++ )
	{
		m_space[a][b].push_back(va_arg( args, double ));
	}
	
	va_end( args );
}
void 	PW::CartSet::ResetCoor( int a, int n, ... ){
	assert( ( a >= 0 ) && ( a < 3 ) );
	
	m_coor[a].clear();
	
	m_n[a] = n-1;
	cout << "m_n[" << a << "] = " << n-1 << endl;
	
	// cout << "m_n[" << a << "] = " << n-1 << endl;
	
	va_list args;
	
	va_start( args, n );
	for ( int b = 0; b < n; b++ )
	{
		m_coor[a].push_back(va_arg( args, double ));
	}
	
	va_end( args );
}
void 	PW::CartSet::ResetCoor( int a, vector<double> v ){
	assert( ( a >= 0 ) && ( a < 3 ) );
	assert( !v.empty() );
	
	m_coor[a] = v;
	
	m_n[a] = v.size()-1;
	cout << "m_n[" << a << "] = " << ( v.size() - 1 ) << endl;
}
void 	PW::CartSet::ResetSpace( int a, int b, vector<double> v ){
	assert( ( a >= 0 ) && ( a < 3 ) );
	assert( ( b >= 0 ) && ( b < 3 ) );
	assert( v.size() == m_n[a] );
	
	m_space[a][b] = v;
}
void 	PW::CartSet::CreatePoints(){
	cout << "creating points" << endl;
	m_points.Init( 3, m_n[0]+1, m_n[1]+1, m_n[2]+1 );
	
	for ( int i = 0; i < m_n[0]+1; i++ )
	{
		for ( int j = 0; j < m_n[1]+1; j++ )
		{
			for ( int k = 0; k < m_n[2]+1; k++ )
			{
				// cout << k << " " << m_coor[2].size() << endl;
				
				assert( i < m_coor[0].size() );
				assert( j < m_coor[1].size() );
				assert( k < m_coor[2].size() );
				
				//cout << m_coor[0].at(i) << " " << m_coor[1].at(j) << " " << m_coor[2].at(k) << endl;
				
				m_points.Get(3,i,j,k)->Set(0,m_coor[0].at(i));
				m_points.Get(3,i,j,k)->Set(1,m_coor[1].at(j));
				m_points.Get(3,i,j,k)->Set(2,m_coor[2].at(k));
			}
		}
	}
}
void 	PW::CartSet::CreateConnectors(){
	cout << "creating connectors" << endl;
	for ( int a = 0; a < 3; a++ )
	{
		assert(m_c[a]);
		
		int n0 = m_n[0] + ((a==0)?0:1);
		int n1 = m_n[1] + ((a==1)?0:1);
		int n2 = m_n[2] + ((a==2)?0:1);
		
		for ( int i = 0; i < n0; i++ )
		{
			for ( int j = 0; j < n1; j++ )
			{
				for ( int k = 0; k < n2; k++ )
				{
					shared_ptr<connector> c = m_c[a]->Get(3,i,j,k);
					assert(c);
					
					int ind[] = {i,j,k};
					
					int i0 = i + ((a==0)?1:0);
					int i1 = j + ((a==1)?1:0);
					int i2 = k + ((a==2)?1:0);
					
					c->m_begin = m_points.Get(3,i,j,k);
					c->m_end = m_points.Get(3,i0,i1,i2);
					
					c->m_space[0] = m_space[a][0].at(ind[a]);
					c->m_space[1] = m_space[a][1].at(ind[a]);
					c->m_space[2] = m_space[a][2].at(ind[a]);
				}
			}
		}
	}
}
void 	PW::CartSet::CreateDomains(){
	cout << "creating domains" << endl;
	for ( int a = 0; a < 3; a++ )
	{
		int n0 = m_n[0] + ((a==0)?1:0);
		int n1 = m_n[1] + ((a==1)?1:0);
		int n2 = m_n[2] + ((a==2)?1:0);
		
		for ( int i = 0; i < n0; i++ )
		{
			for ( int j = 0; j < n1; j++ )
			{
				for ( int k = 0; k < n2; k++ )
				{
					shared_ptr<domain> dom = m_d[a]->Get(3,i,j,k);
					assert(dom);
					
					int b = (((a+1)<3)?(a+1):(a-2));
					int c = (((a+2)<3)?(a+2):(a-1));
					
					int b0 = i + ((c==0)?1:0);
					int b1 = j + ((c==1)?1:0);
					int b2 = k + ((c==2)?1:0);
					
					int c0 = i + ((b==0)?1:0);
					int c1 = j + ((b==1)?1:0);
					int c2 = k + ((b==2)?1:0);
					
					// order of c1-c4 is important here
					dom->m_c1 = m_c[b]->Get(3,	i,	j,	k);
					
					dom->m_c2 = m_c[c]->Get(3,	i,	j,	k);
					
					dom->m_c3 = m_c[b]->Get(3,	b0,	b1,	b2);
					
					dom->m_c4 = m_c[c]->Get(3,	c0,	c1,	c2);
				}
			}
		}
	}
}
void 	PW::CartSet::CreateBlocks(){
	cout << "creating blocks" << endl;
	int n0 = m_n[0];
	int n1 = m_n[1];
	int n2 = m_n[2];
	
	for ( int i = 0; i < n0; i++ )
	{
		for ( int j = 0; j < n1; j++ )
		{
			for ( int k = 0; k < n2; k++ )
			{
				shared_ptr<block> blk = m_b->Get(3,i,j,k);
				assert(blk);
				
				int ind[] = {i,j,k};
				
				blk->m_d1 = m_d[0]->Get(3,	i,	j,	k);
				blk->m_d2 = m_d[0]->Get(3,	i+1,j,	k);
				
				blk->m_d3 = m_d[1]->Get(3,	i,	j,	k);
				blk->m_d4 = m_d[1]->Get(3,	i,	j+1,k);
				
				blk->m_d5 = m_d[2]->Get(3,	i,	j,	k);
				blk->m_d6 = m_d[2]->Get(3,	i,	j,	k+1);
			}
		}
	}
}
void 	PW::CartSet::PrintConnectors(ofstream& ofs{
	cout << "print connectors" << endl;
	
	for ( int a = 0; a < 3; a++ )
	{
		array<connector>* ca = m_c[a];
		assert(ca);
		assert(!ca->isEmpty());
		
		int n0 = m_n[0] + ((a==0)?0:1);
		int n1 = m_n[1] + ((a==1)?0:1);
		int n2 = m_n[2] + ((a==2)?0:1);
		//cout << "m_n " << m_n[0] << " " << m_n[1] << " " << m_n[2] << endl;
		//cout << "n " << n0 << " " << n1 << " " << n2 << endl;
		
		for ( int i = 0; i < n0; i++ )
		{
			for ( int j = 0; j < n1; j++ )
			{
				for ( int k = 0; k < n2; k++ )
				{
					shared_ptr<connector> c = ca->Get(3,i,j,k);
					
					//cout << "3" << endl;
					
					assert(c);
					
					c->Print(ofs);
				}
			}
		}
	}
}
void 	PW::CartSet::PrintDomains(ofstream& ofs){
	cout << "print domains" << endl;
	for ( int a = 0; a < 3; a++ )
	{
		int n0 = m_n[0] + ((a==0)?1:0);
		int n1 = m_n[1] + ((a==1)?1:0);
		int n2 = m_n[2] + ((a==2)?1:0);
		
		for ( int i = 0; i < n0; i++ )
		{
			for ( int j = 0; j < n1; j++ )
			{
				for ( int k = 0; k < n2; k++ )
				{
					shared_ptr<domain> dom = m_d[a]->Get(3,i,j,k);
					assert(dom);
					
					dom->Print(ofs);
				}
			}
		}
	}
}
void 	PW::CartSet::PrintBlocks(ofstream& ofs){
	cout << "print blocks" << endl;
	for ( int i = 0; i < m_n[0]; i++ )
	{
		for ( int j = 0; j < m_n[1]; j++ )
		{
			for ( int k = 0; k < m_n[2]; k++ )
			{
				m_b->Get(3,i,j,k)->Print(ofs);
			}
		}
	}
}
void 	PW::CartSet::DumpInfo(){
	cout << endl;
	cout << "connector array dims" << endl;
	cout << "    " << m_c[0]->GetDim(0) << " " << m_c[0]->GetDim(1) << " " << m_c[0]->GetDim(2) << endl;
	cout << "    " << m_c[1]->GetDim(0) << " " << m_c[1]->GetDim(1) << " " << m_c[1]->GetDim(2) << endl;
	cout << "    " << m_c[2]->GetDim(0) << " " << m_c[2]->GetDim(1) << " " << m_c[2]->GetDim(2) << endl;
	cout << endl;
	cout << "domain array dims" << endl;
	cout << "    " << m_d[0]->GetDim(0) << " " << m_d[0]->GetDim(1) << " " << m_d[0]->GetDim(2) << endl;
	cout << "    " << m_d[1]->GetDim(0) << " " << m_d[1]->GetDim(1) << " " << m_d[1]->GetDim(2) << endl;
	cout << "    " << m_d[2]->GetDim(0) << " " << m_d[2]->GetDim(1) << " " << m_d[2]->GetDim(2) << endl;
	cout << endl;
	cout << "block array dims" << endl;
	cout << "    " << m_b->GetDim(0) << " " << m_b->GetDim(1) << " " << m_b->GetDim(2) << endl;
	cout << endl;
}
void 	PW::CartSet::Init(){
	m_c = new array<connector>*[3];
	for ( int a = 0; a < 3; a++ )
	{
		m_c[a] = new array<connector>;
		
		int n0 = m_n[0] + ((a==0)?0:1);
		int n1 = m_n[1] + ((a==1)?0:1);
		int n2 = m_n[2] + ((a==2)?0:1);
		
		m_c[a]->Init( 3, n0, n1, n2 );
		
		PW::s_nb_connector[a] = n0*n1*n2;
	}
	
	// domain array
	m_d = new array<domain>*[3];
	for ( int a = 0; a < 3; a++ )
	{
		m_d[a] = new array<domain>;
		
		int n0 = m_n[0] + ((a==0)?1:0);
		int n1 = m_n[1] + ((a==1)?1:0);
		int n2 = m_n[2] + ((a==2)?1:0);
		
		m_d[a]->Init( 3, n0, n1, n2 );
		
		PW::s_nb_domain[a] = n0*n1*n2;
	}
	
	// block array
	m_b = new array<block>;
	
	int n0 = m_n[0];
	int n1 = m_n[1];
	int n2 = m_n[2];
	
	m_b->Init( 3, n0, n1, n2 );
	
	PW::s_nb_block = n0*n1*n2;
}
void 	PW::CartSet::DefaultProcess(){
	// set coor and space
	for ( int a = 0; a < 3; a++ )
	{
		shared_ptr<Pattern> p;
		if ( p = m_mapPatterns[a] )
		{
			cout << "setting dimension " << a << " from pattern" << endl;
			SetCoorFromPattern(p);
		}
		else
		{
			assert(0);
		}
	}
	
	cout << "initialize arrays" << endl;
	Init();
	CreatePoints();
	CreateConnectors();
	CreateDomains();
	CreateBlocks();
	
	DumpInfo();
}
void 	PW::CartSet::DefaultPrint(ofstream& ofs){
	PW::PrintHeader(ofs);
	PrintConnectors(ofs);
	PrintDomains(ofs);
	PrintBlocks(ofs);
}
void 	PW::CartSet::SetCoorFromPattern(shared_ptr<Pattern> p){
	int dim = p->m_dimension;
	assert( ( dim >= 0 ) && ( dim < 3 ) );
	
	vector<double> v,v0,v1,v2;
	
	v.push_back(0.0);
	
	
	
	
	
	
	
	switch ( p->m_type )
	{
	case Pattern::e_EXPLICIT:
	
		for ( int a = 0; a < p->m_vecSpacings.size(); a++ )
		{
			shared_ptr<Spacing> s = p->m_vecSpacings.at(a);
			
			PushSpacing(v,v0,v1,v2,s);
			
		}
		
		break;
	
	case Pattern::e_MOD_ENDS:
		shared_ptr<Spacing> s;
		shared_ptr<Spacing> se;
		shared_ptr<Spacing> so;
		
		assert( s = p->m_mapSpacings["begin"] );
		PushSpacing(v,v0,v1,v2,s);
		
		assert( se = p->m_mapSpacings["even"] );
		assert( so = p->m_mapSpacings["odd"] );
		
		for ( int a = 0; a < p->m_n; a++ )
		{
			if ( ( a % 2 ) == 0 )
			{
				PushSpacing(v,v0,v1,v2,se);
			}
			else
			{
				PushSpacing(v,v0,v1,v2,so);
			}
		}
		
		assert( s = p->m_mapSpacings["end"] );
		PushSpacing(v,v0,v1,v2,s);
		
		break;
	}
	
	
	
	
	
	ResetCoor(dim,v);
	
	ResetSpace(dim,0,v0); // begin
	ResetSpace(dim,1,v1); // mid
	ResetSpace(dim,2,v2); // end
}
void 	PW::CartSet::PushSpacing(vector<double>& v,vector<double>& v0,vector<double>& v1,vector<double>& v2,shared_ptr<Spacing> s){
	v.push_back( v.back() + *s->m_length );
	v0.push_back( *s->m_length/(*s->m_dimension[0]) );
	v1.push_back( *s->m_length/(*s->m_dimension[1]) );
	v2.push_back( *s->m_length/(*s->m_dimension[2]) );
}	

array<Connector>* 	PW::CartSet::GetConArray(int a)
{
	assert(a<3);
	assert(a>=0);
	assert(m_c);
	
	return m_c[a];
}
array<domain>* 		PW::CartSet::GetDomArray(int a)
{
	assert(a<3);
	assert(a>=0);
	assert(m_d);
	
	return m_d[a];
}
array<Block>*		PW::CartSet::GetBlkArray()
{
	assert(m_b);
	
	return m_b;
}










