#CLR.py
#Python script for å produsere læreratestyring som forsøker å tilnerme sykliske lærerater
#Erlend Omland & Marthe Engvik
#I forbindelse med Bacheloroppgave i Militære studer med fordypning i Elektronikk og Data

steps = []
scales = []
step = 1000
i = 0
LR = 0.001
x = []
y = []
outFx = open("x.txt", "w")
outFy = open("y.txt", "w")

for i in range(70):
   steps.append(step)
   if i%2==0:
      scales.append(0.91)
      LR = LR*0.91
      y.append(LR)
      lr = str(LR)
      outFy.write(lr)
      outFy.write("\n")
   else:
      scales.append(1.03)
      LR = LR*1.03
      y.append(LR)
      lr = str(LR)
      outFy.write(lr)
      outFy.write("\n")
   x.append(i)
   I = str(i)
   outFx.write(I)
   outFx.write("\n")
   step = step + 1000

print(steps)
print(scales)