#plot_mAP.py
#Python script for å teste presisjon på validerings-/treningsdata, samt å generere filer til å plotte dataene
#Erlend Omland & Marthe Engvik
#I forbindelse med Bacheloroppgave i Militære studer med fordypning i Elektronikk og Data

import os, sys

# Lager en liste over alle vekt-filer i aktuell mappe
path = "/home/bachelor/darknet/backup"
weights = os.listdir( path )
weights.sort()

# Kjører presisjons-evaluerings programvare, og skriver all output til fil "output.txt"
for weight in weights:
   string = "./darknet detector map data/obj.data cfg/yolov3-Utkikk9000.cfg backup/"
   string = string + weight + " -thresh 0.5"
   string = string + " >> output.txt"
   os.system(string)

# Oppretter filer for å skrive x- og y-koordinater til filer
outF = open("y.txt", "w")
outFi = open("x.txt", "w")

iteration = 100

# Leser relavant data fra "output.txt" og skriver data til filer
with open("output.txt", "r") as file:
   for line in file:
      if "mean average precision (mAP) =" in line:
         it = str(iteration)
         outFi.write(iteration)
         outFi.write("\n")
         outF.write(line[45:50])
         outF.write("\n")
         iteration = iteration + 100


outF.close()
