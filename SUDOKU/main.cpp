#include <iostream>
#include <fstream>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <cstdlib>
using namespace std;

ifstream g("highscore.in");
int a[10][10],i,j,x,ok,poz,r,vi,vj,nri,nrj,y,z,ns,hc,m[10][10];
///---VERIFICARE TERMINARE
/*int solve()
{
    for(i=1;i<=9;i++)
        for(j=1;j<=9;j++)
        if(a[i][j]==0)
            return 0;
    return 1;
}*/


int valid()
{
    for(r=1; r<=9; r++)
        if(a[r][j]==x||a[i][r]==x)
            return 0;
    if(i-3<=0)
        vi=1;
    else if(i-3<=3)
        vi=4;
    else vi=7;
    if(j-3<=0)
        vj=1;
    else if(j-3<=3)
        vj=4;
    else vj=7;
    for(nri=vi; nri<=vi+2; nri++)
        for(nrj=vj; nrj<=vj+2; nrj++)
            if(a[nri][nrj]==x)
                return 0;

    return 1;

}
///-----GENERARE SUDOKU---
void sudo()
{

    while(ok!=20)
    {

        ok++;
        x=rand()%9+1;
        i=rand()%9+1;
        j=rand()%9+1;
        if(a[i][j]==0&&valid()==1)
            {a[i][j]=x;
            m[i][j]=1;
            }

    }
}
///--------
int main()
{
    time_t start = time(0);
    time_t ant = time(0);
    time_t c = time(0);

    g>>hc;

    srand(time(NULL));
    sudo();
    for(i=1; i<=9; i++)
    {
        for(j=1; j<=9; j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    ///---SETARI FEREASTRA--
    int d=50,sp=5,gata=1,nc=9,nl=9;
    int left=sp,top=sp;
    int W=nc*(d+sp)+sp+125;
    int H=nl*(d+sp)+sp+100;
    initwindow(W,H,"SUDOKU");
    settextstyle(1,0,4);
    setcolor(3);
    ///---TABLA
    for(i=1; i<=9; i++)
        for(j=1; j<=9; j++)
        {
            z=left+(j-1)*(d+sp);
            y=top+(i-1)*(d+sp);
            rectangle(z,y, z+d,y+d);
        }
    ///DELIMITARE ZONE SUDOKU
    setcolor(14);
    y=3*(sp+d)+2;
    z=left;
    line(z,y,(z+9*d+8*sp),y);
    y=(y-2)*2+2;
    line(z,y,(z+9*d+8*sp),y);
    y=(y-2)/2*3+2;
    line(z,y,(z+9*d+8*sp),y);
    y=top-2;
    line(z,y,(z+9*d+8*sp),y);
    y=top;
    z=left-2;
    line(z,y,z,(y+9*d+8*sp));
    z=3*(sp+d)+2;
    line(z,y,z,(y+9*d+8*sp));
    z=(z-2)*2+2;
    line(z,y,z,(y+9*d+8*sp));
    z=(z-2)/2*3+2;
    line(z,y,z,(y+9*d+8*sp));
    z=9*(sp+d)+d;
    y=top;
    setcolor(7);
    ///---INTERFATA
    for(i=1; i<=9; i++)
    {
        rectangle(z,y,z+d,y+d);
        y=y+d+sp;
    }
    char s[2];
    int ok=0;
    s[0]=49;
    s[1]=0;
    y=top+11;
    z=z+12;
    setcolor(9);
    for(i=1; i<=9; i++)
    {
        outtextxy(z,y,s);
        s[0]++;
        y=y+d+5;
    }
    ///AFISARE VALORI MATRICE
    for(i=1; i<=9; i++)
        for(j=1; j<=9; j++)
            if(a[i][j]>0)
            {
                z=left+(j-1)*(d+sp)+13;
                y=top+(i-1)*(d+sp)+13;
                s[0]=48+a[i][j];
                outtextxy(z,y,s);
            }
    int x1,y1,nrc=0,xp,yp,aux=1,ry,rx,y2,k;
    while(!kbhit())
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x1, y1);
            if(x1>=9*(sp+d)+d&&x1<=9*(sp+d)+2*d&&y1<=9*(sp+d))
            {
                if(nrc)
                {
                     rx=9*(sp+d)+d;
                     ry=top+(y2-1)*(d+sp);
                     setcolor(9);
                     s[0]=48+nrc;
                     outtextxy(rx+12,ry+12,s);
                     y2=y1/(sp+d)+1;
                     nrc=y2;
                     rx=9*(sp+d)+d;
                     ry=top+(y2-1)*(d+sp);
                     setcolor(11);
                      s[0]=48+nrc;
                     outtextxy(rx+12,ry+12,s);
                }
                else
                {
                     y2=y1/(sp+d)+1;
                     nrc=y2;
                     rx=9*(sp+d)+d;
                     ry=top+(y2-1)*(d+sp);
                     setcolor(11);
                      s[0]=48+nrc;
                     outtextxy(rx+12,ry+12,s);
                }
                }
            else if(x1<=9*(sp+d)&&nrc!=0&&x1>=top&&y1>=left&&y1<=9*(sp+d))
            {
                y=y1/(sp+d)+1;
                z=x1/(sp+d)+1;
                if(m[y][z]==0)
                {
                    xp=left+(z-1)*(d+sp);
                yp=top+(y-1)*(d+sp);
                aux=1;
                cout<<endl<<y<<" "<<z;
                for(r=1;r<=9;r++)
                    if((a[y][r]==nrc&&r!=z)||(a[r][z]==nrc&&r!=y))
                          aux=0;
                if(y>=1&&y<=3)
                    vi=1;
                else if(y>=4&&y<=6)
                    vi=4;
                else vi=7;
                if(z>=1&&z<=3)
                    vj=1;
                else if(z>=4&&z<=6)
                    vj=4;
                else vj=7;
                cout<<endl<<vi<<" "<<vj;
                for(nri=vi;nri<=vi+2;nri++)
                    for(nrj=vj;nrj<=vj+2;nrj++)
                      if(a[nri][nrj]==nrc)
                        if(nri==y&&nrj==z)
                        {

                        }
                        else
                            aux=0;
                cout<<endl<<aux;
                if(aux==0)
                {
                    if(a[y][z]!=0)
                    {
                        setcolor(0);
                        s[0]=48+a[y][z];
                        outtextxy(xp+13,yp+13,s);
                        a[y][z]=nrc;
                        s[0]=48+nrc;
                       setcolor(12);
                       outtextxy(xp+13,yp+13,s);
                    }
                   else
                    {
                        a[y][z]=nrc;
                        s[0]=48+nrc;
                    setcolor(12);
                    outtextxy(xp+13,yp+13,s);
                    }
                }
                else
                {
                    k++;
                    if(a[y][z]!=0)
                    {
                        setcolor(0);
                        s[0]=48+a[y][z];
                        outtextxy(xp+13,yp+13,s);
                        a[y][z]=nrc;
                        s[0]=48+nrc;
                    setcolor(10);
                    outtextxy(xp+13,yp+13,s);
                    }
                    else
                    {
                        a[y][z]=nrc;
                        s[0]=48+nrc;
                    setcolor(10);
                    outtextxy(xp+13,yp+13,s);
                    }
                 }
                }

            }
        }
        c = time(0);
        int nrsec=difftime( c, ant);
        int ss,mm;
         char r[10];
    char rm[10];
    char t[100]="";
    char text[500];
    char prr[500];
    char rez[500]="Ai castigat in ";
    char high[500]="Highscore: ";
        if(nrsec>0)
        {
            ns++;
            ss=ns%60;
            mm=ns/60;
            ant=c;
            setcolor(0);
            outtextxy(100,H-50,t);
            itoa(ss,r,10);
            itoa(mm,rm,10);
            strcpy(t,rm);
            strcat(t,":");
            strcat(t,r);
            setcolor(7);
            outtextxy(270,H-75,t);
        }
      if(k==66)
      {
       time_t stop =time(0);
    int nrsec=difftime( stop, start);
    if(nrsec<hc)
       {ofstream g("highscore.in");
       hc=nrsec;
       g<<hc;
       }
    itoa(hc,prr,10);
    strcat(high,prr);
    strcat(high, " secunde!");
    itoa(nrsec,text,10);
    strcat(rez,text);
    strcat(rez, " secunde!");
    setcolor(8);
    rectangle(1,1,W,H);
    setfillstyle(1,0);
    floodfill(2,2,8);
    setcolor(10);
    outtextxy(50,H/2,rez);
    outtextxy(50,H/2-50,high);
    delay(150000);

      }


    }

    return 0;
}
