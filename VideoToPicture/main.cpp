#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;

#define NUM_FRAME 300 //定义最大帧数
#define _CRT_SECURE_NO_WARNINGS

long stringToFloat(string i)
{
	stringstream sf;
	long score = 0;
	sf << i;
	sf >> score;
	return score;
}

string part(string _str)
{
	long long sumYMD = 0;
	long long sumHMS = 0;
	unsigned int i = 0;

	while (i < _str.length())
	{
		if ('0' <= _str.at(i) && _str.at(i) <= '9')
		{
			//还原连续的数字
			sumYMD = sumYMD * 10 + (_str.at(i) - '0');
		}
		i++;
	}
	return  _str;
}

long title(string filenameNUM)
{
	//long score = stringToFloat(filename);//2018 01 01 12 12 12
	int score1 = 12 % 100000000000;
	int score2 = score1 % 1000000000;
	int score3 = score2 % 10000000;
	if (score1 == 60)
	{
		if (score2 == 60)
		{
			if (score3 == 24)
			{
				cout << "1天了" << endl;
			}
		}
		else
		{
			//filenameNUM = filenameNUM + 100;
		}
	}
	else
	{
		//filenameNUM = filenameNUM + 1;
	}
	return score1;
}

void Video_to_image(char* filename)
{
	cout << "------------- 视频开始转换图片 ... -------按“q”退出---------" << endl;


	CvCapture* capture = cvCaptureFromAVI(filename); //初始化一个视频文件捕捉器
	cvQueryFrame(capture); //获取视频信息
	int frameH = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	int frameW = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	int fps = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FPS); //帧率
	int TimeMS = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_POS_MSEC); //以毫秒计算的当前的位置
	int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	cout << "tvideo height :" << frameH << endl \
		<< "tvideo width :" << frameW << endl \
		<< "tfps : " << fps << endl \
		<< "tframe numbers : " << numFrames << endl;


	//定义和初始化变量
	int i = 0;
	IplImage* img = 0;
	char image_name[13];
	long currentFrame = 0;//定义帧数位置

	cvNamedWindow("picture", CV_WINDOW_AUTOSIZE); //创建显示窗

	string filenameNUM = part(filename);

	while (1) //读取和显示
	{

		char key = cvWaitKey(31);
		if (currentFrame == numFrames || key == 'q')
		{
			break;
		}

		img = cvQueryFrame(capture); //获取一帧图片
		cvShowImage("picture", img); //将其显示
		if (img == NULL)
		{
			break;
		}

		//if (currentFrame % 30 == 0 && currentFrame == 0) //30帧打一次
		//{
		//	sprintf(image_name, "%s%d%s", "image", ++i, ".jpg"); //保存的图片名
		//	//sprintf(image_name, "%l%s", filenameNUM, ".jpg"); //保存的图片名
		//	cvSaveImage(image_name, img); //保存一帧图片
		//}

		if (currentFrame % 30 == 0 && currentFrame >= 0) //30帧打一次
		{
			sprintf(image_name, "%s%d%s", "image", ++i, ".jpg"); //保存的图片名
			//long score = title(filenameNUM);
			//sprintf(image_name, "%l%s", score, ".jpg"); //保存的图片名
			//cout << "save image" << i << ".jpg--" << endl;
			cvSaveImage(image_name, img); //保存一帧图片
		}

		currentFrame++;

		TimeMS = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_POS_MSEC); //以毫秒计算的当前的位置
		cout << "-- 时间打印 --单位ms--" << "TimeMS :" << TimeMS <<"\t--进度--当前帧/总帧数--"<< currentFrame << "/" << numFrames << endl;
	}//while (1) //读取和显示


	cvReleaseCapture(&capture);
	cvDestroyWindow("mainWin");
}//void Video_to_image(char* filename)

int main(int argc, char *argv[])
{
	char filename[40] = "VID_20190530_143837.3gp";
	Video_to_image(filename); //视频转图片
	return 0;
}//int main(int argc, char *argv[])
