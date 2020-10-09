#include "Engine.h"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <stdio.h>

using namespace cv;

namespace engine {

	void debug(const char* message)
	{
		std::cout << message << std::endl;
	}

	void test()
	{
		Mat image;
		image = imread("./img/brdhand.png", IMREAD_UNCHANGED);
		if (image.empty())
		{
			std::cout << "No Img" << std::endl;
			std::cin.get();
		}

		std::cout << "Channels: " << image.channels() << std::endl;

		// Show the window
		imshow("Hello W0rld", image);
		waitKey(0);
	}
}