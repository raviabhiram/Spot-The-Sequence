#include <iostream>
#include<GL/glut.h>
#include<unistd.h>
#include<sys/time.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<GL/freeglut.h>

#define MAX 10
#define INCR 30

using namespace std;

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec3f;

const vec3f _FONT_SIZE_SMALL = {0.25f, 0.25f, 1.0f};
const vec3f *FONT_SIZE_SMALL = &_FONT_SIZE_SMALL;

const vec3f _FONT_SIZE_XSMALL = {0.15f, 0.15f, 1.0f};
const vec3f *FONT_SIZE_XSMALL = &_FONT_SIZE_XSMALL;

int coordinates[11]={0,30,60,90,120,150,180,210,240,270,300};
int demox[MAX],demoy[MAX],dframe=-1,dcolorg=-3000,dcolorw=-3001,gtemp,wtemp;
int mousex,mousey,icount=0,score=0,ipnum,opnum=0;
int curround=3,level=3,counti,countj,maxx,maxy,shown=0;
int kflag=0,iflag=0;
string str = "LEVEL ";
int go=0;

void myinit();
void display();
void frontScreen();
void instructions();
void sequence(int level,int curround);

string itoa(int i)
{
	string ret = "";

	if(i == 0)
	{
		int temp=0;
		ret+=temp + '0';
	}
	else
	{
		int temp=0;
		string strtemp;
		while (i)
		{
			strtemp= "";
			temp = (i%10);
			strtemp = temp + '0';
			ret= strtemp+ret;
			i/=10;
		}
	}
	return ret;
}

void drawStrokeText(std::string text, int x, int y, int z, const vec3f *fontSize)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(fontSize->x, fontSize->y, fontSize->z);
    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char const *) text.c_str());
    glPopMatrix();
}

void drawstring( float x, float y,const char* string )
{
    int j = strlen( string ),i;
	glRasterPos2f( x, y );
	for( int i = 0; i < j; i++ )
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
	}
}


void frontScreen()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(0.4078,0.6235,0.2196);
    glBegin( GL_POLYGON );
        glVertex3d(0,500,5);
		glVertex3d(500,500,5);
		glVertex3d(500,40,5);
		glVertex3d(0,40,5);
	glEnd();
	glColor3f(0.545,0.7647,0.2901);
    glBegin( GL_POLYGON );
        glVertex3f(0,0,0);
        glVertex3f(500,0,5);
        glVertex3f(500,40,5);
        glVertex3f(0,40,5);
	glEnd();
	glLineWidth(3);
    drawStrokeText("SPOT THE SEQUENCE", 80, 3*500/4, 0, FONT_SIZE_SMALL);
	glColor3f(1,1,1);
	drawstring(5,14,"Developed by : Abhiram Ravi Bharadwaj and Harsha R S");
    glColor3f(1,0,0);
	drawstring(350,14,"Guide : SARASVATHI");
	glColor3f(0.7,0.7,0.7);
	drawstring(130,100,"CLICK TO CONTINUE TO THE GAME");

    int i,j,counti=0,countj=0;
	int foffset=100+(12*(MAX-4));

    for(i=0;i<5*INCR;i+=INCR)
    {
        counti++;
        for(j=0;j<5*INCR;j+=INCR)
        {
            countj++;
            glLineWidth(1);
            glColor3f(1.0,1.0,1.0);
            glBegin(GL_LINE_LOOP);
                glVertex3d(foffset+i,foffset+j,dframe);
                glVertex3d(foffset+i,foffset+j+INCR,dframe);
                glVertex3d(foffset+i+INCR,foffset+j+INCR,dframe);
                glVertex3d(foffset+i+INCR,foffset+j,dframe);
            glEnd();
         }
    }

	glFlush();
}



void myexit()
{
	_exit(0);
}

void mouse(int btn,int state,int cmousex,int cmousey)
{
	if(kflag == 0 && state == GLUT_DOWN)
    {
	kflag = 1;
        return;
    }
    float tmousex,tmousey;
    tmousex=(cmousex*500)/(750);
    tmousey=500-(cmousey*500)/(700);
    if(shown!=1)
    {
        display();
    }
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(tmousex>=demox[icount] && tmousex<=(demox[icount]+INCR) && tmousey>=demoy[icount] && tmousey<=(demoy[icount]+INCR))
        {
            glColor3f(0.0,1,0);
            glBegin(GL_QUADS);
                glVertex3d(demox[icount],demoy[icount],gtemp);
                glVertex3d(demox[icount],demoy[icount]+INCR,gtemp);
                glVertex3d(demox[icount]+INCR,demoy[icount]+INCR,gtemp);
                glVertex3d(demox[icount]+INCR,demoy[icount],gtemp);
            glEnd();
            gtemp+=2;
            glFlush();
            wtemp+=2;
            sleep(1);
            glColor3f(0.3764,0.4901,0.545);
            glBegin(GL_QUADS);
                glVertex3d(demox[icount],demoy[icount],wtemp);
                glVertex3d(demox[icount],demoy[icount]+INCR,wtemp);
                glVertex3d(demox[icount]+INCR,demoy[icount]+INCR,wtemp);
                glVertex3d(demox[icount]+INCR,demoy[icount],wtemp);
            glEnd();
            score++;
            icount++;
            if(icount==curround)
            {
                curround++;
                shown=0;
            }
        }
        else
        {
            glColor3f(1.0,0,0);
            glBegin(GL_QUADS);
                glVertex3d(demox[icount],demoy[icount],gtemp);
                glVertex3d(demox[icount],demoy[icount]+INCR,gtemp);
                glVertex3d(demox[icount]+INCR,demoy[icount]+INCR,gtemp);
                glVertex3d(demox[icount]+INCR,demoy[icount],gtemp);
            glEnd();
            glFlush();
            sleep(3);
            string gomsg = "Your Score is:- " + itoa(score+1-1);
            char *gostr = &gomsg[0u];
            drawstring(190,50,gostr);
            drawstring(200,100,"Game Over!!");
            glFlush();
            sleep(3);
            myexit();
        }
    }
}

