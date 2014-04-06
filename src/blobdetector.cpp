#include "blobdetector.h"


BlobDetector::BlobDetector()
{
}

void BlobDetector::detectBlackBlob(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs)
{
    //thresholding
    //TODO: make params
    cv::Mat bw_image;
    double threshold = 40;
    double maxval = 255;
    cv::threshold(input_image, bw_image, threshold, maxval, cv::THRESH_BINARY_INV);
    // 0 = black, 255 = white

    //distance transform
    cv::Mat distance_image;
    cv::distanceTransform(bw_image, distance_image, CV_DIST_C, 3);
    // how far from black



    double min_val(0), max_val(0);
    cv::Point p_min, p_max;
//    while(true)
//    {
        cv::minMaxLoc(distance_image, &min_val, &max_val, &p_min, &p_max);
        cv::circle(distance_image, p_max, 20, cv::Scalar(0,0,255) );


        cv::Rect rect;
        cv::floodFill(distance_image, p_max, cv::Scalar(255, 255, 255), &rect, cv::Scalar(50), cv::Scalar(60));

//    }
    blobs_image = distance_image;
    cv::normalize(blobs_image, blobs_image, 0, 1., cv::NORM_MINMAX);
//    std::cout<<blobs_image;

}


