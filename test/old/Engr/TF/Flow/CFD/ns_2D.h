
namespace Engr {
	namespace TF {
		namespace Flow {
			class Cell;
			struct FaceType {
				enum Enum {
					eINTERIOR,
					eWALL,
					eVEL,
					ePRES
				};
			};
			class Face {
			public:
				Face();
				void 	Generate2D(double x,double y,double nx,double ny,double A);
				void 	RegisterNeighbors();
				double	VelGrad_Coeff(Cell* cell,int d,int f);
				double	VelGrad_Const(Cell* cell,int d,int f);
				double	VelGrad(Cell* cell,int d,int f);
				double	Vel_Coeff(Cell* cell,int d);
				double	Vel_Const(Cell* cell,int d);
				double	Vel(Cell* cell,int d);
				double	PGrad_Coeff( Cell* cell,int d);
				double	PGrad_Const( Cell* cell,int d);
				double	P( Cell* cell );
				double	X( int e ) { return m_x[e]; }
				double	N( int e ) { return m_n[e]; }
				void	Print();
				double 	Normal(Cell* cell,int e);
				
				FaceType::Enum		m_type;
				vector<Cell*> 		m_cell;
			private:
				vec		 			m_x;
				double* 			m_u;
				vec		 			m_n;
				double 				m_A;
				
				map<Cell*,Cell*> 	m_cellMap;
				map<Cell*,double>	m_mapA;
			};
			class Cell {
			public:
				Cell(){};
				~Cell(){};
				void 	GenerateSquare(Face* n,Face* s,Face* e,Face* w,double x,double y);
				double 	Advec_Coeff(int d);
				double 	Advec_Const(int d);
				double 	Diffu_Coeff(int d);
				double 	Diffu_Const(int d);
				double 	Pres(int d);
				double 	Momentum();
				double 	Poisson();
				void	PrintFaceType();
				void	Print();
				
				vec		m_x;
				double* m_u;
				double 	m_P;
				
				int m_nbFace;
				Face** m_face;
			};
			class Mesh {
			public:
				void GenerateSquare(int n,double dx);
				void Iter();
				void Write();
				void Print();
				
				matrix<Cell*> m_cell;
				int m_n;
				
				matrix<Face*> m_face;
				
				FaceType::Enum	m_typeN;
				FaceType::Enum	m_typeS;
				FaceType::Enum	m_typeE;
				FaceType::Enum	m_typeW;
				
			};
			class CFD {
			public:
				void GenerateSquare(int n,double dx);
				void Iter();
				void Write();
				
				int m_dim;
				
