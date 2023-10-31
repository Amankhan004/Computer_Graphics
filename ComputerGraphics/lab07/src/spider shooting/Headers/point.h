#define POINT2 1

#include <GL/glut.h>


class Point2
{
public:
    // constructor 1
    Point2();
    // constructor 2
    Point2(float xx, float yy);
    void set(float xx, float yy);
    float getX();
    float getY();
    void draw(void);

private:
    float x, y;
};

Point2::Point2()
{
    x = y = 0.0f;
}
// constructor 2
Point2::Point2(float xx, float yy)
{
    x = xx;
    y = yy;
}
void Point2::set(float xx, float yy)
{
    x = xx;
    y = yy;
}
float Point2::getX() { return x; }
float Point2::getY() { return y; }
void Point2::draw(void)
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
}