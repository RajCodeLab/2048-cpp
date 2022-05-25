#include "dos.h"
#include "stdio.h"
#include "conio.h"
#include "string.h"
#include "stdlib.h"
#include "graphics.h"
#include "iostream.h"

int gstat,gd = DETECT,gm,err;	//gstat 0=contiue,1=lost or quit,2=won
void showele(int w,int h, int el)
{
	int col,ls;
	char eval[6];
	if(el==2)
	{
		col=59;
		ls=23;
		strcpy(eval,"2");
	}
	else if(el==4)
	{
		col=3;
		ls=23;
		strcpy(eval,"4");
	}

	else if(el==8)
	{
		col=57;
		ls=23;
		strcpy(eval,"8");
	}

	else if(el==16)
	{
		col=1;
		ls=20;
		strcpy(eval,"16");
	}

	else if(el==32)
	{
		col=58;
		ls=20;
		strcpy(eval,"32");
	}

	else if(el==64)
	{
		col=2;
		ls=20;
		strcpy(eval,"64");
	}

	else if(el==128)
	{
		col=62;
		ls=17;
		strcpy(eval,"128");
	}

	else if(el==256)
	{
		col=20;
		ls=17;
		strcpy(eval,"256");
	}

	else if(el==512)
	{
		col=5;
		ls=17;
		strcpy(eval,"512");
	}

	else if(el==1024)
	{
		col=60;
		ls=11;
		strcpy(eval,"1024");
	}

	else if(el==2048)
	{
		col=20;
		ls=11;
		strcpy(eval,"2048");
	}
	setcolor(col);
	outtextxy(w+ls,h,eval);

}

class twog
{
	int elem[4][4];
	int pelem[4][4];
	int score;

	public:
	int cmove(int move);
	int compgrid(int g1[][4],int g2[][4]);
	void changegrid(int old[][4],int newg[][4]);
	void rspawn();
	void setup();
	void board();
	void fill0(int move);
	void input(int move);
	void logic();
	void checkwin();

};
void twog::checkwin()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(elem[i][j]>=2048)
				gstat=2;
		}
	}
}
void twog::rspawn()
{
	randomize();
	int i,j,v,f=1;
	while(f)
	{
		v=random(100);
		i=random(4);
		j=random(4);
		if(elem[i][j]==0)
		{
			if(v<20)
				elem[i][j]=4;
			else
				elem[i][j]=2;
			f=0;
		}

	}
}
void twog::changegrid(int oldg[][4],int newg[][4])
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			oldg[i][j]=newg[i][j];
		}
	}
}
int twog::compgrid(int g1[][4],int g2[][4])
{
	int flag=0;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(g1[i][j]!=g2[i][j])
			{
				flag=1;
				break;
			}
		}
	}
	return flag;
}

void twog::setup()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			elem[i][j]=0;
		}
	}
	score=0;
	gstat=0;
	rspawn();
	rspawn();
}

void twog::board()
{
	int li,lj,i,j,ls;
	li=200;lj=20;
	clrscr();
	initgraph(&gd,&gm,"..\\bgi");
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			bar(li,lj,li+50,lj+50);
			if(elem[i][j]!=0)
			{
				showele(li,lj+23,elem[i][j]);
			}
			li+=60;
		}
		lj+=60;
		li=200;
	}
	setcolor(63);
	line(0,lj+20,getmaxx(),lj+20);
	outtextxy(3,lj+40,"CONTROLS :W = UP, A = LEFT, S = DOWN, D = RIGHT, U = UNDO, R = RESTART,K = QUIT ");

}


int twog::cmove(int move)
{
	int i,j,ni,nj,canmove=0;
	switch(move)
	{
		case 3:
			for(i=2;i>=0;i--)
			{
				for(j=0;j<4;j++)
				{
					ni=i+1;
					nj=j;
					if((ni>=0)&&(ni<=3)&&(nj>=0)&&(nj<=3))
					{
						if((elem[ni][nj]==elem[i][j])||(elem[ni][nj]==0))
						{
							if(elem[i][j]!=0)
								canmove=1;
						}
					}
				}
			}
			break;
	}
	return canmove;
}

