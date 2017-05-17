#include "../../include/MyXLib.h"

using namespace std;

int main() {
	shared_ptr<MyXLib::Display> display( new MyXLib::Display );
	{
		shared_ptr<MyXLib::Window> win( new MyXLib::Window );
		
		display->Open("localhost:10.0");
		
		win->Open(display);
		
		win->SelectInput( KeyPressMask | ButtonPressMask | ExposureMask );
		
		XEvent an_event;
		int done = 0;
		while (!done) {
			XNextEvent( display->m_display, &an_event );
			switch ( an_event.type ) {
			case Expose:
				win->DrawLine( 20, 20, 40, 100 );
				break;
			case ButtonPress:
				win->FillRectangle( 60, 150, 50, 60);
				break;
			case KeyPress:
				done = 1;
				break;
			default:
				break;
			}
		}
	}
}
