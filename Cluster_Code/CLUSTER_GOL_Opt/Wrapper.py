#!/usr/bin/env python

import os
import sys
for j in range(8, 12):	
	if os.fork() == 0:
		os.execv("a.out", ["a.out", str(1000), str(1000), str(2**j)])
	else:
		os.wait()
