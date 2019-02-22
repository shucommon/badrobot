import struct

# if input is string, per @robyschek will fail on python 3
#data=b'\x64\xd8\x64\x3f'
data=b'\xd7*\x7fD[L*\xc2\x81J\x85\xc5' # 12 bytes = 3 float
print struct.unpack('<fff', data)   #little endian
#print struct.unpack('>f', data[0,3])   # big endian
