# rename.py
# python script for å gi nye filnavn til negative datasamples, samt å generere annoteringsfiler
# Erlend Omland & Marthe Engvik
# I forbindelse med Bacheloroppgave i Militære studer med fordypning i Elektronikk og Data

import os

filepath = "/home/bachelor/data/Negatives/"

dirs = os.listdir(filepath)
dirs.sort()

first = 3751

# Gi nytt navn til filer
for dir in dirs:
    path = "/home/bachelor/data/Negatives/" + dir
    print(path)
    ims = os.listdir(path)
    for im in ims:
        name = "00" + str(first) + ".jpg"
        pic = path + "/" + im
        os.rename(pic, name)
        first = first + 1
        textfile = "00" + str(first) + ".txt"
        open(textfile, "w+")

