/*
	main.cpp
	�ȵ���̵� �̽� �� ���� �׽�Ʈ�� �ڵ�
*/

#include "main.h"

typedef struct values {
	Vec3b rgb;
	int cnt;
	Point pt;
} value;


Vec3b detectcolor(Mat &image, int row, int col) {
	int blue, green, red;
	blue = 0; green = 0; red = 0;
	int cnt = 0;
	for (int j = row; j < row + 5; j++) {
		for (int i = col; i < col + 5; i++) {
			if (image.at<Vec3b>(j, i)[0] == 255 && image.at<Vec3b>(j, i)[1] == 255 && image.at<Vec3b>(j, i)[2] == 255)
				continue;

			blue += image.at<Vec3b>(j, i)[0]; // blue
			green += image.at<Vec3b>(j, i)[1]; // green
			red += image.at<Vec3b>(j, i)[2]; // red
			cnt++;
		}
	}
	if (cnt == 0)
		return 0;

	blue /= cnt; green /= cnt; red /= cnt;

	return Vec3b(blue, green, red);
}

void putValue(vector<value> &arr, Vec3b color, Point pt) {
	int count = 0;
	for (size_t i = 0; i < arr.size(); ++i) {
		count = 0;
		int count2 = 0;
		for (int j = 0; j < 3; j++) {
			if (abs(arr[i].rgb[j] - color[j]) < 40) { // �� �ø�40���� ���������� ����
				count2++;
			}
		}
		if (count2 == 3) {
			count++;
			arr[i].cnt++; // �ߺ�üũ���� ����
			break;
		}
	}
	value v1;
	if (count == 0) {
		v1.rgb = color;
		v1.cnt = 0;
		v1.pt = pt;
		arr.push_back(v1);
	}
}

void TonOnTon(Mat &m, vector<value> &arr) { //�����
	
	Mat Up(1000, 1000, CV_8UC3, Scalar(255, 255, 255));

	float b, g, r, h, s, v;
	b = 0; g = 0; r = 0, h = 0, s=0, v=0;	
	
	b = arr[0].rgb[0];  //�ϴ� ������� arr(Up_colorArray)�� ù��° ����ִ� rgb������ ��
	g = arr[0].rgb[1];
	r = arr[0].rgb[2];

	//RGB -> HSV�� ��ȯ�ϴ� ����(å ��������)
	float tmp1 = ((r - g) + (r - b)) * 0.5f;
	float tmp2 = sqrt((r - g) * (r - b) + (g - b)*(g - b));
	float angle = acos(tmp1 / tmp2) * (180.f / CV_PI);

	h = ((b <= g) ? angle : 360 - angle); //����
	s = (1 - 3 * min(r, min(g, b)) / (r + g + b)); //ä��
	v = ((r + g + b) / 3.0f);  //��

	
	float C, X, M;
	int red, green, blue, l=0, k=0;

	//for (s = 0; s <= 1; s += 0.05) {
		for (v = 0; v <= 1; v += 0.05) { //�����̶� ä���� �����ϰ� ���� �ٸ�����...
			C = s * v;
			X = C * (1 - abs(int(h / 60) % 2 - 1)); 
			M = v - C;		//�� ����(HSV->RGB)�� https://www.rapidtables.com/convert/color/hsv-to-rgb.html �� �־���

			if (0 <= h && h < 60) {
				red = (C + M) * 255;  
				green = (X + M) * 255;
				blue = M * 255;
			}
			else if (60 <= h && h < 120) {
				red = (X + M) * 255;
				green = (C + M) * 255;
				blue = (0+M) * 255;
			}
			else if (120 <= h && h < 180) {
				red = (0 + M) * 255;
				green = (C + M) * 255;
				blue = (X + M) * 255;
			}
			else if (180 <= h && h < 240) {
				red = (0 + M) * 255;
				green = (X + M) * 255;
				blue = (C + M) * 255;
			}
			else if (240 <= h && h < 300) {
				red = (X + M) * 255;
				green = (0 + M) * 255;
				blue = (C + M) * 255;
			}
			else {
				red = (C + M) * 255;
				green = (0 + M) * 255;
				blue = (X + M) * 255;
			}
			circle(Up, Point(10, 10 + l), 10, Scalar(blue, green, red), -1);
			l += 10;
		}
		//k += 10;
		l = 0;
	//}
		v = ((r + g + b) / 3.0f)/255;  //0~1�� ���ֱ����� 255�� ����

		for (s = 0; s <= 1; s += 0.05) { //�����̶� ���� �����ϰ� ä���� �ٸ�����...
			C = s * v;
			X = C * (1 - abs(int(h / 60) % 2 - 1));
			M = v - C;  

			if (0 <= h && h < 60) {
				red = (C + M) * 255;
				green = (X + M) * 255;
				blue = M * 255;
			}
			else if (60 <= h && h < 120) {
				red = (X + M) * 255;
				green = (C + M) * 255;
				blue = (0 + M) * 255;
			}
			else if (120 <= h && h < 180) {
				red = (0 + M) * 255;
				green = (C + M) * 255;
				blue = (X + M) * 255;
			}
			else if (180 <= h && h < 240) {
				red = (0 + M) * 255;
				green = (X + M) * 255;
				blue = (C + M) * 255;
			}
			else if (240 <= h && h < 300) {
				red = (X + M) * 255;
				green = (0 + M) * 255;
				blue = (C + M) * 255;
			}
			else {
				red = (C + M) * 255;
				green = (0 + M) * 255;
				blue = (X + M) * 255;
			}
			circle(Up, Point(40, 10 + l), 10, Scalar(blue, green, red), -1);
			l += 10;
		}
		//k += 10;
		
	
	imshow("TonOnTon", Up);
}


