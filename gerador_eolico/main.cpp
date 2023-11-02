// Loading .obj files in OpenGL
// obtido deste site:
// http://netization.blogspot.com/2014/10/loading-obj-files-in-opengl.html
// https://github.com/nanosmooth/opengl_objloader

//header

#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<vector>
#include<cstring>
#include <string>
using namespace std;
#include "objloader.h"
//texture
#include "texturas/arvore_image.h"
#include "texturas/predio_image.h"
#include "texturas/praca_image.h"
#include "texturas/bg_image.h"
#include "texturas/veloci_image.h"
#include "texturas/ponteiro_image.h"

#ifdef GL_VERSION_1_1
static GLuint *texName = new GLuint[4];
#endif


// variaveis potencia = nTurbinas * (rAr*(velocidade * velocidade * velocidade) * area)/2;
float rotate_angle;
float velocidade = 0;
double potencia = 0;
int nTurbinas = 1;
double raio = 1.0;
float rAr = 1.225;
float spin = 0;
//int m,n;



//indice de luz de cada nivel 
GLfloat pot1 = 0;
GLfloat pot2 = 0;
GLfloat pot3 = 0;
GLfloat pot4 = 0;
GLfloat pot5 = 0;
GLfloat pot6 = 0;

//vetores das meshs
//arvore
std::vector <point3> arvore_vertex;
std::vector <point3> arvore_normal;
std::vector <point2> arvore_uv;
//

//predio
std::vector <point3> predio_vertex;
std::vector <point3> predio_normal;
std::vector <point2> predio_uv;

//praca
std::vector <point3> praca_vertex;
std::vector <point3> praca_normal;
std::vector <point2> praca_uv;

//helice
std::vector <point3> helice_vertex;
std::vector <point3> helice_normal;
std::vector <point2> helice_uv;

//poste da helice
std::vector <point3> poste_vertex;
std::vector <point3> poste_normal;
std::vector <point2> poste_uv;

//Estagios de potencia
//estagio1
std::vector <point3> estagio1_vertex;
std::vector <point3> estagio1_normal;
std::vector <point2> estagio1_uv;

//estagio2
std::vector <point3> estagio2_vertex;
std::vector <point3> estagio2_normal;
std::vector <point2> estagio2_uv;

//estagio3
std::vector <point3> estagio3_vertex;
std::vector <point3> estagio3_normal;
std::vector <point2> estagio3_uv;

//estagio4
std::vector <point3> estagio4_vertex;
std::vector <point3> estagio4_normal;
std::vector <point2> estagio4_uv;

//estagio5
std::vector <point3> estagio5_vertex;
std::vector <point3> estagio5_normal;
std::vector <point2> estagio5_uv;

//estagio6
std::vector <point3> estagio6_vertex;
std::vector <point3> estagio6_normal;
std::vector <point2> estagio6_uv;

//bg
std::vector <point3> bg_vertex;
std::vector <point3> bg_normal;
std::vector <point2> bg_uv;

//definição de material e luz
void material1()
{
	GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 0.0 };
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void material2()
{
	GLfloat mat_ambient[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 0.0 };
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void materialLetra()
{
	GLfloat mat_ambient[] = { 0.6, 0.6, 0.8, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.8, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.1, 0.8, 1.0 };
	GLfloat mat_emission[] = { 0.7, 0.7, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 0.0 };
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}
// material com emissao variavel
void materialVariavel(GLfloat delta)
{
	GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat mat_specular[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_emission[] = { delta, delta, delta * (GLfloat)0.8, 1.0 };
	GLfloat mat_shininess[] = { 0.0 };
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}


void light()
{
	GLenum lightID = GL_LIGHT0;
	GLfloat light_ambient[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_position[] = {0, 10, -20, 0};
	GLfloat light_spotDirection[] = {0.0, 0.0, 0.0};
	GLfloat light_spotExponent = 0.0;
	GLfloat light_spotCutoff = 90.000005f;
	GLfloat light_constantAttenuation = 1.0;
	GLfloat light_linearAttenuation = 0.0;
	GLfloat light_quadraticAttenuation = 0.0;
	
	 glEnable( lightID );
        glLightfv( lightID, GL_AMBIENT, light_ambient);
        glLightfv( lightID, GL_DIFFUSE, light_diffuse);
        glLightfv( lightID, GL_SPECULAR,light_specular );
        glLightfv( lightID, GL_POSITION,light_position );
        glLightfv( lightID, GL_SPOT_DIRECTION, light_spotDirection);
        glLightf( lightID, GL_SPOT_EXPONENT, light_spotExponent );
        glLightf( lightID, GL_SPOT_CUTOFF,light_spotCutoff );
        glLightf( lightID, GL_CONSTANT_ATTENUATION, light_constantAttenuation );
        glLightf( lightID, GL_LINEAR_ATTENUATION, light_linearAttenuation );
        glLightf( lightID, GL_QUADRATIC_ATTENUATION, light_quadraticAttenuation );
	
	
}
//
void loadTexture(){


   	glGenTextures(3, texName);
   	glBindTexture(GL_TEXTURE_2D, texName[0]);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	#ifdef GL_VERSION_1_1
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, arvore_image.width, arvore_image.height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, arvore_image.pixel_data);
	#else
    	glTexImage2D(GL_TEXTURE_2D, 0, 3, arvore_image.width, arvore_image.height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, arvore_image.pixel_data);
	#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	#ifdef GL_VERSION_1_1   	
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, predio_image.width, predio_image.height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, predio_image.pixel_data);
	#else
    	glTexImage2D(GL_TEXTURE_2D, 0, 3, predio_image.width, predio_image.height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, predio_image.pixel_data);
	#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	#ifdef GL_VERSION_1_1   	
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, praca_image.width, praca_image.height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, praca_image.pixel_data);
	#else
    	glTexImage2D(GL_TEXTURE_2D, 0, 3, praca_image.width, praca_image.height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, praca_image.pixel_data);
	#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
	glBindTexture(GL_TEXTURE_2D, texName[3]);
	
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	#ifdef GL_VERSION_1_1   	
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bg_image.width, bg_image.height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, bg_image.pixel_data);
	#else
    	glTexImage2D(GL_TEXTURE_2D, 0, 3, bg_image.width, bg_image.height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, bg_image.pixel_data);
	#endif
}

