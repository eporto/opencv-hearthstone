#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/types.hpp"
#include <windows.h>
#include <windowsx.h> //isMinimized
#include <iostream>
#include <vector>
#include "imageReader.h"


RECT windowRect;
//Get image from string and transform it
cv::Mat processImage(std::string stringData) {
    std::vector<byte> vectordata(stringData.begin(),stringData.end());

    cv::Mat data_mat(vectordata,true);
    cv::Mat image(cv::imdecode(data_mat,1)); //put 0 if you want greyscale*/

   //Card image = W 307, H 465
   cv::Rect areaRect = cv::Rect(30,70,250,370);
   cv::Mat imageROI = image(areaRect);

   cv::Size size(186,273);
   cv::resize(imageROI,imageROI,size);
  
   return imageROI;
}

POINT TemplateMatch(cv::Mat cardToSearch, cv::Mat sourceImage, int method)
{
    //Template Methods: 0: SQDIFF | 1: SQDIFF NORMED | 2: TM CCORR | 3: TM CCORR NORMED | 4: TM COEFF | 5: TM COEFF NORMED";
    const char* image_window = "Source Image";
    POINT imagePoint = {0};
    /// Source image to display
    //cv::Mat templ = cardToSearch.clone();
    cv::Mat templ; //= cardToSearch.clone();
    cv::Mat img = sourceImage.clone();
    cv::Mat img_display;
    cv::Mat result;
    int match_method = 5; 
    img.copyTo( img_display );
    
    //CV_BGRA2BGR : 4 -> 3
    //CV_BGR2BGRA: 3 -> 4
    cv::cvtColor( cardToSearch,templ, CV_BGR2BGRA );
    /// Create the result matrix
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
   
    result.create( result_rows, result_cols, CV_8UC4 );
     
    /*std::cout << "Search:" << templ.type() << std::endl;
    std::cout << "source:" << img.type() << std::endl;
    std::cout << "Result:" << result.type() << std::endl;*/
    //Remover normalize (Se não da sempre perfect match)
    cv::matchTemplate( img, templ, result, match_method );
    
    /// Localizing the best match with minMaxLoc
    double minVal; 
    double maxVal; 
    cv::Point minLoc; 
    cv::Point maxLoc;
    cv::Point matchLoc;

    cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );

    /*  For SQDIFF and SQDIFF_NORMED -> matchLoc = minLoc 
        For the rest -> matchLoc = maxLoc
    */
    matchLoc = maxLoc;

    //std::cout << "matchLoc: " << matchLoc << std::endl;
    //std::cout << "minVal: " << minVal << std::endl;
    //std::cout << "maxVal: " << maxVal << std::endl;
    if (maxVal < 0.45) {//1.0 perfect match
        /*std::cout << "Not Found: " << maxVal << std::endl;
        cv::rectangle( img_display, matchLoc, cv::Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), cv::Scalar(0,0,255), 2, 8, 0 );
        cv::imshow( image_window, img_display );*/
    }
    else {
        /// Show me what you got
        /*std::cout << "Found: " << maxVal << std::endl;
        cv::rectangle( img_display, matchLoc, cv::Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), cv::Scalar(0,255,0), 2, 8, 0 );
        cv::imshow( image_window, img_display );*/
        imagePoint.x = windowRect.left + matchLoc.x + templ.cols/2;
        imagePoint.y = windowRect.top + matchLoc.y + templ.rows;
    }
    return imagePoint;
}


cv::Mat GetWindowScreenShot(std::string screenName) {
    BITMAPINFOHEADER bInfo;
    cv::Mat ssMat;
    int ssHeight, ssWidth;
    HWND hwnd = FindWindow(NULL, screenName.c_str());    
    if (hwnd == NULL)
    {
        std::cout <<"Error opening " << screenName << "(code: " << GetLastError() << ")" << std::endl;
        return ssMat;
    }

    while(IsMinimized(hwnd)) {
        std::cout << "Please maximize " << screenName << " window." << std::endl;

        system("pause");
    }

    //GetwindowRect for window borders
    GetClientRect(hwnd, &windowRect); 
    ssHeight = windowRect.bottom - windowRect.top;
    ssWidth = windowRect.right - windowRect.left;
    
    ssMat.create(ssHeight, ssWidth, CV_8UC4);

    /* Creating ScreenShot */

    //Get Device Context for entire screen
    HDC hdcScreen = GetDC(hwnd);
    //Create Comptabile Memory DC
    HDC hdc = CreateCompatibleDC(hdcScreen);
    SetStretchBltMode(hdc,COLORONCOLOR);  
    //Create Compatible Bitmap for the specified DC (DC,width,height)
    HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen, ssWidth, ssHeight);

    bInfo.biSize = sizeof(BITMAPINFOHEADER);
    bInfo.biWidth = ssWidth;
    bInfo.biHeight = -ssHeight;
    bInfo.biPlanes = 1;
    bInfo.biBitCount = 32;
    bInfo.biCompression = BI_RGB;
    bInfo.biSizeImage = 0;
    bInfo.biXPelsPerMeter = 0;
    bInfo.biYPelsPerMeter = 0;
    bInfo.biClrUsed = 0;
    bInfo.biClrImportant = 0;

    //Select bmp object into the compatible DC
    SelectObject(hdc, hbmp);

    //Copy from DC Screen to Compatible DC
    //BitBlt(hdc, 0, 0, ssWidth, ssHeight, hdcScreen, 0, 0, SRCCOPY);
     StretchBlt(hdc, 0, 0, ssWidth, ssHeight, hdcScreen, 0, 0,ssWidth, ssHeight, SRCCOPY);

    GetDIBits(hdc, hbmp, 0, ssHeight, ssMat.data, (BITMAPINFO *)&bInfo, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow
    
    //release
    DeleteDC(hdc);
    DeleteObject(hbmp);
    ReleaseDC(hwnd, hdcScreen);

    return ssMat;
}