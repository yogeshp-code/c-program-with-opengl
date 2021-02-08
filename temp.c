/*
 * temp.c
 *
 *  Created on: 14-Oct-2020
 *      Author: HP 14s DK0093AU
 */

#include<stdio.h>
#include<GL/glut.h>
#include<windows.h>
#include<time.h>

#include"header.h"
struct snake{
	point body;
}snake[100];
point eye[2];
point xaxis[2]={{0,0},{640,0}};
point yaxis[2]={{0,0},{0,640}};
point box[4];
int Display_Option=0;
int score =0;
int Snake_length=1;
int food=1;
int seedflag=1;
int tempflag=0;
int cflag=0;
point f;
float rr,gr,br;
int Direction=0;
int dflag=0;
int flag=0;
int Up_flag=True,Down_flag=True,Right_flag=True,Left_flag=True;
int color=0;
int Select_Option=0;
int c=0;
int c2=0;
int c3=0;

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.2, 0.2, 1);
}

void Translate()
{
	for(int i=Snake_length;i>0;i--)
	{
		snake[i].body=snake[i-1].body;
	}
	if(Direction==Up)
	{
			snake[0].body.y+=20;
	}
	else if(Direction==Down)
	{
			snake[0].body.y-=20;
	}
	else if(Direction==Right)
	{
			snake[0].body.x+=20;
	}
	else if(Direction==Left)
	{
			snake[0].body.x-=20;
	}
	if(snake[0].body.x>640 ||snake[0].body.x<10)
	{
		if(snake[0].body.x>640)
		{
			snake[0].body.x=10;
		}
		else
		{
			snake[0].body.x=650;
		}
	}
	if(snake[0].body.y>640 ||snake[0].body.y<10)
	{
		if(snake[0].body.y>640)
		{
			snake[0].body.y=10;
		}else
		{
			snake[0].body.y=650;
		}
	}
	for(int i=1;i<Snake_length-1;i++)
	{
		if(snake[i].body.x==snake[0].body.x && snake[i].body.y==snake[0].body.y)
		{
		    Display_Option++;
		}
	}
	if(snake[0].body.x==f.x && snake[0].body.y==f.y)
	{
		score+=10;
		food=True;
		Snake_length++;
		if(score%20==0)
		{
			c3+=2;
			if(c3>=74)
			{
				c3=74;
			}
		}
	}
}
int random(int min,int max)
{
    int temp=1;
    if(seedflag==1)
    {
        srand(time(NULL));
        seedflag=0;
    }
    else
    {
        seedflag=1;
    }
    do
    {
    	temp=min+rand()%(max-min);
    } while(temp%20!=0);
    temp+=10;
    return temp;
}
void Display_food()
{
	if(color==0)
	{
		srand(time(NULL));
		rr=(rand()%10);
		gr=(rand()%10);
		br=(rand()%10);
	}
	glColor3f(rr, gr, br);
	int check=0;
	if(food==True)
	{
		do{
			f.x=random(5,640);
			f.y=random(5,640);
			check=0;
			for(int j=0;j<Snake_length-1;j++)
			{
				if(f.x==snake[j].body.x && f.y==snake[j].body.y)
				{
					check++;
				}
			}
		}while(check>0);
		food=False;
	}
	glBegin(GL_POINTS);
	circle(f,10,20);
	glEnd();
}
void Main_menu()
{
	glColor3f(1.0,1.0,0.5);
	text("Snake Game",230,420,24);
	text("-by yogesh",340,30,24);
	text("Start",270,310,18);
	text("Exit",275,240,18);
	text("Use arrow Key To Up-Down",230,140,10);
	text("Special_key_press Enter To Proceed",240,125,10);
	if(Select_Option==First)
	{
		box[0].x=250;
		box[0].y=300;
	}
	else
	{
		box[0].y=230;
	}
	box[1]=box[0];
	box[1].x+=80;
	box[2]=box[1];
	box[2].y+=30;
	box[3]=box[0];
	box[3].y+=30;

	for(int i=0;i<3;i++)
	{
		line(box[i],box[i+1],5);
	}
	line(box[3],box[0],5);
	glutSwapBuffers();
	glEnd();
}
void Game_over()
{
	char sc[20];
	itoa(score,sc,10);
	glColor3f(0.5,1.0,0.5);
	text("Game Over Score :",200,520,24);
	text(sc,400,520,24);
	text("Restart",280,410,18);
	text("Main Menu",265,310,18);
	text("Exit",285,210,18);
	text("Use arrow Key To Up-Down",230,140,10);
	text("Special_key_press Enter To Proceed",240,125,10);
		if(Select_Option==First)
		{
			box[0].x=250;
			box[0].y=400;
		}
		else if(Select_Option==Second)
		{
			box[0].y=300;
		}
		else
		{
			box[0].y=200;
		}
		box[1]=box[0];
		box[1].x+=120;
		box[2]=box[1];
		box[2].y+=50;
		box[3]=box[0];
		box[3].y+=50;
		for(int i=0;i<3;i++)
		{
			line(box[i],box[i+1],5);
		}
		line(box[3],box[0],5);
		glutSwapBuffers();
		glEnd();

}
void Game_display()
{
	glColor3f(1.0, 0.8, 0.8);

	glColor3f(1.0,0.8,0.0);
	for(int i=0;i<Snake_length;i++)
	{
		if(i==0)
		{
			glColor3f(1.0,0.0,0.0);
			circle(snake[i].body,6,10);
			circle(snake[i].body,7,10);

		}
		else
		{
			glColor3f(1.0,0.0,0.0);
			circle(snake[i].body,6,10);
			glColor3f(1.0,0.8,0.0);
			circle(snake[i].body,5,10);

		}
	}
	glColor3f(0,0,0);
	eye[0].x=snake[0].body.x-3;
	eye[1].x=snake[0].body.x+3;
	eye[0].y=snake[0].body.y+3;
	eye[1].y=snake[0].body.y+3;
	circle(eye[0],2,2);
	circle(eye[1],2,2);
	eye[0].y-=7;
	eye[1].y-=7;
	line(eye[0],eye[1],3);
	Display_food();
	glutSwapBuffers();
	glEnd();
}
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.5,0.5);
	if(Display_Option==First)
	{
		Main_menu();
	}else if(Display_Option==Second)
	{
		glColor3f(0.0, 0.0, 0.0);
		for(int j=0;j<=640;j+=20)
		{
				line(xaxis[0],xaxis[1],2);
				line(yaxis[0],yaxis[1],2);
				xaxis[0].y+=20;
				xaxis[1].y=xaxis[0].y;
				yaxis[0].x+=20;
				yaxis[1].x=yaxis[0].x;
				if(j==640)
				{
					xaxis[0].y=0;
					yaxis[0].x=0;
					xaxis[1].y=0;
					yaxis[1].x=0;
				}
		}
		Game_display();
	}
	else if(Display_Option==Third)
	{
		Game_over();
	}
	glEnd();
}

