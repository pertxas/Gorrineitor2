//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <stdlib.h>
#include <MPlayer.hpp>

//---------------------------------------------------------------------------
#define DES 50
#define DELAY 500000
#define NUMSTARS 1000
#define MAXLASER 100
#define MAXSHIELD 100
#define INITSPEED 101
#define SHIELDSPEED 1
#define DISTBVL 160
#define BICHOSNIVEL 20
#define NUMLEVELS 11
#define TIMEKRASH 300
#define SPEEDINC 20
#define crTarget -5
#define crCuennos -6
//---------------------------------------------------------------------------
struct TStar{
        int x;
        int y;
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *TIM_1;
        TBevel *Bevel1;
        TTimer *TIM_BorraLaser;
        TTimer *TIM_Pinta;
        TTimer *TIM_3;
        TTimer *TIM_2;
        TLabel *LBL_Skore;
        TLabel *LBL_SkoreV;
        TTimer *TIM_4;
        TTimer *TIM_Laser;
        TImage *IMG_Fondo;
        TImage *IMG_Laser;
        TImage *IMG_Shield;
        TImage *BUT_Exit;
        TImage *BUT_Pause;
        TImage *BUT_Start;
        TTimer *TIM_Shield;
        TTimer *TIM_S;
        TTimer *TIM_BorraBicho1;
        TTimer *TIM_BorraBicho3;
        TTimer *TIM_BorraBicho4;
        TTimer *TIM_BorraBicho2;
        TLabel *LBL_BodyCount;
        TLabel *LBL_Eficiency;
        TLabel *LBL_Title;
        TTimer *TIM_Stars;
        TMediaPlayer *MPY_1;
        TMediaPlayer *MPY_2;
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall TIM_1Timer(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall TIM_PintaTimer(TObject *Sender);
        void __fastcall TIM_BorraLaserTimer(TObject *Sender);
        void __fastcall TIM_2Timer(TObject *Sender);
        void __fastcall TIM_3Timer(TObject *Sender);
        void __fastcall TIM_4Timer(TObject *Sender);
        void __fastcall TIM_LaserTimer(TObject *Sender);
        void __fastcall BUT_StartClick(TObject *Sender);
        void __fastcall BUT_ExitClick(TObject *Sender);
        void __fastcall BUT_ExitMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall BUT_PauseMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall BUT_StartMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall BUT_PauseClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall TIM_STimer(TObject *Sender);
        void __fastcall TIM_ShieldTimer(TObject *Sender);
        void __fastcall TIM_BorraBicho1Timer(TObject *Sender);
        void __fastcall TIM_BorraBicho2Timer(TObject *Sender);
        void __fastcall TIM_BorraBicho3Timer(TObject *Sender);
        void __fastcall TIM_BorraBicho4Timer(TObject *Sender);
        void __fastcall TIM_StarsTimer(TObject *Sender);
private:	// User declarations
public:
    int oldx;
    int oldy;
    Graphics::TBitmap* bicho1;
    Graphics::TBitmap* bicho2;
    Graphics::TBitmap* bicho3;
    Graphics::TBitmap* bicho4;
    Graphics::TBitmap* bichoshield;
    TRect rect1;
    TRect rect2;
    TRect rect3;
    TRect rect4;
    int x1;
    int y1;
    int s1;
    int laser;
    int shield;
    TStar kosmos[NUMSTARS];  
    int xl;
    int inc;
    int inc2;
    double f1;
    bool shooting;
    int yl;
    int s2;
    int s3;
    int x2;
    int x3;
    int y2;
    int y3;
    unsigned int skore;
    
    int s4;
    int x4;
    int y4;
    bool playing;
    int xs;
    int ys;
    int ss;
    TRect rects;
    int level;
    int kuentabichos;
    int r1;
    int r2;
    int r3;
    int r4;
    int d1;
    int d2;
    int d3;
    int d4;
    int kuentatiros;
    

            		// User declarations
        __fastcall TForm1(TComponent* Owner);
    void __fastcall BorraBicho(TRect rect, Graphics::TBitmap *bicho);
    void __fastcall OtroBicho(int &x, int &y, int &s, TRect &rect, Graphics::TBitmap *bicho, int &d);
    void __fastcall Krash(TRect rect, Graphics::TBitmap *bicho);
    void __fastcall Laser();
    void __fastcall Shield();
    void __fastcall InitKosmos();
    void __fastcall Skore();
    void __fastcall NewGame();
    void __fastcall EndGame();
    void __fastcall Pause();
    void __fastcall Resume();
    int __fastcall LevelX(int &r, int s);
    int __fastcall LevelY(int r, int s);
    int __fastcall LevelS();
    void __fastcall BorraBichoChield();
    AnsiString __fastcall Title();
    void __fastcall PintaKosmos();
    void inline __fastcall PintaBichos();
    

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
