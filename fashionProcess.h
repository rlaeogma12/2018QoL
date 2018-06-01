#pragma once

#ifndef FASHIONPROCESS_H
#define FASHIONPROCESS_H

#include "common_headers.h"

void load_cascade(CascadeClassifier& cascade, string fname);
Mat preprocessing(Mat image);

class FashionHandler {
private:
	HOGDescriptor hog;
	Mat targetImage;
public:
	FashionHandler();
	FashionHandler(Mat defaultImage);
	~FashionHandler();

	void setHumanRect(Mat & img);	//제데로 작동하질 않는다... 
	Rect getHumanUpperBodyRect(Rect face);
	Rect getHumanLowerBodyRect(Rect face, Rect UpperBody);
};

#endif FASHIONPROCESS_H