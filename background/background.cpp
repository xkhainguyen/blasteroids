#include "background.h"
#include "fssimplewindow.h"
#include <cmath>

int window_width = 800;
int window_height = 600;
const double YS_PI = 3.1415927;


Sphere::Sphere()
{
    Initialize();
}

void Sphere::Initialize(void)
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
    r = 0.0;
}

Sphere::~Sphere()
{
    CleanUp();
}

void Sphere::CleanUp(void)
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
    r = 0.0;
}


void DrawSphere(double cx, double cy, double r, 
                int divH, int divP, int red, int green, int blue)
{
	glBegin(GL_QUADS);

	for(int i = -divP; i < divP; ++i)
	{
		double p0 = (double) i * YS_PI * 0.5 / (double) divP;
		double p1 = (double) (i + 1) * YS_PI * 0.5 / (double) divP;
		for(int j = 0; j < divH; ++j)
		{
			double h0 = (double) j * 2.0 * YS_PI / (double) divH;
			double h1 = (double) (j + 1) * 2.0 * YS_PI / (double) divH;

			double x0 = cx + r * cos(p0) * cos(h0);
			double y0 = cy + r * sin(p0);

			double x1 = cx + r * cos(p0) * cos(h1);
			double y1 = cy + r * sin(p0);

			double x2 = cx + r * cos(p1) * cos(h1);
			double y2 = cy + r * sin(p1);

			double x3 = cx + r * cos(p1) * cos(h0);
			double y3 = cy + r * sin(p1);

			glColor3ub(red, green, blue);
			glVertex2d(x0, y0);
			glVertex2d(x1, y1);
			glVertex2d(x2, y2);
			glVertex2d(x3, y3);
		}
	}
	glEnd();
}


const int nStar = 20;
static Sphere star[nStar];


void DrawBackground() 
{
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(window_width, 0);
    glVertex2i(window_width, window_height);
    glVertex2i(0, window_height);
    glEnd();

    for(int i = 0; i < nStar; ++i)
    {
      star[i].x = (double) (((double) rand() / (double) RAND_MAX) * window_width);
      star[i].y = (double) (((double) rand() / (double) RAND_MAX) * window_height);
      star[i].r = (double) (((double) rand() / (double) RAND_MAX) * 0.5) + 0.7;

        if(i % 4 == 0)
        {
            DrawSphere(star[i].x, star[i].y, star[i].r, 36, 18, 255, 255, 255);
        }
        else if(i % 4 == 1)
        {
            DrawSphere(star[i].x, star[i].y, star[i].r, 36, 18, 255, 0, 0);
        }
        else if(i % 4 == 2)
        {
            DrawSphere(star[i].x, star[i].y, star[i].r, 36, 18, 0, 255, 0);
        }
        else if(i % 4 == 3)
        {
            DrawSphere(star[i].x, star[i].y, star[i].r, 36, 18, 0, 0, 255);
        }
    }
}

