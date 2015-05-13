#ifndef _ENGR_TF_FLOW_INTERNAL_CONST_AREA_DUCT_H
#define _ENGR_TF_FLOW_INTERNAL_CONST_AREA_DUCT_H



namespace Engr {
	namespace TF {
		namespace Flow {
			namespace Internal {
				class ConstantAreaDuct {
				public:
					ConstantAreaDuct(double A,double Dh,double L,double a);
					
					double m_A;
					double m_Dh;
					double m_L;
					double m_a;
				};
				class RectangularDuct: public ConstantAreaDuct {
				public:
					RectangularDuct(double w,double h,double L);
				};
			}
		}
	}
}

Engr::TF::Flow::Internal::ConstantAreaDuct::ConstantAreaDuct(double A, double Dh, double L, double a) {
	m_A = A;
	m_Dh = Dh;
	m_L = L;
	m_a = a;
}
Engr::TF::Flow::Internal::RectangularDuct::RectangularDuct(double w,double h,double L): ConstantAreaDuct(w*h, 2*w*h/(w+h), L, h/w) {
}


#endif



