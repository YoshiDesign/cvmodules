#include "./FeatureFunctions.h"

namespace FeatureFunctions {
	void OpticalFlow()
	{

		// Acquire a processor instance
		VideoProcessor processor;

		// Acquire a feature tracker instance
		FeatureTracker tracker;

		// Open a video file
		//processor.setInput("vid/clouds.mp4");

		// Or use a webcam
		int deviceID = 0;
		int apiID = cv::CAP_ANY;		// Autodetect default API

		// open the video
		processor.setInput(deviceID + apiID);

		// set frame processor
		processor.setFrameProcessor(&tracker);

		// Declare a window
		processor.displayOutput("Optical Flow");

		// Play at original framerate if CPU is up for it
		processor.setDelay(1000.0 / processor.getFrameRate());

		// Go
		processor.run();


	}
}
