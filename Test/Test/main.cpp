#include "includes.h"

//#pragma comment(lib,"glut32.lib")

#define COUNT 100.0 
#define COUNT2 5.0

using namespace std;
int IsPause = 0;
double SyncTime, DeltaTime, FPS, angle = 0;
background b;



void Idle(void)
{
    static long ltime = -1;
    long ctime = clock();
    double dtime;
    dtime = (double)(ctime - ltime) / CLOCKS_PER_SEC;

    if (dtime > 0.02)
    {
        ltime = ctime;
    }
}

void Display(void)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3d(0, 0, 0);
    
    b.draw(1);

    glutPostRedisplay();
    glFinish();
    glutSwapBuffers();
} /* End */

void Keyboard(unsigned char Key, int X, int Y)
{
    if (Key == 27)
        exit(0);
} /* End */

/* Resize window hanlde function */
void Reshape(int W, int H)
{
    double s = 0.1, rx = s, ry = s;

    if (W >= H)
        rx *= (double)W / H;
    else
        ry *= (double)H / W;

    //glViewport(0, 0, W, H);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glFrustum(-rx, rx, -ry, ry, s, 1000);
    //gluLookAt(0, -1, 0, 0, 10, 0, 0, 0, 1);
    //glMatrixMode(GL_MODELVIEW);
} /* End of 'Reshape' function */

void main(int argc, char* argv[])
{
    float pos1[4] = { 0, 0.2, 0, 0.1 };
    float pos[4] = { 0, 0, 0, 0.1 };

    /* GLUT library init */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    // glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    /* Create work window */
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("LIFE!!!");


    glutFullScreen();
    // glutMouseFunc(Mouse);

    b.load_texture("a.bmp");

    glutDisplayFunc(Display);
    glutIdleFunc(Idle);
    glutKeyboardFunc(Keyboard);
    glutReshapeFunc(Reshape);
    // glutDisplayFunc(Display);
    // glutIdleFunc(Idle);
    // glutKeyboardFunc(Keyboard);
    // glutReshapeFunc(Reshape);

    /* OpenGL setup */
    glClearColor(0.3, 0.7, 0.5, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glutMainLoop();
} /* End */