				Mesh* m_mesh;
				
			};
		};
	};
};



		Engr::TF::Flow::Face::Face() {
	//m_x = NULL;
	m_u = NULL;
	//m_n = NULL;
}
void	Engr::TF::Flow::Face::Generate2D(double x,double y,double nx,double ny,double A) {
	m_n.init(2);
	m_x.init(2);
	
	m_n[0] = nx;
	m_n[1] = ny;
	
	m_x[0] = x;
	m_x[1] = y;
	
	m_A = A;

}
void	Engr::TF::Flow::Face::RegisterNeighbors() {
	/*
	if (m_cell.size() != 2) {
		printf("number of cells %i\n",m_cell.size());
	}
	*/
	double c = 0;
	vec d;
	d.init(2);
	
	for ( int a = 0; a < m_cell.size(); a++ ) {
		Cell* cell = m_cell.at(a);
		
		d = ( m_x - cell->m_x );
		
		c = d.dot( m_n );
		
		if ( c==0 ) {
			printf("d   = {%f %f}\n",d.at(0),d.at(1));
			printf("m_n = {%f %f}\n",m_n.at(0),m_n.at(1));
		}
		
		if ( c > 0 ) {
			m_mapA[cell] = 1;
		}
		else if ( c < 0 ) {
			m_mapA[cell] = -1;
		}
		else {
			assert(0);
		}
	}
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		if ( m_cell.size() != 2 ) {
			printf("number of cells %i\n",m_cell.size());
		}
		else {
			m_cellMap[m_cell.at(0)] = m_cell.at(1);
			m_cellMap[m_cell.at(1)] = m_cell.at(0);
		}
		break;
	case FaceType::Enum::eWALL:
		
		break;
	case FaceType::Enum::eVEL:
		m_u = new double[2];
		
		m_u[0] = m_n[0];
		m_u[1] = m_n[1];
		break;
	case FaceType::Enum::ePRES:
		
		break;
	default:
		assert(0);
		break;
	}
}
double 	Engr::TF::Flow::Face::VelGrad_Coeff( Cell* cell,int d,int f) {
	double a = 0;
	double A4 = 0;
	Cell* nbr = NULL;
	
	if ( m_type == FaceType::Enum::eINTERIOR ) {
		nbr = m_cellMap[cell];
		assert(nbr);
	}
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		a = nbr->m_x[f] - cell->m_x[f];
		if ( a==0 ) {
			assert( m_n[f]==0 );
		}
		else {
			A4 = 1.0 / a;
		}
		break;
	case FaceType::Enum::eWALL:
		a = m_x[f] - cell->m_x[f];
		if ( a==0 ) {
			assert( m_n[f]==0 );
		}
		else {
			A4 = 1.0 / a;
		}
		break;
	case FaceType::Enum::eVEL:
		a = m_x[f] - cell->m_x[f];
		if ( a==0 ) {
			assert( m_n[f]==0 );
		}
		else {
			A4 = 1.0 / a;
		}
		break;
	case FaceType::Enum::ePRES:
		A4 = 0.0;
		break;
	default:
		assert(0);
		break;
	}
	//printf("A4 %f\n",A4);
	return A4;
}
double 	Engr::TF::Flow::Face::VelGrad_Const( Cell* cell,int e,int f) {
	double a = 0;
	double b = 0;
	Cell* nbr = NULL;
	
	if ( m_type == FaceType::Enum::eINTERIOR ) {
		nbr = m_cellMap[cell];
		assert(nbr);
	}
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		a = nbr->m_x[f] - cell->m_x[f];
		if ( a==0 ) {
			assert( m_n[f]==0 );
		}
		else {
			b = nbr->m_u[e] / a;
		}
		break;
	case FaceType::Enum::eWALL:
		b = 0;
		break;
	case FaceType::Enum::eVEL:
		a = m_x[f] - cell->m_x[f];
		if ( a==0 ) {
			assert( m_n[f]==0 );
		}
		else {
			b = m_u[e] / a;
		}
		break;
	case FaceType::Enum::ePRES:
		b = 0;
		break;
	default:
		assert(0);
	}
	
	return b;
}
double 	Engr::TF::Flow::Face::VelGrad( Cell* cell,int d,int f) {
	double a = 0;
	double b = 0;
	Cell* nbr = NULL;
	
	if ( m_type == FaceType::Enum::eINTERIOR ) {
		nbr = m_cellMap[cell];
		assert(nbr);
	}
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		a = nbr->m_x[f] - cell->m_x[f];
		if ( a==0 ) {
			assert( m_n[f]==0 );
		}
		else {
			b = ( nbr->m_u[d] - cell->m_u[d] ) / a;
		}
		break;
	case FaceType::Enum::eWALL:
		a = m_x[f] - cell->m_x[f];
		if ( a==0 ) {
			assert( m_n[f]==0 );
		}
		else {
			b = ( 0 - cell->m_u[d] ) / a;
		}
		break;
		break;
	case FaceType::Enum::eVEL:
		a = m_x[f] - cell->m_x[f];
		if ( a==0 ) {
			assert( m_n[f]==0 );
		}
		else {
			b = ( m_u[d] - cell->m_u[d] ) / a;
		}
		break;
	case FaceType::Enum::ePRES:
		b = 0;
		break;
	default:
		assert(0);
	}
	
	return b;
}
double 	Engr::TF::Flow::Face::Vel_Coeff( Cell* cell,int d) {
	double a = 0;
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		a = 0.5;
		break;
	case FaceType::Enum::eWALL:
		a = 0.0;
		break;
	case FaceType::Enum::eVEL:
		a = 0.0;
		break;
	case FaceType::Enum::ePRES:
		a = 1.0;
		break;
	default:
		assert(0);
		break;
	}
	
	return a;
}
double 	Engr::TF::Flow::Face::Vel_Const( Cell* cell,int d) {
	double a = 0;
	Cell* nbr = NULL;
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		nbr = m_cellMap[cell];
		
		a = 0.5 * nbr->m_u[d];
		break;
	case FaceType::Enum::eWALL:
		a = 0.0;
		break;
	case FaceType::Enum::eVEL:
		a = m_u[d];
		break;
	case FaceType::Enum::ePRES:
		a = 0.0;
		break;
	default:
		assert(0);
		break;
	}
	
	return a;
}
double 	Engr::TF::Flow::Face::Vel( Cell* cell,int d) {
	double a = 0;
	Cell* nbr = NULL;
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		nbr = m_cellMap[cell];
		
		a = 0.5 * nbr->m_u[d] + 0.5 * cell->m_u[d];
		break;
	case FaceType::Enum::eWALL:
		a = 0;
		break;
	case FaceType::Enum::eVEL:
		a = m_u[d];
		break;
	case FaceType::Enum::ePRES:
		a = cell->m_u[d];
		break;
	default:
		assert(0);
		break;
	}
}
double 	Engr::TF::Flow::Face::PGrad_Coeff( Cell* cell,int e) {
	double a = 0;
	double b = 0;
	Cell* nbr = NULL;
	
	if ( m_type == FaceType::Enum::eINTERIOR ) {
		nbr = m_cellMap[cell];
		assert(nbr);
	}
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		a = nbr->m_x[e] - cell->m_x[e];
		if ( a==0 ) {
			assert( m_n[e]==0 );
		}
		else {
			b = 1 / a;
		}
		break;
	case FaceType::Enum::eWALL:
		b = 0; // pressure gradient zero at wall. dont know if this is true!
		break;
	case FaceType::Enum::eVEL:
		b = 0; // pressure gradient zero at velocity inlet. dont know if this is true!
		break;
	case FaceType::Enum::ePRES:
		a = m_x[e] - cell->m_x[e];
		if ( a==0 ) {
			assert( m_n[e]==0 );
		}
		else {
			b = 1 / a;
		}
		break;
	default:
		assert(0);
	}
}
double 	Engr::TF::Flow::Face::PGrad_Const( Cell* cell,int e) {
	double a = 0;
	double b = 0;
	Cell* nbr = NULL;
	
	if ( m_type == FaceType::Enum::eINTERIOR ) {
		nbr = m_cellMap[cell];
		assert(nbr);
	}
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		a = nbr->m_x[e] - cell->m_x[e];
		if ( a==0 ) {
			assert( m_n[e]==0 );
		}
		else {
			b = nbr->m_P / a;
		}
		break;
	case FaceType::Enum::eWALL:
		b = 0; // pressure gradient zero at wall. dont know if this is true!
		break;
	case FaceType::Enum::eVEL:
		b = 0; // pressure gradient zero at velocity inlet. dont know if this is true!
		break;
	case FaceType::Enum::ePRES:
		b = 0; // pressure outlet has pressure of zero;
		break;
	default:
		assert(0);
	}
	
	return b;
}
double 	Engr::TF::Flow::Face::P(Cell* cell) {
	Cell* nbr;
	double P = 0;
	
	switch ( m_type ) {
	case FaceType::Enum::eINTERIOR:
		nbr = m_cellMap[cell];
		assert(nbr);
		
		P = 0.5 * cell->m_P + 0.5 * nbr->m_P;
		break;
	case FaceType::Enum::eWALL:
		P = cell->m_P;
		break;
	case FaceType::Enum::eVEL:
		P = cell->m_P;
		break;
	case FaceType::Enum::ePRES:
		P = 0;
		break;
	default:
		assert(0);
		break;
	}
	
	return P;
}