void init()
{
	
	glClearColor (0.0,0.0,0.4,1.0);
	glShadeModel (GL_SMOOTH);
	loadTexture();
	//habilita e configura a iluminação
	light();
   	glEnable(GL_LIGHTING);
   	glEnable(GL_LIGHT0);
   	glEnable(GL_DEPTH_TEST); 
   	//carrega as malhas 
	loadObj("mesh/arvore.obj",arvore_vertex, arvore_normal, arvore_uv);
   	loadObj("mesh/predio.obj",predio_vertex, predio_normal, predio_uv);
   	loadObj("mesh/praca.obj",praca_vertex, praca_normal, praca_uv);
   	loadObj("mesh/helice.obj",helice_vertex, helice_normal, helice_uv);
   	loadObj("mesh/poste.obj",poste_vertex, poste_normal, poste_uv);
   	loadObj("mesh/estagio1.obj",estagio1_vertex, estagio1_normal, estagio1_uv);
   	loadObj("mesh/estagio2.obj",estagio2_vertex, estagio2_normal, estagio2_uv);
   	loadObj("mesh/estagio3.obj",estagio3_vertex, estagio3_normal, estagio3_uv);
   	loadObj("mesh/estagio4.obj",estagio4_vertex, estagio4_normal, estagio4_uv);
   	loadObj("mesh/estagio5.obj",estagio5_vertex, estagio5_normal, estagio5_uv);
   	loadObj("mesh/estagio6.obj",estagio6_vertex, estagio6_normal, estagio6_uv);
   	loadObj("mesh/bg.obj",bg_vertex, bg_normal, bg_uv);
}



