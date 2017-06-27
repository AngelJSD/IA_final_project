#include <cstdlib>
#include <iostream>
#include <random>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "qlearning.hpp"

#define COLUMNS 10
#define ROWS 10
#define FPS 20

using namespace std;

int state, inix, iniy, goalx, goaly;
bool s;

void init(){

    glClearColor(0.0,0.0,0.0,1.0);
}

void cell(int x, int y){

    glLineWidth(1.0);
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
    glEnd();
}

void fillCell(int x, int y){

    glRectd(y,(COLUMNS-1)-x,y+1,(COLUMNS-1)-x+1);
}

void drawGrid(){

    glColor3f(1.0,0.0,0.0);
    fillCell(inix,iniy);
    glColor3f(0.0,1.0,0.0);
    fillCell(goalx,goaly);
    glColor3f(0.4,0.4,0.3);
    for(int i=0; i<obstacles.size(); ++i){
        fillCell(obstacles[i]/COLUMNS,obstacles[i]%COLUMNS);
    }

    for(int i=0; i<ROWS; ++i){
        
        for(int j=0; j<COLUMNS; ++j){

            cell(i,j);
        }
    }
    
}

void display_callback(){

    int x,y;
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    if(s){
        state=qlearning_step(state, COLUMNS*inix+iniy, COLUMNS*goalx+goaly);
        x=state/COLUMNS;
        y=state%COLUMNS;
        fillCell(x,y);
    }
    //cout<<"here"<<endl;
    glutSwapBuffers();
}

void reshape_callback(int w, int h){

    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int){

    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer_callback,0);
}

void myMouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
        cout<<x/(500/COLUMNS)<<","<<y/(500/COLUMNS)<<endl;
        setObstacle(y/(500/COLUMNS),x/(500/COLUMNS));
    }
    if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
        s=true;
}

int main(int argc, char** argv) {

    srand(time(NULL));
    s=false;
    inix=1;
    iniy=1;
    goalx=8;
    goaly=9;
    qini();
    state=COLUMNS*inix+iniy;
    setGoal(goalx, goaly);
    setStart(inix, iniy);
    /*setObstacle(4,4);
    setObstacle(5,4);
    setObstacle(4,5);
    setObstacle(5,5);*/
    /*for(int i=0; i<20; ++i){
        setRandObstacle();
    }*/

	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Grid");
    glutMouseFunc(myMouse);
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timer_callback,0);
    init();
    glutMainLoop();

	return 0;
}