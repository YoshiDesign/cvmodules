#include <iostream>
#include "opencv2/highgui.hpp"
#include "Engine.h"
#include "VidCap.h"
#include "ImageFunctions.h"
#include "ScanningFunctions.h"
#include "feature/FeatureFunctions.h"

#define LOG(a, b) std::cout<< a << std::endl;

int main()
{
	//engine::debug("Hello Lib");
	FeatureFunctions::OpticalFlow();
	//engine::scanning::scan3();
	//Performance reading
	//double time = engine::scanning::test();
	//std::cout << "T: "; LOG(time);

	//engine::imageFunctions::image5();

	cv::waitKey(0);
	
	return 0;
}