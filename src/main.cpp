#include <iostream>
#include "opencv2/highgui.hpp"
#include "Engine.h"
#include "VidCap.h"
#include "ImageFunctions.h"
#include "ScanningFunctions.h"


int main()
{
	engine::debug("Hello Lib");
	//engine::vidcap::capture4();

	
	// Performance reading
	// double time = engine::scanning::scan3();
	//std::cout << "T: " << time << std::endl;
	
	engine::scanning::scan3();
	
	cv::waitKey(0);

	return 0;
}