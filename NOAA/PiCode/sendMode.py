import serial
import subprocess
from time import sleep
mode = 0
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
uno = serial.Serial("/dev/ttyACM0", 9600, timeout = 100)
while True: # Run forever\]
    
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
            mode = 2
        if mode > 0 and not sent:
            uno.write(bytes(str(mode) + "\n", "utf-8"))
            sleep(1)
            #data = uno.readline().rstrip().decode('utf8')
            #print(data)
            sent = True
uno.close()
        

"""
ts = serial.Serial("/dev/ttyUSB0", 38400, timeout = 1)
mode = []
while True:
    #try:
    ser_bytes = ts.readline()
    ser_msg = ser_bytes[0:len(ser_bytes) - 2].decode('utf-8')
    if ser_msg != '':
        mode.append(ser_msg)
    
    except:
        print("Keyboard Interrupt")
        break
    
    if (len(mode)==30 and mode.count('5') > 27):
        #subprocess.call("./weatherMode.sh", shell=True)
        print(mode, 5)
        mode = []
    elif (len(mode)==30):
        #uno = serial.Serial("/dev/ttyUSB1", 115200, timeout = 1)
        #uno.write(bytes(str(int((max(set(mode), key=mode.count)) - 1) + "\n"), "utf-8"))
        #uno.close()
        print(mode)
        print(str(min([int(i) for i in mode])+) + "\n")
        mode = []  
"""
