

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <math.h>
#include <limits> 
#include <iostream>   
#include <algorithm>   


#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaders.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "solver.h"
#define G180 3.14159265358979323846
#define G90  1.57079632679489661923
int flagTecla = -1;
int mouseoldx, mouseoldy ;
float timeOffsetTecla;
int piezaSeleccionada = -1;
int cubeType=2;
GLfloat radY = 0.75;
GLfloat radX = 0.75;
GLfloat rEye = 5.0;
GLfloat radYUp = 0;
GLfloat radXUp = G90;
GLfloat anguloUp = 0;
GLuint vertexshader, fragmentshader, shaderprogram ;
GLuint projectionPos, modelviewPos, objectPos;
glm::mat4 projection, modelview; 
glm::mat4 identity(1.0f);
/***************   BASIC SET UP FOR DRAWING OBJECTS ***********************/
glm::vec3 eye, center, up;
const int numobjects = 21 ; 
const int numperobj  = 3 ; // Vertices, colors, indices
GLuint VAOs[numobjects]; // A VAO for each object
GLuint buffers[9] ; // List of buffers for geometric data 
GLuint buffersEtiquetas[4 * 18]; // List of buffers for geometric data 

GLuint objects[numobjects] ; // For each object
GLenum PrimType[numobjects] ; // Primitive Type (quads, polygons etc.)
GLsizei NumElems[numobjects] ; // Number of geometric elements

GLuint textures[54];
GLuint texturaNula;

std::vector <glm::mat4> modelviewStack;

// Floor Geometry is specified with a vertex array

enum { ejeX, ejeY, ejeZ };
enum {Vertices, Colors, Elements} ; // For arrays for object 
enum { BLANCO, ROJO, AZUL,NARANJA,VERDE,AMARILLO };
enum {CENTRO, ARISTA, VERTICE,
    ETIQUETA_BL1, ETIQUETA_RO1, ETIQUETA_AZ1, ETIQUETA_NA1, ETIQUETA_VE1, ETIQUETA_AM1,
    ETIQUETA_BL2, ETIQUETA_RO2, ETIQUETA_AZ2, ETIQUETA_NA2, ETIQUETA_VE2, ETIQUETA_AM2,
    ETIQUETA_BL3, ETIQUETA_RO3, ETIQUETA_AZ3, ETIQUETA_NA3, ETIQUETA_VE3, ETIQUETA_AM3} ; // For objects, for the floor





const GLfloat verticesCentro[12][3] = {
  {0.2, 0.195, 0.2}, {0.2, 0.195, -0.0}, {-0.0, 0.195, -0.0}, {-0.0, 0.195, 0.2},
  {0.2, -0.0, 0.2}, {0.2, -0.0, -0.0}, {-0.0, -0.0, -0.0}, {-0.0, -0.0, 0.2},
  //cara superior
  {0.185, 0.2, 0.185}, {0.185, 0.2, 0.015}, {0.015, 0.2, 0.015}, {0.015, 0.2, 0.185}
};
const GLfloat coloresCentro[16][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
  //cara superior
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
};
const GLubyte indicesCentro[1][54] = { 
    {0,4,1,4,1,5, 1,5,2,5,2,6,  2,6,3,6,3,7,    3,7,0,7,0,4,   4,5,6,4,6,7, 
    0,8,1,8,1,9, 1,9,2,9,2,10, 2,10,3,10,3,11, 3,11,0,11,0,8} 
};

const GLfloat verticesArista[16][3] = {
  {0.2, 0.195, 0.195}, {0.2, 0.195, -0.0}, {-0.0, 0.195, -0.0}, {-0.0, 0.195, 0.195},
  {0.2, -0.0, 0.195}, {0.2, -0.0, -0.0}, {-0.0, -0.0, -0.0}, {-0.0, -0.0, 0.195},
  //cara superior
  {0.185, 0.2, 0.185}, {0.185, 0.2, 0.015}, {0.015, 0.2, 0.015}, {0.015, 0.2, 0.185},
  //cara frontal
  {0.185, 0.185, 0.2}, {0.185, 0.015, 0.2}, {0.015, 0.015, 0.2}, {0.015, 0.185, 0.2}
};
const GLfloat coloresArista[16][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
  //cara superior
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
  //cara frontal
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
};
const GLubyte indicesArista[1][72] = {
    {0,4,1,4,1,5, 1,5,2,5,2,6,  2,6,3,6,3,7,   4,5,6,4,6,7,
    0,8,1,8,1,9, 1,9,2,9,2,10, 2,10,3,10,3,11, 3,11,0,11,0,8,
    0,12,4,12,4,13, 4,13,7,13,7,14, 7,14,3,14,3,15, 3,15,0,15,0,12}
};

const GLfloat verticesVertice[20][3] = {
  {0.195, 0.195, 0.195}, {0.195, 0.195, 0.0}, {0.0, 0.195, 0.0}, {0.0, 0.195, 0.195},
  {0.195, 0.0, 0.195}, {0.195, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.195},
  //cara superior
  {0.185, 0.2, 0.185}, {0.185, 0.2, 0.015}, {0.015, 0.2, 0.015}, {0.015, 0.2, 0.185},
  //cara frontal
  {0.185, 0.185, 0.2}, {0.185, 0.015, 0.2}, {0.015, 0.015, 0.2}, {0.015, 0.185, 0.2},
  //cara lateral
  {0.2, 0.185, 0.185}, {0.2, 0.185, 0.015}, {0.2,0.015, 0.015}, {0.2, 0.015, 0.185}
};
const GLfloat coloresVertice[20][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
  //cara superior
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
  //cara frontal
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0},
  //cara lateral
  {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}
};
const GLubyte indicesVertice[1][90] = {
    { 1,5,2,5,2,6,  2,6,3,6,3,7,   4,5,6,4,6,7,
    0,8,1,8,1,9, 1,9,2,9,2,10, 2,10,3,10,3,11, 3,11,0,11,0,8,
    0,12,4,12,4,13, 4,13,7,13,7,14, 7,14,3,14,3,15, 3,15,0,15,0,12,
    0,16,1,16,1,17, 1,17,5,17,5,18, 5,18,4,18,4,19, 4,19,0,19,0,16}
};
 
const GLfloat verticesEtiquetaUp[4][3] = {
  {0.185, 0.2, 0.185}, {0.185, 0.2, 0.015}, {0.015, 0.2, 0.015}, {0.015, 0.2, 0.185}
};
const GLfloat verticesEtiquetaFront[4][3] = {
  {0.185, 0.185, 0.2}, {0.185, 0.015, 0.2}, {0.015, 0.015, 0.2}, {0.015, 0.185, 0.2}
};
const GLfloat verticesEtiquetaLat[4][3] = {
  {0.2, 0.185, 0.185}, {0.2, 0.185, 0.015}, {0.2, 0.015, 0.015}, {0.2, 0.015, 0.185}
};

const GLfloat texturasEtiqueta[4][2]{
    {0.925, 0.925}, {0.925, 0.075}, {0.075, 0.075}, {0.075, 0.925}
};

//blanco,rojo,azul,naranja,verde,amarillo
const GLfloat coloresEtiquetaBlanco[4][3] = {
  {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0}
};
const GLfloat coloresEtiquetaRojo[4][3] = {
  {0.7255,0.0,0.0}, {0.7255,0.0,0.0}, {0.7255,0.0,0.0}, {0.7255,0.0,0.0}
};
const GLfloat coloresEtiquetaAzul[4][3] = {
  {0.0,0.2745,0.7255}, {0.0,0.2745,0.7255}, {0.0,0.2745,0.7255}, {0.0,0.2745,0.7255}
};
const GLfloat coloresEtiquetaNaranja[4][3] = {
  {1.0,0.3529,0.0}, {1.0,0.3529,0.0}, {1.0,0.3529,0.0}, {1.0,0.3529,0.0}
};
const GLfloat coloresEtiquetaVerde[4][3] = {
  {0.0,0.6078,0.2745}, {0.0,0.6078,0.2745}, {0.0,0.6078,0.2745}, {0.0,0.6078,0.2745}
};
const GLfloat coloresEtiquetaAmarillo[4][3] = {
  {1.0,0.8353,0.0}, {1.0,0.8353,0.0}, {1.0,0.8353,0.0}, {1.0,0.8353,0.0}
};
const GLubyte indicesEtiqueta[1][6] = {
    {0,1,2,0,2,3}
};


void pushMatrix(glm::mat4 mat) {
    modelviewStack.push_back(glm::mat4(mat));
}

// This function pops a matrix from the modelview stack and assigns that to the matrix passed in
void popMatrix(glm::mat4& mat) {
    if (modelviewStack.size()) {
        mat = glm::mat4(modelviewStack.back());
        modelviewStack.pop_back();
    }
    else { // Just to prevent an unwanted error
        mat = glm::mat4(1.0f);
    }
}

