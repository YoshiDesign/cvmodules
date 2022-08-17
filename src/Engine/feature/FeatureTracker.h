#pragma once
#include <iostream>
#include "video/VideoProcessor.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>


class FeatureTracker : public FrameProcessor
{
private:

	cv::Mat gray;		// Current Image
	cv::Mat gray_prev;	// Previous Image

	// tracked features from 0 -> 1
	std::vector<cv::Point2f> points[2];

	// initial position of tracked points
	std::vector<cv::Point2f> initial;
	std::vector<cv::Point2f> features;

	int max_count;				// Max number of features to detect
	double qlevel;				// Quality level
	double minDist;				// Min distance between 2 points on a feature
	std::vector<uchar> status;	// Status of tracked features
	std::vector<float> err;		// error in tracking


public:

	FeatureTracker() : max_count(500), qlevel(0.001), minDist(10.0) {}

	void process(cv::Mat& frame, cv::Mat& output)
	{
		
		// convert to grayscale image
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		frame.copyTo(output);

		// 1. if new feature points must be added
		if (addNewPoints())
		{
			//detect feature points
			detectFeaturePoints();

			// add the detected features to currently tracked features
			points[0].insert(points[0].end(), 
				features.begin(), features.end());

			initial.insert(initial.end(), 
				features.begin(), features.end());

		}

		// for first image of the sequence
		if (gray_prev.empty())
		{
			gray.copyTo(gray_prev);
		}

		// track features
		cv::calcOpticalFlowPyrLK(
			gray_prev, gray,		// 2 consecutive images
			points[0],				// inpt point positions in the 1st image
			points[1],				// inpt point positions in the 2nd image
			status,					// Success??
			err						// or not
		);

		// 3. Loop over the tracked points to reject some  
		int k = 0;
		for (int i = 0; i < points[1].size(); i++)
		{
			// Do we keep the points?
			if (acceptTrackedPoint(i))
			{
				// keep it in the vector
				initial[k] = initial[i];
				points[1][k++] = points[1][i];
			}
		}

		// eliminate unsuccessful points
		points[1].resize(k);
		initial.resize(k);

		// 4. Handle the accepted tracked points
		handleTrackedPoints(frame, output);

		// 5. Current points and image become previous ones
		std::swap(points[1], points[0]);
		cv::swap(gray_prev, gray);
	
	}

	// Feature point detection
	void detectFeaturePoints()
	{
		cv::goodFeaturesToTrack(gray,	// The image
			features,					// The output detected features
			max_count,					// Maximum numlber of features to track
			qlevel,						// Quality threshold
			minDist						// Minimum distance between two detected features
		);
	}

	// Determines if new points should be added
	bool addNewPoints() {
		// if too few points
		return points[0].size() <= 10;
	}

	// Used to reject uninteresting points, or points which cannot be tracked
	bool acceptTrackedPoint(int i)
	{
		// Criteria : The position of this tracked point from 1 frame to the next is > 2
		return status[i] &&
			(abs(points[0][i].x - points[1][i].x) +
			(abs(points[0][i].y - points[1][i].y)) > 2 );
	}

	// Iterate through tracked points and do stuff
	void handleTrackedPoints(const cv::Mat& frame, cv::Mat& output)
	{
		// for all tracked points
		for (int i = 0; i < points[1].size(); i++)
		{

			cv::line(output,
				initial[i],			// Initial position of tracked feature
				points[1][i],		// New position
				cv::Scalar(255, 255, 255)
			);

			cv::circle(output, points[1][i], 3, cv::Scalar(255, 255, 255), -1);

		}
	}

};