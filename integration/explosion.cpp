#include "explosion.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "fssimplewindow.h"


void Explosion::Explode(int x,int y)
{
	step=0;
	state=1;
	particles.resize(NUM_PARTICLES);
	for(auto &p : particles)
	{
		p.x=x;
		p.y=y;
		p.vx=rand()%20-5;
		p.vy=rand()%20-5;
		p.r=rand()%256;
		p.g=rand()%256;
		p.b=0;
	}
}
void Explosion::Move(void)
{
	if(0!=state)
	{
		for(auto &p : particles)
		{
			p.x+=p.vx;
			p.y+=p.vy;
		}
		++step;
		if(30<step)
		{
			state=0;
		}
	}
}
void Explosion::Draw(void) 
{
	if(0!=state)
	{
		glBegin(GL_POINTS);
		for(auto p : particles)
		{
			glColor3ub(p.r,p.g,p.b);
			glVertex2i(p.x,p.y);
		}
		glEnd();
	}
}