struct Piezas {
    short type;//0 centro, 1 arista, 3 vertice
    short color[3];//0 blanco,1 rojo,2 azul,3 naranja,4 verde,5 amarillo
    bool flagTextura;
    short iTextura[3];
    glm::mat4 transformation;
    Piezas(int i = 0) {
        flagTextura = 0;
        type = -1;
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        iTextura[0] = 0;
        iTextura[1] = 0;
        iTextura[2] = 0;
    }
    /*Piezas(short t,short i,short c1, short c2=0, short c3=0){
        flagTextura = 0;
        iTextura[0] = 0;
        iTextura[1] = 0;
        iTextura[2] = 0;
        type = t;
        color[0] = c1;
        color[1] = c2;
        color[2] = c3;
        if (t == 0) {
            //transformation = glm::translate(identity, glm::vec3(0.0, 0.2, 0.0));
            transformation = glm::translate(identity, glm::vec3(-0.1, 0.1, -0.1));
            if (i == 1)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0)) * transformation;
            else if (i == 2)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0)) * transformation;
            else if (i == 3)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, 1.0)) * transformation;
            else if(i == 4)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(-1.0, 0.0, 0.0)) * transformation;
            else if(i == 5 )
                transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 0.0, 1.0)) * transformation;
        }else if (t == 1) {
            //transformation = glm::translate(identity, glm::vec3(0.0, 0.2, 0.2));
            transformation = glm::translate(identity, glm::vec3(-0.1, 0.1, 0.1));
            int flag = 1;
            if (i > 7) {
                transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 0.0, 1.0)) * transformation;
            }
            else if (i > 3) {
                flag = -1;
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0)) * transformation;
            }
            if(i%4==1)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, flag*1.0, 0.0)) * transformation;
            else if (i % 4 == 2)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, flag * -1.0, 0.0)) * transformation;
            else if (i % 4 == 3)
                transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 1.0, 0.0)) * transformation;
        }else if (t == 2) {
            //transformation = glm::translate(identity, glm::vec3(0.2, 0.2, 0.2));
            transformation = glm::translate(identity, glm::vec3(0.1, 0.1, 0.1));
            if(i>3)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0)) * transformation;
            if (i % 4 == 1)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, -1.0, 0.0)) * transformation;
            else if (i % 4 == 2)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 1.0, 0.0)) * transformation;
            else if (i % 4 == 3)
                transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 1.0, 0.0)) * transformation;
        }
    }*/
    //Constructor para hacer un mirror
    Piezas(int flagMirror, short t, short i, short c1, short c2 = -1, short c3 = -1) {
        type = t;
        color[0] = c1;
        color[1] = std::max(c2, (short)0);
        color[2] = std::max(c3, (short)0);
        flagTextura = 0;
        iTextura[0] = 0;
        iTextura[1] = 0;
        iTextura[2] = 0;
        if (!flagMirror) {
            if (t == 0) {
                //transformation = glm::translate(identity, glm::vec3(0.0, 0.2, 0.0));
                transformation = glm::translate(identity, glm::vec3(-0.1, 0.1, -0.1));
                if (i == 1)
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0)) * transformation;
                else if (i == 2)
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0)) * transformation;
                else if (i == 3)
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, 1.0)) * transformation;
                else if (i == 4)
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(-1.0, 0.0, 0.0)) * transformation;
                else if (i == 5)
                    transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 0.0, 1.0)) * transformation;
            }
            else if (t == 1) {
                //transformation = glm::translate(identity, glm::vec3(0.0, 0.2, 0.2));
                transformation = glm::translate(identity, glm::vec3(-0.1, 0.1, 0.1));
                int flag = 1;
                if (i > 7) {
                    transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 0.0, 1.0)) * transformation;
                }
                else if (i > 3) {
                    flag = -1;
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0)) * transformation;
                }
                if (i % 4 == 1)
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, flag * 1.0, 0.0)) * transformation;
                else if (i % 4 == 2)
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, flag * -1.0, 0.0)) * transformation;
                else if (i % 4 == 3)
                    transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 1.0, 0.0)) * transformation;
            }
            else if (t == 2) {
                //transformation = glm::translate(identity, glm::vec3(0.2, 0.2, 0.2));
                transformation = glm::translate(identity, glm::vec3(0.1, 0.1, 0.1));
                if (i > 3)
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0)) * transformation;
                if (i % 4 == 1)
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, -1.0, 0.0)) * transformation;
                else if (i % 4 == 2)
                    transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 1.0, 0.0)) * transformation;
                else if (i % 4 == 3)
                    transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 1.0, 0.0)) * transformation;
            }
            return;
        }
        if (c1 == 3)
            c1 = 4;
        else if (c1 == 4)
            c1 = 3;
        if (c2 == 3)
            c2 = 4;
        else if (c2 == 4)
            c2 = 3;
        if (c3 == 3)
            c3 = 4;
        else if (c3 == 4)
            c3 = 3;
        transformation = glm::scale(identity, glm::vec3(1.0, (float)(c1 + 1) / 3.5, 1.0));
        if (c2 >= 0)
            transformation = glm::scale(transformation, glm::vec3(1.0, 1.0, (float)(c2 + 1) / 3.5));
        if (c3 >= 0)
            transformation = glm::scale(transformation, glm::vec3((float)(c3 + 1) / 3.5, 1.0, 1.0));
        if (t == 0) {
            //transformation = glm::translate(identity, glm::vec3(0.0, 0.2, 0.0));
            transformation = glm::translate(identity, glm::vec3(-0.1, 0.1, -0.1)) * transformation;
            if (i == 1)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0)) * transformation;
            else if (i == 2)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0)) * transformation;
            else if (i == 3)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, 1.0)) * transformation;
            else if (i == 4)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(-1.0, 0.0, 0.0)) * transformation;
            else if (i == 5)
                transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 0.0, 1.0)) * transformation;
        }
        else if (t == 1) {
            //transformation = glm::translate(identity, glm::vec3(0.0, 0.2, 0.2));
            transformation = glm::translate(identity, glm::vec3(-0.1, 0.1, 0.1)) * transformation;
            int flag = 1;
            if (i > 7) {
                transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 0.0, 1.0)) * transformation;
            }
            else if (i > 3) {
                flag = -1;
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0)) * transformation;
            }
            if (i % 4 == 1)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, flag * 1.0, 0.0)) * transformation;
            else if (i % 4 == 2)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, flag * -1.0, 0.0)) * transformation;
            else if (i % 4 == 3)
                transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 1.0, 0.0)) * transformation;
        }
        else if (t == 2) {
            //transformation = glm::translate(identity, glm::vec3(0.2, 0.2, 0.2));
            transformation = glm::translate(identity, glm::vec3(0.1, 0.1, 0.1)) * transformation;
            if (i > 3)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0)) * transformation;
            if (i % 4 == 1)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, -1.0, 0.0)) * transformation;
            else if (i % 4 == 2)
                transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 1.0, 0.0)) * transformation;
            else if (i % 4 == 3)
                transformation = glm::rotate(identity, (float)G180, glm::vec3(0.0, 1.0, 0.0)) * transformation;
        }
    }
    void setTextures(int i1,int i2=0,int i3=0) {
        flagTextura = 1;
        iTextura[0] = i1;
        iTextura[1] = i2;
        iTextura[2] = i3;
    }
    void draw(){
        if (type == -1)
            return;
        pushMatrix(modelview);
        modelview = modelview * transformation;
        glBindTexture(GL_TEXTURE_2D, texturaNula);
        glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
        glBindVertexArray(VAOs[type]);
        glDrawElements(PrimType[type], NumElems[type], GL_UNSIGNED_BYTE, 0);
        if (flagTextura) {
            glBindTexture(GL_TEXTURE_2D, textures[color[0] * 9 + iTextura[0]]);
            glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
            glBindVertexArray(VAOs[3]);
            glDrawElements(PrimType[3], NumElems[3], GL_UNSIGNED_BYTE, 0);
            if (type) {
                glBindTexture(GL_TEXTURE_2D, textures[color[1] * 9 + iTextura[1]]);
                glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
                glBindVertexArray(VAOs[9]);
                glDrawElements(PrimType[9], NumElems[9], GL_UNSIGNED_BYTE, 0);
                if (type == 2) {
                    glBindTexture(GL_TEXTURE_2D, textures[color[2] * 9 + iTextura[2]]);
                    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
                    glBindVertexArray(VAOs[15]);
                    glDrawElements(PrimType[15], NumElems[color[2] + 15], GL_UNSIGNED_BYTE, 0);
                }
            }
        }
        else {
            glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
            glBindVertexArray(VAOs[color[0] + 3]);
            glDrawElements(PrimType[color[0] + 3], NumElems[color[0] + 3], GL_UNSIGNED_BYTE, 0);
            if (type) {
                glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
                glBindVertexArray(VAOs[color[1] + 9]);
                glDrawElements(PrimType[color[1] + 9], NumElems[color[1] + 9], GL_UNSIGNED_BYTE, 0);
                if (type == 2) {
                    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
                    glBindVertexArray(VAOs[color[2] + 15]);
                    glDrawElements(PrimType[color[2] + 15], NumElems[color[2] + 15], GL_UNSIGNED_BYTE, 0);
                }
            }
        }
        glBindVertexArray(0);
        popMatrix(modelview);
    }
    void draw(glm::mat4 tAux) {
        if (type == -1)
            return;
        pushMatrix(modelview);
        modelview = modelview * tAux * transformation;
        glBindTexture(GL_TEXTURE_2D,texturaNula);
        glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
        glBindVertexArray(VAOs[type]);
        glDrawElements(PrimType[type], NumElems[type], GL_UNSIGNED_BYTE, 0);

        if (flagTextura) {
            glBindTexture(GL_TEXTURE_2D, textures[color[0] * 9 + iTextura[0]]);
            glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
            glBindVertexArray(VAOs[3]);
            glDrawElements(PrimType[3], NumElems[3], GL_UNSIGNED_BYTE, 0);
            if (type) {
                glBindTexture(GL_TEXTURE_2D, textures[color[1] * 9 + iTextura[1]]);
                glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
                glBindVertexArray(VAOs[9]);
                glDrawElements(PrimType[9], NumElems[9], GL_UNSIGNED_BYTE, 0);
                if (type == 2) {
                    glBindTexture(GL_TEXTURE_2D, textures[color[2] * 9 + iTextura[2]]);
                    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
                    glBindVertexArray(VAOs[15]);
                    glDrawElements(PrimType[15], NumElems[color[2] + 15], GL_UNSIGNED_BYTE, 0);
                }
            }
        }
        else {
            glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
            glBindVertexArray(VAOs[color[0] + 3]);
            glDrawElements(PrimType[color[0] + 3], NumElems[color[0] + 3], GL_UNSIGNED_BYTE, 0);
            if (type) {
                glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
                glBindVertexArray(VAOs[color[1] + 9]);
                glDrawElements(PrimType[color[1] + 9], NumElems[color[1] + 9], GL_UNSIGNED_BYTE, 0);
                if (type == 2) {
                    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &(modelview)[0][0]);
                    glBindVertexArray(VAOs[color[2] + 15]);
                    glDrawElements(PrimType[color[2] + 15], NumElems[color[2] + 15], GL_UNSIGNED_BYTE, 0);
                }
            }
        }
        glBindVertexArray(0);
        popMatrix(modelview);
    }
};

