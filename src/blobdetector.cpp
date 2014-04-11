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

