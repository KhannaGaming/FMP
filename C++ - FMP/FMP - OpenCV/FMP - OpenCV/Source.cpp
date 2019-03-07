#include "FaceDetection.h"

int main()
{
	FaceDetection* faceDetection = new FaceDetection();
	faceDetection->Run();

	delete faceDetection;
	faceDetection = nullptr;

	return 0;
}

//#include <opencv2\opencv.hpp>
//#include <opencv2\highgui\highgui.hpp>
//int MAX_KERNEL_LENGTH = 3;
//int DELAY_BLUR = 100;
//using namespace cv;
//using namespace std;
//
//int display_dst(int delay, Mat frame);
//int main()
//{
//	Mat frame;
//	VideoCapture cap(0);
//	cap.open(0);
//
//	while (true)
//	{
//		cap >> frame;
//		imshow("frame", frame);
//		cvtColor(frame, frame, COLOR_BGRA2GRAY);
//	
//		adaptiveThreshold(frame,frame, 255, ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_TRUNC, 11, 6);
//			imshow("window", frame);
//		char c = (char)waitKey(25);
//		if (c == 27)
//			break;
//	}
//}
//int display_dst(int delay, Mat frame)
//{
//	int c = waitKey(delay);
//	if (c >= 0) { return -1; }
//	return 0;
//}
//const int max_value_H = 360 / 2;
//const int max_value = 255;
//const String window_capture_name = "Video Capture";
//const String window_detection_name = "Object Detection";
//int low_H = 0, low_S = 0, low_V = 0;
//int high_H = max_value_H, high_S = max_value, high_V = max_value;
//static void on_low_H_thresh_trackbar(int, void *)
//{
//	low_H = min(high_H - 1, low_H);
//	setTrackbarPos("Low H", window_detection_name, low_H);
//}
//static void on_high_H_thresh_trackbar(int, void *)
//{
//	high_H = max(high_H, low_H + 1);
//	setTrackbarPos("High H", window_detection_name, high_H);
//}
//static void on_low_S_thresh_trackbar(int, void *)
//{
//	low_S = min(high_S - 1, low_S);
//	setTrackbarPos("Low S", window_detection_name, low_S);
//}
//static void on_high_S_thresh_trackbar(int, void *)
//{
//	high_S = max(high_S, low_S + 1);
//	setTrackbarPos("High S", window_detection_name, high_S);
//}
//static void on_low_V_thresh_trackbar(int, void *)
//{
//	low_V = min(high_V - 1, low_V);
//	setTrackbarPos("Low V", window_detection_name, low_V);
//}
//static void on_high_V_thresh_trackbar(int, void *)
//{
//	high_V = max(high_V, low_V + 1);
//	setTrackbarPos("High V", window_detection_name, high_V);
//}
//int main(int argc, char* argv[])
//{
//	VideoCapture cap(argc > 1 ? atoi(argv[1]) : 0);
//	namedWindow(window_capture_name);
//	namedWindow(window_detection_name);
//	// Trackbars to set thresholds for HSV values
//	createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
//	createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
//	createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
//	createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
//	createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
//	createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
//	Mat frame, frame_HSV, frame_threshold;
//	while (true) {
//		cap >> frame;
//		if (frame.empty())
//		{
//			break;
//		}
//		// Convert from BGR to HSV colorspace
//		cvtColor(frame, frame_HSV, COLOR_BGR2GRAY);
//		// Detect the object based on HSV Range Values
//		inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
//		// Show the frames
//		imshow(window_capture_name, frame);
//		imshow(window_detection_name, frame_threshold);
//		char key = (char)waitKey(30);
//		if (key == 'q' || key == 27)
//		{
//			break;
//		}
//	}
//	return 0;
//}