struct Cubo {
    glm::mat4 transformation;
    double timeOffset;
    solver::solverRubik* naiveSolver;
    std::vector<int> movimientosPendientes;
    typedef bool (Cubo::*fptr)(float);
    Piezas* pieza[3][3][3];
    fptr movimientos[24];
    int ejeAnimacion;
    int iAnimacion;
    float gradoAnimacion;
    int iSeleccionado;
    int jSeleccionado;
    int kSeleccionado;
    int caraSeleccionada;
    Cubo(int i, glm::vec3 cen) {
        transformation = glm::translate(identity,cen);
        naiveSolver = new solver::solverRubik(0);
        ejeAnimacion = -1;
        iAnimacion = 0;
        gradoAnimacion = 0.0;
        iSeleccionado =-1;
        jSeleccionado = -1;
        kSeleccionado = -1;
        caraSeleccionada =-1;
        movimientos[0] = &Cubo::U;
        movimientos[1] = &Cubo::E;
        movimientos[2] = &Cubo::D;
        movimientos[3] = &Cubo::F;
        movimientos[4] = &Cubo::S;
        movimientos[5] = &Cubo::B;
        movimientos[6] = &Cubo::R;
        movimientos[7] = &Cubo::M;
        movimientos[8] = &Cubo::L;
        movimientos[9] = &Cubo::Uprima;
        movimientos[10] = &Cubo::Eprima;
        movimientos[11] = &Cubo::Dprima;
        movimientos[12] = &Cubo::Fprima;
        movimientos[13] = &Cubo::Sprima;
        movimientos[14] = &Cubo::Bprima;
        movimientos[15] = &Cubo::Rprima;
        movimientos[16] = &Cubo::Mprima;
        movimientos[17] = &Cubo::Lprima;
        movimientos[18] = &Cubo::Y;
        movimientos[19] = &Cubo::Z;
        movimientos[20] = &Cubo::X;
        movimientos[21] = &Cubo::Yprima;
        movimientos[22] = &Cubo::Zprima;
        movimientos[23] = &Cubo::Xprima;
        pieza[0][0][0] = new Piezas(i,VERTICE, 0, BLANCO, ROJO, AZUL);
        pieza[0][0][0]->setTextures(8,2,0);
        pieza[0][0][1] = new Piezas(i, ARISTA, 0, BLANCO, ROJO);
        pieza[0][0][1]->setTextures(7, 1);
        pieza[0][0][2] = new Piezas(i , VERTICE, 1, BLANCO, VERDE, ROJO);
        pieza[0][0][2]->setTextures(6, 2, 0);
        pieza[0][1][0] = new Piezas(i , ARISTA, 1, BLANCO, AZUL);
        pieza[0][1][0]->setTextures(5, 1);
        pieza[0][1][1] = new Piezas(i ,CENTRO , 0, BLANCO);
        pieza[0][1][1]->setTextures(4);
        pieza[0][1][2] = new Piezas(i , ARISTA, 2, BLANCO, VERDE);
        pieza[0][1][2]->setTextures(3, 1);
        pieza[0][2][0] = new Piezas(i , VERTICE, 2, BLANCO, AZUL, NARANJA);
        pieza[0][2][0]->setTextures(2, 2, 0);
        pieza[0][2][1] = new Piezas(i , ARISTA, 3, BLANCO, NARANJA);
        pieza[0][2][1]->setTextures(1, 1);
        pieza[0][2][2] = new Piezas(i , VERTICE, 3, BLANCO, NARANJA, VERDE);
        pieza[0][2][2]->setTextures(0, 2, 0);

        pieza[1][0][0] = new Piezas(i , ARISTA, 4, AZUL, ROJO);
        pieza[1][0][0]->setTextures(3,5);
        pieza[1][0][1] = new Piezas(i  ,CENTRO, 1, ROJO);
        pieza[1][0][1]->setTextures(4);
        pieza[1][0][2] = new Piezas(i , ARISTA, 5, ROJO, VERDE);
        pieza[1][0][2]->setTextures(3,5);
        pieza[1][1][0] = new Piezas(i, CENTRO, 2, AZUL);
        pieza[1][1][0]->setTextures(4);
        pieza[1][1][1] = new Piezas(-1);
        pieza[1][1][2] = new Piezas(i, CENTRO, 3, VERDE);
        pieza[1][1][2]->setTextures(4);
        pieza[1][2][0] = new Piezas(i , ARISTA, 6, NARANJA, AZUL);
        pieza[1][2][0]->setTextures(3,5);
        pieza[1][2][1] = new Piezas(i, CENTRO, 4, NARANJA);
        pieza[1][2][1]->setTextures(4);
        pieza[1][2][2] = new Piezas(i , ARISTA, 7, VERDE, NARANJA);
        pieza[1][2][2]->setTextures(3,5);

        pieza[2][0][0] = new Piezas(i , VERTICE, 4, ROJO, AMARILLO, AZUL);
        pieza[2][0][0]->setTextures(8,2,6);
        pieza[2][0][1] = new Piezas(i , ARISTA, 8, AMARILLO, ROJO);
        pieza[2][0][1]->setTextures(1,7);
        pieza[2][0][2] = new Piezas(i , VERTICE, 5, VERDE, AMARILLO, ROJO);
        pieza[2][0][2]->setTextures(8,0,6);
        pieza[2][1][0] = new Piezas(i , ARISTA, 9, AMARILLO, AZUL);
        pieza[2][1][0]->setTextures(5,7);
        pieza[2][1][1] = new Piezas(i, CENTRO, 5, AMARILLO);
        pieza[2][1][1]->setTextures(4);
        pieza[2][1][2] = new Piezas(i , ARISTA, 10, AMARILLO, VERDE);
        pieza[2][1][2]->setTextures(3,7);
        pieza[2][2][0] = new Piezas(i , VERTICE, 6, AZUL, AMARILLO, NARANJA);
        pieza[2][2][0]->setTextures(8,8,6);
        pieza[2][2][1] = new Piezas(i , ARISTA, 11, AMARILLO, NARANJA);
        pieza[2][2][1]->setTextures(7,7);
        pieza[2][2][2] = new Piezas(i , VERTICE, 7, NARANJA, AMARILLO, VERDE);
        pieza[2][2][2]->setTextures(8,6,6);
    }
    void OnOffTexture() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    pieza[i][j][k]->flagTextura = !pieza[2][2][2]->flagTextura;
    }
    void draw() {
        if (ejeAnimacion == ejeX) {
            //tercera
            glm::mat4 matAuxRotacion = transformation*glm::rotate(identity, gradoAnimacion, glm::vec3(1.0, 0.0, 0.0));
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    for (int k = 0; k < 3; ++k)
                        if(iAnimacion==4||k==iAnimacion)
                            pieza[i][j][k]->draw(matAuxRotacion);
                        else
                            pieza[i][j][k]->draw(transformation);
        }
        else if (ejeAnimacion == ejeY) {
            //primera
            glm::mat4 matAuxRotacion = transformation * glm::rotate(identity, gradoAnimacion, glm::vec3(0.0, 1.0, 0.0)) ;
            for (int i = 0; i < 3; ++i) 
                if (iAnimacion == 4 || i == iAnimacion)
                    for (int j = 0; j < 3; ++j)
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(matAuxRotacion);
                else
                    for (int j = 0; j < 3; ++j)
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(transformation);
        }
        else if (ejeAnimacion == ejeZ) {
            //segunda
            glm::mat4 matAuxRotacion = transformation * glm::rotate(identity, gradoAnimacion, glm::vec3(0.0, 0.0, 1.0));
            for (int i = 0; i < 3; ++i)
                 for (int j = 0; j < 3; ++j)
                    if (iAnimacion == 4 || j == iAnimacion)
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(matAuxRotacion);
                    else
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(transformation);
        }
        else{
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    for (int k = 0; k < 3; ++k)
                        pieza[i][j][k]->draw(transformation);
        }
    }
    void draw(glm::mat4 animacion) {
        animacion = animacion * transformation;
        if (ejeAnimacion == ejeX) {
            //tercera
            glm::mat4 matAuxRotacion = animacion * glm::rotate(identity, gradoAnimacion, glm::vec3(1.0, 0.0, 0.0));
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    for (int k = 0; k < 3; ++k)
                        if (iAnimacion == 4 || k == iAnimacion)
                            pieza[i][j][k]->draw(matAuxRotacion);
                        else
                            pieza[i][j][k]->draw(animacion);
        }
        else if (ejeAnimacion == ejeY) {
            //primera
            glm::mat4 matAuxRotacion = animacion * glm::rotate(identity, gradoAnimacion, glm::vec3(0.0, 1.0, 0.0));
            for (int i = 0; i < 3; ++i)
                if (iAnimacion == 4 || i == iAnimacion)
                    for (int j = 0; j < 3; ++j)
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(matAuxRotacion);
                else
                    for (int j = 0; j < 3; ++j)
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(animacion);
        }
        else if (ejeAnimacion == ejeZ) {
            //segunda
            glm::mat4 matAuxRotacion = animacion * glm::rotate(identity, gradoAnimacion, glm::vec3(0.0, 0.0, 1.0));
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (iAnimacion == 4 || j == iAnimacion)
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(matAuxRotacion);
                    else
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(animacion);
        }
        else {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    for (int k = 0; k < 3; ++k)
                        pieza[i][j][k]->draw(animacion);
        }
    }
    void generarSolucion() {
        movimientosPendientes = naiveSolver->resolver();
        timeOffset = glfwGetTime();
    }
    void reiniciarSolver() {
        naiveSolver->reinicio();
    }
    void realizarMovimientos() {
        if (movimientosPendientes.size() && movimiento(movimientosPendientes[0], (glfwGetTime() - timeOffset) * 4)) {
            movimientosPendientes.erase(movimientosPendientes.begin());
            if (movimientosPendientes.size() == 0) {
                switch (pieza[0][1][1]->color[0]) {
                case BLANCO:
                    switch (pieza[1][0][1]->color[0]) {
                    case AZUL:
                        movimientosPendientes.push_back(21);
                        break;
                    case NARANJA:
                        movimientosPendientes.push_back(18);
                        movimientosPendientes.push_back(18);
                        break;
                    case VERDE:
                        movimientosPendientes.push_back(18);
                    }
                    break;
                case ROJO:
                    movimientosPendientes.push_back(23);
                    break;
                case AZUL:
                    movimientosPendientes.push_back(19);
                    break;
                case NARANJA:
                    movimientosPendientes.push_back(20);
                    break;
                case VERDE:
                    movimientosPendientes.push_back(22);
                    break;
                case AMARILLO:
                    if (pieza[1][0][1]->color[0] == ROJO) {
                        movimientosPendientes.push_back(19);
                        movimientosPendientes.push_back(19);
                    }
                    else {
                        movimientosPendientes.push_back(20);
                        movimientosPendientes.push_back(20);
                    }
                }
                naiveSolver->reinicio();
            }
            timeOffset = glfwGetTime();
        }
    }
    void rotar(Piezas*& p1, Piezas*& p2, Piezas*& p3, Piezas*& p4) {
        Piezas* aux = p1;
        p1 = p2;
        p2 = p3;
        p3 = p4;
        p4 = aux;
    }
    bool U(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 0;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[0][i][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, -1.0, 0.0))   * pieza[0][i][j]->transformation;
            rotar(pieza[0][0][0], pieza[0][2][0], pieza[0][2][2], pieza[0][0][2]);
            rotar(pieza[0][0][1], pieza[0][1][0], pieza[0][2][1], pieza[0][1][2]);
            naiveSolver->movimiento(0);
            return true;
        }
        return false;
    }
    bool Uprima(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 0;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[0][i][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, 1.0, 0.0))   * pieza[0][i][j]->transformation;
            rotar(pieza[0][0][0], pieza[0][0][2], pieza[0][2][2], pieza[0][2][0]);
            rotar(pieza[0][0][1], pieza[0][1][2], pieza[0][2][1], pieza[0][1][0]);
            naiveSolver->movimiento(9);
            return true;
        }
        return false;
    }
    bool E(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 1;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[1][i][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, 1.0, 0.0))   * pieza[1][i][j]->transformation;
            rotar(pieza[1][0][0], pieza[1][0][2], pieza[1][2][2], pieza[1][2][0]);
            rotar(pieza[1][0][1], pieza[1][1][2], pieza[1][2][1], pieza[1][1][0]);
            naiveSolver->movimiento(1);
            return true;
        }
        return false;
    }
    bool Eprima(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 1;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[1][i][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, -1.0, 0.0))   * pieza[1][i][j]->transformation;
            rotar(pieza[1][0][0], pieza[1][2][0], pieza[1][2][2], pieza[1][0][2]);
            rotar(pieza[1][0][1], pieza[1][1][0], pieza[1][2][1], pieza[1][1][2]);
            naiveSolver->movimiento(10);
            return true;
        }
        return false;
    }
    bool D(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 2;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[2][i][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, 1.0, 0.0))   * pieza[2][i][j]->transformation;
            rotar(pieza[2][0][0], pieza[2][0][2], pieza[2][2][2], pieza[2][2][0]);
            rotar(pieza[2][0][1], pieza[2][1][2], pieza[2][2][1], pieza[2][1][0]);
            naiveSolver->movimiento(2);
            return true;
        }
        return false;
    }
    bool Dprima(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 2;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[2][i][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, -1.0, 0.0))   * pieza[2][i][j]->transformation;
            rotar(pieza[2][0][0], pieza[2][2][0], pieza[2][2][2], pieza[2][0][2]);
            rotar(pieza[2][0][1], pieza[2][1][0], pieza[2][2][1], pieza[2][1][2]);
            naiveSolver->movimiento(11);
            return true;
        }
        return false;
    }
    bool F(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 0;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][0][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0))   * pieza[i][0][j]->transformation;
            rotar(pieza[0][0][0], pieza[0][0][2], pieza[2][0][2], pieza[2][0][0]);
            rotar(pieza[0][0][1], pieza[1][0][2], pieza[2][0][1], pieza[1][0][0]);
            naiveSolver->movimiento(3);
            return true;
        }
        return false;
    }
    bool Fprima(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 0;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][0][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, 1.0))   * pieza[i][0][j]->transformation;
            rotar(pieza[0][0][0], pieza[2][0][0], pieza[2][0][2], pieza[0][0][2]);
            rotar(pieza[0][0][1], pieza[1][0][0], pieza[2][0][1], pieza[1][0][2]);
            naiveSolver->movimiento(12);
            return true;
        }
        return false;
    }
    bool S(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 1;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][1][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0))   * pieza[i][1][j]->transformation;
            rotar(pieza[0][1][0], pieza[0][1][2], pieza[2][1][2], pieza[2][1][0]);
            rotar(pieza[0][1][1], pieza[1][1][2], pieza[2][1][1], pieza[1][1][0]);
            naiveSolver->movimiento(4);
            return true;
        }
        return false;
    }
    bool Sprima(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 1;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][1][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, 1.0))   * pieza[i][1][j]->transformation;
            rotar(pieza[0][1][0], pieza[2][1][0], pieza[2][1][2], pieza[0][1][2]);
            rotar(pieza[0][1][1], pieza[1][1][0], pieza[2][1][1], pieza[1][1][2]);
            naiveSolver->movimiento(13);
            return true;
        }
        return false;
    }
    bool B(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 2;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][2][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, 1.0))   * pieza[i][2][j]->transformation;
            rotar(pieza[0][2][0], pieza[2][2][0], pieza[2][2][2], pieza[0][2][2]);
            rotar(pieza[0][2][1], pieza[1][2][0], pieza[2][2][1], pieza[1][2][2]);
            naiveSolver->movimiento(5);
            return true;
        }
        return false;
    }
    bool Bprima(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 2;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][2][j]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0))   * pieza[i][2][j]->transformation;
            rotar(pieza[0][2][0], pieza[0][2][2], pieza[2][2][2], pieza[2][2][0]);
            rotar(pieza[0][2][1], pieza[1][2][2], pieza[2][2][1], pieza[1][2][0]);
            naiveSolver->movimiento(14);
            return true;
        }
        return false;
    }
    bool R(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 0;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][0]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(-1.0, 0.0, 0.0))   * pieza[i][j][0]->transformation;
            rotar(pieza[0][0][0], pieza[2][0][0], pieza[2][2][0], pieza[0][2][0]);
            rotar(pieza[0][1][0], pieza[1][0][0], pieza[2][1][0], pieza[1][2][0]);
            naiveSolver->movimiento(6);
            return true;
        }
        return false;
    }
    bool Rprima(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 0;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][0]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0))   * pieza[i][j][0]->transformation;
            rotar(pieza[0][0][0], pieza[0][2][0], pieza[2][2][0], pieza[2][0][0]);
            rotar(pieza[0][1][0], pieza[1][2][0], pieza[2][1][0], pieza[1][0][0]);
            naiveSolver->movimiento(15);
            return true;
        }
        return false;
    }
    bool M(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 1;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][1]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0))   * pieza[i][j][1]->transformation;
            rotar(pieza[0][0][1], pieza[0][2][1], pieza[2][2][1], pieza[2][0][1]);
            rotar(pieza[0][1][1], pieza[1][2][1], pieza[2][1][1], pieza[1][0][1]);
            naiveSolver->movimiento(7);
            return true;
        }
        return false;
    }
    bool Mprima(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 1;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][1]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(-1.0, 0.0, 0.0))   * pieza[i][j][1]->transformation;
            rotar(pieza[0][0][1], pieza[2][0][1], pieza[2][2][1], pieza[0][2][1]);
            rotar(pieza[0][1][1], pieza[1][0][1], pieza[2][1][1], pieza[1][2][1]);
            naiveSolver->movimiento(16);
            return true;
        }
        return false;
    }
    bool L(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 2;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][2]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0))   * pieza[i][j][2]->transformation;
            rotar(pieza[0][0][2], pieza[0][2][2], pieza[2][2][2], pieza[2][0][2]);
            rotar(pieza[0][1][2], pieza[1][2][2], pieza[2][1][2], pieza[1][0][2]);
            naiveSolver->movimiento(8);
            return true;
        }
        return false;
    }
    bool Lprima(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 2;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][2]->transformation =   glm::rotate(identity, (float)G90, glm::vec3(-1.0, 0.0, 0.0))   * pieza[i][j][2]->transformation;
            rotar(pieza[0][0][2], pieza[2][0][2], pieza[2][2][2], pieza[0][2][2]);
            rotar(pieza[0][1][2], pieza[1][0][2], pieza[2][1][2], pieza[1][2][2]);
            naiveSolver->movimiento(17);
            return true;
        }
        return false;
    }
    bool Y(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 4;
        gradoAnimacion = -g;
        if (g >= G90)
            return U(3.0) && Eprima(3.0) &&Dprima(3.0);
        return false;
    }
    bool Yprima(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 4;
        gradoAnimacion = g;
        if (g >= G90)
            return Uprima(3.0) && E(3.0) && D(3.0);
        return false;
    }
    bool Z(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 4;
        gradoAnimacion = -g;
        if (g >= G90)
            return F(3.0) && S(3.0) && Bprima(3.0);
        return false;
    }
    bool Zprima(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 4;
        gradoAnimacion = g;
        if (g >= G90)
            return Fprima(3.0) && Sprima(3.0) && B(3.0);
        return false;
    }
    bool X(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 4;
        gradoAnimacion = -g;
        if (g >= G90)
            return R(3.0) && Mprima(3.0) && Lprima(3.0);
        return false;
    }
    bool Xprima(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 4;
        gradoAnimacion = g;
        if (g >= G90)
            return Rprima(3.0) && M(3.0) && L(3.0);
        return false;
    }

    void separar() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                pieza[i][0][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.0, 0.1)) * pieza[i][0][j]->transformation;
                pieza[i][2][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.0, -0.1)) * pieza[i][2][j]->transformation;
                pieza[i][j][0]->transformation = glm::translate(identity, glm::vec3(0.1, 0.0, 0.0)) * pieza[i][j][0]->transformation;
                pieza[i][j][2]->transformation = glm::translate(identity, glm::vec3(-0.1, 0.0, 0.0)) * pieza[i][j][2]->transformation;
                pieza[0][i][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.1, 0.0)) * pieza[0][i][j]->transformation;
                pieza[2][i][j]->transformation = glm::translate(identity, glm::vec3(0.0, -0.1, 0.0)) * pieza[2][i][j]->transformation;
            }
    }

    void juntar() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                pieza[i][0][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.0, -0.1)) * pieza[i][0][j]->transformation;
                pieza[i][2][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.0, 0.1)) * pieza[i][2][j]->transformation;
                pieza[i][j][0]->transformation = glm::translate(identity, glm::vec3(-0.1, 0.0, 0.0)) * pieza[i][j][0]->transformation;
                pieza[i][j][2]->transformation = glm::translate(identity, glm::vec3(0.1, 0.0, 0.0)) * pieza[i][j][2]->transformation;
                pieza[0][i][j]->transformation = glm::translate(identity, glm::vec3(0.0, -0.1, 0.0)) * pieza[0][i][j]->transformation;
                pieza[2][i][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.1, 0.0)) * pieza[2][i][j]->transformation;
            }
    }

    bool movimiento(int i, float g) {
        return (this->*movimientos[i])(g);
    }
    void scramble(int n) {
        for (int i = 0; i < n; ++i) {
            (this->*movimientos[rand()%18])(G90+1);
        }
    }
    int seleccionarMejor(glm::vec3 pos, glm::vec3 direccion) {
        float escalarX = (abs(pos.x) - 0.3) / abs(direccion.x);
        float escalarY = (abs(pos.y) - 0.3) / abs(direccion.y);
        float escalarZ = (abs(pos.z) - 0.3) / abs(direccion.z);
        glm::vec3 posMod = pos + escalarX * direccion;
        int seleccionadoInt = -1;
        caraSeleccionada = -1;
        iSeleccionado = -1;
        jSeleccionado = -1;
        kSeleccionado = -1;
        if (posMod.y<0.301 && posMod.y > -0.301 && posMod.z<0.301 && posMod.z > -0.301) {
            caraSeleccionada = ejeX;
            iSeleccionado = (int)((0.301 - posMod.y) / 0.2);
            jSeleccionado = (int)((0.301 - posMod.z) / 0.2);
            if (direccion.x < 0)
                kSeleccionado = 0;
            else
                kSeleccionado = 2;
            seleccionadoInt = kSeleccionado + 9 * iSeleccionado + jSeleccionado * 3;
            return seleccionadoInt;
        }
        posMod = pos + escalarY * direccion;
        if (posMod.x<0.301 && posMod.x > -0.301 && posMod.z<0.301 && posMod.z > -0.301){
            caraSeleccionada = ejeY;
            jSeleccionado = (int)((0.301 - posMod.z) / 0.2);
            kSeleccionado = (int)((0.301 - posMod.x) / 0.2);
            if (direccion.y < 0)
                iSeleccionado = 0;
            else
                iSeleccionado = 2;
            seleccionadoInt = kSeleccionado + 9 * iSeleccionado + jSeleccionado * 3;
            return seleccionadoInt;
        }
        posMod = pos + escalarZ * direccion;
        if (posMod.y<0.301 && posMod.y > -0.301 && posMod.x<0.301 && posMod.x > -0.301){
            caraSeleccionada = ejeZ;
            iSeleccionado = (int)((0.301 - posMod.y) / 0.2);
            kSeleccionado = (int)((0.301 - posMod.x) / 0.2);
            if (direccion.z < 0)
                jSeleccionado = 0;
            else
                jSeleccionado = 2;
            seleccionadoInt = kSeleccionado + 9 * iSeleccionado + jSeleccionado * 3;
            return seleccionadoInt;
        }
        return-1;
    }
    void moverMouse(glm::vec3 direccion) {
        gradoAnimacion = 0;
        if (caraSeleccionada == ejeX) {
            if (abs(direccion.y) > abs(direccion.z) && abs(direccion.y)>0.05) {
                //std::cout << "FSB" << std::endl;
                if (jSeleccionado < 2)
                    (this->*movimientos[3 + jSeleccionado + (9 * !((direccion.y > 0) ^ !kSeleccionado))])(std::min(1.5f, 4 * abs(direccion.y)));
                else
                    (this->*movimientos[3+ jSeleccionado + (9 * ((direccion.y > 0) ^ !kSeleccionado))])(std::min(1.5f, 4 * abs(direccion.y)));
            }
            else if(abs(direccion.z) > 0.05){
                //std::cout << "UED" << std::endl;
                if(iSeleccionado==0)
                    (this->*movimientos[iSeleccionado +(9*((direccion.z>0) ^ !kSeleccionado))])(std::min(1.5f,4*abs(direccion.z)) );
                else
                    (this->*movimientos[iSeleccionado + (9 * !((direccion.z > 0) ^ !kSeleccionado))])(std::min(1.5f, 4 * abs(direccion.z)));
            }
        }
        else if (caraSeleccionada == ejeY) {
            if (abs(direccion.x) > abs(direccion.z)){
                //std::cout << "FSB" << std::endl;
                if (jSeleccionado < 2)
                    (this->*movimientos[3 + jSeleccionado + (9 * !((direccion.x > 0) ^ (bool)iSeleccionado))])(std::min(1.5f, 4 * abs(direccion.x)));
                else
                    (this->*movimientos[3 + jSeleccionado + (9 * ((direccion.x > 0) ^ (bool)iSeleccionado))])(std::min(1.5f, 4 * abs(direccion.x)));
            }
            else {
                //std::cout << "LMR" << std::endl;
                if (kSeleccionado ==0)
                    (this->*movimientos[6 + kSeleccionado + (9 * !((direccion.z > 0) ^ !iSeleccionado))])(std::min(1.5f, 4 * abs(direccion.z)));
                else
                    (this->*movimientos[6 + kSeleccionado + (9 * ((direccion.z > 0) ^ !iSeleccionado))])(std::min(1.5f, 4 * abs(direccion.z)));
            }
        }
        else {
            if (abs(direccion.y) > abs(direccion.x)){
                //std::cout << "LMR" << std::endl;
                if (kSeleccionado == 0)
                    (this->*movimientos[6 + kSeleccionado + (9 * !((direccion.y > 0) ^ (bool)jSeleccionado))])(std::min(1.5f, 4 * abs(direccion.y)));
                else
                    (this->*movimientos[6 + kSeleccionado + (9 * ((direccion.y > 0) ^ (bool)jSeleccionado))])(std::min(1.5f, 4 * abs(direccion.y)));
            }
            else {
                //std::cout << "UED" << std::endl;
                if (iSeleccionado == 0)
                    (this->*movimientos[iSeleccionado + (9 * ((direccion.x > 0) ^ (bool)jSeleccionado) )])(std::min(1.5f, 4 * abs(direccion.x)));
                else
                    (this->*movimientos[iSeleccionado + (9 * !((direccion.x > 0) ^ (bool)jSeleccionado))])(std::min(1.5f, 4 * abs(direccion.x)));
            }
        }
    }
    void terminarGiro() {
        if (ejeAnimacion > -1 && iSeleccionado > -1 && abs(gradoAnimacion) > 0.8f) {
            if (ejeAnimacion == ejeX)
                (this->*movimientos[6 + iAnimacion + (9 * !(gradoAnimacion > 0 ^ iAnimacion ==0))])(G90 + 1);
            else if (ejeAnimacion == ejeY)
                (this->*movimientos[iAnimacion + (9 * !(gradoAnimacion > 0 ^ iAnimacion == 0))])(G90 + 1);
            else
                (this->*movimientos[3 + iAnimacion + (9 * !(gradoAnimacion > 0 ^ iAnimacion < 2))])(G90 + 1);
        }
        ejeAnimacion = -1;
        iSeleccionado = -1;
        jSeleccionado = -1;
        kSeleccionado = -1;
        gradoAnimacion = 0.0;
    }
    ~Cubo() {
        delete naiveSolver;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    delete pieza[i][j][k];
    }
};

