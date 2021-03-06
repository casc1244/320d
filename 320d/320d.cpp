﻿#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

	cv::Mat binaryMat;
	cv::Mat labelMat;
	cv::Mat statsMat;
	cv::Mat centrMat;
	cv::Mat resultMat;
	cv::Mat srcMat = imread("D:\\360downloads\\4.png", 0);
	int font_face = cv::FONT_HERSHEY_COMPLEX;
	double font_scale = 1.5;
	int thickness = 1;
	int baseline;

	int elementSize = 5;

	cv::threshold(srcMat, binaryMat, 0, 255, THRESH_OTSU);

	int nComp = cv::connectedComponentsWithStats(binaryMat,
		labelMat,
		statsMat,
		centrMat,
		8,
		CV_32S);

	for (int i = 0; i < nComp; i++)
	{
		cout << "connected Components NO. " << i << endl;
		cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
		cout << "width = " << statsMat.at<int>(i, 2) << endl;
		cout << "height = " << statsMat.at<int>(i, 3) << endl;
		cout << endl;
	}
cout << " 数量是 = " << nComp - 1 << endl;
	resultMat = cv::Mat::zeros(srcMat.size(), CV_8UC3);
	for (int i = 1; i < nComp; i++)
	{
		char num[10];
		sprintf(num, "%d", i);

		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
	
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);

		rectangle(resultMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);

		cv::putText(resultMat, num, Point(bndbox.x, bndbox.y), font_face, 1, cv::Scalar(0, 255, 255), thickness, 8, 0);
	}

	char text[20];
	int length = sprintf(text, "%d", nComp - 1);

	cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
	cv::Point origin;
	origin.x = 0;
	origin.y = text_size.height;
	cv::putText(resultMat, text, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);

	imshow("binaryMat", binaryMat);
	imshow("results", resultMat);
	imshow("frame", srcMat);
	moveWindow("frame", 0, 20);
	moveWindow("binaryMat", srcMat.cols, 20);
	moveWindow("results", srcMat.cols * 2, 20);
	waitKey(0);
	return 0;
}
