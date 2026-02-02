import hidapi
import os
import sys

d = hidapi.Device(vendor_id=0xCafe, product_id=0x4004)

while (1):
	b = os.urandom(64)
	d.write(b)
	r = d.read(64)
	if (b != r):
		print("Failed")
	else:
		sys.stdout.write(".")
		sys.stdout.flush()
