import os 

lat,lon = os.popen('curl ipinfo.io/loc').read().split(',')

location = open('loc.txt', 'w')
location.write(lat + "\n" + lon)
print(lat, lon)