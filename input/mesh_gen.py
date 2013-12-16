import os

size = 100

with open('mesh.co', 'w') as co_file:
	co_file.write("p aux sp co ")
	co_file.write(str(size**2) + os.linesep)
	for y in xrange(size):
		for x in xrange(size):
			point = x + y * size
			point += 1
			co_file.write("v {0} {1} {2}".format(point, x, y) + os.linesep)

with open('mesh.gr', 'w') as gr_file:
	for y in xrange(size):
		for x in xrange(size):
			point = x + y * size
			point += 1
			if x != 0:
				gr_file.write("a {0} {1} 666".format(point - 1, point) + os.linesep) 
				gr_file.write("a {0} {1} 666".format(point, point - 1) + os.linesep) 
			if y != 0:
				gr_file.write("a {0} {1} 666".format(point - size, point) + os.linesep) 
				gr_file.write("a {0} {1} 666".format(point, point - size) + os.linesep) 