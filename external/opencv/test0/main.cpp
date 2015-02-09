#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

const char* window_name = "Display Image";

const char* trackbar_value_0 = "Threshold";
const char* trackbar_value_1 = "Circle Param 1";

int threshold_value = 128;
int circle_value = 1000;
int circle_radius_min = 300;
int circle_radius_max = 1000;

Mat image, gray0, gray1;

void draw(int, void*)
{
	Mat im(image);

	threshold(gray0, gray1, threshold_value, 255, CV_THRESH_BINARY);

	vector<Vec3f> circles;

	HoughCircles(
			gray1,
			circles,
			CV_HOUGH_GRADIENT,
			1,
			gray1.rows/32,
			circle_value,
			100,
			circle_radius_min,
			circle_radius_max);

	printf("circles = %lu\n", circles.size());

	// Draw the circles detected
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

		int radius = cvRound(circles[i][2]);
		// circle center
		circle( im, center, 3, Scalar(0,255,0), -1, 8, 0 );
		// circle outline
		circle( im, center, radius, Scalar(0,0,255), 10, 8, 0 );
	}

	imshow(window_name, im);
}
int main(int argc, char** argv )
{
	if ( argc != 2 )
	{
		printf("usage: DisplayImage.out <Image_Path>\n");
		return -1;
	}

	image = imread( argv[1], 1 );

	resize(image, image, Size(), 0.1, 0.1);

	if (!image.data) {
		printf("No image data \n");
		return -1;
	}

	cvtColor(image, gray0, CV_BGR2GRAY);

	namedWindow(window_name, CV_WINDOW_NORMAL);

	createTrackbar(
			trackbar_value_0,
			window_name,
			&threshold_value,
			255,
			draw );
	createTrackbar(
			trackbar_value_1,
			window_name,
			&circle_param_0,
			1000,
			draw );
	createTrackbar(
			trackbar_value_2,
			window_name,
			&circle_radius_min,
			1000,
			draw );

	waitKey(0);

	// Wait until user finishes program
	while(true)
	{
		int c;
		c = waitKey( 20 );
		if( (char)c == 27 )
		{ break; }
	}

	return 0;
}



