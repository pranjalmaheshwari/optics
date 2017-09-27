import matplotlib.pyplot as plt
import sys

if(len(sys.argv) < 2):
	exit(0)
if(len(sys.argv) == 3):
	fac = float(sys.argv[2])
else:
	fac = 1.5

file_name = str(sys.argv[1])
num_elems = -1
counter = 0
max_val = 0.0
vals = []
x_pos = []

with open(file_name) as f:
	for line in f:
		vals.append(float(line.strip()))
		max_val = max(max_val, vals[counter])
		x_pos.append(counter+1)
		counter += 1

for i in range(counter):
	if(vals[i] == -1.0):
		vals[i] = fac*max_val
 
# plt.bar(x_pos, vals, align='center', alpha=0.5)
plt.margins(0.05)
plt.bar(x_pos, vals, color='black')
plt.ylabel('Reachability Distance')
plt.xlabel('Points Number')
plt.title('Reachability Plot')
plt.show()
