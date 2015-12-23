

myfile = open("somebigfile.txt", "w")

BIG = 20000000 # -> 1.5 Gb
MEDIUM = 5000000 # -> 330 Mb
SMALL_TO_MEDIUM = 10000;
SMALL = 100 # Kb ...

for i in range(BIG):
	myfile.write(str(i) * 10)

myfile.close()
