
	MyXLib::Display::~Display() {
	delete m_window;
	
	XCloseDisplay( m_display );
}

int MyXLib::Display::OpenWindow() {
	m_window = new Window;
	
	m_window->Open( this );
}





	MyXLib::Window::~Window() {
	
}
int MyXLib::Window::Open( MyXLib::Display* display ) {
	
}

int MyXLib::Window::SelectInput( long event_mask ) {
	
}


int MyXLib::Window::DrawPoint( int x, int y ) {
	XDrawPoint( m_display->m_display, m_win, m_gc, x, x);
}
int MyXLib::Window::DrawLine( int x1, int y1, int x2, int y2 ) {
	XDrawLine( m_display->m_display, m_win, m_gc, x1, y1, x2, y2 );
}
int MyXLib::Window::DrawArc( int x, int y, int w, int h, int angle1, int angle2 ) {
	XDrawArc( m_display->m_display, m_win, m_gc, x-(w/2), y-(h/2), w, h, angle1, angle2);
}
int MyXLib::Window::DrawLines( XPoint points[] ) {
	int npoints = sizeof(points)/sizeof(XPoint);
	XDrawLines( m_display->m_display, m_win, m_gc, points, npoints, CoordModeOrigin);
}
int MyXLib::Window::DrawRectangle( int x, int y, int w, int h ) {
	XDrawRectangle( m_display->m_display, m_win, m_gc, x, y, w, h );
}
int MyXLib::Window::FillRectangle( int x, int y, int w, int h ) {
	XFillRectangle( m_display->m_display, m_win, m_gc, x, y, w, h );
}





