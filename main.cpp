#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

int qtdObjects = 1;
int selectedObj = 25;
typedef struct{
    float x;
    float y;
} Objeto;

vector<Objeto*> objetos;


void mouse(int button, int state, int mousex, int mousey)
{

    int coord_x = mousex;
    int coord_y = 400 - mousey;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        printf("%d\n", (int)objetos.size());
        printf("%d\n", coord_x);
        printf("%d\n", coord_y);
        printf("%f\n", objetos[1]->x);
        printf("%f\n", objetos[1]->y);
        for (int i = 0; i < (int)objetos.size(); i++) {
            printf((coord_x+25>=objetos[i]->x&&coord_x-25<=objetos[i]->x) ? "true" : "false");
            printf((coord_y+25>=objetos[i]->y&&coord_y-25<=objetos[i]->y) ? "true" : "false");
            printf((coord_x+25>=objetos[i]->x&&coord_x-25<=objetos[i]->x)&&(coord_y+25>=objetos[i]->y&&coord_y-25<=objetos[i]->y) ? "true" : "false");
            if((coord_x+25>=objetos[i]->x&&coord_x-25<=objetos[i]->x)&&(coord_y+25>=objetos[i]->y&&coord_y-25<=objetos[i]->y)){
                selectedObj = i;
            }
        }
    }
    glutPostRedisplay();
}

void tecladoSpecial(int key, int x, int y){
    switch(key){
    case GLUT_KEY_LEFT:
        if(objetos[selectedObj]->x != 25){
            for (int i = 0; i < (int)objetos.size(); i++) {
                if(i != selectedObj){
                    if((objetos[selectedObj]->x - 50 == objetos[i]->x) && (objetos[selectedObj]->y == objetos[i]->y)){
                        break;
                    }else{
                        objetos[selectedObj]->x -= 50;
                    }
                }

            }
            break;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(objetos[selectedObj]->x != 375){

            for (int i = 0; i < objetos.size(); i++) {
                if(i != selectedObj){
                    if((objetos[selectedObj]->x + 50 == objetos[i]->x) && (objetos[selectedObj]->y == objetos[i]->y)){
                        break;
                    }else{
                        glTranslatef(-50,0,1);

                        objetos[selectedObj]->x += 50;
                    }
                }

            }
            break;
        }
        break;
    case GLUT_KEY_DOWN:
        if(objetos[selectedObj]->y != 25){

            for (int i = 0; i < (int)objetos.size(); i++) {
                if(i != selectedObj){
                    if((objetos[selectedObj]->y - 50 == objetos[i]->y) && (objetos[selectedObj]->x == objetos[i]->x)){
                        break;
                    }else{
                        objetos[selectedObj]->y -= 50;
                    }
                }

            }
            break;
        }
        break;
    case GLUT_KEY_UP:
        if(objetos[selectedObj]->y != 375){

            for (int i = 0; i < (int)objetos.size(); i++) {
                if(i != selectedObj){
                    if((objetos[selectedObj]->y + 50 == objetos[i]->y) && (objetos[selectedObj]->x == objetos[i]->x)){
                        break;
                    }else{
                        objetos[selectedObj]->y += 50;
                    }
                }

            }
            break;
        }
        break;
    }
    glutPostRedisplay();
}
void desenhaCirculo(int x, int y, int cor = 3){

    switch (cor) {
    case 0:
        glColor3f(1.0,0.0,0.0);
        break;
    case 1 :
        glColor3f(0.0,1.0,0.0);
        break;
    case 2:
        glColor3f(0.0,0.0,1.0);
        break;
    case 3:
        glColor3f(0.8,0.3,0.7);
        break;
    default:
        glColor3f(0.8,0.3,0.1);
        break;
    }

    float radius = 15.0;
    int qtdTriangulos = 20;
    GLfloat dobroPi = 2.0f * M_PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= qtdTriangulos;i++) {
        glVertex2f(
                    x + (radius * cos(i *  dobroPi / qtdTriangulos)),
                    y + (radius * sin(i * dobroPi / qtdTriangulos))
                    );
    }
    glEnd();

}
void desenhaQuadrado(int x, int y){
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x, y + 50);
    glVertex2i(x + 50, y + 50);
    glVertex2i(x + 50, y);
    glEnd();
}
void myDisplay(void)
{
    bool isBlack = false;
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,800,0,400);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int x = 0; x < 400; x+=50)
    {

        for (int y = 0; y <= 400; y+=50)
        {
            if (isBlack)
            {
                glColor3f(0.0,0.0,0.0);
                isBlack = false;
            }
            else
            {
                glColor3f(1.0,1.0,1.0);
                isBlack = true;
            }
            desenhaQuadrado(x,y);
        }

    }

    /*glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(50, 0);
    glVertex2i(50, -50);
    glVertex2i(0, -50);
    glEnd();*/
    desenhaCirculo(objetos[0]->x,objetos[0]->y);
    desenhaCirculo(objetos[1]->x,objetos[1]->y,0);
    glFlush();

}


void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    Objeto *camera = new Objeto;
    camera->x = 25;
    camera->y = 375;
    objetos.push_back(camera);
    Objeto *objInicial = new Objeto;
    objInicial->x = 325;
    objInicial->y = 225;
    objetos.push_back(objInicial);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(800,400);
    glutCreateWindow("Janela");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse);
    glutSpecialFunc(tecladoSpecial);
    glutMainLoop();
    return 0;
}