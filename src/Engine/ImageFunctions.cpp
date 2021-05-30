#include <iostream>
//#include <stdio.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "ImageFunctions.h"
#include "opencv2/objdetect.hpp"

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
			image = cv::imread("./img/birdhand.png");
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

			cv::Mat image3 = cv::imread("./img/birdhand.png");
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

		// Image mask (Zero Values)
		void image4()
		{

			cv::Mat im1(720, 1080, CV_8UC3, cv::Scalar(90, 100, 100));
			cv::Mat logo;
			logo = cv::imread("./img/tonz.png", 1);

			cv::Rect roi = cv::Rect(im1.cols - logo.cols, im1.rows - logo.rows, logo.cols, logo.rows);
			cv::Mat imageRoi(im1, roi);
			cv::Mat mask(logo);
			logo.copyTo(imageRoi, mask);
			cv::imshow("Hello", im1);
			cv::waitKey(0);

		}

		void cannyFrame(cv::Mat& img, cv::Mat& out)
		{
			// convert to grey
			if (img.channels() == 3)
			{
				cv::cvtColor(img, out, cv::COLOR_BGR2GRAY);

			}

			// compute canny edges
			cv::Canny(out, out, 100, 200);

			// invert the image
			cv::threshold(out, out, 128, 255, cv::THRESH_BINARY_INV);


		}


		// Salt & pepper noise
		void salt(cv::Mat img, int n) 
		{
			int i, j;

			for (int k = 0; k < n; k++)
			{
			
				i = std::rand() % img.cols;
				j = std::rand() % img.rows;

				// If it's a grayscale image
				if (img.type() == CV_8UC1)
				{
					
					img.at<uchar>(j, i) = 255;
				}
				// If it's a color image
				else if (img.type() == CV_8UC3)
				{
					if (img.at<cv::Vec3b>(j, i)[0] >= 200) {
						img.at<cv::Vec3b>(j, i)[0] = i % 10;
						img.at<cv::Vec3b>(j, i)[1] = i % 115;
						img.at<cv::Vec3b>(j, i)[2] = k % 255;
					}
					else {
						img.at<cv::Vec3b>(j, i)[0] = j % 255;
						img.at<cv::Vec3b>(j, i)[1] = j % 115;
						img.at<cv::Vec3b>(j, i)[2] = j % 255;
					}
				}

			}

		}
		void image5()
		{
			cv::Mat img = cv::imread("./img/tonz.png");
			std::cout << img.channels() << std::endl;
			//salt(img, 50000);
			cv::Mat out(720, 1080, CV_8UC3);

			cannyFrame(img, out);

			cv::imshow("HelllO", out);
			
			cv::waitKey(0);
		}

		// Edge detection
		int image6()
		{

			cv::Mat img = cv::imread("./img/tonz.png");
			cv::Mat out(720, 1080, CV_8UC3);

			cannyFrame(img, out);

			cv::imshow("Tonz", out);

			return 0;
		}




	}
}