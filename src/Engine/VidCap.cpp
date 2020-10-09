#include <iostream> // Remove

#include "opencv2/core.hpp" 
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/objdetect.hpp"

#include "VidCap.h"
#include "video/VideoProcessor.h"

using namespace cv;


//void detectAndDisplay(Mat frame);

namespace engine {

	namespace vidcap {

		cv::Mat frame;
			   
		// Capture from webcam. Basic
		int capture() 
		{

			// Initialize video capture
			VideoCapture cap;
			// Open the default camera using default API
			// OR [Advanced] select any API backend
			int deviceID = 0;
			int apiID = cv::CAP_ANY;		// Autodetect default API

			// open selected camera using selected API
			cap.open(deviceID + apiID);

			// check if success
			if (!cap.isOpened())
			{
				std::cerr << "Error! Unable to open Camera\n";
				return -1;
			}

			// Grab and Write loop
			std::cout << "Start Grabbing" << std::endl
				<< "Press any key to terminate" << std::endl;

		
			for (;;)
			{
				// wait for a new frame from camera and store it into 'frame'
				cap.read(frame);
				// check for success
				if (frame.empty()) {
					std::cerr << "Error! Blank frame grabbed\n";
					break;
				}

				// show live and wait for a key with timeout long enough to show images
				imshow("Live", frame);

				if (waitKey(5) >= 0)
					break;
			}
			// Will automatically deinitialize in VideoCapture deconstructor
			return 0;

		}


		// Read a video file
		int capture2()
		{
		
			cv::VideoCapture capture("./vid/soundcheck.mp4");
			if (!capture.isOpened())
			{
				return 1;
			}

			// Get the frame rate or any other properties
			double rate = capture.get(CAP_PROP_FPS);

			// Create a var to store each frame
			bool stop(false);

			cv::namedWindow("Extracted Frame");

			 // Calculate delay between each frame. Display in ms
			int delay = 1000 / rate;
		
			// for all frames in video
			while (!stop) 
			{
				// read next frame if its there
				if (!capture.read(frame))
					break;

				// show the image and wait for the delay or a key press to exit
				cv::imshow("extracted frame", frame);
				// introduce a delay or press key to stop
				if (cv::waitKey(delay) >= 0)
					stop = true;
			}

			capture.release();
			return 0;

		}

		void cannyFrame(cv::Mat& img, cv::Mat& out)
		{
			// convert to grey
			if (img.channels() == 3)
			{
				cv::cvtColor(img, out, COLOR_BGR2GRAY);
				
			}

			// compute canny edges
			cv::Canny(out, out, 100, 200);

			// invert the image
			cv::threshold(out, out, 128, 255, cv::THRESH_BINARY_INV);


		}

		// Edge Detection 1 - Video file
		int capture3()
		{
	
			VideoProcessor processor;

			// open the video
			processor.setInput("vid/soundcheck.mp4");

			// declare the window
			processor.displayInput("Current Frame");
			processor.displayOutput("OutPut Frame");

			// Play the video at the original framerate
			processor.setDelay(1000.0 / processor.getFrameRate());

			// Set the frame processor callback function
			processor.setFrameProcessor(cannyFrame);

			// Start processing
			processor.run();

			return 0;

		}

		// Edge Detection 1 - Video file
		int capture4()
		{

			VideoProcessor processor;
			int deviceID = 0;
			int apiID = cv::CAP_ANY;		// Autodetect default API

			// open the video
			processor.setInput(deviceID + apiID);

			// declare the window
			//processor.displayInput("Current Frame");
			processor.displayOutput("OutPut Frame");

			// Play the video at the original framerate
			processor.setDelay(1000.0 / processor.getFrameRate());

			// Set the frame processor callback function
			processor.setFrameProcessor(cannyFrame);

			// Start processing
			processor.run();

			return 0;

		}

	}
}