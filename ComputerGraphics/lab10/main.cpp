#include <stdio.h>
#include <Windows.h>
#include <Gl/GLU.h>
#include <Gl/GL.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <GL/glut.h>

#define PI 3.141592

float planeX = 245.0f;     // Initial X position of the plane
float planeY = 230.0f;     // Initial Y position of the plane
bool planeCrashed = false; // Flag to indicate if the plane has crashed

void display(void);      // draw everything
void drawWind(void);     // draw single blade
void drawwindmill(void); // complete this to complete windmill i.e. call drawWind() in it
void drawplane();        // work in this function for crash landing of plane i.e. animate and collision with land
void drawlandscape();    // do nothing with it
void Timer(int value);   // update variable for animation here
void keyboard(unsigned char key, int x, int y);
void init(void);
void reshape(GLsizei w, GLsizei h);

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawlandscape();
    drawplane();
    drawwindmill();
    glutSwapBuffers();
}

void drawWind()
{
    static float current_angle = 0.0f;
    const float step_angle = 05.50f;
    const float center_x = 125.0f; // Adjust these values as needed
    const float center_y = 90.0f;

    glPushMatrix();

    // Translate to the center point
    glTranslatef(center_x, center_y, 0.0f);

    // Rotate around the center point
    glRotatef(current_angle, 0, 0, 1);
    current_angle += step_angle;

    // Translate back to the original position
    glTranslatef(-center_x, -center_y, 0.0f);

    // Define the blade coordinates as an array of endpoints
    float bladeCoordinates[4][6] = {
        {125.0, 90.0, 115.0, 125.0, 135.0, 125.0}
    };

    for (int i = 0; i < 4; ++i)
    {
        glPushMatrix();
        glTranslatef(center_x, center_y, 0.0f);
        glRotatef(i * 90.0, 0.0, 0.0, 1.0); // Rotate by 90 degrees clockwise around the Z-axis
        glTranslatef(-center_x, -center_y, 0.0f);
        glBegin(GL_TRIANGLES);
        glColor3f(0.8, 0.8, 0.8);
        // Loop through the blade coordinates and draw each blade
        glVertex2f(bladeCoordinates[0][0], bladeCoordinates[0][1]);
        glVertex2f(bladeCoordinates[0][2], bladeCoordinates[0][3]);
        glVertex2f(bladeCoordinates[0][4], bladeCoordinates[0][5]);
        glEnd();
        glPopMatrix();
    }

    glPopMatrix();
}

void drawwindmill()
{
    drawWind();
}

void Timer(int value)
{
    if (!planeCrashed)
    {
        // Update plane position (move it downward)
        planeY -= 1.0;
        planeX -= 1.0;

        // Check for collision with the ground (grass)
        if (planeY < 50.0)
        {
            planeCrashed = true;
            printf("Plane crashed!\n");
        }
    }

    // Redraw the scene
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 1);
}

void drawplane()
{
    /* Draw a plane */
    glBegin(GL_TRIANGLES);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(planeX, planeY);
    glVertex2f(planeX, planeY + 10.0); // Increase Y to simulate the plane descending
    glVertex2f(planeX - 30.0, planeY); // Move the plane to the left

    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(planeX - 1.0, planeY - 2.0);
    glVertex2f(planeX - 1.0, planeY + 5.0);  // Increase Y to simulate the plane descending
    glVertex2f(planeX - 17.0, planeY + 5.0); // Move the plane to the left

    glEnd();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("BSCS 514 Lab #8");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(5, Timer, 1);
    glutMainLoop();
}

void drawlandscape()
{
    /* Draw a box of grass */
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(250.0, 0.0);
    glColor3f(0.0, 0.9, 0.0);
    glVertex2f(250.0, 50.0);
    glColor3f(0.0, 0.8, 0.0);
    glVertex2f(0.0, 50.0);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2f(0.0, 0.0);
    glEnd();

    /* An attempt at a few snow covered mountains */

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.6);
    glVertex2f(250.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(200.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(150.0, 50.0);

    // glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(200.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(150.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);

    glColor3f(0.0, 0.0, 0.7);
    glVertex2f(150.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(100.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(50.0, 50.0);

    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(50.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(0.0, 50.0);

    glEnd();

    /* Draw the body of a windmill */
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.0);
    glVertex2f(145.0, 50.0);
    glVertex2f(135.0, 100.0);
    glVertex2f(115.0, 100.0);
    glVertex2f(105.0, 50.0);
    glEnd();
}

void init()
{
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}
