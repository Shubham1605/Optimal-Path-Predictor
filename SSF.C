#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define INFINITY 9999
#define MAX 49
#define n 49
int X[MAX],Y[MAX];
float G[MAX][MAX];
int path[120];
int msource=0,mdestination=0;
int proximity[50];
//algo functions
void dijikstra(int startnode,int destination,int path[], int X[], int Y[],int flag);
void astar(int startnode,int destination,int via);
void traffic_generator(int start_node,int dest_node);
void cost_optimal(int startnode,int destination,int mileage,int gasprice);
void calc_distance();
void create_map();
void node_coordinates();
int get_optimal();
void create_proximity();
void check_monument(int msource,int mdestination);
void data(int);
void print();
void bellman_ford();
//graphic functions
void weight();
void screen1();
void screen2(int X[],int Y[],int path[],int len);
void screen3(float);
void first();
void input_screen(int path[],int X[],int Y[]);
void display_path(int source,int destination,int distance,int );
//void path();

typedef struct Site
{
char name[1000];
char details[20000];
char rating[2000];
char trans[10000];
}Site;

//structure of BMP image file format
      struct BMP
{
  char Type[2];           //File type. Set to "BM".
  unsigned long Size;     //Size in BYTES of the file.
  unsigned long Reserved;      //Reserved. Set to zero.
  unsigned long OffSet;   //Offset to the data.
  unsigned long headsize; //Size of rest of header. Set to 40.
  unsigned long Width;     //Width of bitmap in pixels.
  unsigned long Height;     //  Height of bitmap in pixels.
  unsigned int  Planes;    //Number of Planes. Set to 1.
  unsigned int  BitsPerPixel;       //Number of Bits per pixels.
  unsigned long Compression;   //Compression. Usually set to 0.
  unsigned long SizeImage;  //Size in bytes of the bitmap.
  unsigned long XPixelsPreMeter;     //Horizontal pixels per meter.
  unsigned long YPixelsPreMeter;     //Vertical pixels per meter.
  unsigned long ColorsUsed;   //Number of colors used.
  unsigned long ColorsImportant;  //Number of "important" colors.
};

void screen1()
{
int gd=DETECT,gm,a,b;
initgraph(&gd,&gm,"");
setcolor(1);
setfillstyle(WIDE_DOT_FILL,BROWN);
bar(10,0,630,500);
settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
setcolor(3);
setfillstyle(SOLID_FILL,GREEN);
outtextxy(150,30,"MINOR PROJECT-1");
settextstyle(4,0,3);
bar(145,60,508,62);
setcolor(15);
settextstyle(7,0,4);
outtextxy(100,130,"OPTIMAL PATH PREDICTOR");
setcolor(14);
settextstyle(3,0,2);
outtextxy(80,270,"SUBMITTED BY;");
setcolor(13);
outtextxy(360,270,"SUBMITTED TO:");
settextstyle(1,0,1);
setcolor(12);
outtextxy(349,310," COES,UPES");
outtextxy(360,330,"Dehradun,Uttrakhand.");
setcolor(11);
settextstyle(1,0,2);
outtextxy(80,310,"Shubham Sharma-65");
outtextxy(80,330,"Shubham Sinha-66");
outtextxy(80,353,"B.Tech CSE-OGI(V SEM)");
a=getmaxx();
b=getmaxy();
setcolor(2);
settextstyle(2,0,5);
outtextxy(a-150,b-20,"Press any key...");
getch();
}

void screen2(int X[],int Y[],int path[],int len_path)
{
int i,j,k,x1,y1,x2,y2,lx1,lx2,ly1,ly2;

for(i=len_path;i>0;i--)
{
//printf("Value of i %d\n",i);
x1=path[i];
y1=x1;
x2=path[i-1];
y2=x2;
//printf("Value of i %d\n",i);
//printf("Value of x1 and x2 are %d and %d\n",x1,x2);
lx1=X[x1];
lx2=X[x2];
ly1=Y[y1];
ly2=Y[y2];
//printf("\n %d %d %d %d \n",lx1,ly1,lx2,ly2);
for( j = 0 ; j <= 120 ; j = j + 10, k++ )
{
line(lx1,ly1,lx2,ly2);
setcolor(k);
delay(50);
if(j == 120)
break;
}
if(proximity[x1]>0)
{

msource=x1;
mdestination=proximity[x1];
}
}
}

