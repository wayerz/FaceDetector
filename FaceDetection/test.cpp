#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    VideoCapture video(0); // Попробуйте 0 или 1, в зависимости от вашей камеры
    if (!video.isOpened()) {
        cerr << "Error opening video stream!" << endl;
        return -1;
    }

    CascadeClassifier facedetect;
    if (!facedetect.load("haarcascade_frontalface_default.xml")) {
        cerr << "Error loading cascade file!" << endl;
        return -1;
    }

    Mat img;
    while (true) {
        video.read(img);
        if (img.empty()) {
            cerr << "Error capturing image!" << endl;
            break;
        }

        vector<Rect> faces;
        facedetect.detectMultiScale(img, faces, 1.3, 5);

        cout << faces.size() << endl;

        for (int i = 0; i < faces.size(); i++) {
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 3);
            rectangle(img, Point(0, 0), Point(250, 70), Scalar(50, 50, 255), FILLED);
            putText(img, to_string(faces.size()) + " FACE FOUND", Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);
        }

        imshow("Frame", img);
        if (waitKey(30) >= 0) break; // Задержка в 30 мс
    }

    return 0;
}