struct MegaCubo {
    double timeOffset;
    solver::solverRubik* naiveSolver;
    std::vector<int> movimientosPendientes;
    typedef bool (MegaCubo::* fptr)(float);
    Cubo* pieza[3][3][3];
    fptr movimientos[24];
    int ejeAnimacion;
    int iAnimacion;
    float gradoAnimacion;
    int iSeleccionado;
    int jSeleccionado;
    int kSeleccionado;
    int caraSeleccionada;
    MegaCubo(int i) {
        naiveSolver = new solver::solverRubik(0);
        ejeAnimacion = -1;
        iAnimacion = 0;
        gradoAnimacion = 0.0;
        iSeleccionado = -1;
        jSeleccionado = -1;
        kSeleccionado = -1;
        caraSeleccionada = -1;
        movimientos[0] = &MegaCubo::U;
        movimientos[1] = &MegaCubo::E;
        movimientos[2] = &MegaCubo::D;
        movimientos[3] = &MegaCubo::F;
        movimientos[4] = &MegaCubo::S;
        movimientos[5] = &MegaCubo::B;
        movimientos[6] = &MegaCubo::R;
        movimientos[7] = &MegaCubo::M;
        movimientos[8] = &MegaCubo::L;
        movimientos[9] = &MegaCubo::Uprima;
        movimientos[10] = &MegaCubo::Eprima;
        movimientos[11] = &MegaCubo::Dprima;
        movimientos[12] = &MegaCubo::Fprima;
        movimientos[13] = &MegaCubo::Sprima;
        movimientos[14] = &MegaCubo::Bprima;
        movimientos[15] = &MegaCubo::Rprima;
        movimientos[16] = &MegaCubo::Mprima;
        movimientos[17] = &MegaCubo::Lprima;
        movimientos[18] = &MegaCubo::Y;
        movimientos[19] = &MegaCubo::Z;
        movimientos[20] = &MegaCubo::X;
        movimientos[21] = &MegaCubo::Yprima;
        movimientos[22] = &MegaCubo::Zprima;
        movimientos[23] = &MegaCubo::Xprima;
        pieza[0][0][0] = new Cubo(i, glm::vec3(0.6,0.6,0.6));
        pieza[0][0][1] = new Cubo(i, glm::vec3(0.0, 0.6, 0.6));
        pieza[0][0][2] = new Cubo(i, glm::vec3(-0.6, 0.6, 0.6));
        pieza[0][1][0] = new Cubo(i, glm::vec3(0.6, 0.6, 0.0));
        pieza[0][1][1] = new Cubo(i, glm::vec3(0.0, 0.6, 0.0));
        pieza[0][1][2] = new Cubo(i, glm::vec3(-0.6, 0.6, 0.0));
        pieza[0][2][0] = new Cubo(i, glm::vec3(0.6, 0.6, -0.6));
        pieza[0][2][1] = new Cubo(i, glm::vec3(0.0, 0.6, -0.6));
        pieza[0][2][2] = new Cubo(i, glm::vec3(-0.6, 0.6, -0.6));
        pieza[1][0][0] = new Cubo(i, glm::vec3(0.6, 0.0, 0.6));
        pieza[1][0][1] = new Cubo(i, glm::vec3(0.0, 0.0, 0.6));
        pieza[1][0][2] = new Cubo(i, glm::vec3(-0.6, 0.0, 0.6));
        pieza[1][1][0] = new Cubo(i, glm::vec3(0.6, 0.0, 0.0));
        pieza[1][1][1] = new Cubo(i, glm::vec3(0.0, 0.0, 0.0));
        pieza[1][1][2] = new Cubo(i, glm::vec3(-0.6, 0.0, 0.0));
        pieza[1][2][0] = new Cubo(i, glm::vec3(0.6, 0.0, -0.6));
        pieza[1][2][1] = new Cubo(i, glm::vec3(0.0, 0.0, -0.6));
        pieza[1][2][2] = new Cubo(i, glm::vec3(-0.6, 0.0, -0.6));
        pieza[2][0][0] = new Cubo(i, glm::vec3(0.6, -0.6, 0.6));
        pieza[2][0][1] = new Cubo(i, glm::vec3(0.0, -0.6, 0.6));
        pieza[2][0][2] = new Cubo(i, glm::vec3(-0.6, -0.6, 0.6));
        pieza[2][1][0] = new Cubo(i, glm::vec3(0.6, -0.6, 0.0));
        pieza[2][1][1] = new Cubo(i, glm::vec3(0.0, -0.6, 0.0));
        pieza[2][1][2] = new Cubo(i, glm::vec3(-0.6, -0.6, 0.0));
        pieza[2][2][0] = new Cubo(i, glm::vec3(0.6, -0.6, -0.6));
        pieza[2][2][1] = new Cubo(i, glm::vec3(0.0, -0.6, -0.6));
        pieza[2][2][2] = new Cubo(i, glm::vec3(-0.6, -0.6, -0.6));
    }
    void OnOffTexture() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    pieza[i][j][k]->OnOffTexture();
    }
    void draw() {
        if (ejeAnimacion == ejeX) {
            //tercera
            glm::mat4 matAuxRotacion = glm::rotate(identity, gradoAnimacion, glm::vec3(1.0, 0.0, 0.0));
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    for (int k = 0; k < 3; ++k)
                        if (iAnimacion == 4 || k == iAnimacion)
                            pieza[i][j][k]->draw(matAuxRotacion);
                        else
                            pieza[i][j][k]->draw();
        }
        else if (ejeAnimacion == ejeY) {
            //primera
            glm::mat4 matAuxRotacion =glm::rotate(identity, gradoAnimacion, glm::vec3(0.0, 1.0, 0.0));
            for (int i = 0; i < 3; ++i)
                if (iAnimacion == 4 || i == iAnimacion)
                    for (int j = 0; j < 3; ++j)
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(matAuxRotacion);
                else
                    for (int j = 0; j < 3; ++j)
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw();
        }
        else if (ejeAnimacion == ejeZ) {
            //segunda
            glm::mat4 matAuxRotacion =  glm::rotate(identity, gradoAnimacion, glm::vec3(0.0, 0.0, 1.0));
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (iAnimacion == 4 || j == iAnimacion)
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw(matAuxRotacion);
                    else
                        for (int k = 0; k < 3; ++k)
                            pieza[i][j][k]->draw();
        }
        else {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    for (int k = 0; k < 3; ++k)
                        pieza[i][j][k]->draw(glm::translate(identity, glm::vec3(0.7 * (pieza[i][j][k]->movimientosPendientes.size() > 0) * (1 - k), 0.7 * (pieza[i][j][k]->movimientosPendientes.size() > 0) * (1 - i), 0.7 * (pieza[i][j][k]->movimientosPendientes.size() > 0) * (1 - j))));
        }
    }
    void generarSolucion() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    pieza[i][j][k]->generarSolucion();
        movimientosPendientes = naiveSolver->resolver();
        timeOffset = glfwGetTime();
    }
    
    void realizarMovimientos() {
        bool flag = 1;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k) {
                    flag = flag && (pieza[i][j][k]->movimientosPendientes.size() == 0);
                    pieza[i][j][k]->realizarMovimientos();
                }

        if (flag && movimientosPendientes.size() && movimiento(movimientosPendientes[0], (glfwGetTime() - timeOffset) * 2)) {
            movimientosPendientes.erase(movimientosPendientes.begin());
            if (movimientosPendientes.size() == 0) {
                naiveSolver->reinicio();
            }
            timeOffset = glfwGetTime();
        }
        else if(!flag){
            timeOffset = glfwGetTime()+1;
        }
    }
    void rotar(Cubo*& p1, Cubo*& p2, Cubo*& p3, Cubo*& p4) {
        Cubo* aux = p1;
        p1 = p2;
        p2 = p3;
        p3 = p4;
        p4 = aux;
    }
    bool U(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 0;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[0][i][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, -1.0, 0.0)) * pieza[0][i][j]->transformation;
            rotar(pieza[0][0][0], pieza[0][2][0], pieza[0][2][2], pieza[0][0][2]);
            rotar(pieza[0][0][1], pieza[0][1][0], pieza[0][2][1], pieza[0][1][2]);
            naiveSolver->movimiento(0);
            return true;
        }
        return false;
    }
    bool Uprima(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 0;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[0][i][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 1.0, 0.0)) * pieza[0][i][j]->transformation;
            rotar(pieza[0][0][0], pieza[0][0][2], pieza[0][2][2], pieza[0][2][0]);
            rotar(pieza[0][0][1], pieza[0][1][2], pieza[0][2][1], pieza[0][1][0]);
            naiveSolver->movimiento(9);
            return true;
        }
        return false;
    }
    bool E(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 1;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[1][i][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 1.0, 0.0)) * pieza[1][i][j]->transformation;
            rotar(pieza[1][0][0], pieza[1][0][2], pieza[1][2][2], pieza[1][2][0]);
            rotar(pieza[1][0][1], pieza[1][1][2], pieza[1][2][1], pieza[1][1][0]);
            naiveSolver->movimiento(1);
            return true;
        }
        return false;
    }
    bool Eprima(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 1;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[1][i][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, -1.0, 0.0)) * pieza[1][i][j]->transformation;
            rotar(pieza[1][0][0], pieza[1][2][0], pieza[1][2][2], pieza[1][0][2]);
            rotar(pieza[1][0][1], pieza[1][1][0], pieza[1][2][1], pieza[1][1][2]);
            naiveSolver->movimiento(10);
            return true;
        }
        return false;
    }
    bool D(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 2;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[2][i][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 1.0, 0.0)) * pieza[2][i][j]->transformation;
            rotar(pieza[2][0][0], pieza[2][0][2], pieza[2][2][2], pieza[2][2][0]);
            rotar(pieza[2][0][1], pieza[2][1][2], pieza[2][2][1], pieza[2][1][0]);
            naiveSolver->movimiento(2);
            return true;
        }
        return false;
    }
    bool Dprima(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 2;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[2][i][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, -1.0, 0.0)) * pieza[2][i][j]->transformation;
            rotar(pieza[2][0][0], pieza[2][2][0], pieza[2][2][2], pieza[2][0][2]);
            rotar(pieza[2][0][1], pieza[2][1][0], pieza[2][2][1], pieza[2][1][2]);
            naiveSolver->movimiento(11);
            return true;
        }
        return false;
    }
    bool F(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 0;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][0][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0)) * pieza[i][0][j]->transformation;
            rotar(pieza[0][0][0], pieza[0][0][2], pieza[2][0][2], pieza[2][0][0]);
            rotar(pieza[0][0][1], pieza[1][0][2], pieza[2][0][1], pieza[1][0][0]);
            naiveSolver->movimiento(3);
            return true;
        }
        return false;
    }
    bool Fprima(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 0;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][0][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, 1.0)) * pieza[i][0][j]->transformation;
            rotar(pieza[0][0][0], pieza[2][0][0], pieza[2][0][2], pieza[0][0][2]);
            rotar(pieza[0][0][1], pieza[1][0][0], pieza[2][0][1], pieza[1][0][2]);
            naiveSolver->movimiento(12);
            return true;
        }
        return false;
    }
    bool S(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 1;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][1][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0)) * pieza[i][1][j]->transformation;
            rotar(pieza[0][1][0], pieza[0][1][2], pieza[2][1][2], pieza[2][1][0]);
            rotar(pieza[0][1][1], pieza[1][1][2], pieza[2][1][1], pieza[1][1][0]);
            naiveSolver->movimiento(4);
            return true;
        }
        return false;
    }
    bool Sprima(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 1;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][1][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, 1.0)) * pieza[i][1][j]->transformation;
            rotar(pieza[0][1][0], pieza[2][1][0], pieza[2][1][2], pieza[0][1][2]);
            rotar(pieza[0][1][1], pieza[1][1][0], pieza[2][1][1], pieza[1][1][2]);
            naiveSolver->movimiento(13);
            return true;
        }
        return false;
    }
    bool B(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 2;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][2][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, 1.0)) * pieza[i][2][j]->transformation;
            rotar(pieza[0][2][0], pieza[2][2][0], pieza[2][2][2], pieza[0][2][2]);
            rotar(pieza[0][2][1], pieza[1][2][0], pieza[2][2][1], pieza[1][2][2]);
            naiveSolver->movimiento(5);
            return true;
        }
        return false;
    }
    bool Bprima(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 2;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][2][j]->transformation = glm::rotate(identity, (float)G90, glm::vec3(0.0, 0.0, -1.0)) * pieza[i][2][j]->transformation;
            rotar(pieza[0][2][0], pieza[0][2][2], pieza[2][2][2], pieza[2][2][0]);
            rotar(pieza[0][2][1], pieza[1][2][2], pieza[2][2][1], pieza[1][2][0]);
            naiveSolver->movimiento(14);
            return true;
        }
        return false;
    }
    bool R(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 0;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][0]->transformation = glm::rotate(identity, (float)G90, glm::vec3(-1.0, 0.0, 0.0)) * pieza[i][j][0]->transformation;
            rotar(pieza[0][0][0], pieza[2][0][0], pieza[2][2][0], pieza[0][2][0]);
            rotar(pieza[0][1][0], pieza[1][0][0], pieza[2][1][0], pieza[1][2][0]);
            naiveSolver->movimiento(6);
            return true;
        }
        return false;
    }
    bool Rprima(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 0;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][0]->transformation = glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0)) * pieza[i][j][0]->transformation;
            rotar(pieza[0][0][0], pieza[0][2][0], pieza[2][2][0], pieza[2][0][0]);
            rotar(pieza[0][1][0], pieza[1][2][0], pieza[2][1][0], pieza[1][0][0]);
            naiveSolver->movimiento(15);
            return true;
        }
        return false;
    }
    bool M(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 1;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][1]->transformation = glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0)) * pieza[i][j][1]->transformation;
            rotar(pieza[0][0][1], pieza[0][2][1], pieza[2][2][1], pieza[2][0][1]);
            rotar(pieza[0][1][1], pieza[1][2][1], pieza[2][1][1], pieza[1][0][1]);
            naiveSolver->movimiento(7);
            return true;
        }
        return false;
    }
    bool Mprima(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 1;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][1]->transformation = glm::rotate(identity, (float)G90, glm::vec3(-1.0, 0.0, 0.0)) * pieza[i][j][1]->transformation;
            rotar(pieza[0][0][1], pieza[2][0][1], pieza[2][2][1], pieza[0][2][1]);
            rotar(pieza[0][1][1], pieza[1][0][1], pieza[2][1][1], pieza[1][2][1]);
            naiveSolver->movimiento(16);
            return true;
        }
        return false;
    }
    bool L(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 2;
        gradoAnimacion = g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][2]->transformation = glm::rotate(identity, (float)G90, glm::vec3(1.0, 0.0, 0.0)) * pieza[i][j][2]->transformation;
            rotar(pieza[0][0][2], pieza[0][2][2], pieza[2][2][2], pieza[2][0][2]);
            rotar(pieza[0][1][2], pieza[1][2][2], pieza[2][1][2], pieza[1][0][2]);
            naiveSolver->movimiento(8);
            return true;
        }
        return false;
    }
    bool Lprima(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 2;
        gradoAnimacion = -g;
        if (g >= G90) {
            ejeAnimacion = -1;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    pieza[i][j][2]->transformation = glm::rotate(identity, (float)G90, glm::vec3(-1.0, 0.0, 0.0)) * pieza[i][j][2]->transformation;
            rotar(pieza[0][0][2], pieza[2][0][2], pieza[2][2][2], pieza[0][2][2]);
            rotar(pieza[0][1][2], pieza[1][0][2], pieza[2][1][2], pieza[1][2][2]);
            naiveSolver->movimiento(17);
            return true;
        }
        return false;
    }
    bool Y(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 4;
        gradoAnimacion = -g;
        if (g >= G90)
            return U(3.0) && Eprima(3.0) && Dprima(3.0);
        return false;
    }
    bool Yprima(float g) {
        ejeAnimacion = ejeY;
        iAnimacion = 4;
        gradoAnimacion = g;
        if (g >= G90)
            return Uprima(3.0) && E(3.0) && D(3.0);
        return false;
    }
    bool Z(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 4;
        gradoAnimacion = -g;
        if (g >= G90)
            return F(3.0) && S(3.0) && Bprima(3.0);
        return false;
    }
    bool Zprima(float g) {
        ejeAnimacion = ejeZ;
        iAnimacion = 4;
        gradoAnimacion = g;
        if (g >= G90)
            return Fprima(3.0) && Sprima(3.0) && B(3.0);
        return false;
    }
    bool X(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 4;
        gradoAnimacion = -g;
        if (g >= G90)
            return R(3.0) && Mprima(3.0) && Lprima(3.0);
        return false;
    }
    bool Xprima(float g) {
        ejeAnimacion = ejeX;
        iAnimacion = 4;
        gradoAnimacion = g;
        if (g >= G90)
            return Rprima(3.0) && M(3.0) && L(3.0);
        return false;
    }

    void separar() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                pieza[i][0][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.0, 0.1)) * pieza[i][0][j]->transformation;
                pieza[i][2][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.0, -0.1)) * pieza[i][2][j]->transformation;
                pieza[i][j][0]->transformation = glm::translate(identity, glm::vec3(0.1, 0.0, 0.0)) * pieza[i][j][0]->transformation;
                pieza[i][j][2]->transformation = glm::translate(identity, glm::vec3(-0.1, 0.0, 0.0)) * pieza[i][j][2]->transformation;
                pieza[0][i][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.1, 0.0)) * pieza[0][i][j]->transformation;
                pieza[2][i][j]->transformation = glm::translate(identity, glm::vec3(0.0, -0.1, 0.0)) * pieza[2][i][j]->transformation;
            }
    }

    void juntar() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                pieza[i][0][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.0, -0.1)) * pieza[i][0][j]->transformation;
                pieza[i][2][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.0, 0.1)) * pieza[i][2][j]->transformation;
                pieza[i][j][0]->transformation = glm::translate(identity, glm::vec3(-0.1, 0.0, 0.0)) * pieza[i][j][0]->transformation;
                pieza[i][j][2]->transformation = glm::translate(identity, glm::vec3(0.1, 0.0, 0.0)) * pieza[i][j][2]->transformation;
                pieza[0][i][j]->transformation = glm::translate(identity, glm::vec3(0.0, -0.1, 0.0)) * pieza[0][i][j]->transformation;
                pieza[2][i][j]->transformation = glm::translate(identity, glm::vec3(0.0, 0.1, 0.0)) * pieza[2][i][j]->transformation;
            }
    }


    bool movimiento(int i, float g) {
        return (this->*movimientos[i])(std::max(g,0.0f));
    }
    void scramble(int n) {
        //std::cout << "mori\n";
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    pieza[i][j][k]->scramble( (rand() % 18+1)*10);
                  
        for (int i = 0; i < n; ++i) {

            //std::cout << "moriiiiii\n";
            (this->*movimientos[rand() % 18])(G90 + 1);
        }

        //std::cout << "mori2\n";
    }

    ~MegaCubo() {
        delete naiveSolver;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    delete pieza[i][j][k];
    }
};
Cubo* rubik;
MegaCubo* megaRubik;

