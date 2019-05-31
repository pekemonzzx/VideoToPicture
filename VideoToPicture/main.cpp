#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;

#define NUM_FRAME 300 //�������֡��
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
			//��ԭ����������
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
				cout << "1����" << endl;
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
	cout << "------------- ��Ƶ��ʼת��ͼƬ ... -------����q���˳�---------" << endl;


	CvCapture* capture = cvCaptureFromAVI(filename); //��ʼ��һ����Ƶ�ļ���׽��
	cvQueryFrame(capture); //��ȡ��Ƶ��Ϣ
	int frameH = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	int frameW = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	int fps = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FPS); //֡��
	int TimeMS = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_POS_MSEC); //�Ժ������ĵ�ǰ��λ��
	int numFrames = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	cout << "tvideo height :" << frameH << endl \
		<< "tvideo width :" << frameW << endl \
		<< "tfps : " << fps << endl \
		<< "tframe numbers : " << numFrames << endl;


	//����ͳ�ʼ������
	int i = 0;
	IplImage* img = 0;
	char image_name[13];
	long currentFrame = 0;//����֡��λ��

	cvNamedWindow("picture", CV_WINDOW_AUTOSIZE); //������ʾ��

	string filenameNUM = part(filename);

	while (1) //��ȡ����ʾ
	{

		char key = cvWaitKey(31);
		if (currentFrame == numFrames || key == 'q')
		{
			break;
		}

		img = cvQueryFrame(capture); //��ȡһ֡ͼƬ
		cvShowImage("picture", img); //������ʾ
		if (img == NULL)
		{
			break;
		}

		//if (currentFrame % 30 == 0 && currentFrame == 0) //30֡��һ��
		//{
		//	sprintf(image_name, "%s%d%s", "image", ++i, ".jpg"); //�����ͼƬ��
		//	//sprintf(image_name, "%l%s", filenameNUM, ".jpg"); //�����ͼƬ��
		//	cvSaveImage(image_name, img); //����һ֡ͼƬ
		//}

		if (currentFrame % 30 == 0 && currentFrame >= 0) //30֡��һ��
		{
			sprintf(image_name, "%s%d%s", "image", ++i, ".jpg"); //�����ͼƬ��
			//long score = title(filenameNUM);
			//sprintf(image_name, "%l%s", score, ".jpg"); //�����ͼƬ��
			//cout << "save image" << i << ".jpg--" << endl;
			cvSaveImage(image_name, img); //����һ֡ͼƬ
		}

		currentFrame++;

		TimeMS = (int)cvGetCaptureProperty(capture, CV_CAP_PROP_POS_MSEC); //�Ժ������ĵ�ǰ��λ��
		cout << "-- ʱ���ӡ --��λms--" << "TimeMS :" << TimeMS <<"\t--����--��ǰ֡/��֡��--"<< currentFrame << "/" << numFrames << endl;
	}//while (1) //��ȡ����ʾ


	cvReleaseCapture(&capture);
	cvDestroyWindow("mainWin");
}//void Video_to_image(char* filename)

int main(int argc, char *argv[])
{
	char filename[40] = "VID_20190530_143837.3gp";
	Video_to_image(filename); //��ƵתͼƬ
	return 0;
}//int main(int argc, char *argv[])
