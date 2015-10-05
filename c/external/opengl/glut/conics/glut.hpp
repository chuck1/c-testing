#ifndef MAIN
#define MAIN

#include <glm/glm.hpp>

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

// view
extern float		g_view_dist;

extern float		g_view_yaw;
extern float		g_view_pitch;

extern glm::vec3	g_eye_off;


extern float g_time;

extern struct timeval last_idle_time;


#endif