/*void screen3(float x)
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
printf("\nTime taken to execute %f",x);
getch();
}
*/
void input_screen(int path[],int X[],int Y[])
{
int gd=DETECT,gm,i,start_node,dest_node,mileage,gasprice,via,a,b,choice;
initgraph(&gd,&gm,"C\\TurboC\\TC\\BGI");
setfillstyle(SOLID_FILL,CYAN);
bar(0,0,700,700);
setcolor(0);
rectangle(19,99,441,141);
rectangle(19,159,441,201);
rectangle(19,219,441,261);
rectangle(19,279,441,321);
rectangle(19,339,441,381);
settextstyle(1,0,4);
outtextxy(190,20,"INPUT CONSOLE");
setfillstyle(SOLID_FILL,BLACK);
bar(185,60,440,61);
setfillstyle(SOLID_FILL,LIGHTGREEN);
bar(20,100,440,140);
setfillstyle(SOLID_FILL,LIGHTMAGENTA);
bar(20,160,440,200);
setfillstyle(SOLID_FILL,LIGHTRED);
bar(20,220,440,260);
setfillstyle(SOLID_FILL,LIGHTBLUE);
bar(20,280,440,320);
setfillstyle(SOLID_FILL,LIGHTGRAY);
bar(20,340,440,380);
setcolor(BROWN);
settextstyle(1,0,2);
outtextxy(30,105,"ENTER STARTING NODE:");
setcolor(BLUE);
outtextxy(30,165,"ENTER ENDING NODE:");
setcolor(DARKGRAY);
outtextxy(30,225,"ENTER VEHCILE MILEAGE:");
setcolor(10);
outtextxy(30,285,"ENTER GASOLINE PRICE:");
setcolor(GREEN);
outtextxy(30,345,"VIA*:");
setcolor(7);
settextstyle(4,0,1);
setcolor(1);
outtextxy(20,395,"*:");
outtextxy(30,395,"If no via City,set value=0");
settextstyle(3,0,1);
gotoxy(35,8);
scanf("%d",&start_node);
gotoxy(34,12);
scanf("%d",&dest_node);
gotoxy(38,15);
scanf("%d",&mileage);
gotoxy(35,19);
scanf("%d",&gasprice);
gotoxy(10,23);
scanf("%d",&via);
a=getmaxx();
b=getmaxy();
outtextxy(a-150,b-25,"Press any key");
choice=get_optimal();
switch(choice)
{
case 1:

dijikstra(start_node,dest_node,path,X,Y,0);
break;
case 2:
astar(start_node,dest_node,via);
break;
case 3:
traffic_generator(start_node,dest_node);
break;
case 4:
cost_optimal(start_node,dest_node,mileage,gasprice);
break;
case 5:
bellman_ford();
break;
}
}

int get_optimal()
{
int gd=DETECT,gm,i,a,b;
initgraph(&gd,&gm,"C\\TurboC4\\TC\\BGI");
setfillstyle(SOLID_FILL,MAGENTA);
bar(0,0,650,650);
settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
setcolor(0);
rectangle(79,16,561,76);
setfillstyle(SOLID_FILL,YELLOW);
bar(80,17,560,75);
settextstyle(1,0,5);
outtextxy(100,20,"ALGORITHM SELECTION");
setfillstyle(SOLID_FILL,BROWN);
bar(90,70,550,72);
setfillstyle(SOLID_FILL,CYAN);
bar(76,295,349,354);
setcolor(0);
rectangle(75,295,350,355);
setcolor(10);
settextstyle(8,0,4);
outtextxy(50,100,"1. DISTANCE");
setcolor(1);
outtextxy(350,100,"2. A-STAR");
setcolor(12);
outtextxy(50,160,"3. TRAFFIC");
setcolor(11);
outtextxy(350,160,"4. COST");
setcolor(6);
outtextxy(50,220,"5. BELLMAN");
outtextxy(90,300,"SELECTION:");
gotoxy(37,21);
scanf("%d",&i);
a=getmaxx();
b=getmaxy();
settextstyle(2,0,5);
outtextxy(a-150,b-25,"Press any key");
return i;
}

