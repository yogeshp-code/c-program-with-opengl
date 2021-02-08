///*
// * header.h
// *
// *  Created on: 10-Oct-2020
// *      Author: HP 14s DK0093AU
// */
//
#ifndef HEADER_H_
#define HEADER_H_

#include<stdio.h>
#include<windows.h>
#include<GL/glut.h>
#include<math.h>
#define True 1
#define False 0
#define Up 0
#define Down 1
#define Right 2
#define Left 3
#define First 0
#define Second 1
#define Third 2
float radius;
struct mypoint{
	float x,y;
};
typedef struct mypoint point;
void text(char *s,float x1,float y1,int x)
{
		glRasterPos2f(x1,y1);
		for(char *c=s;*c!='\0';c++)
		{
			if(x==24)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
			}
			else if(x==18)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*c);

			}
			else
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,*c);
			}
		}
		glFlush();
		glEnd();
}


void ploatpixel(float x,float y ,float xc, float yc)
{
	glVertex2f(x+xc,y+yc);
	glVertex2f(y+xc,x+yc);
	glVertex2f(-x+xc,-y+yc);
	glVertex2f(-y+xc,-x+yc);
	glVertex2f(x+xc,-y+yc);
	glVertex2f(y+xc,-x+yc);
	glVertex2f(-x+xc,y+yc);
	glVertex2f(-y+xc,x+yc);
}

void line(point p1,point p2,int pointsize)
{
	float dx,dy,steps,xinc,yinc,xp,yp;
	int k;
	dx=p2.x-p1.x;
	dy=p2.y-p1.y;
	if(abs(dx)>abs(dy))
	{
		steps=abs(dx);
	}
	else
	{
		steps=abs(dy);
	}
	xinc=(dx/steps);
	yinc=(dy/steps);

	yp=p1.y;
	xp=p1.x;
	glPointSize(pointsize);
	glBegin(GL_POINTS);
	glVertex2f(round(xp) , round(yp));
	k=1;
	while(k<=steps)
	{
		xp=xp+xinc;
		yp=yp+yinc;
		glVertex2f(round(xp),round(yp));
		k++;
	}
	glEnd();
	glFlush();
}
void circle(point p1,float radius,float pointsize)
{
	int d1;
	float x1=0;
	float y1=radius;
	glPointSize(pointsize);
	glBegin(GL_POINTS);
	ploatpixel(x1,y1,p1.x,p1.y);
	d1=3-2*radius;
	while(x1 <= y1)
	{
		if(d1<0)
		{
			x1=x1+1;
			d1=d1+4*x1+6;
			ploatpixel(x1,y1,p1.x,p1.y);
		}
		else
		{
			x1=x1+1;
			y1=y1-1;
			d1=d1+4*(x1-y1)+10;
			ploatpixel(x1,y1,p1.x,p1.y);
		}
	}
	glEnd();
	glFlush();
}
void curve(point p1,point p2,float theta)
{
	float dth,angle,rtheta;
	dth=1/(3.2* abs(p2.x-p1.x) + abs(p2.y-p1.y));
	if(dth>0.01)
	{
		dth=0.01;
	}
	angle=0.0;
	rtheta = 3.14159 * theta /180.0;

	glBegin(GL_POINTS);
	while(angle<rtheta)
	{
		glVertex2f(p2.x,p2.y);
		p2.x=p2.x-((p2.y-p1.y)*dth);
		p2.y=p2.y+((p2.x-p1.x)*dth);
		angle=angle+dth;
	}
	glEnd();
	glFlush();
}
void ploatpixel1(float x,float y,float xc, float yc)
{
	glVertex2i(xc+x, yc+y);
	glVertex2i(xc-x, yc-y);
	glVertex2i(xc+x, yc-y);
	glVertex2i(xc-x, yc+y);

}
void ellipse(point p1,point p2)
{
	int x, y, p;
	glPointSize(5.0);
	glBegin(GL_POINTS);
	x = 0;
	y = p2.y;
	p = (p2.y*p2.y) - (p2.x*p2.x*p2.y) + ((p2.x*p2.x)/4);

	while((2*p2.y*p2.y*x) <= (2*p2.x*p2.x*y))
	{
		if(p < 0)
		{
			x = x + 1;
			p = p + (2*p2.y*p2.y*x) + (p2.y*p2.y);
			ploatpixel1(x,y,p1.x,p1.y);
		}
		else
		{
			x = x + 1;
			y = y - 1;
			p = p + (2*p2.y*p2.y*x) - (2*p2.x*p2.x*y) + (p2.y*p2.y);
			ploatpixel1(x,y,p1.x,p1.y);
		}

	}

	p = (p2.y*p2.y)*((float)x+0.5)*((float)x+0.5) + (p2.x*p2.x)*(y-1)*(y-1) - (p2.x*p2.x*p2.y*p2.y);
	while(y>=0)
	{
		if (p <= 0)
		{
			y = y - 1;
			x = x + 1;
			p = p + (p2.y*p2.y*2*x) - (2*p2.x*p2.x*y) + (p2.x*p2.x);
			ploatpixel1(x,y,p1.x,p1.y);
		}
		else
		{
			y = y - 1;
			p = p - (2*p2.x*p2.x*y) + (p2.x*p2.x);
			ploatpixel1(x,y,p1.x,p1.y);
		}
	}
	glEnd();
	glFlush();
}

#endif /* HEADER_H_ */


