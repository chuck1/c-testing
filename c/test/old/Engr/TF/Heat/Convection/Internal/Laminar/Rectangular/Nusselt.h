// Z:\cfs\code\cpp\engr_comp\Engr\TF\Heat\Convection\Internal\Laminar\Rectangular\Nusselt.h

#ifndef _ENGR_TF_HEAT_INTERNAL_LAMINAR_RECTANGULAR_NUSSELT_H
#define _ENGR_TF_HEAT_INTERNAL_LAMINAR_RECTANGULAR_NUSSELT_H




namespace Engr
{
	namespace TF
	{
		namespace Heat
		{
			namespace Convection
			{
				namespace Internal
				{
					namespace Laminar
					{
						namespace Rectangular
						{
							namespace Nusselt
							{
								class SL1978
								{
								public:
									struct BCType
									{
										enum e
										{
											eNONE = 0,
											eH1
										};
									};
									struct WCType
									{
										enum e
										{
											eNONE = 0,
											eCASE4
										};
									};
									
									static double Nu( double a, string bc, string wc )
									{
										map<string,BCType::e> mapBC;
										map<string,WCType::e> mapWC;
										
										mapBC["H1"] 	= BCType::e::eH1;
										mapWC["Case4"] 	= WCType::e::eCASE4;
										
										BCType::e BC = mapBC[bc];
										WCType::e WC = mapWC[wc];
										
										double Nu = 0;
										
										switch ( BC )
										{
										case BCType::e::eH1:
											switch ( WC )
											{
											case WCType::e::eCASE4:
												Nu = ( tanh( 0.48 * log(a) ) + 1 ) * 5.385/2;
												return Nu;
											default:
												assert( 0 );
												return Nu;
											}
										default:
											assert( 0 );
											return Nu;
										}
									}
								};
							};
						};
					};
				};
			};
		};
	};
};



#endif