double 	Engr::TF::Flow::Face::Normal(Cell* cell,int e) {
	return ( m_n[e] * m_mapA[cell] * m_A );
}
void	Engr::TF::Flow::Face::Print() {
	printf("x={%f %f}\n",m_x[0],m_x[1]);
	printf("n={%f %f}\n",m_n[0],m_n[1]);
	
}



void	Engr::TF::Flow::Cell::GenerateSquare(Face* n,Face* s,Face* e,Face* w,double x,double y) {
	m_x.init(2);
	m_x[0] = x;
	m_x[1] = y;
	
	m_u = new double[2];
	m_u[0] = 1;
	m_u[1] = 0;
	
	m_face = new Face*[4];
	
	m_nbFace = 4;
	
	m_face[0] = n;
	m_face[1] = s;
	m_face[2] = e;
	m_face[3] = w;
	
	for ( int a = 0; a < m_nbFace; a++ ) { 
		m_face[a]->m_cell.push_back(this);
	}
}
double	Engr::TF::Flow::Cell::Advec_Coeff( int e ) {
	Cell* nbr = NULL;
	Face* face = NULL;
	
	double A1 = 0;
	
	for ( int d = 0; d < m_nbFace; d++ ) {
		face = m_face[d];
		assert(face);
		
		for ( int f = 0; f < 2; f++ ) {
			A1 += face->Vel_Coeff(this,e) * face->Vel(this,f) * face->Normal(this,f);
		}
	}
	
	assert( !isnan(A1) );
	assert( !isinf(A1) );
	
	return A1;
}
double	Engr::TF::Flow::Cell::Advec_Const( int e ) {
	Cell* nbr = NULL;
	Face* face = NULL;
	
	// A2
	double A2 = 0;
	
	for ( int d = 0; d < m_nbFace; d++ ) {
		face = m_face[d];
		assert(face);
		
		for ( int f = 0; f < 2; f++ ) {
			A2 += face->Vel_Const(this,e) * face->Vel(this,f) * face->Normal(this,f);
		}
	}
	
	assert( !isnan(A2) );
	assert( !isinf(A2) );
	
	return A2;
}
double	Engr::TF::Flow::Cell::Diffu_Coeff( int e ) {
	Face* face = NULL;
	
	// A4
	double A4 = 0;
	double a = 0;
	//printf("diffu coeff\n");
	for ( int d = 0; d < m_nbFace; d++ ) {
		face = m_face[d];
		assert(face);
		
		for ( int f = 0; f < 2; f++ ) {
			
			A4 += face->VelGrad_Coeff(this,e,f) * face->Normal(this,f);
			
			//printf("mapA = %f\n",face->m_mapA[this]);
		}
	}
	
	assert( !isnan(A4) );
	assert( !isinf(A4) );
	
	return A4;
}
double	Engr::TF::Flow::Cell::Diffu_Const( int e ) {
	Face* face = NULL;
	
	// A3
	double A3 = 0;
	double a = 0;
	
	for ( int d = 0; d < m_nbFace; d++ ) {
		face = m_face[d];
		assert(face);
		
		for ( int f = 0; f < 2; f++ ) {
			A3 += face->VelGrad_Const(this,e,f) * face->Normal(this,f);
		}
	}
	
	assert( !isnan(A3) );
	assert( !isinf(A3) );
	
	return A3;
}
double	Engr::TF::Flow::Cell::Pres(int e) {
	Cell* nbr = NULL;
	Face* face = NULL;
	
	//A5
	double A5 = 0;
	
	for ( int d = 0; d < m_nbFace; d++ ) {
		face = m_face[d];
		assert(face);
		
		A5 += face->P(this) * face->Normal(this,e);
	}
	
	return A5;
}
double	Engr::TF::Flow::Cell::Momentum() {
	double A1, A2, A3, A4, A5;
	
	double res = 0;
	
	for ( int e = 0; e < 2; e++ ) {
		Cell* nbr = NULL;
		Face* face = NULL;
		
		double u_old = m_u[e];
		
		A1 = Advec_Coeff(e);
		A2 = Advec_Const(e);
		A3 = Diffu_Const(e);
		A4 = Diffu_Coeff(e);
		A5 = Pres(e);
		
		double a = A1 - A4;
		double b = A3 - A5 - A2;
		
		if ( a==0 ) {
			printf("A1=%f A4=%f\n",A1,A4);
			
			if ( b!=0 ) {
				printf("A3=%f A5=%f A2=%f\n",A3,A5,A2);
				
				printf("x=%f y=%f\n",m_x[0],m_x[1]);
				
				PrintFaceType();
				Print();
			}
			assert( b==0 );
			
			m_u[e] = 0;
		}
		else {
			m_u[e] = b / a;
		}
		
		double r = ( u_old - m_u[e] );
		res += r * r;
	}
	
	return res;
}
double	Engr::TF::Flow::Cell::Poisson() {
	double A6, A7, A8;
	
	Face* face = NULL;
	
	double P_old = m_P;
	
	A6 = 0;
	for ( int d = 0; d < m_nbFace; d++ ) {
		face = m_face[d];
		assert(face);
		
		for ( int e = 0; e < 2; e++ ) {
			for ( int f = 0; f < 2; f++ ) {
				A6 += face->Vel(this,f) * face->VelGrad(this,e,f) * face->Normal(this,e);
			}
		}
	}
	
	A7 = 0;
	A8 = 0;
	for ( int d = 0; d < m_nbFace; d++ ) {
		face = m_face[d];
		assert(face);
		
		for ( int e = 0; e < 2; e++ ) {
			A7 += face->PGrad_Const(this,e) * face->Normal(this,e);
			A8 += face->PGrad_Coeff(this,e) * face->Normal(this,e);
		}
	}
	
	m_P = ( A6 + A7 ) / A8;
	
	double r = ( m_P - P_old );
	return r * r;
}
void	Engr::TF::Flow::Cell::PrintFaceType() {
	for ( int a = 0; a < 4; a++ ) {
		printf("face %i type %i\n",a,m_face[a]->m_type);
	}
}
void	Engr::TF::Flow::Cell::Print() {
	for ( int a = 0; a < 4; a++ ) {
		printf("face[%i]\n",a);
		m_face[a]->Print();
	}
}
int		perind(int a,int n) {
	if ( a < 0 ) {
		return ( a + n );
	}
	else if ( a < n ) {
		return a;
	}
	else {
		return ( a - n );
	}
}



