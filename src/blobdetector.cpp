#include "blobdetector.h"


BlobDetector::BlobDetector()
{
}

void BlobDetector::detectBlobsContours(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs)
{

}




void BlobDetector::detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity, const int& max_intensity)
{
    //thresholding
    //TODO: make params
    //TODO: different thresholds to segment a grey value

    const cv::Scalar floodfill_lo_diff = cv::Scalar(0);
    const cv::Scalar floodfill_up_diff = cv::Scalar(10);
    const int min_blob_radius = 10;

    cv::Mat blurred_image;
    cv::GaussianBlur(input_image, blurred_image, cv::Size(3, 3), 0, 0);

    cv::Mat closed_image;
    cv::morphologyEx(input_image, closed_image, cv::MORPH_CLOSE, cv::Mat());


    cv::Mat bw_image;
    double thresh_set_value = 255;

//    cv::adaptiveThreshold(input_image, bw_image, black_value, cv::ADAPTIVE_THRESH_GAUSSIAN_C ,cv::THRESH_BINARY_INV, 3, 0);

    cv::threshold(closed_image, bw_image, 50, thresh_set_value, cv::THRESH_BINARY_INV);

//    cv::threshold(closed_image, bw_image, max_intensity, thresh_set_value, cv::THRESH_TOZERO_INV);
//    cv::threshold(bw_image, bw_image, min_intensity, thresh_set_value, cv::THRESH_BINARY);

    cv::namedWindow( "bw Image", CV_WINDOW_AUTOSIZE );
    cv::imshow( "bw Image", bw_image );
    cv::waitKey(0);


    // 0 = black, 255 = white

    //show circles on input_image
    blobs_image = input_image;


    //distance transform
    cv::Mat distance_image;
    cv::distanceTransform(bw_image, distance_image, CV_DIST_L1, 3);
    // how far from black



    double min_val(0), max_val(0);
    cv::Point p_min, p_max;
    int area(0);
    double circularity(0);
    cv::Mat mask = cv::Mat::ones(distance_image.rows, distance_image.cols, CV_8U);

    while(true)
    {

        cv::minMaxLoc(distance_image, &min_val, &max_val, &p_min, &p_max, mask);

        if (max_val < min_blob_radius)
        {
            return;
        }

        cv::Mat mask_flood = cv::Mat::zeros(bw_image.rows + 2, bw_image.cols + 2, CV_8U);
        cv::Rect rect;
        area = cv::floodFill(bw_image, mask_flood, p_max, cv::Scalar(0), &rect, floodfill_lo_diff, floodfill_up_diff);


        //draw blobs
        cv::circle(blobs_image, p_max, max_val, cv::Scalar(175), 1);
//        cv::circle(blobs_image, p_max, 3, cv::Scalar(175), 10 );

        circularity = (M_PI * max_val * max_val)/static_cast<double> (area);

        Blob blob(p_max, area, circularity);
        blobs.push_back(blob);

        mask = mask - mask_flood(cv::Rect(1, 1, bw_image.cols, bw_image.rows));

    }
//    blobs_image = bw_image;
//    cv::normalize(blobs_image, blobs_image, 0, 1., cv::NORM_MINMAX);
//    std::cout<<blobs_image;

}



