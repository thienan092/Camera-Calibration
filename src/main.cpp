#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d.hpp>

using namespace std;

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{
    /* INIT VARIABLES AND DATA STRUCTURES */

    // data location
    string dataPath = "../";
    
    // chessboard_images
    string chessboard_path = dataPath + "chessboard_images/";
    
    // load image from file 
    cv::Mat img = cv::imread(chessboard_path + "calibration2.jpg");
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    
    vector<cv::Point2f> corners;
    cv::Size patternsize(9,6);
    bool patternfound = cv::findChessboardCorners(imgGray, patternsize, corners,
        cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE
        + cv::CALIB_CB_FAST_CHECK);
        
    if(patternfound)
    {
        cv::cornerSubPix(imgGray, corners, cv::Size(11, 11), cv::Size(-1, -1),
            cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1));


        cv::drawChessboardCorners(img, patternsize, cv::Mat(corners), patternfound);
    }

    cv::imshow("win1", img);
    cv::waitKey(0);

    return 0;
}