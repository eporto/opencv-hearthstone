#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/types.hpp"
#include <windows.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include "httpImageReader.h"
#include "collectionManager.h"
#include "imageReader.h"


#define DEBUG_MODE 1 //debug mode
/*
COMPILE STEPS:
    g++ -c -I"D:\OpenCV-build\install\include" -L"D:\OpenCV-build\install\x86\mingw\lib" a.cpp
    g++ -I"D:\OpenCV-build\install\include" -L"D:\OpenCV-build\install\x86\mingw\lib" a.o httpImageReader.o collectionManager.o imageReader.o -llibopencv_core320 -llibopencv_imgcodecs320 -lgdi32 -llibopencv_highgui320 -lopencv_imgproc320 -lws2_32

 httpImageReader.cpp
    g++  -c httpImageReader.cpp 

collectionManager.cpp
    g++  -c collectionManager.cpp

imageReader.cpp
    g++ -c -I"D:\OpenCV-build\install\include" -L"D:\OpenCV-build\install\x86\mingw\lib" imageReader.cpp
*/

/*
    highgui:imread(), namedWindow(), imshow() and waitKey()
*/


void debug(std::string msg);
void LeftClick();
using namespace cv;
 int main() {
    //cv::cvtColor(colorMat, greyMat, cv::COLOR_BGR2GRAY);
    int page = 0;
    int cardCount = 1;
    POINT imgpoint;
    cm::fillSearchCollection();
    int szCol = cm::collection.size();
    cv::Mat imgbg;
    cv::Mat img_nextpage = cv::imread("nextpage.jpg");

    system("cls");
    std::cout << "How to use:" << std::endl;
    std::cout << "1 - Open Hearthstone" << std::endl;
    std::cout << "2 - Go to My Collection and enter Crafting Mode" << std::endl;
    std::cout << "3 - Press Enter" << std::endl;
    char opt;
    while ((opt = getch()) != VK_RETURN) {
        if(opt == VK_ESCAPE)
            exit(0);
        std::cout << "Invalid\n";
    }
    

    for(int i = 0; i < szCol; i++) {
        if(cardCount == 1) {
            imgbg = GetWindowScreenShot("Hearthstone");
            page++;
        }
        cv::Mat image =  processImage(GetImage(cm::collection[i].id));
        if(!image.empty()) {
            //Template Methods: 0: SQDIFF | 1: SQDIFF NORMED | 2: TM CCORR | 3: TM CCORR NORMED | 4: TM COEFF | 5: TM COEFF NORMED";  
            imgpoint = TemplateMatch(image,imgbg,5);
            if(imgpoint.x != 0 && imgpoint.y != 0) {
                //cv::waitKey(1000);
                std::cout << cm::collection[i].name << std::endl;
            }
        }
        cardCount++;
        if(cardCount > 8) {
            cardCount = 1;
            imgpoint = TemplateMatch(img_nextpage,imgbg,5);
            SetCursorPos(imgpoint.x, imgpoint.y);
            Sleep(100);
            LeftClick();
        }
        Sleep(1000);
    }
    system("pause");

    return 0;
}

void LeftClick()
{  
	INPUT    Input={0};													// Create our input.

	Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
	SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.

	ZeroMemory(&Input,sizeof(INPUT));									// Fills a block of memory with zeros.
	Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
	SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.
}

/*
UINT WINAPI SendInput(
  _In_ UINT    nInputs,     //The number of structures in the pInputs array.
  _In_ LPINPUT pInputs,     //An array of INPUT structures. Each structure represents an event to be inserted into the keyboard or mouse input stream.
  _In_ int     cbSize       //The size, in bytes, of an INPUT structure. If cbSize is not the size of an INPUT structure, the function fails.
);

typedef struct tagMOUSEINPUT {
  LONG      dx;
  LONG      dy;
  DWORD     mouseData;
  DWORD     dwFlags;    //MOUSEEVENTF_ABSOLUTE, MOUSEEVENTF_MOVE (Move a partir da posição atual), MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP
  DWORD     time;
  ULONG_PTR dwExtraInfo;
} MOUSEINPUT, *PMOUSEINPU

SetCursorPos(x,y);
*/


//POINT mouse - getmouse...
//mouse.x,mouse.y
/*POINT GetMousePosition()
{
	static POINT m;
	POINT mouse;
	GetCursorPos(&mouse);
	m.x = mouse.x;
	m.y = mouse.y;
	return m;
}*/
//GetAsyncKeyState(VK_ESCAPE) = retorna 1 se VK_ESCAPE estiver "down" qdo a função foi chamada
/*BOOL WINAPI ShowWindow(
  _In_ HWND hWnd,
  _In_ int  nCmdShow    //SW_HIDE = 0, SW_MAXIMIZE = 3, SW_MINIMIZE = 6, SW_SHOWNORMAL = 1, SW_SHOW = 5
);
*/
/*
void SetMousePosition(POINT& mp)
{
	long fScreenWidth	    = GetSystemMetrics( SM_CXSCREEN ) - 1; 
	long fScreenHeight	    = GetSystemMetrics( SM_CYSCREEN ) - 1; 

	// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx		        = mp.x * ( 65535.0f / fScreenWidth  );
	float fy		        = mp.y * ( 65535.0f / fScreenHeight );		  
				
	INPUT Input             = { 0 };			
	Input.type		        = INPUT_MOUSE;

	Input.mi.dwFlags	    = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
				
	Input.mi.dx		        = (long)fx;
	Input.mi.dy		        = (long)fy;

	SendInput(1,&Input,sizeof(INPUT));
}*/

