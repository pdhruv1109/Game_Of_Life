#!/usr/bin/env python

import os
import sys

k = 1
while k < 17:
	if k == 3:
		k = k - 1
	if k == 10 or k == 14:
		k = k + 2
	for j in range(8, 12):	
		if os.fork() == 0:
			os.execv("a.out", ["a.out", str(1000), str(1000), str(2**j), str(k)])
		else:
			os.wait()
	k = k + 2
