#include"aruco2d.hpp"

using namespace cv;
#define devView(i) imshow(#i,i);

int main()
{

	aruco2d aruco(aruco::DICT_6X6_250);
	//aruco.getBoard();
	aruco.outputMarkers("D:\\DICT_4X4_250\\");
	VideoCapture cam(0);
	for (Mat frame = Mat::zeros(Size(640, 480), CV_8UC3),gray; waitKey(1); cam >> frame)
	{
		int n_detected = aruco.detect(frame);
		if (n_detected > 0)
		{
			auto markerConers = aruco.QueryMarkerCorners();
			for (auto i = 0; i < n_detected; i++){
				aruco.DrawDetected(frame,i);
			}
		}
		devView(frame);
	}
}
