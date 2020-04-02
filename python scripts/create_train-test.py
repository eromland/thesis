#create_train-test.py
#Python script for å generere train.txt og test.txt, viktige filer for å kunne trene modeller i darknet.
#Erlend Omland & Marthe Engvik
#I forbindelse med Bacheloroppgave i Militære studer med fordypning i Elektronikk og Data

import os

# Lager en liste av alle filer i en aktuell mappe, train/test
path = "/home/bachelor/data/DatasetDarknet/train"
dirs = os.listdir( path )
dirs.sort()

# Åpner en fil for å skrive filbaner for bildene som skal trenes/valideres på
# filnavn: train.txt/test.txt

outF = open("train.txt", "w")


# Skriver filbanen til alle .jpg bilder i aktuell mappe

for file in dirs:
   filepath = "data/obj/"
   filename = os.path.splitext(file)[0]
   imgpath = filepath + filename + ".jpg"
   outF.write(imgpath)
   outF.write("\n")

outF.close()