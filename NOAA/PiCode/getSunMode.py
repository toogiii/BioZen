from astral.sun import sun
from datetime import datetime, timedelta
from astral import Observer
import serial
from time import sleep

uno = serial.Serial("/dev/ttyUSB1", 9600, timeout = 1)

while True:

    location = open('/home/pi/BioZen/NOAA/PiCode/loc.txt', 'r')
    coords = location.read().split('\n')
    lat = float(coords[0])
    lon = float(coords[1])
    location.close()

    current_time = datetime.now().astimezone()
    obs = Observer(latitude=lat, longitude=lon)
    s = sun(obs, date=current_time, tzinfo=current_time.tzinfo)
    sunrise = s['sunrise']
    sunset = s['sunset']

    sunMode = 0

    if abs(sunrise - current_time) < timedelta(minutes=30):
        sunMode = 'q\n'
    elif abs(sunset - current_time) < timedelta(minutes=30):
        sunMode = 't\n'
    elif current_time - sunset > timedelta() or sunrise - current_time > timedelta():
        sunMode = 'e\n'
    elif current_time - sunset < timedelta() or sunrise - current_time < timedelta():
        sunMode = 'w\n'
    print(bytes((sunMode), "utf-8"))
    uno.write(bytes((sunMode), "utf-8"))
    sleep(7200)
uno.close() 
       
