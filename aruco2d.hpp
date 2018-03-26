#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2\aruco.hpp>
#include <opencv2/aruco/charuco.hpp>
using namespace std;
class aruco2d
{
public:
	aruco2d(cv::aruco::PREDEFINED_DICTIONARY_NAME dictName) :sidePixels(200), borderBits(1), parameters(cv::aruco::DetectorParameters::create()) {
		dictionary = getPredefinedDictionary(dictName);
		dictionarySize = dictNameToSize(dictName);
	}
	void setDictionary(cv::Ptr<cv::aruco::Dictionary> &dict){
		dictionary = dict;
	}
	vector<cv::Mat>& outputMarkers() 
	{
		vector<cv::Mat> v;
		for (size_t i = 0; i <  dictionarySize; i++){
			cv::Mat img;
			cv::aruco::drawMarker(dictionary, i, sidePixels, img, borderBits);
			v.push_back(img);
		}
		return v;
	}
	void getBoard() {
		auto board = cv::aruco::CharucoBoard::create(5, 7, 0.04, 0.02, dictionary);
		cv::Mat boardImage;
		board->draw(cv::Size(600, 500), boardImage, 10, 1);
		imwrite("b.BMP",boardImage);
	}
	void outputMarkers(const char * filePath)
	{
		string pathname = filePath;
		for (size_t i = 0; i <  dictionarySize; i++) {
			cv::Mat img;
			cv::aruco::drawMarker(dictionary, i, sidePixels, img, borderBits);
			cv::imshow("markers", img); cv::waitKey(1);
			cv::imwrite(filePath+std::to_string(i)+".bmp", img);
		}
		cv::destroyWindow("markers");
	}
	cv::Mat outputMarker(int id = 0)
	{
		cv::Mat img;
		cv::aruco::drawMarker(dictionary, id, sidePixels, img, borderBits);
		return img;
	}
	void output_setSidePixels(int d = 200){
		sidePixels = d;
	}
	void output_setBorderBits(int bit = 1){
		borderBits = bit ? 1 : 0;
	}
	int dictSize() {
		return dictionarySize;
	}
	int detect(cv::Mat frame) {
		cv::aruco::detectMarkers(frame, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
		return markerIds.size();
	}
	cv::aruco::DetectorParameters * QueryDetectorParameters() {
		return parameters;
	}
	int QueryNumberOfDetected() {
		return markerIds.size();
	}
	vector<vector<cv::Point2f>> & QueryMarkerCorners() {
		return markerCorners;
	}
	vector<int>  & QueryMarkerIds() {
		return markerIds;
	}
	vector<vector<cv::Point2f>> & QueryRejectedCandidates() {
		return rejectedCandidates;
	}
	void DrawDetected(cv::Mat &Canvas, int idx)
	{
		if (markerCorners[idx].empty())	return;
		auto p4 = markerCorners[idx];
		for (size_t i = 0; i < p4.size(); i++)	{
			circle(Canvas, p4[i], 3, Color4[i],-1,CV_AA);
		}
		cv::Point2f center;
		for (size_t i = 0; i < p4.size(); i++) {
			center.x += p4[i].x;
			center.y += p4[i].y;
		}
		center.x /= p4.size();
		center.y /= p4.size();
		auto ph = (p4[0] + p4[1]) / 2;
		line(Canvas, center, ph, cv::Scalar(255, 255, 0),1,CV_AA);
		circle(Canvas, center, sqrt(pow(center.x - ph.x, 2) + pow(center.y - ph.y, 2)), cv::Scalar(255, 255, 255), 1, CV_AA);
		cv::String str = "ID = ";
		putText(Canvas, str + to_string(markerIds[idx]), (center + ph) / 2, CV_FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 0),3,CV_AA);
	}
protected:

	cv::Scalar Color4[4] = {
		cv::Scalar(0, 0, 255),
		cv::Scalar(0, 255, 0),
		cv::Scalar(0, 255, 255),
		cv::Scalar(255, 0, 255)
	};
	int dictNameToSize(cv::aruco::PREDEFINED_DICTIONARY_NAME dictName) {
		switch (dictName)
		{
		case cv::aruco::DICT_4X4_50:
			return 50;
		case cv::aruco::DICT_4X4_100:
			return 100;
		case cv::aruco::DICT_4X4_250:
			return 250;
		case cv::aruco::DICT_4X4_1000:
			return 1000;
		case cv::aruco::DICT_5X5_50:
			return 50;
		case cv::aruco::DICT_5X5_100:
			return 100;
		case cv::aruco::DICT_5X5_250:
			return 250;
		case cv::aruco::DICT_5X5_1000:
			return 1000;
		case cv::aruco::DICT_6X6_50:
			return 50;
		case cv::aruco::DICT_6X6_100:
			return 100;
		case cv::aruco::DICT_6X6_250:
			return 250;
		case cv::aruco::DICT_6X6_1000:
			return 1000;
		case cv::aruco::DICT_7X7_50:
			return 50;
		case cv::aruco::DICT_7X7_100:
			return 100;
		case cv::aruco::DICT_7X7_250:
			return 250;
		case cv::aruco::DICT_7X7_1000:
			return 1000;
		default:
			return 0;
		}
	}
	vector<int> markerIds;
	vector<vector<cv::Point2f>> markerCorners, rejectedCandidates;
	cv::Ptr<cv::aruco::Dictionary> dictionary;
	cv::Ptr<cv::aruco::DetectorParameters> parameters;
	int dictionarySize = 0;
	int sidePixels = 200, borderBits = 1;
};