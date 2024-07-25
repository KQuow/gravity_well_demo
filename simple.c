#include "simple.h"
#include <gl/gl.h>


void draw_triangle(float x1,float y1,float x2,float y2,float x3,float y3) {
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(x1,y1);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(x2,y2);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(x3,y3);
	glEnd();
}


void draw_rectangle(float x1,float y1,float x2,float y2) {
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(x1,y1);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(x2,y1);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(x1,y2);

		glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(x1,y2);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(x2,y1);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(x2,y2);
	glEnd();
	glPopMatrix();
}

void draw_cube(float x1,float y1,float z1,float x2,float y2,float z2) {
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		//UP
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x1,y1,z1);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x2,y1,z1);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x1,y1,z2);
			glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x2,y1,z1);
			glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x1,y1,z2);
			glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x2,y1,z2);
		//RIGHT
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x2,y1,z1);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x2,y2,z1);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x2,y1,z2);
			glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x2,y2,z1);
			glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x2,y1,z2);
			glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x2,y2,z2);
		//DOWN
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x1,y2,z1);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x2,y2,z1);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x1,y2,z2);
			glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x2,y2,z1);
			glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x1,y2,z2);
			glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x2,y2,z2);
		//LEFT
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x1,y1,z1);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x1,y2,z1);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x1,y1,z2);
			glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x1,y2,z1);
			glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x1,y1,z2);
			glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x1,y2,z2);
		//TOP
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x1,y1,z1);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x2,y1,z1);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x1,y2,z1);
			glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x1,y2,z1);
			glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x2,y1,z1);
			glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x2,y2,z1);
		//BOTTOM
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x1,y1,z2);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x2,y1,z2);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x1,y2,z2);
			glColor3f(1.0f, 0.0f, 0.0f);   glVertex3f(x1,y2,z2);
			glColor3f(0.0f, 1.0f, 0.0f);   glVertex3f(x2,y1,z2);
			glColor3f(0.0f, 0.0f, 1.0f);   glVertex3f(x2,y2,z2);
	glEnd();
	glPopMatrix();
}










