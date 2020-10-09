#include <iostream> // Remove
//#include <stdio.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "ImageFunctions.h"
//#include "opencv2/objdetect.hpp"

namespace engine {

	namespace imageFunctions {
		
		void mouseEvent(int event, int x, int y, int flags, void* userdata)
		{
			if (event == cv::EVENT_LBUTTONDOWN)
			{
				std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
			}
			else if (event == cv::EVENT_RBUTTONDOWN)
			{
				std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
			}
			else if (event == cv::EVENT_MBUTTONDOWN)
			{
				std::cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
			}
			else if (event == cv::EVENT_MOUSEMOVE)
			{
				std::cout << "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;

			}
		}

		int image1()
		{
			
			cv::Mat image;
			image = cv::imread("./img/brdhand.png");
			for (int x = 0; x < 20; x++)
			{
			
				cv::Mat roi(image, cv::Rect(10 * x,10 * x,100,100));
				roi = cv::Scalar((15 * x) % 255, (25 * x) % 255, (40 * x) % 255);
			
			}

			std::cout << "Dimensions: " << image.rows << " x " << image.cols << std::endl;

			if (image.empty())
			{
				return 1;
			}


			cv::imshow("Hello", image);



			//cv::setMouseCallback("Original Image", mouseEvent, NULL);
			
			cv::waitKey(0);
			return 0;
		}

		cv::Mat makeImage()
		{
		
			cv::Mat img(500, 500, CV_8U, 50);
			return img;
			
		
		}

		// Allocation stuff
		void image2()
		{

			/*cv::namedWindow("Window 1");
			cv::namedWindow("Window 12");
			cv::namedWindow("Window 13");
			cv::namedWindow("Window 14");
			cv::namedWindow("Window 15");
			cv::namedWindow("Window 16");
			cv::namedWindow("Window 17");*/

			// Create a new image 240x320
			cv::Mat image1(240, 320, CV_8U, 100);

			cv::imshow("Window 1", image1);
			cv::waitKey(0);

			// re-allocate a new image
			image1.create(200, 200, CV_8U);
			image1 = cv::Scalar(120,246,100);

			cv::imshow("Derp", image1); 
			cv::waitKey(0);

			cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255));

			cv::imshow("Flerp", image2);
			cv::waitKey(0);

			cv::Mat image3 = cv::imread("./img/brdhand.png");
			cv::Mat image4(image3);

			image3.copyTo(image2);
			cv::Mat image5 = image3.clone();
			cv::imshow("IM3", image3);
			cv::imshow("IM4", image4);
			cv::imshow("IM5", image5);
			cv::waitKey(0);

			//std::cout << "Image Data\n" << image3.data << std::endl;
			cv::waitKey(0);
		}

		// Logo insertion
		void image3()
		{

			std::cout << "???????" << std::endl;
			std::cout << "???????" << std::endl;

			cv::Mat im1(720, 1080, CV_8UC3, cv::Scalar(90, 100, 100));
			cv::Mat logo;
			logo = cv::imread("./img/sum.bmp", 1);

			cv::Rect roi = cv::Rect(im1.cols - logo.cols, im1.rows - logo.rows, logo.cols, logo.rows);
			cv::Mat imageRoi(im1, roi);
			logo.copyTo(imageRoi);

			cv::Range range = cv::Range(im1.rows - logo.rows, im1.rows);

			cv::imshow("Sup",im1);
			std::cout << range.size() << "\nStart: " << range.start << "\nEnd: " << range.end << std::endl;

			cv::waitKey(0);

		}


	}
}