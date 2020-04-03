# Utkikk9000
This repository was created as a part of my Bachelor thesis, during my time at The Royal Norwegian Naval Academy. 
The thesis consists of a Computer Vision application for classifying ships, as well as their relative heading to the observer.
As I am Norwegian, the thesis-document is written in Norwegian, however all of the code and scripts should be understandable for non-norwegian speakers.

The production of the application relied heavily on AlexeyAB's version of [Darknet](https://github.com/AlexeyAB/darknet)

## System overview
![System Overview](/pics/overview.png)

## Detection examples
![Military](/pics/example.png)
![Civillian](/pics/example2.png)
![Civillian](/pics/example3.png)

## Downloads

### Thesis

[Maskinlæring som klassifiseringsverktøy - den nye Marinen?](thesis/Bacheloroppgave2018_Omland_Engvik.pdf)

### Processed video
Theese results can be produced on live video if you have cloned the Darknet repository referenced above, using main.cpp included in this repository.
[Download](https://mega.nz/file/bslxzDjB#X1X4wZ5_i2LbiFKnJbHR3_kJjXErW3aCWfHKJ1vjfCo)

### Dataset 
This dataset was produced solely for this project, and totals 7643 labeled images.
[download](https://mega.nz/file/jt1l3RIa#Mxx0paLdOb5fJAs4Bu1Z_waYa5Q8HbFMoGNzWl0C8xM)
### Weights
[download](https://mega.nz/file/u8tDDLqR#64C2QchJW3unnAM6k-slaxxGrEO2PRwu_rfx5vpecn0)

## Prerequisites/Software used 

Installed version of [Darknet](https://github.com/AlexeyAB/darknet). On AlexeyAB's repository, you will find detailed installation guides for your system.  
Labeling images: [Yolo_mark](https://github.com/AlexeyAB/Yolo_mark)  
[OpenCV 3.4.0](https://opencv.org/releases.html)  
[CUDA 9.1](https://developer.nvidia.com/cuda-91-download-archive)  
Python script for web-scraping large amounts of image data: [ScrapeImages.py](https://gist.github.com/genekogan/ebd77196e4bf0705db51f86431099e57)

## How to use
Follow installation guide according to AlexeyAB's darknet repository  
Make sure to include [yolo_v2_class.hpp](https://github.com/AlexeyAB/darknet/blob/master/include/yolo_v2_class.hpp) (Already done in funksjoner.h, from this repository)  
Download weights referenced above, remember to apply correct paths according to your system for all files  
Build project and run main.cpp from this repository  
