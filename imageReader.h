#ifndef IMAGEREADER_H
#define IMAGEREADER_H

cv::Mat processImage(std::string stringData);
POINT TemplateMatch(cv::Mat cardToSearch, cv::Mat sourceImage, int method);
cv::Mat GetWindowScreenShot(std::string screenName);

extern RECT windowRect;
extern bool canTurnPage;
#endif