import serial
import subprocess

ts = serial.Serial("/dev/ttyUSB1", 28800, timeout = 1)
mode = '0'
while True:
    try:
        ser_bytes = nano.readline()
        mode = ser_bytes[0:len(ser_bytes - 2)].decode('utf-8')
    except:
        print("Keyboard Interrupt")
        break
    if (mode == '5'):
        subprocess.call("./weatherMode.sh", shell=True)
    else:
        uno = serial.Serial("/dev/ttyUSB1", 115200, timeout = 1)
        uno.write(bytes((mode + "\n"), "utf-8"))
        uno.close()    

