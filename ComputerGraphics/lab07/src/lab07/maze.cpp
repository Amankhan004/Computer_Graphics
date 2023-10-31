#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define R 10 // Number of rows
#define C 10 // Number of columns

// Data structures to represent maze walls
char northWall[R][C];
char eastWall[R][C];
int grid[R][C];
// Mouse position
int mouseX, mouseY, mouseXcoor, mouseYcoor;

// Initialize maze with all walls intact
void initializeMaze()
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            grid[i][j] = 0;
            northWall[i][j] = 1; // All north walls are intact
            eastWall[i][j] = 1;  // All east walls are intact
        }
    }
}

// Function to draw the maze
void drawMaze()
{
    // Set the color for walls (black)
    glColor3f(0.0, 0.0, 0.0);
    // Draw vertical lines based on eastWall array
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (eastWall[i][j])
            {
                GLfloat x = j * 0.2 - 1.0;
                GLfloat y1 = 1.0 - i * 0.2;
                GLfloat y2 = y1 - 0.2;
                glBegin(GL_LINES);
                glVertex2f(x, y1);
                glVertex2f(x, y2);
                glEnd();
            }
        }
    }
    // Draw horizontal lines based on northWall array
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (northWall[i][j])
            {
                GLfloat x1 = j * 0.2 - 1.0;
                GLfloat x2 = x1 + 0.2;
                GLfloat y = 1.0 - i * 0.2;
                glBegin(GL_LINES);
                glVertex2f(x1, y);
                glVertex2f(x2, y);
                glEnd();
            }
        }
    }
}

// Function to move the mouse
void moveMouse(int x, int y)
{
    mouseXcoor = x;
    mouseYcoor = y;
}

// Function to eat through walls and connect cells
void eatWalls(int x, int y)
{
    // Choose a random direction (north or east)
    int direction = rand() % 2;
    grid[y][x] = 1;
    auto move = false;
    if (direction == 0 && y > 0)
    {
        // Move north and eat the north wall
        northWall[y][x] = 0;
        // mouseY = y - 1;
        move = !move;
        cout << "NORTH" << endl;
        grid[y - 1][x] = 1;
    }
    else if (x <= C - 1 || x == C - 1)
    {
        // Move east and eat the east wall
        eastWall[y][x] = 0;
        move = !move;
        cout << "EAST" << endl;
        grid[y][x - 1] = 1;
        // mouseX = x + 1;
    }
    int i = 0;
    while (grid[mouseY][mouseX] && move)
    {
        mouseX = rand() % R;
        mouseY = rand() % C;
        i++;
        cout << i << endl;
        if (i >= 100)
        {
            break;
        }
    }
    cout << "++++++++++++" << endl;
}

// Wrapper function for glutMouseFunc
void mouseWrapper(int button, int state, int x, int y)
{
    if (!state)
    {
        x = (mouseX * 40) + 1;
        y = (mouseY * 40) + 1;
        eatWalls(x / 40, y / 40); // Convert mouse coordinates to maze cell coordinates
    }
}

// Display callback function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Call the function to draw the maze
    drawMaze();

    // Draw the mouse as a small dot
    glColor3f(1.0, 0.0, 0.0); // Red color for the mouse
    glPointSize(5.0);         // Adjust the point size for the mouse
    glBegin(GL_POINTS);
    // cout << mouseX << "-" << mouseY << endl;
    glVertex2f(mouseX * 0.2 - 0.9, 0.9 - mouseY * 0.2);
    glEnd();
    glPointSize(1.0); // Reset point size

    glFlush();
}

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("OpenGL Maze with Mouse");

    // Set the display callback function
    glutDisplayFunc(display);

    // Set the clear color (white)
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the maze with all walls intact
    initializeMaze();

    // Place the mouse in a random cell
    mouseX = rand() % C;
    mouseY = rand() % R;

    // Register the mouse movement function
    glutPassiveMotionFunc(moveMouse);

    // Register the mouse click function using the wrapper
    glutMouseFunc(mouseWrapper);

    // Main loop
    glutMainLoop();

    return 0;
}