void first()
{
int gd=DETECT,gm,i;
initgraph(&gd,&gm,"C:\\TC\\BGI");
settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
settextstyle(8,0,2);
outtextxy(250,0,"SMART CITIES");
bar(195,30,330,30);
setbkcolor(2);

setfillstyle(SOLID_FILL,6);
rectangle(3,65,15,75);
floodfill(4,66,WHITE);
rectangle(573,440,612,460);
floodfill(574,441,WHITE);
rectangle(335,395,375,428);
floodfill(336,396,WHITE);

setfillstyle(SOLID_FILL,6);
rectangle(185,345,265,380);
floodfill(186,346,WHITE);
rectangle(55,115,125,135);
floodfill(56,116,WHITE);
rectangle(310,265,340,305);
floodfill(311,266,WHITE);
rectangle(320,155,405,185);
floodfill(321,156,WHITE);

setfillstyle(SOLID_FILL,7);
rectangle(20,65,35,95);
floodfill(21,66,WHITE);
rectangle(310,55,355,75);
floodfill(311,56,WHITE);
rectangle(235,440,280,455);
floodfill(236,441,WHITE);

setfillstyle(SOLID_FILL,7);
rectangle(437,355,452,385);
floodfill(438,356,WHITE);
rectangle(3,105,35,135);
floodfill(4,106,WHITE);
rectangle(25,195,37,235);
floodfill(26,196,WHITE);
rectangle(310,340,380,385);
floodfill(311,341,WHITE);

setfillstyle(SOLID_FILL,6);
rectangle(573,415,612,435);
floodfill(574,416,WHITE);
rectangle(410,355,425,385);
floodfill(411,356,WHITE);
rectangle(3,330,30,350);
floodfill(4,331,WHITE);

setfillstyle(SOLID_FILL,7);
circle(610,180,15);
floodfill(611,181,WHITE);
rectangle(508,415,547,460);
floodfill(509,416,WHITE);

setfillstyle(SOLID_FILL,7);
rectangle(5,165,50,185);
floodfill(6,166,WHITE);
circle(480,197,13);
floodfill(481,198,WHITE);
rectangle(510,330,525,340);
floodfill(511,336,WHITE);

setfillstyle(SOLID_FILL,6);
rectangle(160,175,205,215);
floodfill(161,176,WHITE);
rectangle(415,415,480,467);
floodfill(416,416,WHITE);
rectangle(420,255,440,275);
floodfill(421,256,WHITE);

setfillstyle(SOLID_FILL,6);
rectangle(3,195,15,205);
floodfill(4,196,WHITE);
rectangle(3,215,15,225);
floodfill(4,216,WHITE);
rectangle(464,355,479,385);
floodfill(465,356,WHITE);
rectangle(425,165,535,180);
floodfill(426,166,WHITE);

setfillstyle(SOLID_FILL,7);
rectangle(395,119,445,135);
floodfill(396,120,WHITE);
circle(570,220,15);
floodfill(571,221,WHITE);
rectangle(450,330,465,340);
floodfill(451,331,WHITE);
rectangle(65,340,140,375);
floodfill(66,341,WHITE);

setfillstyle(SOLID_FILL,6);
rectangle(3,105,35,135);
floodfill(4,106,WHITE);
rectangle(55,65,75,105);
floodfill(56,66,WHITE);
rectangle(425,215,535,230);
floodfill(426,216,WHITE);
rectangle(190,265,282,308);
floodfill(196,266,WHITE);
rectangle(122,205,132,225);
floodfill(123,206,WHITE);

setfillstyle(SOLID_FILL,7);
rectangle(162,65,277,130);
floodfill(163,66,WHITE);
rectangle(108,205,117,225);
floodfill(109,206,WHITE);
rectangle(175,335,275,390);
floodfill(176,336,WHITE);
rectangle(112,165,145,195);
floodfill(113,166,WHITE);
rectangle(480,330,495,340);
floodfill(481,331,WHITE);
rectangle(420,330,435,340);
floodfill(421,331,WHITE);

setfillstyle(SOLID_FILL,15);
ellipse(220,97,0,360,55,25);
floodfill(221,98,WHITE);

setfillstyle(SOLID_FILL,9);
ellipse(530,285,0,360,50,18);
ellipse(622,96,0,360,15,40);
ellipse(75,430,0,360,50,20);
floodfill(76,431,WHITE);
floodfill(531,286,WHITE);
floodfill(623,97,WHITE);

setfillstyle(SOLID_FILL,10);
circle(145,290,17);
floodfill(146,291,WHITE);
circle(170,437,6);
floodfill(171,438,WHITE);

rectangle(0,40,5000,50);
rectangle(490,40,500,150);
rectangle(210,150,220,240);
rectangle(40,50,50,140);
rectangle(140,50,150,140);
rectangle(540,150,550,240);
rectangle(390,390,5000,400);
rectangle(0,460,300,470);
rectangle(40,325,50,390);
rectangle(590,250,600,315);
rectangle(0,315,5000,325);
rectangle(390,325,400,390);
rectangle(290,50,300,5000);
rectangle(490,400,500,700);
rectangle(0,140,5000,150);
rectangle(0,240,55,250);
rectangle(137,240,300,250);
rectangle(390,240,5000,250);
rectangle(300,190,400,200);
rectangle(390,190,400,240);
rectangle(490,95,600,105);
rectangle(145,355,155,470);
rectangle(390,400,400,445);
rectangle(335,435,390,445);
rectangle(85,385,145,395);
rectangle(555,400,565,475);
rectangle(625,400,635,475);
line(155,415,243,415);
line(155,425,225,425);
line(155,460,300,387);
line(155,470,300,398);
line(93,151,43,240);
line(105,151,55,240);
line(138,250,38,315);
line(153,250,53,315);
line(505,250,405,315);
line(490,250,390,315);
line(487,390,585,325);
line(505,390,600,325);
line(300,140,490,40);
line(300,150,490,50);
setfillstyle(SOLID_FILL,1);
circle(495,470,3);
floodfill(496,471,WHITE);
circle(560,470,3);
floodfill(561,471,WHITE);
circle(560,395,3);
floodfill(561,396,WHITE);
circle(630,395,3);
floodfill(631,396,WHITE);
circle(630,470,3);
floodfill(631,471,WHITE);
circle(5,45,3);
floodfill(6,46,WHITE);
circle(150,390,3);
floodfill(151,391,WHITE);
circle(90,390,3);
floodfill(91,391,WHITE);
circle(150,420,3);
floodfill(151,421,WHITE);
circle(237,423,3);
floodfill(238,424,WHITE);
circle(395,440,3);
floodfill(396,441,WHITE);
circle(340,440,3);
floodfill(341,441,WHITE);
circle(150,360,3);
floodfill(151,361,WHITE);
circle(150,465,3);
floodfill(151,466,WHITE);
circle(5,465,3);
floodfill(6,466,WHITE);
circle(100,145,3);
floodfill(101,146,WHITE);
circle(47,245,3);
floodfill(48,246,WHITE);
circle(545,145,3);
floodfill(546,146,WHITE);
circle(545,245,3);
floodfill(546,246,WHITE);
circle(215,145,3);
floodfill(216,146,WHITE);
circle(215,245,3);
floodfill(216,246,WHITE);
circle(595,100,3);
floodfill(596,102,WHITE);
circle(495,100,3);
floodfill(496,101,WHITE);
circle(395,95,3);
floodfill(396,96,WHITE);
circle(395,245,3);
floodfill(396,246,WHITE);
circle(395,195,3);
floodfill(396,196,WHITE);
circle(295,195,3);
floodfill(296,196,WHITE);
circle(45,385,3);
floodfill(46,386,WHITE);
circle(295,395,3);
floodfill(296,396,WHITE);
circle(395,395,3);
floodfill(396,396,WHITE);
circle(495,395,3);
floodfill(496,396,WHITE);
circle(45,320,3);
floodfill(46,321,WHITE);
circle(295,320,3);
floodfill(296,321,WHITE);
circle(595,245,3);
floodfill(596,246,WHITE);
circle(595,320,3);
floodfill(596,321,WHITE);
circle(295,245,3);
floodfill(296,246,WHITE);
circle(145,245,3);
floodfill(146,246,WHITE);
circle(502,245,3);
floodfill(503,246,WHITE);
circle(395,320,3);
floodfill(396,321,WHITE);
circle(295,145,3);
floodfill(296,146,WHITE);
circle(495,145,3);
floodfill(496,146,WHITE);
circle(45,145,3);
floodfill(46,146,WHITE);
circle(145,145,3);
floodfill(146,146,WHITE);
circle(495,45,3);
floodfill(496,46,WHITE);
circle(295,45,3);
floodfill(296,46,WHITE);
circle(45,45,3);
floodfill(46,46,WHITE);
circle(145,45,3);
floodfill(146,46,WHITE);
circle(295,465,3);
floodfill(296,466,WHITE);
setfillstyle(SOLID_FILL,8);
floodfill(405,144,WHITE);
floodfill(491,144,WHITE);
floodfill(491,130,WHITE);
floodfill(491,99,WHITE);
floodfill(345,120,WHITE);
floodfill(445,70,WHITE);
floodfill(74,195,WHITE);
floodfill(215,175,WHITE);
floodfill(150,246,WHITE);
floodfill(305,195,WHITE);
floodfill(391,196,WHITE);
floodfill(391,210,WHITE);
floodfill(410,245,WHITE);
floodfill(545,230,WHITE);
floodfill(498,253,WHITE);
floodfill(50,314,WHITE);
floodfill(497,389,WHITE);
floodfill(560,405,WHITE);
floodfill(630,405,WHITE);
floodfill(395,430,WHITE);
floodfill(385,440,WHITE);
floodfill(96,390,WHITE);
floodfill(150,396,WHITE);
floodfill(156,420,WHITE);
floodfill(12,465,WHITE);
floodfill(146,464,WHITE);
floodfill(160,465,WHITE);
floodfill(180,465,WHITE);
floodfill(510,99,WHITE);
floodfill(592,262,WHITE);
floodfill(289,398,WHITE);
setfillstyle(6,13);
floodfill(291,244,WHITE);
floodfill(291,144,WHITE);
floodfill(291,321,WHITE);
floodfill(291,398,WHITE);
floodfill(299,392,WHITE);
floodfill(291,464,WHITE);
floodfill(295,475,WHITE);
floodfill(292,62,WHITE);
floodfill(292,162,WHITE);
floodfill(292,262,WHITE);
floodfill(292,412,WHITE);
floodfill(292,336,WHITE);
floodfill(291,464,WHITE);
floodfill(295,475,WHITE);
floodfill(291,205,WHITE);
setfillstyle(SOLID_FILL,8);
floodfill(492,412,WHITE);
floodfill(502,392,WHITE);
floodfill(42,337,WHITE);
floodfill(392,337,WHITE);
floodfill(2,142,WHITE);
floodfill(302,142,WHITE);
floodfill(502,142,WHITE);
floodfill(2,242,WHITE);
floodfill(502,242,WHITE);
floodfill(492,62,WHITE);
floodfill(42,62,WHITE);
floodfill(142,62,WHITE);
setfillstyle(2,9);
floodfill(2,318,WHITE);
floodfill(502,318,WHITE);
floodfill(510,44,WHITE);
floodfill(2,42,WHITE);
floodfill(491,44,WHITE);
floodfill(485,46,WHITE);
bar(195,30,400,30);
settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
settextstyle(2,0,5);
outtextxy(3,48,"0");
outtextxy(52,48,"1");
outtextxy(152,48,"2");
outtextxy(302,48,"3");
outtextxy(502,48,"4");
outtextxy(402,98,"5");
outtextxy(502,103,"6");
outtextxy(602,103,"7");
outtextxy(52,148,"8");
outtextxy(110,148,"9");
outtextxy(152,148,"10");
outtextxy(222,148,"11");
outtextxy(302,148,"12");
outtextxy(502,148,"13");
outtextxy(552,148,"14");
outtextxy(302,198,"15");
outtextxy(402,195,"16");
outtextxy(54,248,"17");
outtextxy(152,248,"18");
outtextxy(222,248,"19");
outtextxy(302,248,"20");
outtextxy(402,248,"21");
outtextxy(509,248,"22");
outtextxy(552,248,"23");
outtextxy(602,248,"24");
outtextxy(52,323,"25");
outtextxy(302,323,"26");
outtextxy(402,323,"27");
outtextxy(602,323,"28");
outtextxy(157,363,"29");
outtextxy(52,388,"30");
outtextxy(302,395,"31");
outtextxy(402,398,"32");
outtextxy(502,398,"33");
outtextxy(130,445,"34");
outtextxy(302,455,"35");
outtextxy(342,443,"36");
outtextxy(397,443,"37");
outtextxy(502,460,"38");
outtextxy(567,398,"39");
outtextxy(567,460,"40");
outtextxy(611,398,"41");
outtextxy(608,460,"42");
outtextxy(92,393,"43");
outtextxy(157,393,"44");
outtextxy(129,415,"45");
outtextxy(245,422,"46");
outtextxy(5,443,"47");
setfillstyle(SOLID_FILL,14);
setcolor(5);
bar(280,90,310,93);
bar(280,93,282,95);
bar(308,93,310,95);
bar(345,305,348,335);
bar(348,305,350,307);
bar(348,333,350,335);
bar(279,430,311,433);
bar(279,433,280,435);
bar(309,433,311,435);
getch();

}

