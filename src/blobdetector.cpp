#include "blobdetector.h"
#include <math.h>

Blob operator- ( const Blob& b1, const Blob& b2)
{
    return Blob(b1.center_ - b2.center_, fabs( b1.area_ - b2.area_), fabs( b1.circularity_ - b2.circularity_) );
}

std::ostream& operator << (std::ostream &o, const Blob& b)
{
    o << "center: " << b.center_.x << ", " << b.center_.y << ", area: " << b.area_ << " circularity: " << b.circularity_ ;
    return o;
}

bool operator < (const Blob& b1, const Blob& b2)
{
    return cv::norm (b1.center_) < cv::norm (b2.center_);
}

bool operator > (const Blob& b1, const Blob& b2)
{
    return cv::norm (b1.center_) > cv::norm (b2.center_);
}

void BlobDetector::setGaussianBlurSize(const int& gaussian_blur_size)
{
    gaussian_blur_size_ = gaussian_blur_size;
}

void BlobDetector::setMinBlobRadius(const int& min_blob_radius)
{
    min_blob_radius_ = min_blob_radius;
}

void BlobDetector::setMaxCircularityToDrawCircle(const double& max_circularity_to_draw_circle)
{
    max_circularity_to_draw_circle_ = max_circularity_to_draw_circle;
}

void BlobDetector::setMinCircularityToDrawCircle(const double& min_circularity_to_draw_circle)
{
    min_circularity_to_draw_circle_ = min_circularity_to_draw_circle;
}

void BlobDetector::setBlobRadius(const double& blob_radius)
{
    blob_radius_ = blob_radius;
}

int BlobDetector::getGaussianBlurSize()
{
    return gaussian_blur_size_;
}

int BlobDetector::getMinBlobRadius()
{
    return min_blob_radius_;
}

double BlobDetector::getMaxCircularityToDrawCircle()
{
    return max_circularity_to_draw_circle_;
}

double BlobDetector::getMinCircularityToDrawCircle()
{
    return min_circularity_to_draw_circle_;
}

double BlobDetector::getBlobRadius()
{
    return blob_radius_;
}


