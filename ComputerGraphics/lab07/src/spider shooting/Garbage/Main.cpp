#include <GL/glut.h>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <string>
#include <ctime>
#include "pixMap.h"

using namespace std;

int screenWidth = 640;
int screenHeight = 480;
bool isUpKeyPressed = false;

class Point2
{
public:
    // constructor 1
    Point2()
    {
        x = y = 0.0f;
    }
    // constructor 2
    Point2(float xx, float yy)
    {
        x = xx;
        y = yy;
    }
    void set(float xx, float yy)
    {
        x = xx;
        y = yy;
    }
    float getX() { return x; }
    float getY() { return y; }
    void draw(void)
    {
        glPointSize(2.0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS); // draw this point
        glVertex2f((GLfloat)x, (GLfloat)y);
        glEnd();
        glDisable(GL_POINT_SMOOTH);
    } // end draw
private:
    float x, y;
};

class Spider
{
public:
    RGBApixmap pix[2];
    enum State
    {
        DIE
    } state;
    float pos_X, pos_Y;

public:
    bool isMoving;
    float spiderSpeed;
    float theta;
    float rateOfChange;

    Spider() {}

    Spider(Point2 pos)
    {
        isMoving = true;
        spiderSpeed = 2.0f; // Adjust spider's speed as needed
        theta = 0.0;
        rateOfChange = 1.0;
        this->pos_X = pos.getX();
        this->pos_Y = pos.getY();

        string fname[2] = {"Images/spider.bmp", "Images/mak3.bmp"}; // Replace with actual image filenames
        for (int i = 0; i < 2; i++)
        {
            pix[i].readBMPFile(fname[i], 1);
            pix[i].setChromaKey(192, 192, 192);
        }
    }

    void changePosition(float dx, float dy)
    {
        this->pos_X += dx;
        this->pos_Y += dy;
    }

    void die();
    void render();
};

void Spider::render()
{
    glRasterPos2f(this->pos_X, this->pos_Y);
    if (this->isMoving)
    {
        pix[0].mDraw();
    }
    else
    {
        pix[1].mDraw();
    }
}

class Bullet
{
public:
    float posX, posY;
    float speed;
    float size;

    Bullet(float x, float y, float bulletSpeed, float bulletSize)
        : posX(x), posY(y), speed(bulletSpeed), size(bulletSize) {}

    void update()
    {
        // Move the bullet upward (in the y-axis direction)
        cout << "posY: " << posY << endl;
        cout << speed << endl;
        posY += speed;
    }

    void render()
    {
        // Render the bullet as a triangle
        glColor3f(1.0, 0.0, 0.0); // Set the color to red (you can change it)
        glBegin(GL_TRIANGLES);
        glVertex2f(posX - size / 2.0, posY);             // Top vertex
        glVertex2f(posX + size / 2.0, posY);             // Right vertex
        glVertex2f(posX, posY + sqrt(3.0) * size / 2.0); // Bottom vertex
        glEnd();

        // Render the square below the triangle (polygon)
        glColor3f(0.0, 0.0, 1.0); // Set the color to blue (you can change it)
        glBegin(GL_QUADS);
        glVertex2f(posX - size / 4.0, posY - size / 2.0); // Bottom-left vertex
        glVertex2f(posX + size / 4.0, posY - size / 2.0); // Bottom-right vertex
        glVertex2f(posX + size / 4.0, posY - size);       // Top-right vertex
        glVertex2f(posX - size / 4.0, posY - size);       // Top-left vertex
        glEnd();
    }
};

Spider spider(Point2(0, 0));
Bullet bullet(0.0, 0.0, 5.0, 10.0); // Initial position, speed, and size

bool isSpiderMovingRandomly = false; // Indicates if the spider is currently moving randomly
clock_t lastRandomMoveTime;          // Time of the last random movement
const int randomMoveInterval = 2000; // Interval between random movements (milliseconds)
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Check if the up arrow key is pressed
    if (isUpKeyPressed)
    {
        bullet.update(); // Move the bullet upwards
    }

    // Update the spider's position
    if (isSpiderMovingRandomly)
    {
        clock_t currentTime = clock();
        if ((currentTime - lastRandomMoveTime) >= randomMoveInterval)
        {
            // Generate random movement distances for X and Y directions
            float deltaX = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) * 20.0f; // Adjust the range as needed
            float deltaY = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) * 20.0f; // Adjust the range as needed
            spider.changePosition(deltaX, deltaY);
            lastRandomMoveTime = currentTime;
        }
    }

    // Check if the spider is out of bounds, and change its direction if needed
    if (spider.pos_X < 0 || spider.pos_X > screenWidth)
    {
        // Reverse horizontal direction when hitting the screen boundary
        spider.theta += 3.14159;
    }
    if (spider.pos_Y < 0 || spider.pos_Y > screenHeight)
    {
        // Reverse vertical direction when hitting the screen boundary
        spider.theta += 3.14159;
    }

    // Render the spider and bullet
    spider.render();
    bullet.render();

    glutPostRedisplay();
    glutSwapBuffers();
}

void myKeyboard(int key, int x, int y)
{
    cout << "PRESSED myKeyboard" << endl;
    switch (key)
    {
    case GLUT_KEY_UP:
        isUpKeyPressed = true;
        break;
    }
}

void myKeyboardUp(int key, int x, int y)
{
    cout << "PRESSED myKeyboardUp" << endl;
    switch (key)
    {
    case GLUT_KEY_UP:
        isUpKeyPressed = false;
        break;
    }
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
    srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator

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

    isSpiderMovingRandomly = true; // Start spider's random movement
    lastRandomMoveTime = clock();

    glutMainLoop();
}