void sequence(int level,int curround)
{
    glColor3f(1,1,1);
    glLineWidth(3);
    string levelstr = "Level " + itoa(level-2);
    char *lstr = &levelstr[0u];
    string roundstr = "Round " + itoa(curround-2);
    char *rstr = &roundstr[0u];
    glColor3f(0.698,0.9215,0.949);
    drawStrokeText(lstr,190,420,0,FONT_SIZE_SMALL);
    glLineWidth(1);
    glColor3f(1,1,1);
    drawStrokeText(rstr,200,360,0,FONT_SIZE_XSMALL);
    int number=level;
    int i=0,j=0,counti=0,countj=0,offset,boxx,boxy,hx=0,hy,maxx,maxy;
    struct timeval tp;
    offset=120+(12*(MAX-number));//To bring grid to center of the screen
    glColor3f(1.0,0.0,0.0);
    gtemp=dcolorg;
    wtemp=dcolorw;
    icount=0;
    for(i=0;;i+=INCR)
    {
        counti++;
        for(j=0;;j+=INCR)
        {
            countj++;
            glPointSize(2);
            glColor3f(1.0,1.0,1.0);
            glBegin(GL_LINE_LOOP);
                glVertex3d(offset+i,offset+j,dframe);
                glVertex3d(offset+i,offset+j+INCR,dframe);
                glVertex3d(offset+i+INCR,offset+j+INCR,dframe);
                glVertex3d(offset+i+INCR,offset+j,dframe);
            glEnd();
            if(countj>=number)
            {
                    maxy=j;//Storing max value of y for highlighted block to stay within grid
                    countj=0;
                    break;
            }
        }
        if(counti>=number)
        {
            maxx=i;//Storing max value of x for highlighted block to stay within grid
            break;
        }
    }
    glFlush();
    sleep(2);

    for(hy=0;hy<curround;hy++)
    {
        int r;
        gettimeofday(&tp,NULL);
        r=floor(tp.tv_usec%(number));
        boxx=coordinates[r];
        gettimeofday(&tp,NULL);
        r=floor(tp.tv_usec%(number));
        boxy=coordinates[r];
        demox[hx]=offset+boxx;
        demoy[hx]=offset+boxy;
        hx++;
        if(opnum==0)
        {
            opnum=1;
            glColor3f(0.5,0,0.5);
        }
        else if(opnum==1)
        {
            opnum=0;
            glColor3f(0.0,0.0,1.0);
        }
        glBegin(GL_QUADS);
            glVertex3d(offset+boxx,offset+boxy,gtemp);
            glVertex3d(offset+boxx,offset+boxy+INCR,gtemp);
            glVertex3d(offset+boxx+INCR,offset+boxy+INCR,gtemp);
            glVertex3d(offset+boxx+INCR,offset+boxy,gtemp);
        glEnd();
        gtemp+=2;
        glFlush();
        sleep(1);
        wtemp+=2;
        glColor3f(0.3764,0.4901,0.545);
        glBegin(GL_QUADS);
            glVertex3d(offset+boxx,offset+boxy,wtemp);
            glVertex3d(offset+boxx,offset+boxy+INCR,wtemp);
            glVertex3d(offset+boxx+INCR,offset+boxy+INCR,wtemp);
            glVertex3d(offset+boxx+INCR,offset+boxy,wtemp);
        glEnd();
        sleep(1);
        glFlush();
    }
    glColor3f(0.7,0.7,0.7);
    drawstring(175,offset-30,"Now Input the Sequence : ");
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glClearColor(0.3764,0.4901,0.545,1.0);

    if(kflag == 1)
    {
    	if(!shown)
    	{
        	if(level>MAX)
        	{
                exit(0);
        	}
        	if(curround>(2*level)-2)
            {
                level++;
                curround=3;
            }
        	sequence(level,curround);
        	shown=1;
        }
    }
}

void myinit()
{

    glClearColor(1.0,1.0,1.0,1.0);//Clear the background
    glOrtho(0,500,0,500,-5000,5000);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(750,750);//Initialise window size
    glutInitWindowPosition(200,200);//Initialise window position
    glutCreateWindow("Sequence");
    myinit();
    frontScreen();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
