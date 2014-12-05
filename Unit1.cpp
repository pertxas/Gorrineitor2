//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
randomize();
playing=false;
bicho1=new Graphics::TBitmap();
bicho1->LoadFromFile("bmps/bicho.bmp");
bicho2=new Graphics::TBitmap();
bicho2->LoadFromFile("bmps/bicho.bmp");
bicho3=new Graphics::TBitmap();
bicho3->LoadFromFile("bmps/bicho.bmp");
bicho4=new Graphics::TBitmap();
bicho4->LoadFromFile("bmps/bicho.bmp");
bichoshield=new Graphics::TBitmap();
bichoshield->LoadFromFile("bmps/bichoshield.bmp");
ClientHeight=Screen->Height-27;
ClientWidth=Screen->Width;
Bevel1->Top=0;
Bevel1->Height=ClientHeight;
Bevel1->Left=ClientWidth-DISTBVL;
IMG_Fondo->Height=ClientHeight;
IMG_Fondo->Width=Bevel1->Left;
IMG_Fondo->Picture->LoadFromFile("bmps/intro.bmp");
BUT_Start->Left=Bevel1->Left+(DISTBVL-BUT_Start->Width)/2;
BUT_Pause->Left=Bevel1->Left+(DISTBVL-BUT_Pause->Width)/2;
BUT_Exit->Left=Bevel1->Left+(DISTBVL-BUT_Exit->Width)/2;
BUT_Pause->Top=ClientHeight/2-15;
BUT_Start->Top=BUT_Pause->Top-60;
BUT_Exit->Top=BUT_Pause->Top+60;
BUT_Start->Picture->LoadFromFile("bmps/butstart0.bmp");
BUT_Pause->Picture->LoadFromFile("bmps/butpause1.bmp");
BUT_Exit->Picture->LoadFromFile("bmps/butexit0.bmp");
LBL_Skore->Left=Bevel1->Left+(DISTBVL-LBL_Skore->Width)/2;
LBL_SkoreV->Left=LBL_Skore->Left;
IMG_Laser->Picture->LoadFromFile("bmps/laser.bmp");
IMG_Shield->Picture->LoadFromFile("bmps/shield.bmp");
int spc=(DISTBVL-(2*IMG_Laser->Width+24))/3;
IMG_Laser->Left=Bevel1->Left+spc;
IMG_Laser->Top=ClientHeight-112;
IMG_Shield->Left=IMG_Laser->Left+IMG_Laser->Width+12+spc;
IMG_Shield->Top=ClientHeight-112;
Screen->Cursor=crCuennos;
InitKosmos();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
Screen->Cursors[crTarget]=LoadCursor(HInstance, "C1");
Screen->Cursors[crCuennos]=LoadCursor(HInstance, "C2");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if (!playing || X >= Bevel1->Left-DES )
        {
        if (X >= Bevel1->Left) Screen->Cursor=crCuennos;
        BUT_Start->Picture->LoadFromFile("bmps/butstart"+AnsiString(BUT_Start->Tag)+".bmp");
        BUT_Pause->Picture->LoadFromFile("bmps/butpause"+AnsiString(BUT_Pause->Tag)+".bmp");
        BUT_Exit->Picture->LoadFromFile("bmps/butexit"+AnsiString(BUT_Exit->Tag)+".bmp");
        return;
        }
Screen->Cursor=crTarget;

//PintaBichos();// Refresko de los Bichos
Canvas->StretchDraw(rect1,bicho1);
Canvas->StretchDraw(rect2,bicho2);
Canvas->StretchDraw(rect3,bicho3);
Canvas->StretchDraw(rect4,bicho4);

Canvas->Pen->Width=1; //anchura de las lineas

Canvas->MoveTo(0,0);
Canvas->Pen->Color=clBlack;
Canvas->LineTo(oldx-DES,oldy-DES);
Canvas->MoveTo(0,0);
Canvas->Pen->Color=clRed;
Canvas->LineTo(X-DES,Y-DES);

