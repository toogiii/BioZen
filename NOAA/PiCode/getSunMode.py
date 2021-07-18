from astral.sun import sun
from datetime import datetime, timedelta
from astral import Observer
import serial
from time import sleep

"""
import serial
import time
arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=.1)
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data
while True:
    num = input("Enter a number: ") # Taking input from user
    value = write_read(num)
    print(value.rstrip().decode('utf-8')) # printing the value

"""
uno = serial.Serial(port="/dev/ttyACM0", baudrate=9600, timeout = .1)
sunMode = 0
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

    

    if abs(sunrise - current_time) < timedelta(minutes=30):
        sunMode = 4
    elif abs(sunset - current_time) < timedelta(minutes=30):
        sunMode = 6
    elif current_time - sunset > timedelta() or sunrise - current_time > timedelta():
        sunMode = 7
    elif current_time - sunset < timedelta() or sunrise - current_time < timedelta():
        sunMode = 4
    print(bytes(str(sunMode), 'utf-8'))
    uno.write(bytes(str(sunMode) + "\n", "utf-8"))
    data = uno.readline().rstrip().decode('utf8')
    print(data)
    sleep(1)
    
uno.close() 
       
