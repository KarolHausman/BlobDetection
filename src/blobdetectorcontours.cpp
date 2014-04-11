#include "blobdetectorcontours.h"

BlobDetectorContours::BlobDetectorContours():
    min_contour_size_(40), canny_threshold_(70)
{
}

BlobDetectorContours::~BlobDetectorContours()
{
}


void BlobDetectorContours::detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity, const int& max_intensity)
{
    cv::cvtColor(input_image, blobs_image, CV_GRAY2RGB);
    // no_color flag indicates that we won't do binary thresholding
    bool no_color_flag = true;

    cv::Mat blurred_image;
    cv::Mat processed_image;

    // blur the image
    cv::GaussianBlur(input_image, blurred_image, cv::Size(gaussian_blur_size_, gaussian_blur_size_), 0, 0);

    if ( (max_intensity <= 255) && (max_intensity >= 0) && (min_intensity <= 255) && (max_intensity >= 0) )
    {
        // if the intensities are valid, do the thresholding
        cv::inRange(blurred_image, cv::Scalar(min_intensity), cv::Scalar(max_intensity), processed_image);
        cv::morphologyEx(processed_image, processed_image, cv::MORPH_CLOSE, cv::Mat());
        no_color_flag = false;
    }
    else
    {
        // we use canny and morphology in the other case
        cv::Mat canny_image;
        cv::Canny(blurred_image, canny_image, canny_threshold_, canny_threshold_ * 2);
        cv::morphologyEx(canny_image, processed_image, cv::MORPH_CLOSE, cv::Mat());
    }

    // find contours in the image
    std::vector < std::vector < cv::Point > > contours;
    std::vector < cv::Vec4i > hierarchy;
    cv::findContours(processed_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    cv::RNG rng(12345);
    for( int i = 0; i< contours.size(); i++ )
    {
        // check only for inner contours, check if they're convex and their size
        if ( ( (hierarchy[i][3] != -1) || (!no_color_flag) ) && ( !cv::isContourConvex(contours[i]) ) && ( contours[i].size() > min_contour_size_ ) )
        {
            // calculate moments and center of mass
            cv::Moments mu = cv::moments(contours[i], false );
            cv::Point2f mc = cv::Point2f(mu.m10/mu.m00 , mu.m01/mu.m00 );

            // calculate circularity
            cv::Point2f circle_center = cv::Point2f(0, 0);
            float circle_radius(0.0);
            cv::minEnclosingCircle(contours[i], circle_center, circle_radius);
            double area = mu.m00;
            double circularity = (M_PI * circle_radius * circle_radius) / area;

            cv::Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            if (circularity < max_circularity_to_draw_circle_ && circularity > min_circularity_to_draw_circle_)
            {
                // draw circles on the output_image
                cv::circle(blobs_image, circle_center, circle_radius, color);
            }
            // draw centers if it's not circular enough
            cv::circle(blobs_image, mc, blob_radius_, color);
            // add blob
            Blob blob(mc, area, circularity);
            blobs.push_back(blob);
        }
    }

}