void mostrarMenu() {
    std::cout << "######################################################################" << std::endl;
    std::cout << "                      CUBO DE RUBIK FINAL" << std::endl;
    std::cout << "######################################################################" << std::endl << std::endl;
    std::cout << "CLICK IZQUIERDO SOBRE FONDO ----- Mover Camara" << std::endl;
    std::cout << "CLICK IZQUIERDO SOBRE PIEZAS ----- Mover camadas de piezas (Movimientos del Cubo)" << std::endl;
    std::cout << "CLICK DERECHO  ----- Resetear camara " << std::endl;
    std::cout << "RUEDA DEL RATÓN  ----- Alejar o acercar la camara " << std::endl;
    std::cout << "     T         ----- Activar o desactivar Texturas" << std::endl;
    std::cout << "     S         ----- Revolver piezas" << std::endl;
    std::cout << "     R         ----- Ejecutar Solver (Resolver cubo)" << std::endl;
    std::cout << "     Z         ----- Separar piezas" << std::endl;
    std::cout << "     X         ----- Juntar piezas\n\n\n" << std::endl ;

    std::cout << " --- *** ESCOGE EL CUBO QUE QUIERES EJECUTAR *** --- " << std::endl << std::endl;


    std::cout << " - Cubo 3x3 normal ----> 1\n";
    std::cout << " - Cubo 3x3 mirror ----> 2\n";
    std::cout << " - MegaCubo 9x9x9  ----> 3\n";
    std::cout << " - MegaCubo 9x9x9 mirror (Beta) ----> 4\n";
    std::cout << " OPCION: ";
}


