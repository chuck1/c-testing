#ifndef MAIN
#define MAIN

enum {
	MENU_LIGHTING = 1,
	MENU_POLYMODE,
	MENU_CAMERA,
	MENU_EXIT
};

enum {
	CAM_STATIONARY = 0,
	CAM_FOLLOW,
	CAM_COUNT
};


extern float g_view_dist;// = 5.0;
extern float g_view_x;// = 0.5;//0.0;
extern float g_view_y;// = 0.5;//7.5;
extern float g_view_yaw;// = 0;
extern float g_view_pitch;// = 0;

extern float g_time;

extern struct timeval last_idle_time;


#endif