Canvas->MoveTo(Bevel1->Left,0);
Canvas->Pen->Color=clBlack;
Canvas->LineTo(oldx+DES,oldy-DES);
Canvas->MoveTo(Bevel1->Left,0);
Canvas->Pen->Color=clRed;
Canvas->LineTo(X+DES,Y-DES);

Canvas->MoveTo(Bevel1->Left,ClientHeight);
Canvas->Pen->Color=clBlack;
Canvas->LineTo(oldx+DES,oldy+DES);
Canvas->MoveTo(Bevel1->Left,ClientHeight);
Canvas->Pen->Color=clRed;
Canvas->LineTo(X+DES,Y+DES);

Canvas->MoveTo(0,ClientHeight);
Canvas->Pen->Color=clBlack;
Canvas->LineTo(oldx-DES,oldy+DES);
Canvas->MoveTo(0,ClientHeight);
Canvas->Pen->Color=clRed;
Canvas->LineTo(X-DES,Y+DES);

oldx=X;oldy=Y;
Bevel1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if (laser <= 0 || X >= Bevel1->Left || shooting || !playing) return;
shooting=true;
laser--;
Laser();

// SUPERGUARREO MAXIMO DE LA VIDA kalkulo la 2ª 'Y' copiándola de la 1ª
xl=X;
yl=Y;
inc=X/3;
inc2=(Bevel1->Left-X)/3;
f1=((double)Y-(ClientHeight/2))/(double)X;
TIM_PintaTimer(this);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TIM_1Timer(TObject *Sender)
{
//TIM_1->Enabled=false;
BorraBicho(rect1, bicho1);
// Acercamiento del Bicho
x1+=LevelX(r1, s1);
y1+=LevelY(r1, s1);
s1+=LevelS();
rect1=Rect(x1,y1,x1+s1,y1+s1);
bicho1->LoadFromFile("bmps/bicho.bmp");
Canvas->StretchDraw(rect1,bicho1);
// Detekzión del Choke
if (s1 >= 100)
        {
        TIM_1->Enabled=false;
        MPY_2->Rewind();
        MPY_2->Play();
        Krash(rect1, bicho1);
        d1=2;
        TIM_BorraBicho1->Enabled=true;
        }
//else TIM_1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TIM_2Timer(TObject *Sender)
{
//TIM_2->Enabled=false;
BorraBicho(rect2, bicho2);
// Acercamiento del Bicho
x2+=LevelX(r2, s2);
y2+=LevelY(r2, s2);
s2+=LevelS();
rect2=Rect(x2,y2,x2+s2,y2+s2);
bicho2->LoadFromFile("bmps/bicho.bmp");
Canvas->StretchDraw(rect2,bicho2);
// Detekzión del Choke
if (s2 >= 100)
        {
        TIM_2->Enabled=false;
        MPY_2->Rewind();
        MPY_2->Play();
        Krash(rect2, bicho2);
        d2=2;
        TIM_BorraBicho2->Enabled=true;
        }
//else TIM_2->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TIM_3Timer(TObject *Sender)
{
//TIM_3->Enabled=false;
BorraBicho(rect3, bicho3);
// Acercamiento del Bicho
x3+=LevelX(r3, s3);
y3+=LevelY(r3, s3);
s3+=LevelS();
rect3=Rect(x3,y3,x3+s3,y3+s3);
bicho3->LoadFromFile("bmps/bicho.bmp");
Canvas->StretchDraw(rect3,bicho3);
// Detekzión del Choke
if (s3 >= 100)
        {
        TIM_3->Enabled=false;
        MPY_2->Rewind();
        MPY_2->Play();
        Krash(rect3, bicho3);
        d3=2;
        TIM_BorraBicho3->Enabled=true;
        }
//else TIM_3->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TIM_4Timer(TObject *Sender)
{
//TIM_4->Enabled=false;
BorraBicho(rect4, bicho4);
// Acercamiento del Bicho
x4+=LevelX(r4, s4);
y4+=LevelY(r4, s4);
s4+=LevelS();
rect4=Rect(x4,y4,x4+s4,y4+s4);
bicho4->LoadFromFile("bmps/bicho.bmp");
Canvas->StretchDraw(rect4,bicho4);
// Detekzión del Choke
if (s4 >= 100)
        {
        TIM_4->Enabled=false;
        MPY_2->Rewind();
        MPY_2->Play();
        Krash(rect4, bicho4);
        d4=2;
        TIM_BorraBicho4->Enabled=true;
        }
//else TIM_4->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BorraBicho(TRect rect, Graphics::TBitmap *bicho)
{
bicho->LoadFromFile("bmps/Blank.bmp");
Canvas->StretchDraw(rect,bicho);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OtroBicho(int &x, int &y, int &s, TRect &rect, Graphics::TBitmap *bicho, int &d)
{
x=random(Bevel1->Left-200)+100;
y=random(ClientHeight-200)+100;
s=2;
d=0;
rect=Rect(x,y,x+s,y+s);
Canvas->StretchDraw(rect,bicho);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Krash(TRect rect, Graphics::TBitmap *bicho)
{
bicho->LoadFromFile("bmps/krash.bmp");
Canvas->StretchDraw(rect,bicho);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Laser()
{
int distx=IMG_Laser->Left+IMG_Laser->Width+1;
int disty=10;
int ancho=10;
Canvas->Pen->Width=1;
Canvas->Pen->Color=clLime;
Canvas->Brush->Color=clBlack;
Canvas->Rectangle(distx-1,ClientHeight-MAXLASER-disty-1,distx+ancho+1,ClientHeight-disty+1);
TRect laserrect= Rect(distx,ClientHeight-laser-disty,distx+ancho,ClientHeight-disty);
Canvas->Brush->Color=clOlive;
Canvas->FillRect(laserrect);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Shield()
{
int distx=IMG_Shield->Left+IMG_Shield->Width+1;
int disty=10;
int ancho=10;
Canvas->Pen->Width=1;
Canvas->Pen->Color=clRed;
Canvas->Brush->Color=clBlack;
Canvas->Rectangle(distx-1,ClientHeight-MAXSHIELD-disty-1,distx+ancho+1,ClientHeight-disty+1);
TRect laserrect= Rect(distx,ClientHeight-shield-disty,distx+ancho,ClientHeight-disty);
Canvas->Brush->Color=clMaroon;
Canvas->FillRect(laserrect);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
Laser();
Shield();
PintaKosmos();
PintaBichos();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::InitKosmos()
{
for (int i=0; i < NUMSTARS;i++)
        {
        kosmos[i].x=random(Bevel1->Left)-Bevel1->Left/2;if (kosmos[i].x==0) kosmos[i].x=1;
        kosmos[i].y=random(ClientHeight)-ClientHeight/2;if (kosmos[i].y==0) kosmos[i].y=1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TIM_PintaTimer(TObject *Sender)
{
TIM_Pinta->Enabled=false;
if (TIM_Pinta->Tag <= 0)
        {
        TIM_Pinta->Tag=3;
        TIM_BorraLaser->Enabled=true;
        return;
        }
int j=TIM_Pinta->Tag;

Canvas->Pen->Width=3;

Canvas->MoveTo(xl-j*inc,((ClientHeight/2)+((xl-j*inc)*f1)));
Canvas->Pen->Color=clLime;
Canvas->LineTo(xl-((j-1)*inc),((ClientHeight/2)+((xl-((j-1)*inc))*f1)));

Canvas->MoveTo(xl+j*inc2,((ClientHeight/2)+((xl-j*inc)*f1)));
Canvas->LineTo(xl+((j-1)*inc2),((ClientHeight/2)+((xl-((j-1)*inc))*f1)));

TIM_Pinta->Tag--;
TIM_BorraLaser->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TIM_BorraLaserTimer(TObject *Sender)
{
TIM_BorraLaser->Enabled=false;
if (TIM_BorraLaser->Tag <= 0) // fin de disparo
        {
        TIM_BorraLaser->Tag=3;
        shooting=false;
        kuentatiros++;
        // Detekzión de Impakto
        if (xl > x1 && xl < x1+s1 && yl > y1 && yl < y1+s1 && d1==0)
                {
                TIM_1->Enabled=false;MPY_1->Rewind();MPY_1->Play();
                bicho1->LoadFromFile("bmps/bichotostao.bmp");
                Canvas->StretchDraw(rect1,bicho1);

                kuentabichos++;
                level=kuentabichos/BICHOSNIVEL;
                d1=1;
                TIM_BorraBicho1->Enabled=true;
                }
        else if (xl > x2 && xl < x2+s2 && yl > y2 && yl < y2+s2 && d2==0)
                {
                TIM_2->Enabled=false;MPY_1->Rewind();MPY_1->Play();
                bicho2->LoadFromFile("bmps/bichotostao.bmp");
                Canvas->StretchDraw(rect2,bicho2);

                kuentabichos++;
                level=kuentabichos/BICHOSNIVEL;
                d2=1;
                TIM_BorraBicho2->Enabled=true;
                }
        else if (xl > x3 && xl < x3+s3 && yl > y3 && yl < y3+s3 && d3==0)
                {
                TIM_3->Enabled=false;MPY_1->Rewind();MPY_1->Play();
                bicho3->LoadFromFile("bmps/bichotostao.bmp");
                Canvas->StretchDraw(rect3,bicho3);

                kuentabichos++;
                level=kuentabichos/BICHOSNIVEL;
                d3=1;
                TIM_BorraBicho3->Enabled=true;
                }
        else if (xl > x4 && xl < x4+s4 && yl > y4 && yl < y4+s4 && d4==0)
                {
                TIM_4->Enabled=false;MPY_1->Rewind();MPY_1->Play();
                bicho4->LoadFromFile("bmps/bichotostao.bmp");
                Canvas->StretchDraw(rect4,bicho4);

                kuentabichos++;
                level=kuentabichos/BICHOSNIVEL;
                d4=1;
                TIM_BorraBicho4->Enabled=true;
                }
        else if (xl > xs && xl < xs+ss && yl > ys && yl < ys+ss)
                {
                TIM_S->Enabled=false;
                MPY_1->Rewind();MPY_1->Play();
                kuentabichos++;
                BorraBichoChield();
                ss=0;
                xs=0;
                ys=random(ClientHeight-200)+100;
                rects=Rect(xs,ys,xs+ss,ys+ss);
                if (shield <= MAXSHIELD-20) shield+=20; else shield=MAXSHIELD;
                if (laser <= MAXLASER-30) laser+=30; else laser=MAXLASER;
                Shield();
                Laser();
                TIM_Shield->Interval++;
                }
        return;
        }
int j=TIM_BorraLaser->Tag;

Canvas->Pen->Width=3;

Canvas->MoveTo(xl-j*inc,((ClientHeight/2)+((xl-j*inc)*f1)));
Canvas->Pen->Color=clBlack;
Canvas->LineTo(xl-((j-1)*inc),((ClientHeight/2)+((xl-((j-1)*inc))*f1)));

Canvas->MoveTo(xl+j*inc2,((ClientHeight/2)+((xl-j*inc)*f1)));
Canvas->LineTo(xl+((j-1)*inc2),((ClientHeight/2)+((xl-((j-1)*inc))*f1)));

TIM_BorraLaser->Tag--;
TIM_Pinta->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Skore()
{
LBL_SkoreV->Caption=AnsiString(skore);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TIM_LaserTimer(TObject *Sender)
{
if (laser < MAXLASER-10) laser+=10;
Laser();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NewGame()
{
IMG_Fondo->Visible=false;
LBL_Eficiency->Visible=false;
LBL_Title->Visible=false;
LBL_BodyCount->Visible=false;
playing=true;
level=0;
kuentabichos=0;
kuentatiros=0;
x1=random(Bevel1->Left-200)+100;
x2=random(Bevel1->Left-200)+100;
x3=random(Bevel1->Left-200)+100;
x4=random(Bevel1->Left-200)+100;
xs=0;
y1=random(ClientHeight-200)+100;
y2=random(ClientHeight-200)+100;
y3=random(ClientHeight-200)+100;
y4=random(ClientHeight-200)+100;
ys=random(ClientHeight-200)+100;
s1=2;
s2=2;
s3=2;
s4=2;
ss=0;
d1=d2=d3=d4=0;
rect1=Rect(x1,y1,x1+s1,y1+s1);
rect2=Rect(x2,y2,x2+s2,y2+s2);
rect3=Rect(x3,y3,x3+s3,y3+s3);
rect4=Rect(x4,y4,x4+s4,y4+s4);
rects=Rect(xs,ys,xs+ss,ys+ss);
laser=MAXLASER;
shield=MAXSHIELD;
Laser();
Shield();
shooting=false;
skore=0;
TIM_Stars->Enabled=true;

TIM_1->Interval=INITSPEED;
TIM_1->Enabled=true;
TIM_2->Interval=INITSPEED;
TIM_2->Enabled=true;
TIM_3->Interval=INITSPEED;
TIM_3->Enabled=true;
TIM_4->Interval=INITSPEED;
TIM_4->Enabled=true;
TIM_S->Interval=SHIELDSPEED;
TIM_BorraBicho1->Interval=TIMEKRASH;
TIM_BorraBicho2->Interval=TIMEKRASH;
TIM_BorraBicho3->Interval=TIMEKRASH;
TIM_BorraBicho4->Interval=TIMEKRASH;

TIM_Laser->Enabled=true;
TIM_Shield->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BUT_StartClick(TObject *Sender)
{
if (BUT_Start->Tag==1) return;
BUT_Start->Tag=1;
BUT_Start->Picture->LoadFromFile("bmps/butstart1.bmp");
BUT_Pause->Tag=0;
BUT_Pause->Picture->LoadFromFile("bmps/butpause0.bmp");
NewGame();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EndGame()
{
playing=false;
Screen->Cursor=crCuennos;
TIM_Stars->Enabled=false;
TIM_Laser->Enabled=false;
TIM_1->Enabled=false;
TIM_2->Enabled=false;
TIM_3->Enabled=false;
TIM_4->Enabled=false;
TIM_S->Enabled=false;
TIM_Shield->Enabled=false;
IMG_Fondo->Picture->LoadFromFile("bmps/endgame.bmp");
IMG_Fondo->Visible=true;
BUT_Start->Tag=0;
BUT_Start->Picture->LoadFromFile("bmps/butstart0.bmp");
BUT_Pause->Tag=1;
BUT_Pause->Picture->LoadFromFile("bmps/butpause1.bmp");
LBL_BodyCount->Caption="TE HAS CARGAO "+AnsiString(kuentabichos)+" GORRINOS ESPACIALES";
LBL_BodyCount->Top=ClientHeight/2;
LBL_BodyCount->Left=(Bevel1->Left-LBL_BodyCount->Width)/2;
LBL_BodyCount->Visible=true;
LBL_Eficiency->Caption="CON UNA PUNTERÍA DEL "+AnsiString(100*kuentabichos/kuentatiros)+" %";
LBL_Eficiency->Top=LBL_BodyCount->Top+LBL_BodyCount->Height+20;
LBL_Eficiency->Left=(Bevel1->Left-LBL_Eficiency->Width)/2;
LBL_Eficiency->Visible=true;
LBL_Title->Caption="ERES "+Title();
LBL_Title->Top=LBL_Eficiency->Top+LBL_Eficiency->Height+20;
LBL_Title->Left=(Bevel1->Left-LBL_Title->Width)/2;
LBL_Title->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BUT_ExitClick(TObject *Sender)
{
if (Application->MessageBox("¿Estás segur@ de que quieres salir?","Atención",MB_YESNO)==ID_YES)
Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BUT_ExitMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Screen->Cursor=crCuennos;
BUT_Exit->Picture->LoadFromFile("bmps/butexit2.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BUT_PauseMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Screen->Cursor=crCuennos;
if (BUT_Pause->Tag==0) BUT_Pause->Picture->LoadFromFile("bmps/butpause2.bmp");
if (BUT_Pause->Tag==3) BUT_Pause->Picture->LoadFromFile("bmps/butpause4.bmp");        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BUT_StartMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
Screen->Cursor=crCuennos;
if (BUT_Start->Tag==0) BUT_Start->Picture->LoadFromFile("bmps/butstart2.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Pause()
{
playing=false;
TIM_1->Enabled=false;
TIM_2->Enabled=false;
TIM_3->Enabled=false;
TIM_4->Enabled=false;
TIM_S->Enabled=false;
TIM_Stars->Enabled=false;
TIM_Shield->Enabled=false;
TIM_Laser->Enabled=false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Resume()
{
playing=true;
TIM_1->Enabled=true;
TIM_2->Enabled=true;
TIM_3->Enabled=true;
TIM_4->Enabled=true;
TIM_S->Enabled=true;
TIM_Stars->Enabled=true;
TIM_Shield->Enabled=true;
TIM_Laser->Enabled=true;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::BUT_PauseClick(TObject *Sender)
{
if (BUT_Pause->Tag==1) return;
if (BUT_Pause->Tag==0)
        {
        BUT_Pause->Tag=3;
        BUT_Pause->Picture->LoadFromFile("bmps/butpause3.bmp");
        Pause();
        return;
        }
if (BUT_Pause->Tag==3)
        {
        BUT_Pause->Tag=0;
        BUT_Pause->Picture->LoadFromFile("bmps/butpause0.bmp");
        Resume();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if (Key == VK_ESCAPE) BUT_ExitClick(this);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
if (Key == 's' || Key == 'S') BUT_StartClick(this);
if (Key == 'p' || Key == 'P') BUT_PauseClick(this);
if (Key == 'x' || Key == 'X'
        || Key == 'r' || Key == 'R'
        || Key == 'b' || Key == 'B'
        || Key == 'd' || Key == 'D') Application->MessageBox("la pausa es 'p', empezar 's' y salir 'esc', ¿vale?","¿se pué saber ke koño estás buscando?",MB_ICONQUESTION);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TIM_STimer(TObject *Sender)
{
// Acercamiento del Bicho
BorraBichoChield();
xs+=5;
rects=Rect(xs,ys,xs+ss,ys+ss);
Canvas->StretchDraw(rects,bichoshield);
// Detekzión del Choke
if (xs >= Bevel1->Left-ss)
        {
        TIM_S->Enabled=false;
        MPY_2->Rewind();
        MPY_2->Play();
        BorraBichoChield();
        ss=0;
        xs=0;
        ys=random(ClientHeight-200)+100;
        rects=Rect(xs,ys,xs+ss,ys+ss);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TIM_ShieldTimer(TObject *Sender)
{
ss=24;
TIM_S->Enabled=true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TIM_BorraBicho1Timer(TObject *Sender)
{
TIM_BorraBicho1->Enabled=false;
BorraBicho(rect1, bicho1);
if (d1==2)
        {
        shield-=10;
        if (shield < 0)
                {
                EndGame();
                return;
                }
        Shield();
        }
else
        {
        skore+=(100-s1);
        Skore();
        if (TIM_1->Interval > 1) TIM_1->Interval=INITSPEED-((level/NUMLEVELS)*SPEEDINC);
        }
OtroBicho(x1,y1,s1,rect1,bicho1,d1);
if (playing) TIM_1->Enabled=true;
}
//-------------------------------------------------------------------------------

int __fastcall TForm1::LevelX(int &r, int s)
{
int x=-1;

switch (level%NUMLEVELS)
        {
        case 0:
        x=-1; //kietorl
        break;
        case 1:
        if (s/25==0 || s/25==2) x=0; else x=-2; //alterna iz-de
        break;
        case 2:
        x=-1; //kietorl
        break;
        case 3:
        if (s/25==0 ||s/25==2) x=3; else x=-5; //alterna iz-de +3
        break;
        case 4:
        x=-1; //kietorl
        break;
        case 5:
        if (s==2) r=random(2);
        if (r==0) x=-1;
        else if (s/25==0 ||s/25==2) x=3; else x=-5; //alterna iz-de +3
        break;
        case 6:
        if (s/25==0) x=-1;
        else if (s/25==1) x=3;
        else if (s/25==2) x=-1;
        else if (s/25==3) x=-5;
        break;
        case 7:
        if (s==2 || s%24==0) r=random(4);
        if (r==0) x=-1;
        else if (r==1) x=3;
        else if (r==2) x=-1;
        else if (r==3) x=-5;
        break;
        case 8:
        if (s==2 || s%24==0) r=random(8);
        if (r==0 || r==4) x=-1;
        else if (r==1 || r==2 || r==3) x=3;
        else if (r==5 || r==6 || r==7) x=-5;
        break;
        case 9:
        if (s==2 || s%12==0) r=random(8);
        if (r==0 || r==4) x=-1;
        else if (r==1 || r==2 || r==3) x=3;
        else if (r==5 || r==6 || r==7) x=-5;
        break;
        case 10:
        x=2*((s+10)/5)*(((s+10)/2)%3-1); // ¡¡¡¡¡MIS ALGORITMOS VALEN DINERO!!!!!!!  (bueno, no mucho)
        break;
        }
return x;
}
//-------------------------------------------------------------------------------

int __fastcall TForm1::LevelY(int r, int s)
{
int y=-1;
switch (level%NUMLEVELS)
        {
        case 0:
        y=-1; //kietorl
        break;
        case 1:
        y=-1; //kietorl
        break;
        case 2:
        if (s/25==0 ||s/25==2) y=0; else y=-2; //alterna up-down
        break;
        case 3:
        y=-1; //kietorl
        break;
        case 4:
        if (s/25==0 ||s/25==2) y=3; else y=-5; //alterna up-down +3
        break;
        case 5:
        if (r==1) y=-1;
        else if (s/25==0 || s/25==2) y=3; else y=-5; //alterna up-down +3
        break;
        case 6:
        if (s/25==0) y=-5;
        else if (s/25==1) y=-1;
        else if (s/25==2) y=3;
        else if (s/25==3) y=-1;
        break;
        case 7:
        if (r==0) y=-5;
        else if (r==1) y=-1;
        else if (r==2) y=3;
        else if (r==3) y=-1;
        break;
        case 8:
        if (r==0 || r==1 || r==7) y=-5;
        else if (r==2 || r==6) y=-1;
        else if (r==3 || r==4 || r==5) y=3;
        break;
        case 9:
        if (r==0 || r==1 || r==7) y=-5;
        else if (r==2 || r==6) y=-1;
        else if (r==3 || r==4 || r==5) y=3;
        break;
        case 10:
        y=2*((s+10)/5)*(((s+14)/3)%3-1);
        break;
        }
return y;
}
//-------------------------------------------------------------------------------

int __fastcall TForm1::LevelS()
{
int s=2;
switch (level%NUMLEVELS)
        {
        case 10:
        s=1;
        break;
        }
return s;
}
//-------------------------------------------------------------------------------
void __fastcall TForm1::TIM_BorraBicho2Timer(TObject *Sender)
{
TIM_BorraBicho2->Enabled=false;
BorraBicho(rect2, bicho2);
if (d2==2)
        {
        shield-=10;
        if (shield < 0)
                {
                EndGame();
                return;
                }
        Shield();
        }
else
        {
        skore+=(100-s2);
        Skore();
        if (TIM_2->Interval > 1) TIM_2->Interval=INITSPEED-((level/NUMLEVELS)*SPEEDINC);
        }
OtroBicho(x2,y2,s2,rect2,bicho2,d2);
if (playing) TIM_2->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TIM_BorraBicho3Timer(TObject *Sender)
{
TIM_BorraBicho3->Enabled=false;
BorraBicho(rect3, bicho3);
if (d3==2)
        {
        shield-=10;
        if (shield < 0)
                {
                EndGame();
                return;
                }
        Shield();
        }
else
        {
        skore+=(100-s3);
        Skore();
        if (TIM_3->Interval > 1) TIM_3->Interval=INITSPEED-((level/NUMLEVELS)*SPEEDINC);
        }
OtroBicho(x3,y3,s3,rect3,bicho3,d3);
if (playing) TIM_3->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TIM_BorraBicho4Timer(TObject *Sender)
{
TIM_BorraBicho4->Enabled=false;
BorraBicho(rect4, bicho4);
if (d4==2)
        {
        shield-=10;
        if (shield < 0)
                {
                EndGame();
                return;
                }
        Shield();
        }
else
        {
        skore+=(100-s4);
        Skore();
        if (TIM_4->Interval > 1) TIM_4->Interval=INITSPEED-((level/NUMLEVELS)*SPEEDINC);
        }
OtroBicho(x4,y4,s4,rect4,bicho4,d4);
if (playing) TIM_4->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BorraBichoChield()
{
bichoshield->LoadFromFile("bmps/Blank.bmp");
Canvas->StretchDraw(rects,bichoshield);
bichoshield->LoadFromFile("bmps/bichoshield.bmp");
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::Title()
{
if (skore == 666 || kuentabichos==666) return "EL DIABLO PINCHANDO TAJÁS";
if (skore <= 100) return "LO PUTO PEOR";
if (skore <= 500) return "COMO LO PEOR PERO SIN EL COMO";
if (skore <= 1000) return "MALISMO";
if (skore <= 2000) return "MU MALO";
if (skore <= 3000) return "BASTANTE MALO";
if (skore <= 4000) return "UN POCO MALO";
if (skore <= 5000) return "UN PORRERO DE MIERDA";
if (skore <= 6000) return "UN MIOPE ESPACIAL";
if (skore <= 7000) return "UN JAR JAR BINKS CUALQUIERA";
if (skore <= 8000) return "UN DOMINGUERO DEL ESPACIO";
if (skore <= 9000) return "UN CHEWBACCA DISPARANDO";
if (skore <= 10000) return "UN POCO BUENO, PERO POCO";
if (skore <= 15000) return "UN POCO BUENO";
if (skore <= 20000) return "BASTANTE BUENO";
if (skore <= 25000) return "LA OXTIA DE BUENO";
if (skore <= 30000) return "LA OXTIA EN BICICLETA";
if (skore <= 35000) return "UN ETARRA SIDERAL";
if (skore <= 40000) return "UN SESINO SANGUINARIO";
if (skore <= 45000) return "UN FARLOPERO DE MIERDA";
if (skore <= 50000) return "MASTER GORRINEITOR!!!";
else return "GEORGE BUSH JR";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PintaKosmos()
{
for (int i=0; i < NUMSTARS; i++) Canvas->Pixels[kosmos[i].x+Bevel1->Left/2][kosmos[i].y+ClientHeight/2]=clWhite;
}
//---------------------------------------------------------------------------

void inline __fastcall TForm1::PintaBichos()
{
Canvas->StretchDraw(rect1,bicho1);
Canvas->StretchDraw(rect2,bicho2);
Canvas->StretchDraw(rect3,bicho3);
Canvas->StretchDraw(rect4,bicho4);
Canvas->StretchDraw(rects,bichoshield);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::TIM_StarsTimer(TObject *Sender)
{
int vel=5;
int y0;
for (int i=0; i < NUMSTARS; i++)
        {
        Form1->Canvas->Pixels[Form1->kosmos[i].x+Form1->Bevel1->Left/2][Form1->kosmos[i].y+Form1->ClientHeight/2]=clBlack;
        y0=Form1->kosmos[i].y;
        if (Form1->kosmos[i].y < 0) Form1->kosmos[i].y-=vel; else Form1->kosmos[i].y+=vel;
        Form1->kosmos[i].x=Form1->kosmos[i].x*Form1->kosmos[i].y/y0;
        if (Form1->kosmos[i].y < -Form1->ClientHeight/2 || Form1->kosmos[i].y > Form1->ClientHeight/2)
                {
                Form1->kosmos[i].y=random(150)-75;
                if (Form1->kosmos[i].y==0) Form1->kosmos[i].y=1;
                }
        if (Form1->kosmos[i].x < -Form1->Bevel1->Left/2 || Form1->kosmos[i].x >Form1->Bevel1->Left/2)
                {
                Form1->kosmos[i].x=random(150)-75;
                if (Form1->kosmos[i].x==0) Form1->kosmos[i].x=1;
                }
        Form1->Canvas->Pixels[Form1->kosmos[i].x+Form1->Bevel1->Left/2][Form1->kosmos[i].y+Form1->ClientHeight/2]=clWhite;
        }       
}
//---------------------------------------------------------------------------


