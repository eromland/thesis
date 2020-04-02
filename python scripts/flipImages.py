#flipImages.py
#Python script for å augmentere treningsdataene. Scriptet speilier utvalgte bilder om en 
#vertikal akse, og lagrer nye bilder med korrekte filnavn.
#Erlend Omland & Marthe Engvik
#I forbindelse med Bacheloroppgave i Militære studer med fordypning i Elektronikk og Data

import os
import cv2

path = "/home/bachelor/data/DatasetVOC/flip_theese"

# Lager liste over alle bildefiler som skal speiles
files = os.listdir(path)
files.sort()
first = 3349

# Speiler bilder, lagrer med nye filnavn
for file in files:
    first += 1
    name = "00"
    name = name + str(first) + ".jpg"
    image = cv2.imread(file)
    cv2.flip(image, 1, image)
    cv2.imwrite(name, image)
    print(first)

