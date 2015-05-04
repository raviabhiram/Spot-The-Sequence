#include <iostream>
#include<GL/glut.h>
#include<unistd.h>
#include<sys/time.h>
#include<math.h>

#define MAX 10
#define INCR 30

using namespace std;

int coordinates[11]={0,30,60,90,120,150,180,210,240,270,300};
int demox[MAX],demoy[MAX],dframe=-1,dcolorg=-300,dcolorw=-301;
int mousex,mousey,icount=0,score=0,ipnum;
int curround,level=1,counti,countj,maxx,maxy,shown=0;

void display();

void mouse(int btn,int state,int cmousex,int cmousey)
{
    cout<<"cmousex= "<<cmousex<<" cmousey "<<cmousey<<endl;
    float tmousex,tmousey;
    tmousex=(cmousex*500)/(750);
    tmousey=500-(cmousey*500)/(700);
    cout<<"tmousex= "<<tmousex<<" tmousey "<<tmousey<<endl;
    if(shown!=1)
    {
        display();
        //exit(0);
    }
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        cout<<"Mouse Clicked.\n";
        if(tmousex>=demox[icount] && tmousex<=(demox[icount]+INCR) && tmousey>=demoy[icount] && tmousey<=(demoy[icount]+INCR))
        {
            score++;
            icount++;
            cout<<"Score "<<score<<endl;
            if(icount==curround)
            {
                level++;
                shown=0;
                cout<<"Done with this round.\n";
            }
        }
        else
        {
            cout<<"Sorry wrong input.\n";
            cout<<"Actual answerx:- "<<demox[icount]<<"<x<"<<demox[icount]+INCR<<endl;
            cout<<"Actual answery:- "<<demoy[icount]<<"<x<"<<demoy[icount]+INCR<<endl;
            cout<<"x "<<tmousex<<" y "<<tmousey<<endl;
            exit(0);
        }
    }
}

void sequence(int level,int curround)
{
    cout<<"Curround= "<<curround<<endl;
    int number=level+2;
    int i=0,j=0,counti=0,countj=0,offset,boxx,boxy,hx=0,hy,maxx,maxy;
    struct timeval tp;
    offset=100+(12*(MAX-number));//To bring grid to center of the screen
    glColor3f(1.0,0.0,0.0);
    int gtemp=dcolorg;
    int wtemp=dcolorw;
    icount=0;
    for(i=0;;i+=INCR)
    {
        counti++;
        for(j=0;;j+=INCR)
        {
            countj++;
            glPointSize(2);
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
        //cout<<"maxx= "<<maxx<<"\t maxy="<<maxy<<endl<<endl;
    }
    glFlush();
    sleep(2);
    for(hy=0;hy<curround;hy++)
    {
        int r;
        gettimeofday(&tp,NULL);
        r=floor(tp.tv_usec%(number));
        cout<<r<<"\t";
        boxx=coordinates[r];
        gettimeofday(&tp,NULL);
        r=floor(tp.tv_usec%(number));
        cout<<r<<endl;
        boxy=coordinates[r];
        //cout<<"offset= "<<offset<<endl;
        //cout<<"boxx= "<<boxx<<" boxy= "<<boxy<<endl;
        demox[hx]=offset+boxx;
        demoy[hx]=offset+boxy;
        //cout<<"x= "<<demox[hx]<<" y= "<<demoy[hx]<<endl;
        hx++;
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_QUADS);
            glVertex3d(offset+boxx,offset+boxy,gtemp);
            glVertex3d(offset+boxx,offset+boxy+INCR,gtemp);
            glVertex3d(offset+boxx+INCR,offset+boxy+INCR,gtemp);
            glVertex3d(offset+boxx+INCR,offset+boxy,gtemp);
        glEnd();
        //cout<<"bgtemp "<<gtemp<<"\t";
        //cout<<"bwtemp "<<wtemp<<endl;
        gtemp+=2;
        glFlush();
        sleep(2);
        glColor3f(1.0,1.0,1.0);
        wtemp+=2;
        //cout<<"agtemp "<<gtemp<<"\t";
        //cout<<"awtemp "<<wtemp<<endl;
        glBegin(GL_QUADS);
            glVertex3d(offset+boxx,offset+boxy,wtemp);
            glVertex3d(offset+boxx,offset+boxy+INCR,wtemp);
            glVertex3d(offset+boxx+INCR,offset+boxy+INCR,wtemp);
            glVertex3d(offset+boxx+INCR,offset+boxy,wtemp);
        glEnd();
        sleep(1);
        glFlush();
        //for(int a=0;a<2*curround;a++)
            //cout<<"The coordinates of "<<a<<"th display block is:- x="<<demox[a]<<" y= "<<demoy[a]<<endl;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if(!shown)
    {
        curround=level*2;
        if(level>10)
        {
            cout<<"You're the champ!!\n";
            exit(0);
        }
        sequence(level,curround);
        shown=1;
    }
}

void myinit()
{
    cout<<"Inside init function.\n";
    glClearColor(1.0,1.0,1.0,1.0);//Clear the background
    glOrtho(0,500,0,500,-500,500);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(750,750);//Initialise window size
    glutInitWindowPosition(200,200);//Initialise window position
    glutCreateWindow("Sequence");
    myinit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    //glutPostRedisplay();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
