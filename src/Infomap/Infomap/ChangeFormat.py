#__author__ = 'cheyulin'

import sys

print 'Your Params:'
for i in range(1, len(sys.argv)):
    print "param", i, sys.argv[i]
filename = '/home/cheyulin/ClionProjects/Community-detection/input/com-amazon.ungraph.txt'
filename2 = '/home/cheyulin/ClionProjects/Community-detection/input/modified.txt'
try:
    readfile = open(sys.argv[1])
    writefile = open(sys.argv[2], 'w')
    lines = readfile.readlines()
except IOError as e:
    print e
else:
    for line in lines:
        if not line.startswith('#'):
            # print line
            line = line.replace('\r', '').replace('\n', '') + '\t' + '1' + '\n'
            # print line
            writefile.write(line)
finally:
    readfile.close()
    writefile.close()
print 'finished'
