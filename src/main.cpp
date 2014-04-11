#include <stdio.h>
#include "blobdetectorfloodfill.h"
#include "blobdetectorcontours.h"
#include "blobevaluator.h"


int main( int argc, char** argv )
{  
    bool evaluation = false;

    if( argc < 2)
    {
        std::cout << "No image data, evaluation" << std::endl;
        evaluation = true;
    }

    BlobDetector* blobDetector= NULL;


    if(evaluation)
    {
        srand(time(NULL));


        BlobEvaluator blobEvaluator;

        double center_error(0);
        double area_error(0);
        double circularity_error(0);
        double avg_duration(0);
        int images_to_test(500);

        blobDetector = new BlobDetectorFloodFill;
        blobEvaluator.evaluate(*blobDetector, images_to_test, center_error, area_error, circularity_error, avg_duration);
        delete blobDetector;

        std::cout << "FLOODFILL STATISTICS: " << std::endl;
        std::cout << "center avg error = " << center_error << std::endl;
        std::cout << "area avg error = " << area_error << std::endl;
        std::cout << "circularity avg error= " << circularity_error << std::endl;
        std::cout << "avg duration = " << avg_duration << std::endl;
        std::cout << std::endl;

        blobDetector = new BlobDetectorContours;
        blobEvaluator.evaluate(*blobDetector, images_to_test, center_error, area_error, circularity_error, avg_duration);
        delete blobDetector;

        std::cout << "CONTOURS STATISTICS: " << std::endl;
        std::cout << "center avg error in pixels = " << center_error << std::endl;
        std::cout << "area avg error in pixels = " << area_error << std::endl;
        std::cout << "circularity avg error = " << circularity_error << std::endl;
        std::cout << "avg duration in ms = " << avg_duration << std::endl;
        std::cout << std::endl;

    }
    else
    {
        cv::Mat input_image;
        input_image = cv::imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
        if (!input_image.data)
        {
            return -1;
        }

        std::vector<Blob> blobs;
        cv::Mat blobs_image;

        if ((argc > 3) || (argc == 2))
        {
            blobDetector = new BlobDetectorFloodFill;
            std::cout << "Running FloodFill" << std::endl;
        }
        else if (std::string(argv[2]) == "1")
        {
            blobDetector = new BlobDetectorFloodFill;
            std::cout << "Running FloodFill" << std::endl;
        }
        else
        {
            blobDetector = new BlobDetectorContours;
            std::cout << "Running Contours" << std::endl;
        }


        blobDetector->detectBlobs(input_image, blobs_image, blobs);
        delete blobDetector;

        for(uint i = 0; i < blobs.size(); i++)
        {
            std::cout << blobs[i] <<std::endl;
        }

        cv::namedWindow( "Blobs Image", CV_WINDOW_AUTOSIZE );
        cv::imshow( "Blobs Image", blobs_image );
        cv::waitKey(0);
    }


    return 0;
}
