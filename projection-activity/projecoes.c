#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void reshape(int w, int h);

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

static GLfloat vertices[27] = {
    0.0, 0.0, 30.0,          /* 0 */  // reorganizado: antes era o /* 4 */
    30.0, 0.0, 30.0,         /* 1 */  // reorganizado: antes era o /* 3 */
    // 30.0, 20.0, 30.0,     /* 2 */  // retirado
    // 20.0, 30.0, 30.0,     /* 3 */  // retirado
    0.0, 30.0, 30.0,         /* 4 */  // virou o /* 2 */ // e reorganizado: antes era o /* 1 */
    0.0, 30.0, 0.0,          /* 5 */  // virou o /* 3 */ 
    30.0, 30.0, 0.0,         /* 6 */  // virou o /* 4 */
    30.0, 0.0, 0.0,          /* 7 */  // virou o /* 5 */
    0.0, 0.0, 0.0,           /* 8 */  // virou o /* 6 */
    // 30.0, 30.0, 20.0,     /* 9 */  // retirado
    30.0, 30.0, 30.0,                            /* 7 */ // ponto "mergeado" do "defeito" que formava um triangulo entre os pontos 2, 3 e 9
    15.0, 45.0, 15.0,                            /* 8 */
};

/* Vertices do cubo */
static GLubyte frenteIndices[] = {2, 0, 1, 7};
static GLubyte trasIndices[] = {3, 4, 5, 6};
static GLubyte esquerdaIndices[] = {2, 3, 6, 0};
static GLubyte direitaIndices[] = {7, 1, 5, 4};
static GLubyte topoIndices[] = {2, 7, 4, 3}; 
static GLubyte fundoIndices[] = {1, 0, 6, 5};
// static GLubyte trianguloIndices[] = {1,2,9}; // triangulo retirado

/* Vertices da pirâmide */
static GLubyte frentePiramideIndices[] = {8, 2, 7};
static GLubyte trasPiramideIndices[] = {8, 4, 3};
static GLubyte esquerdaPiramideIndices[] = {8, 3, 2};
static GLubyte direitaPiramideIndices[] = {8, 7, 4};

static int eixoy, eixox;
int largura, altura;

int main(int argc, char **argv) {
    int i;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(256, 256);
    glutInitWindowPosition(100, 100);

    glutCreateWindow(argv[0]);

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    // funcao que detecta as setas do teclado para mover o desenho
    glutSpecialFunc(specialKeyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(-50, 50, -50, 50, -50, 50);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    largura = w;
    altura = h;
}

void display(void) {
    glPushMatrix();
    glRotatef((GLfloat)eixoy, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)eixox, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    /* Renderizacao cubo */

    glColor3f(AZUL); /* frente */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, frenteIndices);

    glColor3f(AMARELO); /* esquerda */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, esquerdaIndices);

    glColor3f(VERMELHO); /* tras */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, trasIndices);

    glColor3f(VERDE); /* direita */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, direitaIndices);

    glColor3f(CYAN); /* topo */
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, topoIndices);

    glColor3f(LARANJA); /* fundo */
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, fundoIndices);

    /* Renderizacao piramide */

    glColor3f(ROSEO); /* frente piramide */
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, frentePiramideIndices);

    glColor3f(CINZA); /* tras piramide */
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, trasPiramideIndices);

    glColor3f(LARANJA); /* esquerda piramide */
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, esquerdaPiramideIndices);

    glColor3f(CYAN); /* direita piramide */
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, direitaPiramideIndices);

    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'a':
            printf("%d, %d\n", x, y);
            break;
        case 'p':
            glLoadIdentity();
            gluPerspective(65.0, (GLfloat)largura / (GLfloat)altura, 20.0, 120.0);
            gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
            glutPostRedisplay();
            break;
        case 'o':
            glLoadIdentity();
            glOrtho(-50, 50, -50, 50, -50, 50);
            glutPostRedisplay();
            break;
    }
}

void specialKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            eixoy = (eixoy + 5) % 360;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            eixoy = (eixoy - 5) % 360;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            eixox = (eixox + 5) % 360;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            eixox = (eixox - 5) % 360;
            glutPostRedisplay();
            break;
    }
}