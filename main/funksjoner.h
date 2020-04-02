/* funksjoner.h
 Header som inneholder funksjoner for bruk av darknet og trent modell i C++ applikasjon.
 Videre inneholder filen funksjoner for å visualisere deteksjoner.
 Erlend Omland & Marthe Engvik - Med god hjelp fra Martin Vonheim Larsen
 I forbindelse med Bacheloroppgave i Militære studer med fordypning i Elektronikk og Data
*/

#ifndef UTKIKK9000_FUNKSJONER_H
#define UTKIKK9000_FUNKSJONER_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <iomanip>
#include <sstream>
#define OPENCV
#include <yolo_v2_class.hpp>

// Visualiserer klasse som enten military/civillian, relativ kurs skal representeres med pil
std::string find_name(int id){
    std::string name;
    switch(id){
        case 0: {
            name = "Civillian";
            break;
        }
        case 1: {
            name = "Civillian";
            break;
        }
        case 2: {
            name = "Civillian";
            break;
        }
        case 3: {
            name = "Military";
            break;
        }
        case 4: {
            name = "Military";
            break;
        }
        case 5: {
            name = "Military";
            break;
        }
    }
    return name;
}

//Tegner bokser rundt detekterte objekter. Videre beregnes relativ peiling, samt relativ kurs.
void draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vec, std::vector<std::string> obj_names) {
    int const colors[6][3] = {{1, 0, 1},
                              {0, 0, 1},
                              {0, 1, 1},
                              {0, 1, 0},
                              {1, 1, 0},
                              {1, 0, 0}};

    for (auto &i : result_vec) {
        cv::Scalar color = obj_id_to_color(i.obj_id);
        cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), color, 2);
        if (obj_names.size() > i.obj_id) {
            std::ostringstream presisjon;
            presisjon << std::setprecision(2);
            presisjon << i.prob;
            std::string obj_name = find_name(i.obj_id) + " " + presisjon.str();
            if (i.track_id > 0) obj_name += " - " + std::to_string(i.track_id);
            cv::Size const text_size = getTextSize(obj_name, cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, 2, 0);
            int const max_width = (text_size.width > i.w + 2) ? text_size.width : (i.w + 2);
            cv::rectangle(mat_img, cv::Point2f(std::max((int) i.x - 1, 0), std::max((int) i.y - 30, 0)),
                          cv::Point2f(std::min((int) i.x + max_width, mat_img.cols - 1),
                                      std::min((int) i.y, mat_img.rows - 1)),
                          color, CV_FILLED, 8, 0);
            putText(mat_img, obj_name, cv::Point2f(i.x, i.y - 10), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.7,
                    cv::Scalar(0, 0, 0), 2);
            if (i.obj_id == 0 || i.obj_id == 3){  //Relative kurs beregnes her, videre visualiseres dette i bildet.
                cv::arrowedLine(mat_img, cv::Point2f(i.x + 50, i.y - 40), cv::Point2f(i.x, i.y - 40),
                                cv::Scalar(0, 0, 0), 3, 8, 0, 0.2);
            }
            else if (i.obj_id == 1 || i.obj_id == 4){
                cv::arrowedLine(mat_img, cv::Point2f(i.x, i.y - 40), cv::Point2f(i.x + 50, i.y - 40),
                                cv::Scalar(0, 0, 0), 3, 8, 0, 0.2);
            }
            int bearing; //Relativ peiling i forhold til bildesenter beregnes, videre visualiseres dette i bildet.
            if ((i.x + i.w/2) < (mat_img.cols/2)){
                cv::drawMarker(mat_img, cv::Point2f(i.x + i.w/2, mat_img.rows - 15), cv::Scalar(0, 255, 0),
                                                    cv::MARKER_TRIANGLE_DOWN, 16, 2, 8);
                int bearing = int(90 - cv::fastAtan2(mat_img.rows - (i.y + i.h/2), mat_img.cols/2 - (i.x + i.w/2)));
                std::string Bearing = std::to_string(bearing);
                cv::putText(mat_img, Bearing, cv::Point2f(i.x + i.w/2 - (4 + 2*Bearing.length()), mat_img.rows - 27),
                                                          cv::FONT_HERSHEY_COMPLEX_SMALL, 0.7,cv::Scalar(0, 255, 0), 1);
            }
            else if ((i.x + i.w/2) > (mat_img.cols/2)){
                cv::drawMarker(mat_img, cv::Point2f(i.x + i.w/2, mat_img.rows - 15), cv::Scalar(0, 0, 255),
                                                    cv::MARKER_TRIANGLE_UP, 16, 2, 8);
                int bearing = int(90 - cv::fastAtan2(mat_img.rows - (i.y + i.h/2),(i.x + i.w/2) - mat_img.cols/2));
                std::string Bearing = std::to_string(bearing);
                cv::putText(mat_img, Bearing, cv::Point2f(i.x + i.w/2 - (4 + 2*Bearing.length()), mat_img.rows - 27),
                                                          cv::FONT_HERSHEY_COMPLEX_SMALL, 0.7,cv::Scalar(0, 0, 255), 1);
            }

        }
    }
}


////////////////////////////////////FUNKSJONER HENTET FRA ÅPEN KILDEKODE///////////////////////////////////////////////
void show_console_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names) {
    for (auto &i : result_vec) {
        if (obj_names.size() > i.obj_id) std::cout << obj_names[i.obj_id] << " - ";
        std::cout << "obj_id = " << i.obj_id << ",  x = " << i.x << ", y = " << i.y
                  << ", w = " << i.w << ", h = " << i.h
                  << std::setprecision(3) << ", prob = " << i.prob << std::endl;
    }
}

std::vector<std::string> objects_names_from_file(std::string const filename) {
    std::ifstream file(filename);
    std::vector<std::string> file_lines;
    if (!file.is_open()) return file_lines;
    for(std::string line; getline(file, line);) file_lines.push_back(line);
    std::cout << "object names loaded \n";
    return file_lines;
}



#endif //UTKIKK9000_FUNKSJONER_H