void weight()
{
setcolor(1);
settextstyle(2,0,4);
outtextxy(20,39,"45");
outtextxy(95,39,"100");
outtextxy(220,39,"150");
outtextxy(395,39,"200");
outtextxy(43,82,"1");
outtextxy(43,90,"0");
outtextxy(43,98,"0");
outtextxy(143,82,"1");
outtextxy(143,90,"0");
outtextxy(143,98,"0");
outtextxy(293,82,"1");
outtextxy(293,90,"0");
outtextxy(293,98,"0");
outtextxy(493,63,"5");
outtextxy(493,71,"5");
outtextxy(493,114,"4");
outtextxy(493,121,"5");
outtextxy(540,94,"100");
outtextxy(443,75,"112");
outtextxy(362,115,"112");
outtextxy(70,139,"55");
outtextxy(120,139,"45");
outtextxy(177,139,"70");
outtextxy(252,139,"80");
outtextxy(392,139,"200");
outtextxy(517,139,"50");
outtextxy(80,175,"1");
outtextxy(75,183,"1");
outtextxy(70,191,"3");
outtextxy(213,178,"1");
outtextxy(213,186,"0");
outtextxy(213,194,"0");
outtextxy(293,163,"5");
outtextxy(293,171,"0");
outtextxy(293,213,"5");
outtextxy(293,221,"0");
outtextxy(340,189,"100");
outtextxy(393,213,"5");
outtextxy(393,221,"0");
outtextxy(445,239,"107");
outtextxy(520,239,"43");
outtextxy(565,239,"50");
outtextxy(175,239,"70");
outtextxy(250,239,"80");
outtextxy(105,280,"125");
outtextxy(453,280,"130.6");
outtextxy(293,270,"7");
outtextxy(293,278,"5");
outtextxy(593,270,"7");
outtextxy(593,278,"5");
outtextxy(163,314,"250");
outtextxy(340,314,"100");
outtextxy(490,314,"200");
outtextxy(43,343,"6");
outtextxy(43,351,"5");
outtextxy(293,353,"7");
outtextxy(293,360,"5");
outtextxy(393,353,"7");
outtextxy(393,360,"5");
outtextxy(555,355,"125");
outtextxy(72,459,"145");
outtextxy(115,384,"60");
outtextxy(148,366,"3");
outtextxy(148,374,"0");
outtextxy(148,395,"3");
outtextxy(148,403,"0");
outtextxy(148,430,"4");
outtextxy(148,438,"5");
outtextxy(190,414,"95");
outtextxy(215,459,"145");
outtextxy(257,406,"56");
outtextxy(190,437,"105");
outtextxy(293,420,"7");
outtextxy(293,428,"0");
outtextxy(362,434,"55");
outtextxy(393,410,"4");
outtextxy(393,418,"5");
outtextxy(440,389,"100");
outtextxy(525,389,"65");
outtextxy(590,389,"70");
outtextxy(493,425,"7");
outtextxy(493,433,"5");
outtextxy(558,425,"7");
outtextxy(558,433,"5");
outtextxy(628,425,"7");
outtextxy(628,433,"5");
getch();
}