void deleteBuffers() 
{
	glDeleteVertexArrays(numobjects, VAOs);
	glDeleteBuffers(9, buffers);
    glDeleteBuffers(18*4, buffersEtiquetas);
}


void initobject(GLuint object, GLfloat * vert, GLint sizevert, GLfloat * col, GLint sizecol, GLubyte * inds, GLint sizeind, GLenum type)
{
  int offset = object * 3;
  std::cout << object << ' ';
  std::cout << offset << ' '<<std::endl;
  glBindVertexArray(VAOs[object]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices+offset]) ; 
  glBufferData(GL_ARRAY_BUFFER, sizevert, vert,GL_STATIC_DRAW);
  // Use layout location 0 for the vertices
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors+offset]) ; 
  glBufferData(GL_ARRAY_BUFFER, sizecol, col,GL_STATIC_DRAW);
  // Use layout location 1 for the colors
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements+offset]) ; 
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeind, inds,GL_STATIC_DRAW);
  PrimType[object] = type;
  NumElems[object] = sizeind;
  // Prevent further modification of this VAO by unbinding it
  glBindVertexArray(0);
}
void initEtiqueta(GLuint object, GLfloat* vert, GLint sizevert, GLfloat* col, GLint sizecol, GLubyte* inds, GLint sizeind, GLubyte* texs, GLint sizetex, GLenum type)
{

    int offset = object * 4;
    offset-=12;
    std::cout << object << ' ';
    std::cout << offset << ' ' << std::endl;
    glBindVertexArray(VAOs[object]);
    glBindBuffer(GL_ARRAY_BUFFER, buffersEtiquetas[Vertices + offset]);
    glBufferData(GL_ARRAY_BUFFER, sizevert, vert, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffersEtiquetas[Colors + offset]);
    glBufferData(GL_ARRAY_BUFFER, sizecol, col, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    
    glBindBuffer(GL_ARRAY_BUFFER, buffersEtiquetas[2 + offset]);
    glBufferData(GL_ARRAY_BUFFER, sizetex, texs, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffersEtiquetas[3 + offset]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeind, inds, GL_STATIC_DRAW);
    
    

    PrimType[object] = type;
    NumElems[object] = sizeind;
    glBindVertexArray(0);
}

void initTextures() {
    glGenTextures(1, &texturaNula);
    glBindTexture(GL_TEXTURE_2D, texturaNula);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    std::string fileName = "C:\\Users\\Jose\\Desktop\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\Cubo_Rubik_4\\texturas\\null.jpg";
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << fileName << std::endl << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // std::cout << "Texturas\nTexturas\nTexturas\nTexturas\nTexturas\nTexturas\n";
    char letra[6] = {'Z','u','c','s','p','G'};
    for (int i = 0; i < 54; ++i) {
        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        std::string fileName = "C:\\Users\\Jose\\Desktop\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\Cubo_Rubik_4\\texturas\\";
        if (cubeType & 1) {
            fileName += "mirror\\"; 
        }
        else {
            fileName += "letras\\";
        }
        //fileName += "U.jpg";
        fileName += letra[i/9];
        fileName += (char)((i % 9) + 48);
        fileName += ".jpg";
        unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << fileName <<std::endl<<"Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
}
void drawobject(GLuint object) 
{
  glBindVertexArray(VAOs[object]);
  glDrawElements(PrimType[object], NumElems[object], GL_UNSIGNED_BYTE, 0); 
  glBindVertexArray(0);
}


void display(GLFWwindow* window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  modelview = glm::lookAt(glm::vec3(sin(radY) * cos(radX), cos(radY), sin(radY) * sin(radX)) * rEye, 
      glm::vec3(0.0,0.0,0.0), glm::vec3(sin(anguloUp), cos(anguloUp), 0));
 
  if (cubeType < 2) {
      rubik->realizarMovimientos();
      rubik->draw();
  }
  else {
      megaRubik->realizarMovimientos();
      megaRubik->draw();
  }
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT)
  {
    if (action == GLFW_RELEASE && cubeType < 2)
	{
      piezaSeleccionada = -1;
      rubik->terminarGiro();
    }
    else if (action == GLFW_PRESS)
	{
      anguloUp = 0.0;
	  double x, y;
      
	  glfwGetCursorPos(window, &x, &y);
      
      float gradoX = ((float)x * 3 / 50)-15.0;
      float gradoY = ((float)y * 3 / 50)-15.0;
      //std::cout << gradoX << ' ' << gradoY << std::endl;
      
      glm::vec3 v(sin(G180 - radY) * cos(radX + G180), cos(G180 - radY), sin(G180 - radY) * sin(radX + G180));
      glm::vec3 u(sin(G90 - radY) * cos(radX + G180), cos(G90 - radY), sin(G90 - radY) * sin(radX + G180));
      glm::vec3 w(cos(radX -G90),0, sin(radX - G90));

      gradoY = ((90.0+gradoY)*G180)/180;
      gradoX = (gradoX * G180) / 180;
      if(cubeType<2)
      piezaSeleccionada= rubik->seleccionarMejor(glm::vec3(sin(radY) * cos(radX)*rEye , cos(radY) * rEye, sin(radY) * sin(radX) * rEye),
          v*sin(gradoY) * cos(gradoX) + u * cos(gradoY) + w* sin(gradoY) * sin(gradoX));
      mouseoldx = (int)x ; 
	  mouseoldy = (int)y ; // so we can move wrt x , y 
    }
  }
  else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS )
  { 
    radY = 1.5 ;
    radX = 1.5;
    anguloUp = 0.0;
    center.x = 0;
    center.y = 0;
    center.z = 0;
    rEye = 5;
	glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
  }
}


