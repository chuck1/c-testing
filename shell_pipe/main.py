
import struct

def bytes_to_hexstring(b):
    return ''.join(['{:02x}'.format(x) for x in b])

b = struct.pack('fff', 3.14, 2.56, 1.68)

print(bytes_to_hexstring(b))


