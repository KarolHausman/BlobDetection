#include "blobdetectorfloodfill.h"


BlobDetectorFloodFill::BlobDetectorFloodFill():
    floodfill_lo_diff_(cv::Scalar(0)), floodfill_up_diff_(cv::Scalar(10)), mask_size_distance_transform_(3)
{
}

BlobDetectorFloodFill::~BlobDetectorFloodFill()
{
}


void BlobDetectorFloodFill::setFloodfillLoDiff(const cv::Scalar& floodfill_lo_diff)
{
    floodfill_lo_diff_ = floodfill_lo_diff;
}

void BlobDetectorFloodFill::setFloodfillUpDiff(const cv::Scalar& floodfill_up_diff)
{
    floodfill_up_diff_ = floodfill_up_diff;
}

void BlobDetectorFloodFill::setMaskSizeDistanceTransform(const int& mask_size_distance_transform)
{
    mask_size_distance_transform_ = mask_size_distance_transform;
}

cv::Scalar BlobDetectorFloodFill::getFloodfillLoDiff()
{
    return floodfill_lo_diff_;
}

cv::Scalar BlobDetectorFloodFill::getFloodfillUpDiff()
{
    return floodfill_up_diff_;
}

int BlobDetectorFloodFill::getMaskSizeDistanceTransform()
{
    return mask_size_distance_transform_;
}




void BlobDetectorFloodFill::detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity, const int& max_intensity)
{
    if ( (max_intensity > 255) || (max_intensity < 0) || (min_intensity > 255) || (max_intensity < 0) )
    {
        std::cerr << "Wrong intensity values! " << std::endl;
        blobs_image = input_image;
        return;
    }

    // draw circles on input_image
    cv::cvtColor(input_image, blobs_image, CV_GRAY2RGB);

    // blur, close and threshold the image
    cv::Mat blurred_image;
    cv::GaussianBlur(input_image, blurred_image, cv::Size(gaussian_blur_size_, gaussian_blur_size_), 0, 0);
    cv::Mat closed_image;
    cv::morphologyEx(input_image, closed_image, cv::MORPH_CLOSE, cv::Mat());
    cv::Mat bw_image;
    cv::inRange(closed_image, cv::Scalar(min_intensity), cv::Scalar(max_intensity), bw_image);
    // 0 = black, 255 = white


    // distance transform that specifies how far each pixel is from black
    cv::Mat distance_image;
    cv::distanceTransform(bw_image, distance_image, CV_DIST_L1, mask_size_distance_transform_);


    double min_val(0), max_val(0);
    cv::Point p_min, p_max;
    int area(0);
    double circularity(0);
    cv::Mat mask = cv::Mat::ones(distance_image.rows, distance_image.cols, CV_8U);

    // loop until no blobs to find
    cv::RNG rng(12345);
    while(true)
    {
        // find maximum of the distance image
        cv::minMaxLoc(distance_image, &min_val, &max_val, &p_min, &p_max, mask);
        if (max_val < min_blob_radius_)
        {
            return;
        }
        // run floodfill algorithm to fill the blob
        cv::Mat mask_flood = cv::Mat::zeros(bw_image.rows + 2, bw_image.cols + 2, CV_8U);
        cv::Rect rect;        
        area = cv::floodFill(bw_image, mask_flood, p_max, cv::Scalar(0), &rect, floodfill_lo_diff_, floodfill_up_diff_);

        // circularity = circle area / real area
        circularity = (M_PI * max_val * max_val)/static_cast<double> (area);

        // draw blobs
        cv::Scalar color(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
        if ( (circularity < max_circularity_to_draw_circle_) && (circularity > min_circularity_to_draw_circle_) )
        {
            cv::circle(blobs_image, p_max, max_val, color);
        }
        cv::circle( blobs_image, p_max, blob_radius_, color);


        Blob blob(p_max, area, circularity);
        blobs.push_back(blob);

        mask = mask - mask_flood(cv::Rect(1, 1, bw_image.cols, bw_image.rows));
    }
}