//algo functions defined
void dijikstra(int start_node,int dest_node,int path[],int X[],int Y[],int flag)
{
int cost[MAX][MAX], distance[MAX], pred[MAX];
int visited[MAX], count, mindistance, nextnode, i,j,len=0;
for(i=0;i < n;i++)
{
for(j=0;j < n;j++)
{
if(G[i][j]==0)
cost[i][j]=INFINITY;
else
cost[i][j]=G[i][j];
}
}
for(i=0;i<n;i++)
{
distance[i]=cost[start_node][i];
pred[i]=start_node;
visited[i]=0;
}
distance[start_node]=0;
visited[start_node]=1;
count=1;
while(count < n-1)
{
mindistance=INFINITY;
for(i=0;i < n;i++)
if(distance[i] < mindistance&&!visited[i])
{
mindistance=distance[i];
nextnode=i;
}
visited[nextnode]=1;
for(i=0;i < n;i++)
{
if(!visited[i])
{
if(mindistance+cost[nextnode][i] < distance[i])
{
distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;
//printf("predecessor array %d \n",pred[i]);
}
}
}
count++;
}
if(dest_node!=start_node)
{
printf("\nDistance of %d = %d\n", dest_node, distance[dest_node]);
//BHAI YEAH VALA SENTENCE DIALOGUE BOX ME PRINT KARVA-TOTALDISTANCE = UPAR VALA PURA
path[len]= dest_node;
j=dest_node;
do
{
len=len+1;
j=pred[j];
path[len]=j;
}
while(j!=start_node);
}
len=len+1;
path[len]=start_node;
first();
screen2(X,Y,path,len-1);
getch();
display_path(start_node,dest_node,distance[dest_node],flag);
}
//dijkstra ends

