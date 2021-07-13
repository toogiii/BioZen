import serial
import subprocess
mode = 0
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
import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library
GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
GPIO.setup(40, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.setup(13, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(7, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(12, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
while True: # Run forever
    if GPIO.input(13) == GPIO.HIGH:
        print("Button 5 was pushed!")
        mode = 5
        subprocess.call('/home/pi/BioZen/NOAA/PiCode/weatherMode.sh', shell=True)
    else:
        if GPIO.input(40) == GPIO.HIGH:
            print("Button 4 was pushed!")
            mode = 4
        elif GPIO.input(7) == GPIO.HIGH:
            print("Button 3 was pushed!")
            mode = 3
        elif GPIO.input(10) == GPIO.HIGH:
            print("Button 2 was pushed!")
            mode = 2
        elif GPIO.input(12) == GPIO.HIGH:
            print("Button 1 was pushed!")
            mode = 1
        #uno = serial.Serial("/dev/ttyUSB1", 115200, timeout = 1)
        #uno.write(bytes(str(mode) + "\n"), "utf-8")
        #uno.close()
        
