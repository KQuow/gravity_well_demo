#include "camera.h"
#include <windows.h>
#include <gl/gl.h>
#include <math.h>

#include <stddef.h>
#include <stdlib.h>

#define gpu_set_ztestenable()	glEnable(GL_DEPTH_TEST)

float xAlfa=20;
float zAlfa=0;

struct POSI {float x;float y;float z;} pos;

void init_cam() {
	gpu_set_ztestenable();
	pos.x=0;pos.y=0;pos.z=8;
}


void move_camera() {
	if(GetKeyState(VK_UP)<0) xAlfa = ++xAlfa > 180 ? 180 : xAlfa ;
	if(GetKeyState(VK_DOWN)<0) xAlfa = --xAlfa < 0 ? 0 : xAlfa ;

	if(GetKeyState(VK_LEFT)<0) zAlfa = ++zAlfa > 360 ? 0 : zAlfa ;
	if(GetKeyState(VK_RIGHT)<0) zAlfa = --zAlfa < 0 ? 360 : zAlfa ;

	if(GetKeyState(VK_SPACE)<0) pos.z+=0.5;
	if(GetKeyState(VK_LCONTROL)<0) pos.z-=0.5;

	float angle=-zAlfa/180*M_PI;
	float speed=0.0;
	if(GetKeyState('W')<0) speed=0.5;
	if(GetKeyState('S')<0) speed=-0.5;
	if(GetKeyState('A')<0) {speed=0.5;angle-=M_PI*0.5;}
	if(GetKeyState('D')<0) {speed=0.5;angle+=M_PI*0.5;}

	if(speed!=0) {
		pos.x+=sin(angle)*speed;
		pos.y+=cos(angle)*speed;
	}


	glRotatef(-xAlfa,1,0,0);
	glRotatef(-zAlfa,0,0,1);
	glTranslatef(-pos.x,-pos.y,-pos.z);
}