void mousedrag_callback(GLFWwindow* window, double x, double y)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		int yloc = (int)y - mouseoldy;
        int xloc = (int)x - mouseoldx;
        if (cubeType>1||piezaSeleccionada == -1) {
            radX += 0.005f * xloc;
            radY -= 0.005f * yloc;		
            radY = std::max(std::min(radY, 3.14f), 0.001f);
            mouseoldy = (int)y;
            mouseoldx = (int)x;
        }
        else {
            glm::vec3 v(sin(G180 - radY) * cos(radX + G180), cos(G180 - radY), sin(G180 - radY) * sin(radX + G180));
            glm::vec3 u(sin(G90 - radY) * cos(radX + G180), cos(G90 - radY), sin(G90 - radY) * sin(radX + G180));
            glm::vec3 w(cos(radX - G90), 0, sin(radX - G90));
            float gradoY = G90 + (float)(y- mouseoldy) * G180 / 3000;
            float gradoX = (float)(x - mouseoldx) * G180 / 3000;
            v= glm::vec3(sin(radY) * cos(radX) * rEye, cos(radY) * rEye, sin(radY) * sin(radX) * rEye) +
                (v* sin(gradoY)* cos(gradoX) + u * cos(gradoY) + w * sin(gradoY) * sin(gradoX) )* rEye;

            rubik->moverMouse(v);
        }

		glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
	}
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset < 0 && rEye<12 || (yoffset > 0 && rEye>3))
        rEye -= yoffset;
}

