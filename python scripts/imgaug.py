# imgaug.py
# Python script for å augmentere treningsdata, samt å generere annoteringsfiler
# Erlend Omland & Marthe Engvik 
# I forbindelse med Bacheloroppgave i Militære studer med fordypning i Elektronikk og Data

import cv2
import numpy as np
import os
import random

dirpath = "/home/bachelor/obj"
last = 4327

files = os.listdir(dirpath)
files.sort()

for file in files:
    if file.endswith(".jpg"):
        pic = cv2.imread(file)
        W = 3 / 4 * np.size(pic, 1)
        H = 3 / 4 * np.size(pic, 0)
        w = int(W)
        h = int(H)
        seed_y = random.randint(0, ((1/4)*np.size(pic, 0)))
        seed_x = random.randint(0, ((1/4)*np.size(pic, 1)))
        # vi klipper bilder til 3/4 av bredde og høyde, med et random seed-punkt innenfor første 1/8 av h/b
        crop = pic[seed_y:h+seed_y, seed_x:w+seed_x]
        name = "00" + str(last) + ".jpg"
        path = "/home/bachelor/cropped/" + name
        # Lagrer croppet bilde
        cv2.imwrite(path, crop)

        tekstfil = os.path.splitext(file)[0] + ".txt"
        File = open(tekstfil)
        new = "00" + str(last) + ".txt"
        Path = "/home/bachelor/cropped/" + new
        Ofile = open(Path, 'w')
        Pic = cv2.imread(file)
        Cropfile = "/home/bachelor/cropped/00" + str(last) + ".jpg"
        Cropped = cv2.imread(Cropfile)
        for line in File:
            fields = line.split(" ")
            delete = True
            obj_id = fields[0]
            # størrelser i piksler, originalt bilde
            center_x = float(fields[1]) * np.size(Pic, 1)
            center_y = float(fields[2]) * np.size(Pic, 0)
            width = float(fields[3]) * np.size(Pic, 1)
            height = float(fields[4]) * np.size(Pic, 0)
            # alle størrelser nå ganget med gammel/ny størrelse + seed
            ny_x = (center_x - seed_x) / np.size(Cropped, 1)
            ny_y = (center_y - seed_y) / np.size(Cropped, 0)
            ny_w = width / np.size(Cropped, 1)
            if (center_x + width/2) > (np.size(Cropped, 1) + seed_x) and (center_x - seed_x) < (np.size(Cropped, 1)):
                # nytt uttrykk for bredde
                ny_w = ((seed_x - np.size(Cropped, 1)) - (center_x - width/2))/np.size(Cropped, 1)
                # flytter bbox center
                x = (np.size(Cropped, 1) - seed_x) - (ny_w*np.size(Cropped, 1))/2
                ny_x = x / np.size(Cropped, 1)
            ny_h = height / np.size(Cropped, 0)
            if (center_y + height/2) > (np.size(Cropped, 0) + seed_y) and (center_y - seed_y) < (np.size(Cropped, 0)):
                ny_h = ((seed_y - np.size(Cropped, 2)) - (center_y - height / 2)) / np.size(Cropped, 0)
                y = (np.size(Cropped, 0) - seed_y) - (ny_h * np.size(Cropped, 0)) / 2
                ny_y = y / np.size(Cropped, 0)


            if center_x < seed_x or center_y < seed_y:
                continue
            elif center_x > (np.size(Cropped, 1) + seed_x) or center_y > (np.size(Cropped, 0) + seed_y):
                continue
            else:
                Ofile.write(obj_id + " " + str(ny_x) + " " + str(ny_y) + " " + str(ny_w) + " " + str(ny_h))
                Ofile.write("\n")
                delete = False
        if delete:
            # Hvis ingen objekter i croppet bilde, eller alle objekters center er utenfor crop, slett croppet bilde
            os.remove(path)
            os.remove(Path)
        File.close()
        Ofile.close()
    last = last + 1
