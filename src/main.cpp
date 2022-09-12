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

    cv::Size imgSize;
    cv::Size patternsize(9, 6);
    vector<vector<cv::Point3f>> objectPoints_vec;
    vector<vector<cv::Point2f>> imgPoints_vec;

    vector<cv::Point3f> objectPoints;

    for (int i = 0; i < patternsize.height; i++)
    {
        for (int j = 0; j < patternsize.width; j++)
        {
            objectPoints.push_back(cv::Point3f(j, i, 0));
        }
    }

    for (int i=2; i<=20; i++)
    {
        vector<cv::Point2f> corners;

        // load image from file 
        cv::Mat img = cv::imread(chessboard_path + "calibration" + to_string(i) + ".jpg");
        cv::Mat imgGray;
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

        bool patternfound = cv::findChessboardCorners(imgGray, patternsize, corners,
            cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE | cv::CALIB_CB_FAST_CHECK);

        if (patternfound)
        {
            imgSize = img.size();

            cv::cornerSubPix(imgGray, corners, cv::Size(11, 11), cv::Size(-1, -1),
                cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.1));

            if (false)
            {
                cv::drawChessboardCorners(img, patternsize, cv::Mat(corners), patternfound);
                cv::imshow("win1", img);
                cv::waitKey(0);
            }


            objectPoints_vec.push_back(objectPoints);
            imgPoints_vec.push_back(corners);
        }
    }

    
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;
    cv::Mat undist_img;
    cv::Mat img = cv::imread(chessboard_path + "calibration1.jpg");

    float error = cv::calibrateCamera(objectPoints_vec, imgPoints_vec, imgSize, cameraMatrix, distCoeffs, rvecs, tvecs);
    cv::undistort(img, undist_img, cameraMatrix, distCoeffs);

    cv::imshow("output", undist_img);
    cv::waitKey(0);

    return 0;
}