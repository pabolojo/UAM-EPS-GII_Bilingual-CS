#! /usr/bin/python3

import os
import sys
import mmap

file_list = {}

if len(sys.argv) < 2:
	print("Error")
	exit(1)

print("Files which contains {}".format(sys.argv[1]))

for path, subdirs, files in os.walk("."):
    for name in files:
    	file_name = os.path.join(path, name)
    	if os.stat(file_name).st_size != 0:
	    	with open(file_name, 'rb', 0) as file, mmap.mmap(file.fileno(), 0, access=mmap.ACCESS_READ) as f:
	    		lines = f.read().split(b'\n')
	    		for i, line in enumerate(lines):
	    			index = line.lower().find(bytes(sys.argv[1].lower(), 'utf-8'))
	    			if index != -1:
	    				print("[{}]{}\t{}".format(i + 1, file_name, str(line[max(index-10, 0):min(index+len(sys.argv[1].lower()) + 10, len(line))])[1:]))
	    				if file_name not in file_list:
	    					file_list[file_name] = []
	    				file_list[file_name].append(i)
    					
print("\n\nRemove lines? [y/n]")
if sys.stdin.readline() != "y\n":
	exit(1)

print("Removing...")
for file_name in file_list:
	file_r = open(file_name, "r")
	lines = []
	with open(file_name, 'rb', 0) as file, mmap.mmap(file.fileno(), 0, access=mmap.ACCESS_READ) as f:
		lines = f.read().split(b'\n')
		
	file_w = open(file_name, "wb")
	for i, line in enumerate(lines):
		if i not in file_list[file_name]:
			file_w.write("{}\n".format(line.decode('utf-8')).encode('utf-8'))
	file_w.close()
	
print("Done!")
