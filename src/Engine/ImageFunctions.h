#pragma once

namespace engine {

	namespace imageFunctions {


		void mouseEvent( int event, int x, int y, int flags, void* param);
		int image1();
		void image2();
		void image3();
		void image4();
		void image5();
		int image6();
		void cannyFrame(cv::Mat& img, cv::Mat& out);

	}

}