///// Global variables
//Mat frame_gray, erosion_dst, dilation_dst, gausian_blur1, gausian_blur2, gausian_blur3, gausian_blur4;
//
//int erosion_elem = 1;
//int erosion_size = 1;
//int dilation_elem = 0;
//int dilation_size = 0;
//int const max_elem = 2;
//int const max_kernel_size = 21;
//
///** Function Headers */
//void Erosion(int, void*);
//void Dilation(int, void*);
//
//double getPSNR(const Mat& I1, const Mat& I2);
//Scalar getMSSIM(const Mat& i1, const Mat& i2);
//
//int main()
//{
//	
//	// Create a VideoCapture object and open the input file
//	// If the input is the web camera, pass 0 instead of the video file name
//	VideoCapture cap(0);
//	cap.open(0);
//
//	// Check if camera opened successfully
//	if (!cap.isOpened()) {
//		cout << "Error opening video stream or file" << endl;
//		return -1;
//	}
//	CascadeClassifier face_cascade;
//	face_cascade.load("D:/GitHub/FMP/C++ - FMP/opencv/build/etc/haarcascades/haarcascade_frontalface_alt2.xml");
//		Mat frame;
//		CascadeClassifier eye_cascade;
//		eye_cascade.load("D:/GitHub/FMP/C++ - FMP/opencv/build/etc/haarcascades/haarcascade_eye.xml");
//		
//	while (1) {
//
//
//		// Image from camera to Mat
//
//		cap >> frame;
//
//		// obtain input image from source
//		cap.retrieve(frame, CAP_OPENNI_BGR_IMAGE);
//
//		// Just resize input image if you want
//		//resize(frame, frame, Size(1000, 640));
//
//		//Mat frame_gray;
//		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
//		equalizeHist(frame_gray, frame_gray);
//
//		// Container of faces
//		vector<Rect> faces;
//		vector<Rect> eyes;
//
//		int sigma = 3;
//		int ksize = (sigma * 5) | 1;
//		createTrackbar("Sigma", "Laplacian", &sigma, 15, 0);
//		imshow("Original", frame_gray);
//		GaussianBlur(frame_gray, gausian_blur1, Size(ksize, ksize), 0, 1);
//		imshow("Gaus1", gausian_blur1);
//		GaussianBlur(frame_gray, gausian_blur2, Size(ksize, ksize), 0, 2);
//		imshow("Gaus2", gausian_blur2);
//		GaussianBlur(frame_gray, gausian_blur3, Size(ksize, ksize), 0, 3);
//		imshow("Gaus3", gausian_blur3);
//		GaussianBlur(frame_gray, gausian_blur4, Size(ksize, ksize), 0, 4);
//		imshow("Gaus4", gausian_blur4);
//		
//
//		// Detect faces
//		//face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0, Size(140, 140));
//		//eye_cascade.detectMultiScale(frame,eyes, 1.1, 1000, 0, Size(30, 30));
//
//
//		//Show the results
//		// Draw circles on the detected faces
//
//		/*for (int i = 0; i < faces.size(); i++)
//		{
//			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
//			ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
//		}*/
//
//		// To draw rectangles around detected faces
//		//for (unsigned i = 0; i < faces.size(); i++)
//		//{
//		//	Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
//		//	ellipse(frame_gray, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
//		//	Mat faceROI = frame_gray(faces[i]);
//		//	//-- In each face, detect eyes
//		//	std::vector<Rect> eyes;
//		//	eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 20, 0, Size(10, 10));
//		//	for (size_t j = 0; j < eyes.size(); j++)
//		//	{
//		//		Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
//		//		int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
//		//		circle(frame_gray, eye_center, radius, Scalar(255, 0, 0), 4);
//		//	}
//		//}
//		
//
//	/*	/// Create Erosion Trackbar
//		createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
//			&erosion_elem, max_elem,
//			Erosion);
//
//		createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
//			&erosion_size, max_kernel_size,
//			Erosion);
//
//		/// Create Dilation Trackbar
//		createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
//			&dilation_elem, max_elem,
//			Dilation);
//
//		createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
//			&dilation_size, max_kernel_size,
//			Dilation);
//
//		imshow("wooohooo", frame_gray);
//		Erosion(0, 0);
//		Dilation(0, 0);*/
//		// Press  ESC on keyboard to exit
//		char c = (char)waitKey(25);
//		if (c == 27)
//			break;
//	}
//
//	// When everything done, release the video capture object
//	cap.release();
//
//	// Closes all the frames
//	//destroyAllWindows();
//
//	return 0;
//
//	
//}
//
//double getPSNR(const Mat& I1, const Mat& I2)
//{
//	Mat s1;
//	absdiff(I1, I2, s1);       // |I1 - I2|
//	s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
//	s1 = s1.mul(s1);           // |I1 - I2|^2
//	Scalar s = sum(s1);        // sum elements per channel
//	double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels
//	if (sse <= 1e-10) // for small values return zero
//		return 0;
//	else
//	{
//		double  mse = sse / (double)(I1.channels() * I1.total());
//		double psnr = 10.0*log10((255 * 255) / mse);
//		return psnr;
//	}
//}
//
//Scalar getMSSIM(const Mat& i1, const Mat& i2)
//{
//	const double C1 = 6.5025, C2 = 58.5225;
//	/***************************** INITS **********************************/
//	int d = CV_32F;
//	Mat I1, I2;
//	i1.convertTo(I1, d);            // cannot calculate on one byte large values
//	i2.convertTo(I2, d);
//	Mat I2_2 = I2.mul(I2);        // I2^2
//	Mat I1_2 = I1.mul(I1);        // I1^2
//	Mat I1_I2 = I1.mul(I2);        // I1 * I2
//								   /*************************** END INITS **********************************/
//	Mat mu1, mu2;                   // PRELIMINARY COMPUTING
//	GaussianBlur(I1, mu1, Size(11, 11), 1.5);
//	GaussianBlur(I2, mu2, Size(11, 11), 1.5);
//	Mat mu1_2 = mu1.mul(mu1);
//	Mat mu2_2 = mu2.mul(mu2);
//	Mat mu1_mu2 = mu1.mul(mu2);
//	Mat sigma1_2, sigma2_2, sigma12;
//	GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
//	sigma1_2 -= mu1_2;
//	GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
//	sigma2_2 -= mu2_2;
//	GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
//	sigma12 -= mu1_mu2;
//	Mat t1, t2, t3;
//	t1 = 2 * mu1_mu2 + C1;
//	t2 = 2 * sigma12 + C2;
//	t3 = t1.mul(t2);                 // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
//	t1 = mu1_2 + mu2_2 + C1;
//	t2 = sigma1_2 + sigma2_2 + C2;
//	t1 = t1.mul(t2);                 // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
//	Mat ssim_map;
//	divide(t3, t1, ssim_map);        // ssim_map =  t3./t1;
//	Scalar mssim = mean(ssim_map);   // mssim = average of ssim map
//	return mssim;
//}
/////**  @function Erosion  */
//void Erosion(int, void*)
//{
//	int erosion_type;
//	if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
//	else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
//	else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
//
//	Mat element = getStructuringElement(erosion_type,
//		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
//		Point(erosion_size, erosion_size));
//
//	/// Apply the erosion operation
//	erode(frame_gray, erosion_dst, element);
//	imshow("Erosion Demo", erosion_dst);
//}
//
///** @function Dilation */
//void Dilation(int, void*)
//{
//	int dilation_type;
//	if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
//	else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
//	else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
//
//	Mat element = getStructuringElement(dilation_type,
//		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
//		Point(dilation_size, dilation_size));
//	/// Apply the dilation operation
//	dilate(frame_gray, dilation_dst, element);
//	imshow("Dilation Demo", dilation_dst);
//}