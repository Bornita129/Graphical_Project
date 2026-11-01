#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include<iostream>
using namespace std;

float waveOffset = 0.0f;
float boatX = -0.8f;


void drawSun()
{
    glColor3f(1.0f, 0.85f, 0.1f);

    glBegin(GL_POLYGON);
    for (int i = 0; i < 120; i++)
    {
        float angle = 2.0f * 3.1416f * i / 120;
        float x = 0.12f * cos(angle);
        float y = 0.12f * sin(angle);
        glVertex2f(x + 0.75f, y + 0.75f);
    }
    glEnd();
}

void drawCloud(float x, float y)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < 4; i++)
    {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 100; j++)
        {
            float angle = 2.0f * 3.1416f * j / 100;
            float cx = 0.06f * cos(angle);
            float cy = 0.045f * sin(angle);

            glVertex2f(cx + x + i * 0.055f, cy + y);
        }
        glEnd();
    }
}

void drawWaves()
{
    glLineWidth(3.0f);

    for (float y = -0.15f; y >= -1.0f; y -= 0.08f)
    {
        glBegin(GL_LINE_STRIP);

        for (float x = -1.0f; x <= 1.0f; x += 0.01f)
        {
            float wave =
                0.06f * sin(8 * x + waveOffset) +
                0.04f * sin(14 * x + waveOffset * 1.5);

            glColor3f(0.0f, 0.1f, 0.6f);
            glVertex2f(x, y + wave);
        }

        glEnd();
    }
}

void drawBoat(float x, float y)
{
    glColor3f(0.45f, 0.2f, 0.05f);

    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 0.35f, y);
        glVertex2f(x + 0.28f, y - 0.08f);
        glVertex2f(x + 0.07f, y - 0.08f);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
        glVertex2f(x + 0.17f, y);
        glVertex2f(x + 0.17f, y + 0.28f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x + 0.17f, y + 0.26f);
        glVertex2f(x + 0.17f, y);
        glVertex2f(x + 0.32f, y + 0.12f);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);


    glBegin(GL_QUADS);
        glColor3f(0.2f, 0.6f, 1.0f);
        glVertex2f(-1, 1);
        glVertex2f(1, 1);

        glColor3f(0.0f, 0.3f, 0.7f);
        glVertex2f(1, -1);
        glVertex2f(-1, -1);
    glEnd();

    drawSun();

    drawCloud(-0.7f, 0.75f);
    drawCloud(-0.1f, 0.65f);

    drawWaves();

    float boatY = -0.1f + 0.01f * sin(waveOffset * 2.0f);
    drawBoat(boatX, boatY);

    glutSwapBuffers();
}

void update(int value)
{
    waveOffset += 0.1f;
    boatX += 0.0025f;

    if (boatX > 1.2f)
        boatX = -1.2f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Visible Wave Ocean Scene");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