void astar(int start_node,int dest_node,int via_ip)
{
int cost[MAX][MAX], distance[MAX], pred[MAX];
int visited[MAX], count, mindistance, nextnode, i,j,len=0,est_distance=0,flag=0;
int temp,via=via_ip;
if(via>0)
{
	flag=1;
}
if(flag)
{
temp=start_node;
start_node=via;
}
/*cost matrix generated*/
for(i=0;i < n;i++)
{
for(j=0;j < n;j++)
{
if(G[i][j]==0)
cost[i][j]=INFINITY;
else
cost[i][j]=G[i][j];
}
}

//finish cost matrix construction

//Distance array-holding distance of vertices from startnode
for(i=0;i<n;i++)
{
distance[i]=cost[start_node][i];
pred[i]=start_node;
visited[i]=0;
}
distance[start_node]=0;
visited[start_node]=1;
count=1;
while(count < n-1)
{
mindistance=INFINITY;
for(i=0;i < n;i++)
{
est_distance=sqrt(pow((X[dest_node]-X[i]),2)+pow((Y[dest_node]-Y[i]),2));
//finding immediate shortest node using dynamic approach
if(distance[i] < (mindistance+est_distance) &&!visited[i])
{
mindistance=distance[i]+est_distance;
nextnode=i;
}

}
visited[nextnode]=1;
for(i=0;i < n;i++)
{
if(!visited[i])
{
if(mindistance+cost[nextnode][i] < distance[i])
{
//A* implementation-estimated distance added to fringe.

distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;


}
}
}
count++;
}
if(dest_node!=start_node)
{

path[len]= dest_node;
j=dest_node;
do
{
len=len+1;
j=pred[j];
path[len]=j;
}
while(j!=start_node);
}
len=len+1;
if(!flag)
{
path[len]=start_node;
}

/* calculating shortest from real start_node to via*/

if(flag)
{
   flag=0;
   start_node=temp;
   dest_node=via;
   for(i=0;i<n;i++)
{
distance[i]=cost[start_node][i];
pred[i]=start_node;
visited[i]=0;
}
distance[start_node]=0;
visited[start_node]=1;
count=1;
while(count < n-1)
{
mindistance=INFINITY;
for(i=0;i < n;i++)
{
est_distance=sqrt(pow((X[dest_node]-X[i]),2)+pow((Y[dest_node]-Y[i]),2));
if(distance[i] < (mindistance+est_distance) &&!visited[i])
{
mindistance=distance[i]+est_distance;
nextnode=i;
}

}
visited[nextnode]=1;
for(i=0;i < n;i++)
{
if(!visited[i])
{
if(mindistance+cost[nextnode][i] < distance[i])
{
//A* implementation-estimated distance added to fringe.

distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;


}
}
}
count++;
}
if(dest_node!=start_node)
{
path[len]= dest_node;
j=dest_node;
do
{
len=len+1;
j=pred[j];
path[len]=j;
}
while(j!=start_node);
}
len=len+1;
if(!flag)
{
path[len]=start_node;
}
	
}
first();
screen2(X,Y,path,len-1);
getch();
display_path(start_node,dest_node,distance[dest_node],0);
}
//astar ends

//bellman ford
void bellman_ford()
{
    int gd=DETECT,gm;
    int i,u,V,j,k,distance[20],parent[20],S;
    int edge[20][2],G[20][20];
    int E,v;
    initgraph(&gd,&gm,"");
    k=0;
    printf("BELLMAN FORD\n");
    printf("Enter no. of vertices: ");
    scanf("%d",&V);
    printf("Enter graph in matrix form:\n");
    for(i=0;i<V;i++)
	for(j=0;j<V;j++)
	{
	    scanf("%d",&G[i][j]);
	    if(G[i][j]!=0)
		edge[k][0]=i,edge[k++][1]=j;
	}
	E=k;

    for(i=0;i<V;i++)
	distance[i] = 1000 , parent[i] = -1 ;
	printf("Enter source: ");
	scanf("%d",&S);
	distance[S-1]=0 ;
    for(i=0;i<V-1;i++)
    {
	for(k=0;k<E;k++)
	{
	    u = edge[k][0] , v = edge[k][1] ;
	    if(distance[u]+G[u][v] < distance[v])
		distance[v] = distance[u] + G[u][v] , parent[v]=u ;
	}
    }
    for(k=0;k<E;k++)
	{
	    u = edge[k][0] , v = edge[k][1] ;
	}

	    for(i=0;i<V;i++)
		printf("Vertex %d -> cost = %d parent = %d\n",i+1,distance[i],parent[i]+1);


}



void cost_optimal(int start_node,int dest_node,int mileage,int gasprice)
{
int i=0,j=0,flag=1;

    for(i=0;i<MAX;i++)
    {
	for(j=0;j<MAX;j++)
	{
	    G[i][j]=((G[i][j]/mileage)*gasprice);
	}
    }
    G[3][12]=(G[3][12])+70;
    G[26][27]=(G[26][27])+150;
    G[31][34]=(G[31][34]+100);
    G[12][3]=(G[12][3])+70;
    G[27][26]=(G[27][26])+150;
    G[34][31]=(G[34][31])+100;

    dijikstra(start_node,dest_node,path,X,Y,flag);
}
//costoptimal ends

