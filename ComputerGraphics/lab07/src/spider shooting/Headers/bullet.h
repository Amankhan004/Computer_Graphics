#define BULLET 1

#include "Headers.h"

class Bullet
{
public:
    float posX, posY;
    float speed;
    float size;
    bool fired;

    Bullet(float x, float y, float bulletSpeed, float bulletSize)
        : posX(x), posY(y), speed(bulletSpeed), size(bulletSize) {}

    void update()
    {
        // cout << "Forward" << endl;
        // Move the bullet upward (in the y-axis direction)
        posY += 2;//speed;
    }

    void reset()
    {
        // cout << "Reset" << endl;
        // Move the bullet upward (in the y-axis direction)
        posY = 15;
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