int flag = 0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{   
    
    if (cubeType < 2) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            deleteBuffers();
            glfwSetWindowShouldClose(window, true);
        }
        else if (key == GLFW_KEY_S && action == GLFW_PRESS && rubik->movimientosPendientes.size() == 0) {
                rubik->scramble(200);
        }
        else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
                rubik->OnOffTexture();
        }
        else if (key == GLFW_KEY_R && action == GLFW_PRESS && rubik->movimientosPendientes.size() == 0) {

                rubik->generarSolucion();
        }
        else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
            rubik->separar();
            flag++;
        }
        else if (key == GLFW_KEY_X && action == GLFW_PRESS && flag > 0) {
            rubik->juntar();
            flag--;
        }
    }
    else {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            deleteBuffers();
            glfwSetWindowShouldClose(window, true);
        }
        else if (key == GLFW_KEY_S && action == GLFW_PRESS && megaRubik->movimientosPendientes.size() == 0) {
            megaRubik->scramble(200);
        }
        else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
            megaRubik->OnOffTexture();
        }
        else if (key == GLFW_KEY_R && action == GLFW_PRESS && megaRubik->movimientosPendientes.size() == 0) {

            megaRubik->generarSolucion();
        }
        else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
            megaRubik->separar();
            flag++;
        }
        else if (key == GLFW_KEY_X && action == GLFW_PRESS && flag > 0) {
            megaRubik->juntar();
            flag--;
        }
    }
}


void reshape_callback(GLFWwindow* window, int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  
  if (h > 0)
  {
	  projection = glm::perspective(30.0f / 180.0f * glm::pi<float>(), (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
	  glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
  }
 
}

void init (void) 
{

  glClearColor (0.5, 0.5, 0.5, 0.5);
  glEnable(GL_DEPTH_TEST);

  projection = glm::mat4(1.0f);
  center.x = 0;
  center.y = 0;
  center.z = 0;

  glm::vec3 pos(sin(radY) * cos(radX), cos(radY), sin(radY) * sin(radX));
  modelview = glm::lookAt(pos * 4.0f, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


  glGenVertexArrays(numobjects, VAOs);
  glGenBuffers(9, buffers);
  glGenBuffers(18*4, buffersEtiquetas);


  initobject(CENTRO, (GLfloat*)verticesCentro, sizeof(verticesCentro), (GLfloat*)coloresCentro, sizeof(coloresCentro), (GLubyte*)indicesCentro, sizeof(indicesCentro), GL_TRIANGLES);
  initobject(ARISTA, (GLfloat*)verticesArista, sizeof(verticesArista), (GLfloat*)coloresArista, sizeof(coloresArista), (GLubyte*)indicesArista, sizeof(indicesArista), GL_TRIANGLES);
  initobject(VERTICE, (GLfloat*)verticesVertice, sizeof(verticesVertice), (GLfloat*)coloresVertice, sizeof(coloresVertice), (GLubyte*)indicesVertice, sizeof(indicesVertice), GL_TRIANGLES);


  //sin texturas
  initEtiqueta(ETIQUETA_BL1, (GLfloat*)verticesEtiquetaUp, sizeof(verticesEtiquetaUp), (GLfloat*)coloresEtiquetaBlanco, sizeof(coloresEtiquetaBlanco), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_RO1, (GLfloat*)verticesEtiquetaUp, sizeof(verticesEtiquetaUp), (GLfloat*)coloresEtiquetaRojo, sizeof(coloresEtiquetaRojo), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_AZ1, (GLfloat*)verticesEtiquetaUp, sizeof(verticesEtiquetaUp), (GLfloat*)coloresEtiquetaAzul, sizeof(coloresEtiquetaAzul), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_NA1, (GLfloat*)verticesEtiquetaUp, sizeof(verticesEtiquetaUp), (GLfloat*)coloresEtiquetaNaranja, sizeof(coloresEtiquetaNaranja), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_VE1, (GLfloat*)verticesEtiquetaUp, sizeof(verticesEtiquetaUp), (GLfloat*)coloresEtiquetaVerde, sizeof(coloresEtiquetaVerde), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_AM1, (GLfloat*)verticesEtiquetaUp, sizeof(verticesEtiquetaUp), (GLfloat*)coloresEtiquetaAmarillo, sizeof(coloresEtiquetaAmarillo), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);

  initEtiqueta(ETIQUETA_BL2, (GLfloat*)verticesEtiquetaFront, sizeof(verticesEtiquetaFront), (GLfloat*)coloresEtiquetaBlanco, sizeof(coloresEtiquetaBlanco), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_RO2, (GLfloat*)verticesEtiquetaFront, sizeof(verticesEtiquetaFront), (GLfloat*)coloresEtiquetaRojo, sizeof(coloresEtiquetaRojo), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_AZ2, (GLfloat*)verticesEtiquetaFront, sizeof(verticesEtiquetaFront), (GLfloat*)coloresEtiquetaAzul, sizeof(coloresEtiquetaAzul), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_NA2, (GLfloat*)verticesEtiquetaFront, sizeof(verticesEtiquetaFront), (GLfloat*)coloresEtiquetaNaranja, sizeof(coloresEtiquetaNaranja), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_VE2, (GLfloat*)verticesEtiquetaFront, sizeof(verticesEtiquetaFront), (GLfloat*)coloresEtiquetaVerde, sizeof(coloresEtiquetaVerde), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_AM2, (GLfloat*)verticesEtiquetaFront, sizeof(verticesEtiquetaFront), (GLfloat*)coloresEtiquetaAmarillo, sizeof(coloresEtiquetaAmarillo), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);

  initEtiqueta(ETIQUETA_BL3, (GLfloat*)verticesEtiquetaLat, sizeof(verticesEtiquetaLat), (GLfloat*)coloresEtiquetaBlanco, sizeof(coloresEtiquetaBlanco), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_RO3, (GLfloat*)verticesEtiquetaLat, sizeof(verticesEtiquetaLat), (GLfloat*)coloresEtiquetaRojo, sizeof(coloresEtiquetaRojo), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_AZ3, (GLfloat*)verticesEtiquetaLat, sizeof(verticesEtiquetaLat), (GLfloat*)coloresEtiquetaAzul, sizeof(coloresEtiquetaAzul), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_NA3, (GLfloat*)verticesEtiquetaLat, sizeof(verticesEtiquetaLat), (GLfloat*)coloresEtiquetaNaranja, sizeof(coloresEtiquetaNaranja), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_VE3, (GLfloat*)verticesEtiquetaLat, sizeof(verticesEtiquetaLat), (GLfloat*)coloresEtiquetaVerde, sizeof(coloresEtiquetaVerde), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initEtiqueta(ETIQUETA_AM3, (GLfloat*)verticesEtiquetaLat, sizeof(verticesEtiquetaLat), (GLfloat*)coloresEtiquetaAmarillo, sizeof(coloresEtiquetaAmarillo), (GLubyte*)indicesEtiqueta, sizeof(indicesEtiqueta), (GLubyte*)texturasEtiqueta, sizeof(texturasEtiqueta), GL_TRIANGLES);
  initTextures();
  std::string vertex_shader_path;
  std::string fragment_shader_path;

#ifdef __unix__         
  vertex_shader_path = "//home//manuel//Documents//Projects//OpenGL//GLFW_GLAD_GLUT_GLEW_cmake_project//src//mytest1_glut//shaders//nop.vert";
  fragment_shader_path = "//home//manuel//Documents//Projects//OpenGL//GLFW_GLAD_GLUT_GLEW_cmake_project//src//mytest1_glut//shaders//nop.frag";

#elif defined(_WIN32) || defined(WIN32) 
  vertex_shader_path = "C:\\Users\\Jose\\Desktop\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\Cubo_Rubik_4\\shaders//nop.vert";
  fragment_shader_path = "C:\\Users\\Jose\\Desktop\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\Cubo_Rubik_4\\shaders//nop.frag";
#endif


  // Initialize the shader program
  vertexshader = initshaders(GL_VERTEX_SHADER, vertex_shader_path.c_str());
  fragmentshader = initshaders(GL_FRAGMENT_SHADER, fragment_shader_path.c_str());

  shaderprogram = initprogram(vertexshader, fragmentshader) ;

  // Get the positions of the uniform variables
  projectionPos = glGetUniformLocation(shaderprogram, "projection");
  modelviewPos = glGetUniformLocation(shaderprogram, "modelview");
  // Pass the projection and modelview matrices to the shader
  glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
  glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

}

int main(int argc, char** argv)
{
    mostrarMenu();
    
    do {
        std::cin >> cubeType;
        cubeType--;
    } while (cubeType < 0 || cubeType > 3);
    if(cubeType<2)
    rubik = new Cubo(cubeType&1,glm::vec3(0,0,0));
    else
    megaRubik = new MegaCubo(cubeType&1);



  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(500, 500, "Simple Demo with Shaders", NULL, NULL);
  
  if (window == NULL)
  {
	  std::cout << "Failed to create GLFW window" << std::endl;
	  glfwTerminate();
	  return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetWindowPos(window, 100, 100);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
	  std::cout << "Failed to initialize GLAD" << std::endl;
	  return -1;
  }

  init (); // Always initialize first

  glfwSetFramebufferSizeCallback(window, reshape_callback);	//glutReshapeFunc(reshape) ;
  glfwSetKeyCallback(window, key_callback);					//glutKeyboardFunc(keyboard);
  glfwSetMouseButtonCallback(window, mouse_callback);		//glutMouseFunc(mouse) ;
  glfwSetCursorPosCallback(window, mousedrag_callback);		//glutMotionFunc(mousedrag) ;
  glfwSetScrollCallback(window, scroll_callback);

  // First scene render
  reshape_callback(window, 500, 500);
  display(window); //glutDisplayFunc(display); 
  

  // render loop
  // Start the main code
  while (!glfwWindowShouldClose(window)) //glutMainLoop(); 
  {
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  display(window); //glutDisplayFunc(display); 

	  glfwSwapBuffers(window);
	  glfwPollEvents();

	  //glFlush();
  }
  delete rubik;
  delete megaRubik;
  deleteBuffers(); 
  
  glfwDestroyWindow(window);

  glfwTerminate();
  
  return 0;  
}
