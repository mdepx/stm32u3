import hidapi

d = hidapi.Device(vendor_id=0xCafe, product_id=0x4004)

b = b'033'

d.write(b)

print("Return: %s" % d.read(3))
