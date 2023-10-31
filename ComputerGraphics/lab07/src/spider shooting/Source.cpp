
#include <stdlib.h>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <Windows.h>
#include <random>
#include <stdio.h>
#include <math.h>
#include <string>
#include <MMSystem.h>
// #include "Headers/pixMap.h"
// #include "Headers/point.h"
// #include "Headers/spider.h"
#include "Headers/Headers.h"

using namespace std;

std::random_device rd;  // Seed the random number generator
std::mt19937 gen(rd()); // Mersenne Twister pseudo-random generator
std::uniform_int_distribution<int> distribution(0.1, 1);

int screenWidth = 640;
int screenHeight = 480;
bool isUpKeyPressed = false;
bool fired = false;

int xP = 0;
int yP = 0;
int xM = 1;
int yM = 1;

Spider spider(Point2(0, 0));
Bullet bullet(0.0, 0.0, 5.0, 10.0); // Initial position, speed, and size

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Check if the up arrow key is pressed
    if (fired)
    {
        if (bullet.posY >= screenHeight)
        {
            bullet.reset();
            fired = false;
        }
        else if ((bullet.posY > spider.pos_Y && bullet.posY < spider.pos_Y + spider.pix[0].nRows) && (bullet.posX > spider.pos_X && bullet.posX < spider.pos_X + spider.pix[0].nCols))
        {
            fired = false;
            spider.isMoving = false;
        }
        else
        {
            bullet.update(); // Move the bullet upwards
        }
    }

    // Update the spider's position
    // spider.changePosition(spider.spiderSpeed * cos(spider.theta) * 10,
    //                       spider.spiderSpeed * cos(spider.theta) * 10);

    xP = distribution(gen) * xM;
    yP = distribution(gen) * yM;

    if (spider.pos_X > screenWidth || spider.pos_Y > screenHeight)
    {
        spider.resetPosition();
    }
    else if (!spider.isMoving)
    {
        PlaySoundA("Audio/music.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    }
    else
    {
        spider.changePosition(xP, yP);
    }
    // Check if the spider is out of bounds, and change its direction if needed

    if (spider.pos_X < 0 || spider.pos_X > screenWidth - spider.pix[0].nCols - 30)
    {
        // cout << "X reversed" << endl;
        xM = xM * -1;
    }
    else if (spider.pos_Y < 0 || spider.pos_Y > screenHeight - spider.pix[0].nRows)
    {
        // cout << "Y reversed" << endl;
        yM = yM * -1;
    }

    // Render the spider and bullet
    spider.render();
    bullet.render();

    glutPostRedisplay();
    glutSwapBuffers();
}

void myKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        PlaySoundA("shoot/music.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
        fired = true;
        isUpKeyPressed = true;
        break;

    case GLUT_KEY_F10:
        if (!spider.isMoving)
        {
            bullet.reset();
            spider.restart(Point2(0, 0));
            break;
        }
    }
}

void myKeyboardUp(int key, int x, int y)
{
    // switch (key)
    // {
    // case GLUT_KEY_UP:
    //     fired = false;
    //     isUpKeyPressed = false;
    //     break;
    // }
}

void myInit(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_EQUAL, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Spider Game");
    glutSpecialFunc(myKeyboard);
    glutSpecialUpFunc(myKeyboardUp);

    // Calculate the initial position to center the spider
    float initialX = (screenWidth - spider.pix[0].nCols) / 2.0f;
    float initialY = (screenHeight - spider.pix[0].nRows) / 2.0f;

    // Initialize the Spider object with the new initial position
    spider = Spider(Point2(initialX, initialY));

    // Initialize the Bullet object below the spider
    float bulletX = initialX + spider.pix[0].nCols / 2.0f; // Place bullet at the center of the spider
    float bulletY = initialY - spider.pix[0].nRows - bullet.size - 120.0f;
    bullet = Bullet(bulletX, bulletY, 5.0, 10.0); // Initial position, speed, and size

    glutDisplayFunc(myDisplay);
    myInit();

    glutMainLoop();
}
