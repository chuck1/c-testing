#ifndef _ENGR_TF_FLOW_INTERNAL_LAMINAR_FRICTION_H
#define _ENGR_TF_FLOW_INTERNAL_LAMINAR_FRICTION_H




namespace Engr
{
	namespace TF
	{
		namespace Flow
		{
			namespace Internal
			{
				namespace Laminar
				{
					namespace Friction
					{
						class SL
						{
						public:
							static double f( double a, double Re )
							{
								// darcy friction factor
								// laminar
								// rectangular duct
								
								a = min( a, 1.0/a );
								
								
								
								double f = 4.0 * 24.0 * ( 
									1 - 
									1.3553 * a + 
									1.9467 * pow(a,2) - 
									1.7012 * pow(a,3) +
									0.9564 * pow(a,4) - 
									0.2537 * pow(a,5)
									) / Re;
								
								//cout << "SF::f a=" << a << " f=" << f << "\n";
								
								return f;
							}
						};
					};
				};
			};
		};
	};
};



#endif