void reshape(int w,int h)
{    
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   	gluPerspective (50, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
   	gluLookAt(19.0, 18.0, 22.0, 0.0, 0.0, 0.0, 0.0 , 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
}

void drawArvore()
{
	glEnable(GL_TEXTURE_2D);
	#ifdef GL_VERSION_1_1
   	glBindTexture(GL_TEXTURE_2D, texName[0]);
	#endif
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < arvore_vertex.size();i++){
  
   		glTexCoord2f(arvore_uv[i].x,arvore_uv[i].y);
   		glNormal3f(arvore_normal[i].x,arvore_normal[i].y,arvore_normal[i].z);	
   		glVertex3f(arvore_vertex[i].x,arvore_vertex[i].y,arvore_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawPredio()
{
	glEnable(GL_TEXTURE_2D);
	#ifdef GL_VERSION_1_1
   	glBindTexture(GL_TEXTURE_2D, texName[1]);
	#endif
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < predio_vertex.size();i++){
  
   		glTexCoord2f(predio_uv[i].x,predio_uv[i].y);
   		glNormal3f(predio_normal[i].x,predio_normal[i].y,predio_normal[i].z);	
   		glVertex3f(predio_vertex[i].x,predio_vertex[i].y,predio_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawPraca()
{
	glEnable(GL_TEXTURE_2D);
	#ifdef GL_VERSION_1_1
   	glBindTexture(GL_TEXTURE_2D, texName[2]);
	#endif
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < praca_vertex.size();i++){
  
   		glTexCoord2f(praca_uv[i].x,praca_uv[i].y);
   		glNormal3f(praca_normal[i].x,praca_normal[i].y,praca_normal[i].z);	
   		glVertex3f(praca_vertex[i].x,praca_vertex[i].y,praca_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawHelice()
{
	spin=spin-velocidade;
	if(spin<0)
	spin=spin+360.0;
	if(spin>360)
	spin=spin-360.0;
	
	
	glPushMatrix();
	glTranslatef(0.777,10.94,9.912);
	glScalef(raio/3,raio/3, 1);
	glRotatef(spin, 0, 0, 1);
	
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < helice_vertex.size();i++){
  
   		glTexCoord2f(helice_uv[i].x,helice_uv[i].y);
   		glNormal3f(helice_normal[i].x,helice_normal[i].y,helice_normal[i].z);	
   		glVertex3f(helice_vertex[i].x,helice_vertex[i].y,helice_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawPoste()
{

	glPushMatrix();
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < poste_vertex.size();i++){
  
   		glTexCoord2f(poste_uv[i].x,poste_uv[i].y);
   		glNormal3f(poste_normal[i].x,poste_normal[i].y,poste_normal[i].z);	
   		glVertex3f(poste_vertex[i].x,poste_vertex[i].y,poste_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}


void drawEstagio1()
{

	glPushMatrix();
	//material2();
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < estagio1_vertex.size();i++){
  
   		glTexCoord2f(estagio1_uv[i].x,estagio1_uv[i].y);
   		glNormal3f(estagio1_normal[i].x,estagio1_normal[i].y,estagio1_normal[i].z);	
   		glVertex3f(estagio1_vertex[i].x,estagio1_vertex[i].y,estagio1_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawEstagio2()
{

	glPushMatrix();
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < estagio2_vertex.size();i++){
  
   		glTexCoord2f(estagio2_uv[i].x,estagio2_uv[i].y);
   		glNormal3f(estagio2_normal[i].x,estagio2_normal[i].y,estagio2_normal[i].z);	
   		glVertex3f(estagio2_vertex[i].x,estagio2_vertex[i].y,estagio2_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawEstagio3()
{

	glPushMatrix();
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < estagio3_vertex.size();i++){
  
   		glTexCoord2f(estagio3_uv[i].x,estagio3_uv[i].y);
   		glNormal3f(estagio3_normal[i].x,estagio3_normal[i].y,estagio3_normal[i].z);	
   		glVertex3f(estagio3_vertex[i].x,estagio3_vertex[i].y,estagio3_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawEstagio4()
{

	glPushMatrix();
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < estagio4_vertex.size();i++){
  
   		glTexCoord2f(estagio4_uv[i].x,estagio4_uv[i].y);
   		glNormal3f(estagio4_normal[i].x,estagio4_normal[i].y,estagio4_normal[i].z);	
   		glVertex3f(estagio4_vertex[i].x,estagio4_vertex[i].y,estagio4_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawEstagio5()
{

	glPushMatrix();
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < estagio5_vertex.size();i++){
  
   		glTexCoord2f(estagio5_uv[i].x,estagio5_uv[i].y);
   		glNormal3f(estagio5_normal[i].x,estagio5_normal[i].y,estagio5_normal[i].z);	
   		glVertex3f(estagio5_vertex[i].x,estagio5_vertex[i].y,estagio5_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawEstagio6()
{

	glPushMatrix();
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < estagio6_vertex.size();i++){
  
   		glTexCoord2f(estagio6_uv[i].x,estagio6_uv[i].y);
   		glNormal3f(estagio6_normal[i].x,estagio6_normal[i].y,estagio6_normal[i].z);	
   		glVertex3f(estagio6_vertex[i].x,estagio6_vertex[i].y,estagio6_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void drawBg()
{
	glEnable(GL_TEXTURE_2D);
	#ifdef GL_VERSION_1_1
   	glBindTexture(GL_TEXTURE_2D, texName[3]);
	#endif
	glPushMatrix();
   	glBegin(GL_TRIANGLES);
   	for(int i = 0; i < bg_vertex.size();i++){
  
   		glTexCoord2f(bg_uv[i].x,bg_uv[i].y);
   		glNormal3f(bg_normal[i].x,bg_normal[i].y,bg_normal[i].z);	
   		glVertex3f(bg_vertex[i].x,bg_vertex[i].y,bg_vertex[i].z);
   	}
   	glEnd();
   	glDisable(GL_TEXTURE_2D);
 	glPopMatrix();
}

void escreve(string frase)
{


    glDepthFunc(GL_ALWAYS);

    int nFrase = frase.size(); // quantidade de characters
    glPushMatrix();
    glLoadIdentity();
    
    glRasterPos2f(-35.0,-45.0);//posiciona na tela
    glScalef(5.1,1.1,1.1);
    for(int i = 0; i < nFrase; i++)
    {
    	
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, int(frase[i]));
    }

    glPopMatrix();
    glDepthFunc(GL_LESS);

}

void display(void)
{  
   	glClearColor (0.0,0.0,0.4,1.0); 
   	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	glLoadIdentity();
   	//glPushMatrix();
   	//materialVariavel(0.1);
   	//drawBg();
   	//glPopMatrix();
   	materialVariavel(0.9);
   	drawBg();
   	glRotatef(rotate_angle *3, 0, 1, 0);
   		material2();
   	
   	material1();
   	drawArvore();
	material2();
   	drawPredio();
   	drawPraca();   	
   	drawHelice();
   	drawPoste();

   	
 	materialVariavel(pot1);  	
   	drawEstagio1();
 	materialVariavel(pot2);   	
   	drawEstagio2();
   	materialVariavel(pot3);
   	drawEstagio3();
   	materialVariavel(pot4);
   	drawEstagio4();
   	materialVariavel(pot5);
   	drawEstagio5();
   	materialVariavel(pot6);
        drawEstagio6();
   	rotate_angle += 0.01;
   	
   	materialLetra();
   	escreve(string("Velocidade do vento:")+to_string(velocidade).substr(0,5)+string("KM/h., Potencia: ")+to_string(
potencia).substr(0,5)+string("W, Diametro:")+to_string(
raio).substr(0,5));


   	glutSwapBuffers(); //swap the buffers

}

void Ativar(void)
{	
    //calcula potencia
    potencia = nTurbinas * (rAr*(velocidade * velocidade * velocidade) * raio * raio * 3.141516)/2;
    double alpha = 0;
	if(potencia <= 0)
	{
		pot1=pot2=pot3=pot4=pot5=pot6=0.0;
	}
	else if(potencia > 0 && potencia < 61250)
	{
        alpha = 0.3 + ((0.7 * potencia) / 61250);
		pot2=pot3=pot4=pot5=pot6=0.0;
		pot1=alpha;
	}
	else if(potencia >= 61250 && potencia < 122500)
	{
        alpha = 0.3 + (0.7 * (potencia - 61250) / 61250);
        	pot3=pot4=pot5=pot6=0.0;
		pot1=1;
		pot2=alpha; 
	}
	else if(potencia >= 122500 && potencia < 183750)
	{

        alpha = 0.3 + (0.7 * (potencia - 122500 ) / 61250);
		pot4=pot5=pot6=0.0;
		pot1=pot2=1;
		pot3=alpha; 
	}
	else if(potencia >= 183750 && potencia < 245000)
	{

        alpha = 0.3 + (0.7 * (potencia - 183750) / 61250);
		pot5=pot6=0.0;
		pot1=pot2=pot3=1;
		pot4=alpha;
	}
	else if(potencia >= 245000 && potencia < 306250)
	{

        alpha = 0.3 + (0.7 * (potencia - 245000) / 61250);
		pot6=0.0;
		pot1=pot2=pot3=pot4=1;
		pot5=alpha;
	}
	else if(potencia > 306250 && potencia < 367500)
	{
        alpha = 0.3 + (0.7 * (potencia - 306250) / 61250);
		pot1=pot2=pot3=pot4=pot5=1;
		pot6=alpha;
	}else {
		pot1=pot2=pot3=pot4=pot5=pot6=1.0;
	}
 }

void teclado(unsigned char tecla, int m, int n)
{
	if(tecla=='w' && velocidade <30)
	{
		velocidade = velocidade+0.10;
	} 
	if(tecla=='s')
	{	
		if(velocidade <=0)
		{
		velocidade = 0;
		}	
		else
		{
		velocidade = velocidade-0.10;
		}	
	} 
	if(tecla=='a')
	{
		rotate_angle = rotate_angle+0.25;
	} 
	if(tecla=='d')
	{
		rotate_angle = rotate_angle-0.25;
	} 
	if(tecla=='t' && raio < 4.90000000000000000000)
	{
		raio = raio+0.10000000000000000000000000;
	} 
	if(tecla=='g'&& raio >1.00000000000000000000000)
	{
		raio = raio-0.100000000000000000000000;
	}
	
}

void Timer(int value)
{
    Ativar();
    glutPostRedisplay();
    glutTimerFunc(66,Timer, 1);
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,450);
	glutInitWindowPosition(20,20);
	glutCreateWindow("Computeiros - Energia eolica");
	glutKeyboardFunc(teclado);
	init();
	glutReshapeFunc(reshape);
   	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutTimerFunc(33, Timer, 1);
	glutMainLoop();
	return 0;
}