void 	Engr::TF::Flow::Mesh::GenerateSquare(int n,double dx) {
	m_cell.init(2,n,n);
	m_n = n;
	
	m_face.init(3,2,n+1,n+1);
	
	double nx = 0;
	double ny = 0;
	double x = 0;
	double y = 0;
	
	for ( int d = 0; d < 2; d++ ) {
		for ( int a = 0; a < (n+1); a++ ) {
			for ( int b = 0; b < (n+1); b++ ) {
				nx = (d==0)?(1.0):(0.0);
				ny = (d==1)?(1.0):(0.0);
				
				x = (d==0)?(0.5*dx):(0.0);
				y = (d==1)?(0.5*dx):(0.0);
				
				m_face.at(d,a,b) = new Face;
				
				m_face.at(d,a,b)->Generate2D( a*dx - x, b*dx - y, nx, ny, dx );
				m_face.at(d,a,b)->m_type = FaceType::Enum::eINTERIOR;
			}
		}
	}
	
	m_typeN = FaceType::Enum::eWALL;
	m_typeS = FaceType::Enum::eWALL;
	m_typeE = FaceType::Enum::ePRES;
	m_typeW = FaceType::Enum::eVEL;
	
	printf("faces generated\n");
	
	for ( int a = 0; a < n; a++ ) {
		for ( int b = 0; b < n; b++ ) {
			m_cell.at(a,b) = new Cell;
			
			Face* N = NULL;
			Face* S = NULL;
			Face* E = NULL;
			Face* W = NULL;
			
			switch ( m_typeN ) {
			case FaceType::Enum::eINTERIOR:
				N = m_face.at( 1, a, perind(b+1,n) );
				break;
			case FaceType::Enum::eWALL:
				N = m_face.at( 1, a, b+1 );
				break;
			case FaceType::Enum::eVEL:
				N = m_face.at( 1, a, b+1 );
				break;
			case FaceType::Enum::ePRES:
				N = m_face.at( 1, a, b+1 );
				break;
			default:
				assert(0);
				break;
			}
			switch ( m_typeS ) {
			case FaceType::Enum::eINTERIOR:
				S = m_face.at( 1, a, b );
				break;
			case FaceType::Enum::eWALL:
				S = m_face.at( 1, a, b );
				break;
			case FaceType::Enum::eVEL:
				S = m_face.at( 1, a, b );
				break;
			case FaceType::Enum::ePRES:
				S = m_face.at( 1, a, b );
				break;
			default:
				assert(0);
				break;
			}
			switch ( m_typeE ) {
			case FaceType::Enum::eINTERIOR:
				E = m_face.at( 0, perind(a+1,n), b );
				break;
			case FaceType::Enum::eWALL:
				E = m_face.at( 0, a+1, b );
				break;
			case FaceType::Enum::eVEL:
				E = m_face.at( 0, a+1, b );
				break;
			case FaceType::Enum::ePRES:
				E = m_face.at( 0, a+1, b );
				break;
			default:
				assert(0);
				break;
			}
			switch ( m_typeW ) {
			case FaceType::Enum::eINTERIOR:
				W = m_face.at( 0, a, b );
				break;
			case FaceType::Enum::eWALL:
				W = m_face.at( 0, a, b );
				break;
			case FaceType::Enum::eVEL:
				W = m_face.at( 0, a, b );
				break;
			case FaceType::Enum::ePRES:
				W = m_face.at( 0, a, b );
				break;
			default:
				assert(0);
				break;
			}
			
			m_cell.at(a,b)->GenerateSquare( N, S, E, W, a*dx, b*dx );
		}
	}
	
	for ( int a = 0; a < n; a++ ) {
		// N
		m_cell.at(a,n-1)->m_face[0]->m_type = m_typeN;
		
		// S
		m_cell.at(a,0)->m_face[1]->m_type = m_typeS;
		
		// E
		m_cell.at(n-1,a)->m_face[2]->m_type = m_typeE;
		
		// W
		m_cell.at(0,a)->m_face[3]->m_type = m_typeW;
	}
	
	printf("cells generated %i cells\n",m_n*m_n);
	
	for ( int d = 0; d < 2; d++ ) {
		for ( int a = 0; a < (n+1); a++ ) {
			for ( int b = 0; b < (n+1); b++ ) {
				m_face.at(d,a,b)->RegisterNeighbors();
			}
		}
	}
	
	printf("neighbors registered\n");
}
void	Engr::TF::Flow::Mesh::Iter() {
	double res, res_P;
	res = 0;
	res_P = 0;
	
	
	printf("momentum\n");
	
	for ( int g = 0; g < 200; g++ ) {
		res = 0;
		for ( int a = 0; a < m_n; a++ ) {
			for ( int b = 0; b < m_n; b++ ) {
				res += m_cell.at(a,b)->Momentum();
			}
		}
		printf("%f\n",res);
	}
	
	printf("pressure\n");
	
	for ( int g = 0; g < 5; g++ ) {
		res_P = 0;
		for ( int a = 0; a < m_n; a++ ) {
			for ( int b = 0; b < m_n; b++ ) {
				res_P += m_cell.at(a,b)->Poisson();
			}
		}
		printf("%f\n",res_P);
	}
	//printf("%f %f\n",res,res_P);
}
void	Engr::TF::Flow::Mesh::Write() {
	matrixD u,v;
	u.init(2,m_n,m_n);
	v.init(2,m_n,m_n);
	
	for ( int a = 0; a < m_n; a++ ) {
		for ( int b = 0; b < m_n; b++ ) {
			u.at(a,b) = m_cell.at(a,b)->m_u[0];
			v.at(a,b) = m_cell.at(a,b)->m_u[1];
		}
	}
	
	u.write("u");
	v.write("v");
}
void	Engr::TF::Flow::Mesh::Print() {
	for ( int d = 0; d < 2; d++ ) {
		
		printf("face[%i,,]\n",d);
		for ( int e = 0; e < 2; e++ ) {
			
			printf("x[%i]=\n",e);
			for ( int a = 0; a < (m_n+1); a++ ) {
				for ( int b = 0; b < (m_n+1); b++ ) {
					printf("%6.2f ",m_face.at(d,a,b)->X(e));
				}
				printf("\n");
			}
			printf("\n\n");
			
			printf("n[%i]=\n",e);
			for ( int a = 0; a < (m_n+1); a++ ) {
				for ( int b = 0; b < (m_n+1); b++ ) {
					printf("%6.2f ",m_face.at(d,a,b)->N(e));
				}
				printf("\n");
			}
			printf("\n\n");
			
		}
		printf("\n\n");
		
	}
}



void	Engr::TF::Flow::CFD::GenerateSquare(int n,double dx) {
	m_mesh = new Mesh;
	m_mesh->GenerateSquare(n,dx);
	
	
}
void	Engr::TF::Flow::CFD::Iter() {
	assert(m_mesh);
	
	for ( int g = 0; g < 1; g++ ) {
		m_mesh->Iter();
	}
	
	
}
void	Engr::TF::Flow::CFD::Write() {
	m_mesh->Write();
}





















