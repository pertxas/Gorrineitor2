//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USEFORM("Unit1.cpp", Form1);
USERES("target.res");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE , HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "GoRrineiTor 2 ";
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
