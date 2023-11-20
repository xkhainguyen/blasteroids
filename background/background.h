#ifndef BLASTEROIDS_SPHERE_H_IS_INCLUDED
#define BLASTEROIDS_SPHERE_H_IS_INCLUDED



void DrawBackground();
void DrawSphere(double cx, double cy, double r, 
                int divH, int divP, int red, int green, int blue);

class Sphere
{
public:
    double x=0, y=0, z=0;
    double r=0;
    Sphere();
    ~Sphere();
    void Initialize(void);
    void CleanUp(void);
};

#endif