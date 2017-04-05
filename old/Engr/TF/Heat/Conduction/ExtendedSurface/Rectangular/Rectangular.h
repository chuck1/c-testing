// Z:\cfs\code\cpp\engr_comp\Engr\TF\Heat\Conduction\ExtendedSurface\Rectangular\Rectangular.h



namespace Engr
{
	namespace TF
	{
		namespace Heat
		{
			namespace Conduction
			{
				namespace ExtendedSurface
				{
					class Rectangular
					{
						struct TCType
						{
							enum e
							{
								eNONE = 0,
								eADIABATIC,
								eCONVECTION
							};
						};
					public:
						static double efficiency( double L, double w, double t, double hk, string tc )
						{
							// hk = h / k_s
							
							map<string,TCType::e> mapTC;
							
							mapTC["adiabatic"] 	= TCType::e::eADIABATIC;
							mapTC["convection"] = TCType::e::eCONVECTION;
							
							TCType::e TC = mapTC[tc];
							
							double L_c;
							
							switch ( TC )
							{
							case TCType::e::eADIABATIC:
								L_c = L;
								break;
							case TCType::e::eCONVECTION:
								L_c = L + t / 2;
								break;
							default:
								assert( 0 );
								return 0;
							}
							
							double P = 2 * (w + t);

							double A_c = w * t;
							
							double N = sqrt( hk * P / A_c ) * L_c;
							
							double eta = tanh(N) / N;
						}
					};
				}
			}
		}
	}
}