int main() {

	CascadeClassifier face_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");

	Mat image = imread("input7.jpg", IMREAD_COLOR);
	CV_Assert(image.data);
	cout << image.size();
	resize(image, image, Size(), double(500)/image.cols, double(600)/image.rows);

	FashionHandler *fashionHandler = new FashionHandler(image);
	
	Mat gray = preprocessing(image);
	Mat dst1, dst2, dst3, th_img;
	Sobel(gray, dst1, CV_32F, 1, 0, 3);
	Sobel(gray, dst2, CV_32F, 0, 1, 3);
	magnitude(dst1, dst2, dst3);
	convertScaleAbs(dst3, dst3);

	
	Mat dst5;
	Canny(gray, dst5, 60, 170);  // ?? �� �ָ� ���� ������ �� ������...???
	threshold(dst3, th_img, 120, 255, THRESH_BINARY);
	
	vector<Rect> face;
	face_cascade.detectMultiScale(gray, face, 1.1, 2, 0, Size(10, 10)); //�� Ž��

	Rect Face = face[0];
	
	rectangle(image, Face.tl(), Face.br(), cv::Scalar(0, 0, 255), 2); //Ž���� �󱼿� �簢�� �׸���
	
	//face[0]�� Face Size�� �ν�.
	//�ٺ�ġ ���Կ� ������, ��ü�� 8����̴�..
	//�ƴ� ���� ���ϰ� ������� �ʴ´�...
	Rect UpperBody, LowerBody;
	
	UpperBody = fashionHandler->getHumanUpperBodyRect(Face);
	LowerBody = fashionHandler->getHumanLowerBodyRect(Face, UpperBody);

	//rectangle(image, UpperBody, Scalar(0, 255, 0), 2);
	//rectangle(image, LowerBody, Scalar(255, 0, 0), 2);

	
	Rect temp1, temp11;
	temp1.x = UpperBody.x + 5;
	temp1.y = UpperBody.y;
	temp1.width = UpperBody.width - 15;
	temp1.height = UpperBody.height - 5;

	/*temp11.x = LowerBody.x + 5;
	temp11.y = LowerBody.y;
	temp11.width = LowerBody.width - 15;
	temp11.height = LowerBody.height - 5;*/

	Mat B(image, Rect(0, 0, temp1.x, image.rows));
	Mat C(image, Rect(temp1.x+temp1.width, 0, image.cols-(temp1.x + temp1.width), image.rows));
	Mat D(image, Rect(0, 0, image.cols, temp1.y));

	Rect temp2, temp22;
	temp2.x = temp1.x + 20;
	temp2.y = temp1.y + 20;
	temp2.width = temp1.width-40;
	temp2.height = temp1.height-40;

	temp22.x = LowerBody.x + 20;
	temp22.y = LowerBody.y + 30;
	temp22.width = LowerBody.width - 40;
	temp22.height = LowerBody.height - 50;

	//rectangle(image, temp1, Scalar(0), 1);
	//imshow("B", B);
	//imshow("C", C);
	//imshow("d", D);

	blur(B, B, Size(7, 7));
	blur(C, C, Size(7, 7));
	blur(D, D, Size(7, 7));

	Mat bgModel, fgModel;
	Mat result, result2;

	grabCut(image,
		result,
		UpperBody,
		bgModel, fgModel,
		2,
		GC_INIT_WITH_RECT);

	compare(result, GC_PR_FGD, result, CMP_EQ);

	Mat cloth_foreground(image.size(), CV_8UC3,
		Scalar(255, 255, 255));

	image.copyTo(cloth_foreground, result);
	
	grabCut(image,
		result2,
		LowerBody,
		bgModel, fgModel,
		5,GC_INIT_WITH_RECT);

	compare(result2, GC_PR_FGD, result2, CMP_EQ);

	Mat pants_foreground(image.size(), CV_8UC3,
		Scalar(255, 255, 255));

	image.copyTo(pants_foreground, result2);

	//rectangle(cloth_foreground, temp2, Scalar(0, 255, 0), 2);

	imshow("cloth_foreground object", cloth_foreground);
	imshow("pants_foreground object", pants_foreground);

	Mat M2(cloth_foreground, temp2);
	Mat M3(pants_foreground, temp22);

	vector<value> Up_colorArray, Lo_colorArray;
	double totalcnt = 0;
	
	for (int j = 5; j < M2.rows-5; j += 5) {
		for (int i = 5; i <M2.cols-5; i += 5) {
			putValue(Up_colorArray, detectcolor(M2, j, i), Point(i,j));
			totalcnt++;
		}
	} //����� �� ����

	TonOnTon(M2, Up_colorArray);

	int k = 0; int l = 0;
	Mat Up_colorchip(300, 300, CV_8UC3, Scalar(255, 255, 255));

	//����� �� ���
	for (size_t i = 0; i < Up_colorArray.size(); i++) {
		int percent = (Up_colorArray[i].cnt / totalcnt) * 100;
		string str = to_string(percent) + "%";

		if (percent == 0)
			continue;

		circle(Up_colorchip, Point(10, 10 + l), 10, Up_colorArray[i].rgb, -1);
		putText(Up_colorchip, str, Point(27, 15 + l), 1, 1, Scalar(0, 0, 0));
		l += 30;
	}

	totalcnt = 0, l = 0;
	Mat Lo_colorchip(300, 300, CV_8UC3, Scalar(255, 255, 255));

	for (int j = 5; j < M3.rows - 5; j += 5) {
		for (int i = 5; i <M3.cols - 5; i += 5) {
			putValue(Lo_colorArray, detectcolor(M3, j, i), Point(i,j));
			totalcnt++;
		}
	}

	for (size_t i = 0; i < Lo_colorArray.size(); i++) {
		int percent = (Lo_colorArray[i].cnt / totalcnt) * 100;
		string str = to_string(percent) + "%";

		if (percent == 0)
			continue;

		circle(Lo_colorchip, Point(10, 10 + l), 10, Lo_colorArray[i].rgb, -1);
		putText(Lo_colorchip, str, Point(27, 15 + l), 1, 1, Scalar(0, 0, 0));
		l += 30;
	}

	imshow("M2", M2);
	imshow("M3", M3);

	/*
	int Blue, Green, Red, flag = 1;

	for (int i = 100; i < 200; i++) {
		for (int j = 100; j < 200; j++) {
			Blue = image.at<Vec3b>(i, j)[0];
			Green = image.at<Vec3b>(i, j)[1];
			Red = image.at<Vec3b>(i, j)[2];
			
			for (int k = 0; k < v1.size(); k++) {
				if (std::abs(v1[k][0] - Blue) < 50 && std::abs(v1[k][1] - Green) < 50 && std::abs(v1[k][2] - Red) < 50)
					break;
				if (k == v1.size() - 1) flag = 1;
			}
			
			if (flag == 1) {
				v1.push_back(Vec3b(Blue, Green, Red));
				flag = 0;
			}
		}
	}
	
	cout << "[v1]" << (Mat)v1 << endl;*/


	/*
	Point face_center = face[0].tl() + Point((face[0].size()) / 2); //�� �簢���� �߾���
	float face_len = face[0].height;

	circle(image, face_center, 1, Scalar(255, 0, 0), 1);

	Point face_lower_center(face[0].tl().x + (face[0].br().x - face[0].tl().x) / 2, face[0].br().y); //�� �߾����� ���� �Ʒ� ��ġ


	int nBlue = image.at<Vec3b>(face_lower_center.y, face_lower_center.x)[0];
	int nGreen = image.at<Vec3b>(face_lower_center.y, face_lower_center.x)[1];
	int nRed = image.at<Vec3b>(face_lower_center.y, face_lower_center.x)[2];

	Point upper_cloth;
	int B, G, R;
	for (int i = face_lower_center.y; i < image.rows; i++) {
		B = image.at<Vec3b>(i, face_lower_center.x)[0];
		G = image.at<Vec3b>(i, face_lower_center.x)[1];
		R = image.at<Vec3b>(i, face_lower_center.x)[2];

		if (std::abs(nBlue - B) < 70 && std::abs(nGreen - G) < 70 && std::abs(nRed - R) < 70)  //������ Ȯ ���Ҷ� ���� ������ ������ ��...���� �ٽ� ����� ���� ���� ��(�Լ��� �����)
			continue;

		upper_cloth = Point(face_lower_center.x, i + 10); //���� �� ��(=���� ������)�� ã�� ��� �������� ���� ���� ���� �� ������ ������ 
		break;
	} // ?? �̷��� ������ Ȯ �ٲ�� �ɷ� �ؾ��ϳ�...?? -> �� �ָ� ����... 

	Point left_shoulder, right_shoulder;

	for (int i = upper_cloth.x; i > 0; i--) {
		if (dst5.at<uchar>(upper_cloth.y, i) == 0)
			continue;

		left_shoulder = Point(i, upper_cloth.y);
		break;
	} //���� ��������� ���鼭 ó������ ������ ��� �ȼ� ��ġ ����

	for (int i = upper_cloth.x; i < image.cols; i++) {
		if (dst5.at<uchar>(upper_cloth.y, i) == 0)
			continue;

		right_shoulder = Point(i, upper_cloth.y);
		break;
	} //������ ��������� ���鼭 ó������ ������ ��� �ȼ� ��ġ ����

	nBlue = image.at<Vec3b>(upper_cloth.y, upper_cloth.x)[0];
	nGreen = image.at<Vec3b>(upper_cloth.y, upper_cloth.x)[1];
	nRed = image.at<Vec3b>(upper_cloth.y, upper_cloth.x)[2];

	Point lower_cloth;
	for (int i = upper_cloth.y; i < image.rows; i++) {
		B = image.at<Vec3b>(i, upper_cloth.x)[0];
		G = image.at<Vec3b>(i, upper_cloth.x)[1];
		R = image.at<Vec3b>(i, upper_cloth.x)[2];

		if (std::abs(nBlue - B) < 70 && std::abs(nGreen - G) < 70 && std::abs(nRed - R) < 70)  //������ Ȯ �ٲ� ���ǰ� ���۵ȴٰ� �ôµ�...���� �ٽ� ����� ���� ���� ��
			continue;

		lower_cloth = Point(upper_cloth.x, i);
		break;
	}

	Rect cloth_rect(left_shoulder.x - 10, left_shoulder.y, right_shoulder.x - left_shoulder.x + 20, lower_cloth.y - left_shoulder.y + 7);

	Mat bgModel, fgModel;
	Mat result;

	grabCut(image,
		result,
		cloth_rect,
		bgModel, fgModel,
		5,
		GC_INIT_WITH_RECT);

	compare(result, GC_PR_FGD, result, CMP_EQ);

	Mat cloth_foreground(image.size(), CV_8UC3,
		Scalar(255, 255, 255));

	image.copyTo(cloth_foreground, result);


	Point upper_pants(lower_cloth.x, lower_cloth.y + 10); //�ʰ� ���� ��迡�� ��¦ ������ �������� ��������(������������ ���ã���� ������!) 

	Point left_side, right_side;

	for (int i = upper_pants.x; i > 0; i--) {
		if (dst5.at<uchar>(upper_pants.y, i) == 0)
			continue;

		left_side = Point(i, upper_pants.y);
		break;
	} //���� �㸮������ ���鼭 ó������ ������ ��� �ȼ� ��ġ ����

	for (int i = upper_pants.x; i < image.cols; i++) {
		if (dst5.at<uchar>(upper_pants.y, i) == 0)
			continue;

		right_side = Point(i, upper_pants.y);
		break;
	} //������ �㸮������ ���鼭 ó������ ������ ��� �ȼ� ��ġ ����

	nBlue = image.at<Vec3b>(upper_pants.y, upper_pants.x)[0];
	nGreen = image.at<Vec3b>(upper_pants.y, upper_pants.x)[1];
	nRed = image.at<Vec3b>(upper_pants.y, upper_pants.x)[2];

	Point lower_pants;
	for (int i = upper_pants.y; i < image.rows; i++) {
		B = image.at<Vec3b>(i, upper_pants.x)[0];
		G = image.at<Vec3b>(i, upper_pants.x)[1];
		R = image.at<Vec3b>(i, upper_pants.x)[2];

		if (std::abs(nBlue - B) < 70 && std::abs(nGreen - G) < 70 && std::abs(nRed - R) < 70)  //������ Ȯ �ٲ� ���ǰ� ���۵ȴٰ� �ôµ�...���� �ٽ� ����� ���� ���� ��
			continue;

		lower_pants = Point(upper_pants.x, i);
		break;
	}

	Rect pants_rect(left_side.x - 10, left_side.y, right_side.x - left_side.x + 20, lower_pants.y - left_side.y + 5);

	Mat result2;

	grabCut(image,
		result2,
		pants_rect,
		bgModel, fgModel,
		5,
		GC_INIT_WITH_RECT);

	compare(result2, GC_PR_FGD, result2, CMP_EQ);

	Mat pants_foreground(image.size(), CV_8UC3,
		Scalar(255, 255, 255));

	image.copyTo(pants_foreground, result2);

	circle(image, upper_cloth, 1, Scalar(0, 0, 255), 1);
	circle(dst5, face_lower_center, 2, Scalar(255), 2);
	circle(dst5, upper_cloth, 2, Scalar(255), 2);
	circle(dst5, left_shoulder, 2, Scalar(255), 2);
	circle(dst5, right_shoulder, 2, Scalar(255), 2);
	circle(dst5, lower_cloth, 2, Scalar(255), 2);
	rectangle(dst5, cloth_rect, Scalar(255), 2);

	circle(dst5, upper_pants, 2, Scalar(255), 2);
	circle(dst5, left_side, 2, Scalar(255), 2);
	circle(dst5, right_side, 2, Scalar(255), 2);
	circle(dst5, lower_pants, 2, Scalar(255), 2);
	rectangle(dst5, pants_rect, Scalar(255), 2);

	*/
	
	imshow("�� image", image);
	imshow("���� ����� ��", Up_colorchip);
	imshow("���� ����� ��", Lo_colorchip);

	/*
	imshow("dst5=canny", dst5);

	imshow("cloth_foreground object", cloth_foreground);
	imshow("pants_foreground object", pants_foreground);
	*/
	waitKey();

	return 0;
}