void traffic_generator(int start_node,int dest_node)
{

int i, j;
/* Intializes random number generator */
/*   for( i = 0 ; i < MAX ; i++ )
   {
      for(j=0;j<MAX;j++)
      {
	  if(G[i][j]>0)
	 {
	     G[i][j]=rand()%50;
	 }

     }
}
  */
G[0][1]=(G[0][1]*0.66);
G[1][2]=(G[1][2]*0.66);
G[2][3]=(G[2][2]*0.66);
G[3][4]=(G[3][4]*0.66);
G[25][26]=(G[25][26]*0.66);
G[26][27]=(G[26][27]*0.66);
G[27][28]=(G[27][28]*0.66);
//NATIONAL HIGHWAY

G[3][12]=(G[3][12]*0.4);
G[12][15]=(G[12][15]*0.4);
G[15][20]=(G[15][20]*0.4);
G[20][26]=(G[20][26]*0.4);
G[26][31]=(G[26][31]*0.4);
G[31][35]=(G[31][35]*0.4);


dijikstra(start_node,dest_node,path,X,Y,0);
}
//traffic generator ends

void create_map()
{
int i=0,j=0;
for(i=0;i<MAX;i++)
{
for(j=0;j<MAX;j++)
{
G[i][j]=0;
}
}
G[0][1]=5;
//1
G[1][0]=5;
G[1][2]=11;
G[1][8]=18;
//2
G[2][1]=11;
G[2][3]=14;
G[2][10]=22;
//3
G[3][2]=14;
G[3][4]=24;
G[3][12]=24;
//4
G[4][3]=10;
G[4][5]=5;
G[4][6]=24;
//5
G[5][4]=18;
G[5][12]=5;
//
G[6][4]=22;
G[6][7]=47;
G[6][13]=34;
//
G[7][6]=24;
//8
G[8][1]=13;
G[8][9]=20;
//9
G[9][8]=20;
G[9][10]=27;
G[9][17]=3;
//10
G[10][9]=27;
G[10][11]=2;
G[10][2]=14;
//11
G[11][10]=2;
G[11][12]=7;
G[11][19]=34;
//12
G[12][5]=32;
G[12][11]=32;
G[12][13]=57;
G[12][15]=32;
G[12][3]=3;

//13
G[13][6]=3;
G[13][12]=57;
G[13][14]=22;
//14
G[14][13]=22;
G[14][23]=30;

//15
G[15][12]=7;
G[15][16]=30;
G[15][20]=30;
//16
G[16][15]=32;
G[16][21]=97;
//17
G[17][9]=27;
//18
G[18][19]=46;
G[18][25]=36;
//19
G[19][18]=26;
G[19][20]=46;
G[19][11]=22;
//20
G[20][19]=2;
G[20][15]=3;
G[20][26]=4;
//21
G[21][16]=5;
G[21][22]=11;
//22
G[22][21]=11;
G[22][23]=14;
//23
G[23][22]=14;
G[23][24]=24;
G[23][14]=24;
//4
G[24][23]=10;
G[24][28]=5;
//5
G[25][18]=18;
G[25][30]=5;
G[25][26]=2;
//
G[26][20]=22;
G[26][25]=47;
G[26][27]=34;
G[26][31]=5;
//
G[27][26]=24;
G[27][28]=3;
G[27][22]=98;
G[27][32]=7;
G[27][48]=12;
//8
G[28][27]=13;
G[28][24]=20;
G[28][33]=22;
G[28][48]=12;
//29
G[29][44]=20;
//30
G[30][25]=2;
//31
G[31][46]=5;
G[31][35]=11;
G[31][26]=18;
//32
G[32][27]=11;
G[32][33]=14;
G[32][37]=22;
//33
G[33][32]=14;
G[33][38]=24;
G[33][39]=24;
G[33][28]=8;
//34
G[34][45]=10;
G[34][46]=5;
G[34][47]=24;
G[34][35]=34;
//35
G[35][34]=18;
G[35][31]=5;
//36
G[36][37]=22;
//37
G[37][36]=24;
G[37][32]=24;
//38
G[38][33]=13;
//39
G[39][33]=20;
G[39][41]=27;
G[39][40]=3;
//40
G[40][39]=8;
//41
G[41][39]=34;
G[41][42]=2;
//42
G[42][41]=32;
//43
G[43][44]=34;
//44
G[44][43]=3;
G[44][29]=13;
G[44][45]=23;
//45
G[45][44]=42;
G[45][46]=2;
G[45][34]=43;
//46
G[46][45]=8;
G[46][31]=40;
G[46][34]=13;
//47
G[47][34]=32;
//48
G[48][28]=12;
G[48][27]=122;
}

void node_coordinates()
{
X[0]=0;
X[1]=45;
X[2]=145;
X[3]=295;
X[4]=495;
X[5]=395;
X[6]=495;
X[7]=595;
X[8]=45;
X[9]=100;
X[10]=145;
X[11]=215;
X[12]=295;
X[13]=495;
X[14]=545;
X[15]=295;
X[16]=395;
X[17]=47;
X[18]=145;
X[19]=215;
X[20]=295;
X[21]=395;
X[22]=502;
X[23]=545;
X[24]=595;
X[25]=45;
X[26]=295;
X[27]=395;
X[28]=595;
X[29]=150;
X[30]=45;
X[31]=295;
X[32]=395;
X[33]=495;
X[34]=150;
X[35]=295;
X[36]=340;
X[37]=395;
X[38]=495;
X[39]=560;
X[40]=560;
X[41]=630;
X[42]=630;
X[43]=90;
X[44]=150;
X[45]=150;
X[46]=245;
X[47]=5;
X[48]=510;

Y[0]=45;
Y[1]=45;
Y[2]=45;
Y[3]=45;
Y[4]=45;
Y[5]=95;
Y[6]=100;
Y[7]=100;
Y[8]=145;
Y[9]=145;
Y[10]=145;
Y[11]=145;
Y[12]=145;
Y[13]=145;
Y[14]=145;
Y[15]=195;
Y[16]=195;
Y[17]=245;
Y[18]=245;
Y[19]=245;
Y[20]=245;
Y[21]=245;
Y[22]=245;
Y[23]=245;
Y[24]=245;
Y[25]=320;
Y[26]=320;
Y[27]=320;
Y[28]=320;
Y[29]=360;
Y[30]=385;
Y[31]=395;
Y[32]=395;
Y[33]=395;
Y[34]=465;
Y[35]=465;
Y[36]=440;
Y[37]=440;
Y[38]=470;
Y[39]=395;
Y[40]=470;
Y[41]=395;
Y[42]=470;
Y[43]=390;
Y[44]=390;
Y[45]=420;
Y[46]=420;
Y[47]=465;
Y[48]=320;
}


