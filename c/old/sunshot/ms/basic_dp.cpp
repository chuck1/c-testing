
#include "../../mylib/mylib.h"


int main() {

Engr::TF::Flow::Internal::RectangularDuct duct( 1e-4, 1e-4,1e-2 );

shared_ptr< ::Engr::TF::Material> m(new Engr::TF::Material("ms1"));

Engr::TF::Flow::Internal::PressureDropBasic dp;

double T0 = 300 + 273.15;
double T1 = 550 + 273.15;

dp.Calc(m,duct,22e-6,T0,T1,1e5);

printf("%f\n",dp.m_f);
printf("%f\n",dp.m_Re);
printf("%f\n",dp.m_dp);

}

