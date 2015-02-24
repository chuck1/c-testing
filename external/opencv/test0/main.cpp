#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

const char* window_name = "Display Image";

const char* trackbar_value_0 = "Threshold";
const char* trackbar_value_1 = "Circle Param 0";
const char* trackbar_value_2 = "Circle Param 1";
const char* trackbar_value_3 = "Circle Min Rad";
const char* trackbar_value_4 = "Circle Max Rad";
const char* trackbar_value_5 = "Circle Min Dist";

int threshold_value = 128;
int circle_param_0 = 148;
int circle_param_1 = 31;
int circle_radius_min = 0;
int circle_radius_max = 38;
int circle_min_dist = 30;

VideoCapture stream0(0);

enum {
	ORIGIN,
	X,
	Y,
	TRACK
};

int mode = ORIGIN;

Vec2f o, x, y;
Point po, px, py;

void solve(Vec2f& c, double& a, double& b)
{
	Vec2f d = c - o;
	
	a = (d[0] - d[1] * y[0] / y[1]) / (x[0] - x[1] * y[0] / y[1]);

	b = (d[0] - a * x[0]) / y[0];
}

void webcam()
{
	Mat img_rgb;
	
	stream0.read(img_rgb);
	
	//imwrite("/home/chuck/git/wiki_private/webcam/image.jpg", img_rgb);
	bool ret = imwrite("/var/www/mysite/static/wiki/webcam/image.jpg", img_rgb);

	if(!ret) {
		printf("write error\n");
		exit(1);
	}
}

struct Match
{
	Match(Vec3f a, Vec3f b)
	{
		if(b[0] < a[0]){
			v_img[0] = Vec2f(b[0], b[1]);
			v_img[1] = Vec2f(a[0], a[1]);
		} else {
			v_img[0] = Vec2f(a[0], a[1]);
			v_img[1] = Vec2f(b[0], b[1]);
		}

		point[0] = Point(cvRound(v_img[0][0]), cvRound(v_img[0][1]));
		point[1] = Point(cvRound(v_img[1][0]), cvRound(v_img[1][1]));


		if(mode == TRACK)
		{
			//Vec2f d = v_img[0] - o;

			solve(v_img[0], A, B);

			v_int[0] = o + x * A;
			v_int[1] = o + y * B;

			point_int[0] = Point(cvRound(v_int[0][0]), cvRound(v_int[0][1]));
			point_int[1] = Point(cvRound(v_int[1][0]), cvRound(v_int[1][1]));

			Vec2f ab = v_img[1] - v_img[0];

			// angle
			angle = acos((ab[0]*x[0] + ab[1]*x[1]) / sqrt(ab[0]*ab[0] + ab[1]*ab[1]) / sqrt(x[0]*x[0] + x[1]*x[1]));

			if(v_img[1][1] > v_img[0][1]) angle = -angle;
		}
	}

	double A, B, angle;

	Vec2f v_img[2];
	Vec2f v[2];
	Vec2f v_int[2];

	Point point[2];
	Point point_int[2];
};

void draw(int arg, void*)
{
	//printf("read stream\n");
	//image = imread( argv[1], 1 );

	Match* match = 0;

	Mat img_rgb0;
	Mat img_gray;

	stream0.read(img_rgb0);

	//double rs = 0.5;
	//resize(image, image, Size(), rs, rs);

	if (!img_rgb0.data) {
		printf("No image data \n");
		exit(1);
	}

	cvtColor(img_rgb0, img_gray, CV_BGR2GRAY);

	//printf("blur\n");

	GaussianBlur(img_gray, img_gray, Size(9, 9), 2, 2);

	//Mat im = gray0.clone();
	//Mat& im = gray0;

	//printf("threshold\n");
	//threshold(img_gray, img_gray, threshold_value, 255, CV_THRESH_BINARY);

	// copy processed image and convert to color
	Mat img_rgb1(img_gray.size(), CV_8UC3);
	cv::cvtColor(img_gray, img_rgb1, CV_GRAY2RGB);

	vector<Vec3f> circles;

	HoughCircles(
			img_gray,
			circles,
			CV_HOUGH_GRADIENT,
			1,
			circle_min_dist,//img_gray.rows/32,
			circle_param_0,
			circle_param_1,
			circle_radius_min,
			circle_radius_max);

	//if(circles.size() > 0) printf("circles = %lu\n", circles.size());

	Point pc;

	if(circles.size() == 2)
	{
		match = new Match(circles[0], circles[1]);
	}

	if(arg == 1 && mode < TRACK)
	{
		if(match) {
			switch(mode) {
				case ORIGIN:
					o = match->v_img[0];
					po = Point(cvRound(match->v_img[0][0]), cvRound(match->v_img[0][1]));
					break;
				case X:
					x = match->v_img[0] - o;
					px = Point(cvRound(match->v_img[0][0]), cvRound(match->v_img[0][1]));
					break;
				case Y:
					y = match->v_img[0] - o;
					py = Point(cvRound(match->v_img[0][0]), cvRound(match->v_img[0][1]));
					break;
				default:
					exit(1);
			}
			mode++;
		}
	}


	// Draw the circles detected
	for( size_t i = 0; i < circles.size(); i++ )
	{
		//printf("%f %f\n", circles[i][0], circles[i][0]);

		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

		int radius = cvRound(circles[i][2]);
		// circle center
		circle( img_rgb1, center, 3, Scalar(0,255,0), -1, 8, 0 );
		// circle outline
		circle( img_rgb1, center, radius, Scalar(0,0,255), 10, 8, 0 );
	}

	if(mode > ORIGIN) {
		circle( img_rgb1, po, 3, Scalar(255,0,0), -1, 8, 0 );
	}
	if(mode > X) {
		circle( img_rgb1, px, 3, Scalar(255,0,0), -1, 8, 0 );
		line(img_rgb1, po, px, Scalar(255,255,0));
	}
	if(mode > Y) {
		circle( img_rgb1, py, 3, Scalar(255,0,0), -1, 8, 0 );
		line(img_rgb1, po, py, Scalar(255,255,0));

		// track
		if(match) {
			line(img_rgb1, match->point_int[0], match->point[0], Scalar(255,255,0));
			line(img_rgb1, match->point_int[1], match->point[0], Scalar(255,255,0));
			line(img_rgb1, match->point[1], match->point[0], Scalar(255,255,0));

			printf("x = %f, y = %f, a = %f\n", match->A, match->B, match->angle);
		}
	}
	
	imshow(window_name, img_rgb1);
}
void callback(void*)
{
	draw(0,0);
}
int main(int argc, char** argv )
{
	/*
	if ( argc != 2 )
	{
		printf("usage: DisplayImage.out <Image_Path>\n");
		return -1;
	}
	*/

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
			&circle_param_1,
			100,
			draw );
	createTrackbar(
			trackbar_value_3,
			window_name,
			&circle_radius_min,
			100,
			draw );
	createTrackbar(
			trackbar_value_4,
			window_name,
			&circle_radius_max,
			100,
			draw );
	createTrackbar(
			trackbar_value_5,
			window_name,
			&circle_min_dist,
			100,
			draw );

	draw(0,0);

	//waitKey(0);

	// Wait until user finishes program
	while(true)
	{
		char c = waitKey(10);
		
		if(c >= 0) printf("key = %i\n", c);
		
		if( c == 27 ) break;
		
		if(0) {
	
		if( c == 32 ) draw(1,0);
		else draw(0,0);
		} else {
			webcam();
		}
		//updateWindow(window_name);
	}


	return 0;
}



