import serial
import subprocess
from time import sleep
from astral.sun import sun
from datetime import datetime, timedelta
from astral import Observer
import serial
from time import sleep
mode = 0
sunMode = 0
import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library
GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
GPIO.setup(40, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.setup(13, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(7, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(12, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(36, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
process = None
sent = False
uno = serial.Serial("/dev/ttyUSB1", 9600, timeout = 100)
while True: # Run forever\]
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
        sunMode = 4
    elif current_time - sunset < timedelta() or sunrise - current_time < timedelta():
        sunMode = 5
    print(bytes(str(sunMode), 'utf-8'))
    uno.write(bytes(str(sunMode) + "\n", "utf-8"))
    data = uno.readline().rstrip().decode('utf8')
    print(data)
    if GPIO.input(13) == GPIO.HIGH:
        while GPIO.input(13) == GPIO.HIGH:
            pass
        print("Button 5 was pushed!")
        sent = False
        mode = 0
        process = subprocess.Popen('/home/pi/BioZen/NOAA/PiCode/weatherMode.sh', shell=True)
    else:
        if process != None:
            process.terminate()
        if GPIO.input(40) == GPIO.HIGH:
            while GPIO.input(40) == GPIO.HIGH:
                pass
            print("Button 4 was pushed!")
            sent = False
            mode = 3
        elif GPIO.input(7) == GPIO.HIGH:
            while GPIO.input(7) == GPIO.HIGH:
                pass
            print("Button 3 was pushed!")
            sent = False
            mode = 1
        elif GPIO.input(10) == GPIO.HIGH:
            while GPIO.input(10) == GPIO.HIGH:
                pass
            print("Button 2 was pushed!")
            sent = False
            mode = 8
        elif GPIO.input(12) == GPIO.HIGH:
            while GPIO.input(12) == GPIO.HIGH:
                pass
            print("Button 1 was pushed!")
            sent = False
            mode = 2
        elif GPIO.input(36) == GPIO.HIGH:
            while GPIO.input(36) == GPIO.HIGH:
                pass
            print("RAINBOW MODE!")
            sent = False
            mode = 9
        if mode > 0 and not sent:
            uno.write(bytes(str(mode) + "\n", "utf-8"))
            sleep(1)
            data = uno.readline().rstrip().decode('utf8')
            print(data)
            sent = True
uno.close()