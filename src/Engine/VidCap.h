#pragma once
#include "opencv2/core.hpp"
namespace engine {

	namespace vidcap {

		int capture();
		int capture2();
		int capture3();
		int capture4();
		int capture5();
		void cannyFrame(cv::Mat& img, cv::Mat& out);
		
	}

}