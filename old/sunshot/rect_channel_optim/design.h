class constants {
public:
	int parse (const char* xmlfile);
	
	shared_ptr<Engr::TF::Material> m_m;
	double m_L;
	double m_kf;
	double m_ks;
	double m_T0;
	double m_T1;
	double m_qpp;
	double m_p0;
	double m_dh;
	double m_dpLim;
	map<string,double>	m_var;
	map<string,string>	m_unit;
};
class Design {
public:
			Design(){}
			Design( double w, double ww, double H, shared_ptr<constants> con ): m_w(w), m_ww(ww), m_H(H), m_con(con) {}
	void 	Set( double w, double ww, double H, shared_ptr<constants> con );
	void 	Calc();
	
	// constants
	shared_ptr<constants>					m_con;
	
	// input
	double									m_w;
	double									m_ww;
	double									m_H;
	
	// calculated
	Engr::TF::Flow::Internal::PressureDrop	m_p;
	
	double									m_Nu1;
	double									m_Nu2;
	double									m_Nu;
	
	double									m_h1;
	double									m_h2;
	double									m_h;
	
	double									m_eta_f;
	double									m_theta;
	
	
};



void 	Design::Set( double w, double ww, double H, shared_ptr<constants> con ) {
	m_w = w;
	m_ww = ww;
	m_H = H;
	m_con = con;
}
void 	Design::Calc() {
	assert (m_con);
	assert (m_con->m_m);
	
	Engr::TF::Flow::Internal::RectangularDuct duct( m_w, m_H, m_con->m_L );
	
	m_p.Calc( m_con->m_m, duct, m_con->m_T0, m_con->m_dh, m_con->m_qpp, m_w+m_ww, m_con->m_p0 );
	
	if ( m_p.m_dp > m_con->m_dpLim ) {
		m_theta = 0.001;
		return;
	}
	
	m_Nu1 = Engr::TF::Heat::Convection::Internal::Laminar::Rectangular::Nusselt::SL1978::Nu(1/duct.m_a,	"H1","Case4");
	m_Nu2 = Engr::TF::Heat::Convection::Internal::Laminar::Rectangular::Nusselt::SL1978::Nu(duct.m_a,	"H1","Case4");
	
	m_Nu = ( ( m_w * m_Nu1 ) + ( m_H * m_Nu2 ) ) / ( m_w + m_H );
	
	m_h = m_Nu * m_con->m_kf / duct.m_Dh;
	m_h1 = m_Nu1 * m_con->m_kf / duct.m_Dh;
	m_h2 = m_Nu2 * m_con->m_kf / duct.m_Dh;
	
	m_eta_f = Engr::TF::Heat::Conduction::ExtendedSurface::Rectangular::efficiency( m_H + ( m_w / 2 ), m_con->m_L, m_ww, m_h / m_con->m_ks, "adiabatic");
	
	m_theta = ( m_ww + m_w ) / ( m_h1 * m_w + m_eta_f * ( m_h1 * m_w + 2 * m_h2 * m_H ) );
}
int 	constants::parse(const char* xmlfile) {
	myxml::attr a[] = {
		{"name",0,myxml::e_CHARSTR,0},
		{"unit",0,myxml::e_CHARSTR,0}
	};
	
	myxml::el e[] = {
		{"mat",	0,0,0,0,0,0,0,myxml::e_CHARSTR,0},
		{"el",	a,2,0,0,0,0,0,myxml::e_DOUBLE,0}
	};
	
	myxml::el des = {"design",0,0,e,2,0,0,0,0,0};
	
	myxml::parse (xmlfile,&des);
	
	assert (des.reschildv);
	for (int a = 0; a < des.reschildc; a++)
	{
		myxml::el *ch = des.reschildv + a;
		
		assert (ch->value);
		//assert (ch->attrv);
		
		//printf("%s %s\n", ch->value, ch->attrv[0].text);
		
		if (strcmp(ch->value,"mat")==0) {
			assert (ch->text);
			//printf("%s %s\n", ch->value, ch->text);
			m_m.reset(new Engr::TF::Material((const char *)ch->text));
		}
		else if (strcmp(ch->value,"el")==0) {
			//printf("%s\n", ch->value);
			
			string name = (const char *)ch->attrv[0].text;
			m_var[name] = *((double*)ch->text);
			m_unit[name] = (const char *)ch->attrv[1].text;
		}
	}
	/*
	printf ("'%s'\n",m_unit["L"].c_str());
	printf ("'%s'\n",m_unit["kf"].c_str());
	printf ("'%s'\n",m_unit["ks"].c_str());
	printf ("'%s'\n",m_unit["T0"].c_str());
	printf ("'%s'\n",m_unit["T1"].c_str());
	printf ("'%s'\n",m_unit["qpp"].c_str());
	printf ("'%s'\n",m_unit["p0"].c_str());
	printf ("'%s'\n",m_unit["dplim"].c_str());
	*/
	m_L 	= unitmanager::ToBase (m_unit["L"], 	m_var["L"]);
	m_kf 	= unitmanager::ToBase (m_unit["kf"], 	m_var["kf"]);
	m_ks 	= unitmanager::ToBase (m_unit["ks"], 	m_var["ks"]);
	m_T0 	= unitmanager::ToBase (m_unit["T0"], 	m_var["T0"]);
	m_T1 	= unitmanager::ToBase (m_unit["T1"], 	m_var["T1"]);
	m_qpp 	= unitmanager::ToBase (m_unit["qpp"], 	m_var["qpp"]);
	m_p0 	= unitmanager::ToBase (m_unit["p0"], 	m_var["p0"]);
	m_dpLim = unitmanager::ToBase (m_unit["dplim"], m_var["dplim"]);
	
	m_dh = m_m->EnthalpyChange( m_T0, m_T1, m_p0 );
}


