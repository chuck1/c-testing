#include "../../include.h"



int main(int argc, char *argv[]) {
	shared_ptr<MyXLib::Display> display( new MyXLib::Display );
	
	display->Open();
	display->OpenWindow();
	
	MyOpenGLX gl;
	
	gl.Initialize( display->m_display, display->m_root_window, display->m_window->m_win );
	
	display->m_window->SelectInput( ExposureMask | KeyPressMask );
	
	
	
	XWindowAttributes gwa;
	XEvent xev;
	while(1) {
		XNextEvent( display->m_display, &xev );
		
		switch( xev.type ) {
		case Expose:
			XGetWindowAttributes( display->m_display, display->m_window->m_win, &gwa );
			glViewport(0, 0, gwa.width, gwa.height);
			gl.DrawQuad();
			glXSwapBuffers( display->m_display, display->m_window->m_win );
			break;
		case KeyPress:
			glXMakeCurrent( display->m_display, None, NULL );
			glXDestroyContext( display->m_display, gl.glc );
			
			return 1;
		}
	}
	
	
}


