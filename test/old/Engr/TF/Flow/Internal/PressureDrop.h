#ifndef _ENGR_TF_FLOW_INTERNAL_PRESSURE_DROP_H
#define _ENGR_TF_FLOW_INTERNAL_PRESSURE_DROP_H



namespace Engr {
	namespace TF {
		namespace Flow {
			namespace Internal
			{
				class PressureDrop
				{
				public:
							PressureDrop();
					void	Calc (shared_ptr< ::Engr::TF::Material> m, ConstantAreaDuct duct, double T0, double dh, double qpp, double w, double p0);
					
					double	m_dp;
					double	m_M;
				};
				class PressureDropBasic {
				public:
							PressureDropBasic();
					void	Calc (shared_ptr< ::Engr::TF::Material> m, ConstantAreaDuct duct, double M, double T0, double T1, double p0);
					
					double	m_Re;
					double	m_f;
					double	m_dp;
					double	m_M;
				};
			}
		}
	}
}

		Engr::TF::Flow::Internal::PressureDrop::PressureDrop() {
	
}
void	Engr::TF::Flow::Internal::PressureDrop::Calc (shared_ptr< ::Engr::TF::Material> m, ConstantAreaDuct duct, double T0, double dh, double qpp, double w, double p0) {
	int n = 100;
	double dx = duct.m_L/n;
	
	double qp = qpp * w;
	
	m_M = qp * duct.m_L / dh;
	
	matrixD dpf, T;
	
	dpf.init(1,n);
	
	T.init(1,n+1);
	
	T[0] = T0;
	
	double cp = 0;
	
	// solve temperature
	for ( int a = 0; a < n; a++ )
	{
		cp = m->Get("specific-heat","T",T[a],"p",p0);
		
		T[a+1] = T[a] + qp*dx/m_M/cp;
	}
	
	// solve pressure
	double mu = 0;
	double rho = 0;
	double Re = 0;
	double f = 0;
	for ( int a = 0; a < n; a++ )
	{
		mu = m->Get("viscosity","T",T[a],"p",p0);
		rho = m->Get("density","T",T[a],"p",p0);
		Re = m_M * duct.m_Dh / mu / duct.m_A;
		
		f = Engr::TF::Flow::Internal::Laminar::Friction::SL::f(duct.m_a,Re);
		
		dpf[a] = f * dx / duct.m_Dh * ( m_M * m_M / 2 / rho / duct.m_A / duct.m_A );
	}
	
	
	double rho0 = m->Get("density","T",T[0],"p",p0);
	double rho1 = m->Get("density","T",T[n],"p",p0);
	double dpK = ( m_M * m_M / 2 / duct.m_A / duct.m_A ) * ( 1 / rho1 - 1 / rho0 );
	
	
	m_dp = dpf.Sum() + dpK;
	
	
}

		Engr::TF::Flow::Internal::PressureDropBasic::PressureDropBasic() {
	
}
void	Engr::TF::Flow::Internal::PressureDropBasic::Calc(shared_ptr< ::Engr::TF::Material> m, ConstantAreaDuct duct, double M, double T0, double T1, double p0) {
	m_M = M;
	
	double T = (T1+T0)/2;
	
	double mu = m->Get("viscosity","T",T,"p",p0);
	double rho = m->Get("density","T",T,"p",p0);
	
	m_Re = m_M * duct.m_Dh / mu / duct.m_A;
	m_f = Engr::TF::Flow::Internal::Laminar::Friction::SL::f(duct.m_a,m_Re);
	
	double dpf = m_f * duct.m_L / duct.m_Dh * ( m_M * m_M / 2 / rho / duct.m_A / duct.m_A );
	
	
	
	double rho0 = m->Get("density","T",T0,"p",p0);
	double rho1 = m->Get("density","T",T1,"p",p0);
	double dpK = ( m_M * m_M / 2 / duct.m_A / duct.m_A ) * ( 1 / rho1 - 1 / rho0 );
	
	
	m_dp = dpf + dpK;
}




#endif