void calc_distance()
{
    int i=0,j=0;
    for(i=0;i<MAX;i++)
    {
	for(j=0;j<MAX;j++)
	{
	    if(G[i][j]>0)
	    {
		G[i][j]=sqrt(pow((X[j]-X[i]),2)+pow((Y[j]-Y[i]),2));
		printf("%f ",G[i][j]);
	    }
	}
	printf("\n");
    }
}

void display_path(int source,int destination,int distance,int flag)
{
int gd=DETECT,gm,a,b;
initgraph(&gd,&gm,"");
settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
setcolor(10);
setfillstyle(SOLID_FILL,CYAN);
bar(150,30,470,32);
outtextxy(170,0,"OPTIMAL PATH");
gotoxy(10,5);
if(flag>0)
{
printf("Your Overall Travelling Cost is ---->Rs %d",distance);
}
else
{
printf("\n\nThe Total Distance Between %d and %d is------> %d",source,destination,distance);
}
}

//output function
void ShowBMP(int x, int y, char* FileName,struct BMP Obj)
{
    int b,a;
    int row_padded;
    unsigned char* Datas;
    int in=0;
    unsigned char c=0;
    FILE * fp;
    fp = fopen(FileName,"rb");

    if(!fp){
    printf("Error : Unable to open file ..");
    exit(0);
    }
    fread(&Obj, sizeof(Obj), 1, fp);
     row_padded = (Obj.Width*3 + 3) & (~3);

    if(Obj.BitsPerPixel!=24)  // This isn't a 24 color bmp we can read;
    {
     fclose(fp);
     printf("Error : File format not supported ..");
     getch();
     exit(0);
    };
    fseek(fp,Obj.OffSet,SEEK_SET);

    for(b=Obj.Height;b>=0;b--)
    {
     fread(Datas, sizeof(unsigned char), row_padded, fp);
     c=0;
     in=0;
     for(a=0;a<=Obj.Width*3;a++)
     {
       c = (Datas[a] + (Datas[a+1] << 8) + (Datas[a+2] << 16))>>5;
	 putpixel(a+x,b+y,c);
	 in++;
     }
    }
    free (Datas);
    fclose(fp);
}

void print(int monuid)
{
  int color;
  int gd=DETECT,gm;
  long int arr[10],image[10];
  int i,j,k,e,ch,num;
  char str[20][20],str1[20];
  int x,y;
  char temp[20];
   FILE *inp[10];
  struct BMP Obj[10];
  clrscr();
  initgraph(&gd,&gm,"");
  setcolor(14);
  settextstyle(1,0,4);
  outtextxy(160,0,"NEAR ATTRACTIONS");
  setfillstyle(SOLID_FILL,GREEN);
  bar(150,35,460,38);
  //ShowBMP(0,60,"tune2.bmp",Obj[x]); /* Change of file name acco to if else */
  switch(monuid)
  {
  case 16:
  {
  ShowBMP(0,60,"mountain.bmp",Obj[x]);
  getch();
  break;
  }
 /* case 29:
  {
  ShowBMP(0,60,"taj3.bmp",Obj[x]);
  getch();
  break;
  }
*/
  case 19:
  {
  ShowBMP(0,60,"taj3.bmp",Obj[x]);
  getch();
  break;
  }
}
getch();
}

void data(int monuid)
{
int id;
FILE *fp,*ft;
char another,choice;
Site view;
char fname[20];
char lname[20];
long int recsize;
clrscr();
if(monuid==16)
fp=fopen("LOTUS.TXT","rb+");
else if(monuid==29)
fp=fopen("TAJ.TXT","rb+");
else if(monuid==19)
fp=fopen("AKS.TXT","rb+");

recsize=sizeof(view);
fflush(stdin);
rewind(fp);
while(fread(&view,recsize,1,fp)==1)
printf("%s\n%s\n%s\n%s\n",view.name,view.details,view.rating,view.trans);
getch();
fclose(fp);
}

void create_proximity()
{
	//monument1
	proximity[12]=16;
	proximity[15]=16;
	proximity[16]=16;

	//monument2
	proximity[43]=29;
	proximity[44]=29;
	proximity[30]=29;
	proximity[29]=29;
	proximity[25]=29;

	//monument3
	proximity[26]=19;
	proximity[19]=19;
	proximity[18]=19;
	proximity[20]=19;
}

void main()
{
//ALGO VARIABLES
node_coordinates();
create_map();
create_proximity();
calc_distance();
screen1();
first();
weight();
input_screen(path,X,Y);
getch();
if(mdestination>0)
{
data(mdestination);
closegraph();
print(mdestination);
closegraph();
}
closegraph();
}
