/*
 main.cpp
 hovedprogram i C++ applikasjon for å bruke darknet til å kjøre deteksjonsmodellen
 Erlend Omland & Marthe Engvik
 I forbindelse med Bacheloroppgave i Militære studer med fordypning i Elektronikk og Data
*/

#include "funksjoner.h"

int main() {
    std::string cfg = "/home/bachelor/darknet-master/cfg/yolov3-Utkikk9000.cfg";
    std::string weights = "/home/bachelor/darknet-master/yolov3-Utkikk9000_v4.0_best.weights";
    std::string names = "/home/bachelor/darknet-master/data/obj.names";
    int gpu = 0;                                                               //GPU index
    float det_thresh = 0.5;                                                    //Detection threshold

    Detector detector(cfg, weights, gpu);
    auto obj_names = objects_names_from_file(names);

    //Funksjonalitet for å kunne analysere utvalgte videofiler gjennom nettverket
    std::string periscope[8] = {"AA-C0002_nosound.MP4", "BB-C0003_nosound.MP4","CC-C0004_nosound.MP4",
                                "DD-C0005_nosound.MP4","EE-C0006_nosound.MP4","GG-C0010_nosound.MP4",
                                "HH-C0011_nosound.MP4", "Demov2.mp4"};
    std::string path = "/home/bachelor/darknet-master/Periskop/";
    path.append(periscope[5]);


    cv::VideoCapture cap(0);                                                   //Åpner webkamera
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

    while (cap.isOpened()){                                                    //Deteksjonsløkke
        cv::Mat frame;
        cap >> frame;
        std::vector<bbox_t> result_vec;

        auto start = std::chrono::steady_clock::now();                         //Deteksjon og FPS utregning
        result_vec = detector.detect(frame, det_thresh);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> spent = end - start;
        double detect_time = spent.count();
        double fps = 1/detect_time;
        std::ostringstream FPS;
        FPS << "FPS: ";
        FPS << std::setprecision(3);
        FPS << fps;

        draw_boxes(frame, result_vec, obj_names);                              //Deteksjonsvisualisering i bilde
        cv::putText(frame, FPS.str(), cv::Point(10,10), CV_FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0,255,0));
        show_console_result(result_vec, obj_names);

        cv::namedWindow("Utkikk9000", CV_WINDOW_NORMAL);
        cv::setWindowProperty("Utkikk9000", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
        cv::imshow("Utkikk9000", frame);

        if(cv::waitKey(10) == 27){                                             //Trykk "esc" for å avslutte programmet
            break;
        }
    }

    return 0;
}