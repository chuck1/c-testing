#ifndef _CART_SET_H
#define _CART_SET_H

#include <MyLib/array/array.h>

//#include <PW/Point/Point.h>

template <class T> class array;

namespace PW {
	class Pattern;
	class Point;
	class CartSet {
	public:
		friend class Model;
	
		CartSet();
		void Init();
		void ResetSpace( int a, int b, int n, ... );
		void ResetSpace( int a, int b, vector<double> v );
		void ResetCoor( int a, int n, ... );
		void ResetCoor( int a, vector<double> v );
		
		void CreatePoints();
		void CreateConnectors();
		void CreateDomains();
		void CreateBlocks();
		
		void PrintConnectors(ofstream& ofs);
		void PrintDomains(ofstream& ofs);
		void PrintBlocks(ofstream& ofs);
		
		void DumpInfo();
		
		
		void DefaultProcess();
		
		void SetCoorFromPattern(shared_ptr<Pattern> p);
		void PushSpacing(vector<double>& v,vector<double>& v0,vector<double>& v1,vector<double>& v2,shared_ptr<Spacing> s);
		
		
		
		
		void DefaultPrint(ofstream& ofs);
		int  GetN(int a) { return m_n[a]; }
		array<Connector>* 	GetConArray(int a);
		array<domain>* 		GetDomArray(int a);
		array<Block>*		GetBlkArray();
		
		
		array<Block>*			m_b;
		array<domain>**			m_d;
		array<Connector>**		m_c;
		array<Point>			m_points;
		
		vector<double>			m_space[3][3];
		vector<double>			m_coor[3];
		int						m_n[3];
		
		// patterns
		map<int,shared_ptr<Pattern> >	m_mapPatterns;
		
		
	};
};


#endif



