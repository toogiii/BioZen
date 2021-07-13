import os 

lat,lon = os.popen('curl ipinfo.io/loc').read().split(',')

location = open('/home/pi/BioZen/NOAA/PiCode/loc.txt', 'w')
location.write(lat + "\n" + lon)
print(lat, lon)
location.close()