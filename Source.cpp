#include <GL/glut.h>

int xc = 0, yc = 0;
bool shouldDrawCircle = false;  

void plotCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

void drawCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int d = 1 - r;  

    plotCirclePoints(xc, yc, x, y);  

    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;  
        }
        else {
            d += 2 * (x - y) + 5;  
            y--;
        }
        x++;
        plotCirclePoints(xc, yc, x, y);  
    }
}

void drawAxes() {
    glBegin(GL_LINES);
    // X-axis
    glVertex2i(-200, 0);
    glVertex2i(200, 0);
    // Y-axis
    glVertex2i(0, -200);
    glVertex2i(0, 200);
    glEnd();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        xc = x - 200;  
        yc = 200 - y;  
        shouldDrawCircle = true;  
        glutPostRedisplay();  
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);  
    drawAxes();

    if (shouldDrawCircle) {
        glColor3f(1.0, 1.0, 0.0);  
        drawCircle(xc, yc, 50);  
    }

    glFlush();  
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); 
    gluOrtho2D(-200, 200, -200, 200);  
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Click to Draw Circle in OpenGL");
    init();
    glutDisplayFunc(display); 
    glutMouseFunc(mouse);  
    glutMainLoop();  
    return 0;
}
