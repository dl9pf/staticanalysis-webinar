#!/usr/bin/env python3

import sys
import re

def convert_release():
    skip_flag = False
    for line in sys.stdin:
        line = line.rstrip()
        if not skip_flag:
            if re.search(r'// +remove +doxygen +{', line):
                skip_flag = True
                continue
        else:
            if re.search(r'// +}', line):
                skip_flag = False
            continue
        print(line)

if __name__ == '__main__':
    convert_release()

# end of file