void twog::fill0(int move)
{
	for(int i=0;i<4;i++)
	{
		if(move==1)
		{
			for(int j=0;j<4;j++)
			{
				if(!(elem[j][i]))
				{
					for(int k=j+1;k<4;k++)
					{
						if(elem[k][i])
						{
							elem[j][i]=elem[k][i];
							elem[k][i]=0;
							break;
						}
					}
				}
			}
		}
		else if(move==2)
		{
			for(int j=0;j<4;j++)
			{

				if(!(elem[i][j]))
				{
					for(int k=j+1;k<4;k++)
					{
						if(elem[i][k])
						{
							elem[i][j]=elem[i][k];
							elem[i][k]=0;
							break;
						}
					}
				}
			}
		}
		else if(move==3)
		{
			for(int j=0;j<4;j++)
			{
				if(!(elem[j][i]))
				{
					for(int k=j-1;k>=0;k--)
					{
						if(elem[k][i])
						{
							elem[j][i]=elem[k][i];
							elem[k][i]=0;
							break;
						}
					}

				}
			}
		}
		else if(move==4)
		{
			for(int j=0;j<4;j++)
			{

				if(!(elem[i][j]))
				{
					for(int k=j-1;k>=0;k--)
					{
						if(elem[i][k])
						{
							elem[i][j]=elem[i][k];
							elem[i][k]=0;
							break;
						}
					}
				}
			}
		}
	}
}







void twog::input(int move)
{
	int i,j,ni,nj;
	if(move==5)
	{
			changegrid(elem,pelem);
	}
	else
	{
		changegrid(pelem,elem);
		fill0(move);
		switch(move)
		{
			case 1:
				for(i=0;i<4;i++)
				{
					for(j=0;j<3;j++)
					{
						if((elem[j][i])&&(elem[j+1][i]==elem[j][i]))
						{
							elem[j][i]+=elem[j-1][i];
							elem[j+1][i]=0;
						}
					}
				}
				break;
			case 2:
				for(i=0;i<4;i++)
				{
					for(j=0;j<3;j++)
					{
						if((elem[i][j])&&(elem[i][j]==elem[i][j+1]))
						{
							elem[i][j]+=elem[i][j+1];
							elem[i][j+1]=0;
						}
					}
				}
				break;
			case 3:
				for(i=0;i<4;i++)
				{
					for(j=3;j>0;j--)
					{
						if((elem[j][i])&&(elem[j-1][i]==elem[j][i]))
						{
							elem[j][i]+=elem[j-1][i];
							elem[j-1][i]=0;
						}
					}
				}
				break;
			case 4:
				for(i=0;i<4;i++)
				{
					for(j=3;j>=0;j--)
					{
						if((elem[i][j])&&(elem[i][j]==elem[i][j-1]))
						{
							elem[i][j]+=elem[i][j-1];
							elem[i][j-1]=0;
						}
					}
				}
				break;

		}
	}
	fill0(move);
	if(compgrid(elem,pelem))
		rspawn();
	board();
}

void main()
{
	twog t1;
	char m;
	lbl:
	t1.setup();

	while(!(gstat))
	{
		t1.board();
		m=getch();
		switch(m)
		{
			case 'k': case 'K':
				gstat=1;
				break;
			case 'R': case 'r':
				closegraph();
				goto lbl;
			case 'w': case 'W':
				t1.input(1);
				break;
			case 'a': case 'A':
				t1.input(2);
				break;
			case 's': case 'S':
				t1.input(3);
				break;
			case 'd': case 'D':
				t1.input(4);
				break;
			case 'u': case 'U':
				t1.input(5);
				break;
			default:
				break;
		}
		delay(50);
		closegraph();
		t1.checkwin();
	}
	getch();
}

