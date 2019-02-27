#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

double getPSNR(const Mat& I1, const Mat& I2);
Scalar getMSSIM(const Mat& i1, const Mat& i2);

int main()
{
	
	// Create a VideoCapture object and open the input file
	// If the input is the web camera, pass 0 instead of the video file name
	VideoCapture cap(0);
	cap.open(0);

	// Check if camera opened successfully
	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}
	CascadeClassifier face_cascade;
	face_cascade.load("D:/GitHub/FMP/C++ - FMP/opencv/build/etc/haarcascades/haarcascade_frontalface_alt2.xml");
		Mat frame;
		CascadeClassifier eye_cascade;
		eye_cascade.load("D:/GitHub/FMP/C++ - FMP/opencv/build/etc/haarcascades/haarcascade_eye.xml");
		
	while (1) {


		// Image from camera to Mat

		cap >> frame;

		// obtain input image from source
		cap.retrieve(frame, CAP_OPENNI_BGR_IMAGE);

		// Just resize input image if you want
		//resize(frame, frame, Size(1000, 640));

		Mat frame_gray;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);

		// Container of faces
		vector<Rect> faces;
		vector<Rect> eyes;


		// Detect faces
		face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0, Size(140, 140));
		//eye_cascade.detectMultiScale(frame,eyes, 1.1, 1000, 0, Size(30, 30));


		//Show the results
		// Draw circles on the detected faces

		/*for (int i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		}*/

		// To draw rectangles around detected faces
		for (unsigned i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
			Mat faceROI = frame_gray(faces[i]);
			//-- In each face, detect eyes
			std::vector<Rect> eyes;
			eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 20, 0, Size(10, 10));
			for (size_t j = 0; j < eyes.size(); j++)
			{
				Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
				int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
				circle(frame, eye_center, radius, Scalar(255, 0, 0), 4);
			}
		}

		imshow("wooohooo", frame);

		// Press  ESC on keyboard to exit
		char c = (char)waitKey(25);
		if (c == 27)
			break;
	}

	// When everything done, release the video capture object
	cap.release();

	// Closes all the frames
	//destroyAllWindows();

	return 0;

	
}

double getPSNR(const Mat& I1, const Mat& I2)
{
	Mat s1;
	absdiff(I1, I2, s1);       // |I1 - I2|
	s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
	s1 = s1.mul(s1);           // |I1 - I2|^2
	Scalar s = sum(s1);        // sum elements per channel
	double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels
	if (sse <= 1e-10) // for small values return zero
		return 0;
	else
	{
		double  mse = sse / (double)(I1.channels() * I1.total());
		double psnr = 10.0*log10((255 * 255) / mse);
		return psnr;
	}
}

Scalar getMSSIM(const Mat& i1, const Mat& i2)
{
	const double C1 = 6.5025, C2 = 58.5225;
	/***************************** INITS **********************************/
	int d = CV_32F;
	Mat I1, I2;
	i1.convertTo(I1, d);            // cannot calculate on one byte large values
	i2.convertTo(I2, d);
	Mat I2_2 = I2.mul(I2);        // I2^2
	Mat I1_2 = I1.mul(I1);        // I1^2
	Mat I1_I2 = I1.mul(I2);        // I1 * I2
								   /*************************** END INITS **********************************/
	Mat mu1, mu2;                   // PRELIMINARY COMPUTING
	GaussianBlur(I1, mu1, Size(11, 11), 1.5);
	GaussianBlur(I2, mu2, Size(11, 11), 1.5);
	Mat mu1_2 = mu1.mul(mu1);
	Mat mu2_2 = mu2.mul(mu2);
	Mat mu1_mu2 = mu1.mul(mu2);
	Mat sigma1_2, sigma2_2, sigma12;
	GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
	sigma1_2 -= mu1_2;
	GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
	sigma2_2 -= mu2_2;
	GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
	sigma12 -= mu1_mu2;
	Mat t1, t2, t3;
	t1 = 2 * mu1_mu2 + C1;
	t2 = 2 * sigma12 + C2;
	t3 = t1.mul(t2);                 // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
	t1 = mu1_2 + mu2_2 + C1;
	t2 = sigma1_2 + sigma2_2 + C2;
	t1 = t1.mul(t2);                 // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
	Mat ssim_map;
	divide(t3, t1, ssim_map);        // ssim_map =  t3./t1;
	Scalar mssim = mean(ssim_map);   // mssim = average of ssim map
	return mssim;
}