void Timer(int value)
{
	glutPostRedisplay();
	if(value<=0)
	{
		value=50;
		color=0;
	}
	else
	{
		color=1;
	}
	if(Display_Option==Second)
	{
		Translate();
	}
	glutTimerFunc(100-c3, Timer, value-5);
}


void Special_key_press(int key,int x,int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		if(Display_Option==First)
		{
			if(Select_Option==First)
			{
				Select_Option++;
			}
			else
			{
				Select_Option=First;
			}
		}
		else if(Display_Option==Second)
		{
			if(Up_flag==True)
			{
				Down_flag=False;
				Right_flag=True;
				Left_flag=True;
				Direction=Up;
			}
		}
		else if(Display_Option==Third)
		{
			if(Select_Option==First)
			{
				Select_Option=Third;
			}
			else if(Select_Option==Second)
			{
				Select_Option--;
			}
			else
			{
				Select_Option--;
			}

		}
		break;
	case GLUT_KEY_DOWN:
		if(Display_Option==First)
		{
			if(Select_Option==First)
			{
				Select_Option++;
			}
			else
			{
				Select_Option=First;
			}

		}
		else if(Display_Option==Second)
		{
			if(Down_flag==True)
			{
				Up_flag=False;
				Right_flag=True;
				Left_flag=True;
				Direction=Down;
			}
		}
		else if(Display_Option==Third)
		{
			if(Select_Option==First)
			{
				Select_Option++;
			}
			else if(Select_Option==Second)
			{
				Select_Option++;
			}
			else
			{
				Select_Option=First;
			}
		}


		break;
	case GLUT_KEY_RIGHT:
		if(Display_Option==Second)
		{
			if(Right_flag==True)
			{
				Up_flag=True;
				Down_flag=True;
				Left_flag=False;
				Direction=Right;
			}
		}
		break;
	case GLUT_KEY_LEFT:
		if(Display_Option==Second)
		{
			if(Left_flag==True)
			{
				Up_flag=True;
				Down_flag=True;
				Right_flag=False;
				Direction=Left;
			}
		}
		break;
	}
}
void Key_press(unsigned char key,int x,int y)
{
	if(Display_Option==First)
	{
		switch(key)
		{
		case  13:
			if(Select_Option==First)
			{
				Snake_length=1;
				Display_Option++;

			}else
			{
				exit(0);
			}
			break;
		}
	}
	else if(Display_Option==Third)
	{
		switch(key)
		{
		case 13:
			if(Select_Option==First)
			{
				Snake_length=1;
				Display_Option=Second;
			}else if(Select_Option==Second)
			{
				Display_Option=First;
			}
			else
			{
				exit(0);
			}
			break;
		}
	}
}
int main(int argc,char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(320, 0);
	glutCreateWindow("Snake");
	gluOrtho2D(0.0, 640.0, 0.0, 640.0);
	glMatrixMode(GL_PROJECTION);
	init();
	snake[0].body.x=10;
	snake[0].body.y=10;
	Direction=Up;
	glutSpecialFunc(Special_key_press);
	glutKeyboardFunc(Key_press);
	glutDisplayFunc(Display);
	glutTimerFunc(100, Timer, 50);
	glutMainLoop();
	return 0;

}
