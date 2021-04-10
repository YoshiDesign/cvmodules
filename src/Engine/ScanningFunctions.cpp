#include <iostream> // Remove
//#include <stdio.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "./ScanningFunctions.h"


namespace engine{

	namespace scanning {
	
		void reduceColor(cv::Mat img, int factor = 64)
		{
			int nl = img.rows;						// number of lines
			int nc = img.cols * img.channels();		// total number of elements per line

			/*
			Basic method for scanning images.
			*/
			uchar *data = img.data;
			

			for (int j = 0; j < nl; j++)
			{
				// Get the address of row J
				//uchar* data = img.ptr <uchar> (j);
				
				for (int i = 0; i < nc; i++)
				{


					data = img.ptr<uchar>(j);
					*data = 0;

					// Calculate vals like a normal human
					//data[i] = (data[i] / factor) * factor + factor / 2;

					// Or using pointer arithmetic DBUG
					// *data = (*data / factor) * factor + factor/2;
					//data++;
					//std::cout << *data << std::endl;
					

					// Or via modular arithmetic
					//data[i] = data[i] - data[i] % factor + factor / 2;

					// Or via bitwise ops
					//uchar mask = 0xFF<<factor;
					// *data &= mask;
					// *data++ += factor >> 1;

				}
				data += img.step;
			}
		}

		void scan1()
		{

			cv::Mat img;
			img = cv::imread("./img/brdhand.png");

			std::cout << "Channels: " << img.channels()
				<< "\nCols: " << img.cols
				<< "\nRows: " << img.rows
				<< "\nTotal: " << img.total()
				<< "\nElemSize" << img.elemSize()
				<< std::endl;

			reduceColor(img, 124);

			cv::imshow("Image", img);
			cv::waitKey(0);
		}




		// Iterators
		void reduceColorIT(cv::Mat_<cv::Vec3b> img, int factor = 64)
		{
			// Begin
			//cv::Mat_<cv::Vec3b>::iterator itrBegin = img.begin<cv::Vec3b>()/* + img.cols * (img.rows / 2)*/ ;
			// End
			//cv::Mat_<cv::Vec3b>::iterator itrEnd = img.end<cv::Vec3b>();

			cv::MatIterator_<cv::Vec3b> itrBegin = img.begin();
			cv::MatIterator_<cv::Vec3b> itrEnd = img.end();

			// loop over all pixels
			int i;
			for (i = 0; itrBegin != itrEnd; itrBegin++)
			{
				//std::cout << img.data[i] << std::endl;
				(*itrBegin)[0] = ((*itrBegin)[0] / factor) * factor + factor / 2;
				(*itrBegin)[1] = ((*itrBegin)[1] / factor) * factor + factor / 2;
				(*itrBegin)[2] = ((*itrBegin)[2] / factor) * factor + factor / 2;
			}

			std::cout << "Pixels: " << i << std::endl;
		}

		void scan2()
		{
			cv::Mat image;
			image = cv::imread("./img/brdhand.png", CV_8SC3);
			// Beginning
			//reduceColorIT(image, 64);
			cv::imshow("Helllo", image);
			cv::waitKey(0);

		}

		// Iter scanning with performance monitor
		double scan3()
		{

			cv::Mat_<cv::Vec3b> img;
			img = cv::imread("./img/brdhand.png");

			if (img.empty())
			{
				std::cout << "No image" << std::endl;
				return 0;
			}

			const int64 start = cv::getTickCount();
			reduceColorIT(img, 64);
			double duration = (cv::getTickCount() - start) / cv::getTickFrequency();
			cv::imshow("Hello", img);

			return duration;
		}

		double test()
		{

			cv::Mat_<cv::Vec3b> img;
			img = cv::imread("./img/brdhand.png", CV_8SC3);

			for (int i = 0; i < img.rows; i++)
			{

				for (int j = 0; j < img.cols; j++)
				{
					img(i, j) = 0;
				}
			}
			const int64 start = cv::getTickCount();
			cv::imshow("Hello", img);
			double duration = (cv::getTickCount() - start) / cv::getTickFrequency();
			
			return 2.0;

		}


	
	}
}