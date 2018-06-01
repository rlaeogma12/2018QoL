/*
	fashionProcess.cpp
	패션 감지용 함수 포함
*/
#include "fashionProcess.h"

void load_cascade(CascadeClassifier& cascade, string fname)
{
	String path = "C:/opencv/sources/data/haarcascades/";
	String full_name = path + fname;

	CV_Assert(cascade.load(full_name));
}

Mat preprocessing(Mat image) {
	Mat gray;
	cvtColor(image, gray, CV_BGR2GRAY);
	equalizeHist(gray, gray);

	return gray;
}

FashionHandler::FashionHandler()
{
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
}

FashionHandler::FashionHandler(Mat defaultImage)
{
	targetImage = defaultImage;
}

FashionHandler::~FashionHandler()
{
}

void FashionHandler::setHumanRect(Mat &img)
{
	vector<Rect> found, found_filtered;
	double t = (double)getTickCount();
	// run the detector with default parameters. to get a higher hit-rate
	// (and more false alarms, respectively), decrease the hitThreshold and
	// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
	int can = img.channels();
	hog.detectMultiScale(img, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);
	size_t i, j;
	for (i = 0; i < found.size(); i++) {
		Rect r = found[i];
		for (j = 0; j < found.size(); j++)
			if (j != i && (r & found[j]) == r)
				break;
		if (j == found.size())
			found_filtered.push_back(r);
	}
	for (i = 0; i < found_filtered.size(); i++) {
		Rect r = found_filtered[i];
		// the HOG detector returns slightly larger rectangles than the real objects.
		// so we slightly shrink the rectangles to get a nicer output.
		r.x += cvRound(r.width*0.1);
		r.width = cvRound(r.width*0.8);
		r.y += cvRound(r.height*0.07);
		r.height = cvRound(r.height*0.8);
		rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
	}
}

Rect FashionHandler::getHumanUpperBodyRect(Rect face)
{
	Rect UpperBody;

	UpperBody.width = face.width * 3;
	UpperBody.height = face.height * 2.5;

	UpperBody.x = face.x - face.width;
	UpperBody.y = face.y + face.height * 1.1 + face.height*0.25;

	return UpperBody;
}

Rect FashionHandler::getHumanLowerBodyRect(Rect face, Rect UpperBody)
{
	Rect LowerBody;
	LowerBody.width = face.width * 3;
	LowerBody.height = face.height * 4;

	LowerBody.x = face.x - face.width*0.8;
	LowerBody.y = UpperBody.br().y + face.height*0.25;

	return LowerBody;
}
