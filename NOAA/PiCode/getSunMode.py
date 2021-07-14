from astral.sun import sun
from datetime import datetime, timedelta
from astral import Observer
import serial
from time import sleep



while True:
    uno = serial.Serial("/dev/ttyUSB1", 115200, timeout = 1)
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
        sunMode = '6'
    elif abs(sunset - current_time) < timedelta(minutes=30):
        sunMode = '7'
    elif current_time - sunset > timedelta() or sunrise - current_time > timedelta():
        sunMode = '8'
    elif current_time - sunset < timedelta() or sunrise - current_time < timedelta():
        sunMode = '9'
        print(sunMode)
    sleep(10)
    uno.write(bytes((sunMode + "\n"), "utf-8"))
    uno.close()    
