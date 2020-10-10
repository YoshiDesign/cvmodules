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
					// Calculate vals like a normal human
					data[i] = (data[i] / factor) * factor + factor / 2;

					// Or using pointer arithmetic DBUG
					//*data = (*data / factor) * factor + factor/2;
					//std::cout << *data << std::endl;
					

					// Or via modular arithmetic DBUG
					//data[i] = data[i] - data[i] % factor + factor / 2;

					// Or via bitwise ops
					//uchar mask = 0xFF<<factor;
					//*data &= mask;
					//*data++ += factor >> 1;

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

		// Iterator
		void scan2()
		{

			

		}
	
	}
}