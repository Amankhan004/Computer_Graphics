// #include "Canvas.h"
#include "Canvas.h"

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <math.h>

// #define M_PI  3.14157
using namespace std;

// display

Canvas cvs(800, 600, "Motifs drawing");

void flakeMotif(Canvas &cvs)
{

    // Move to the starting point.
    cvs.moveTo(0.0f, 5.0f);

    // Draw the flake motif using the Canvas's lineTo function.
    cvs.lineTo(20.0f, 5.0f);
    cvs.lineTo(30.0f, 25.0f);
    cvs.lineTo(35.0f, 18.0f);
    cvs.lineTo(25.0f, 5.0f);
    cvs.lineTo(30.0f, 5.0f);
    cvs.lineTo(45.0f, 15.0f);
    cvs.lineTo(50.0f, 13.0f);
    cvs.lineTo(35.0f, 5.0f);
    cvs.lineTo(55.0f, 5.0f);
    cvs.lineTo(60.0f, 0.0f);
}

void drawFlake()
{
    for (int i = 0; i < 6; i++)
    {
        flakeMotif(cvs);
        cvs.scale2D(1.0, -1.0);
        flakeMotif(cvs);
        cvs.scale2D(1.0, -1.0);
        cvs.rotate2D(60.0);
    }
}

void starmotif()
{

    cvs.moveTo(3.0f, 3.0f); // Move to the starting point
    cvs.lineTo(0.0f, 8.0f);
    cvs.lineTo(-3.0f, 0.0f);
    cvs.lineTo(-2.0f, -1.0f);
    cvs.lineTo(0.0f, 5.0f);
    cvs.lineTo(2.0f, 3.0f);
    cvs.lineTo(3.0f, 3.0f);
}

void drawStar()
{
    for (int i = 0; i < 5; i++)
    {
        starmotif();
        cvs.rotate2D(72.0);
    }
}

//>>>>>>>>>USE THIS DISPLAY FOR SNOWFLAKE<<<<<<<<<<<<<<
void display(void)
{
    cvs.setBackgroundColor(0.0, 0.0, 0.0); // background color is white
    cvs.clearScreen();                     // clear screen
    cvs.setColor(1.0, 0.0, 0.0);           // drawing color is red
    cvs.setWindow(-80.0, 80.0, -80.0, 80.0);
    cvs.setViewport(20, 580, 20, 580);

    drawFlake();
    glFlush();
} // end display

int main(int argc, char **argv)
{
    // the window is opened in the Canvas constructor
    glutDisplayFunc(display);
    glutMainLoop();
} // end main