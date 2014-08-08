#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "glut.hpp"

#define VIEWING_DISTANCE_MIN  3.0
#define TEXTURE_ID_CUBE 1







float g_view_dist = 3.0E11;

float g_view_x = 0.5;//0.0;
float g_view_y = 0.5;//7.5;
float g_view_yaw = 0;
float g_view_pitch = 0;
struct timeval last_idle_time = timeval();


float g_time = 0;



