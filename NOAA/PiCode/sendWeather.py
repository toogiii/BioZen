import serial

weather = open('weather.txt', 'r')
send = weather.readlines().lower()
weather.close()
mode = 0

# Modes: Sunny, Cloudy, Rainy, Stormy
if "storm" in send:
    mode = 4
elif "rain" in send:
    mode = 3
elif "mostly cloud" in send or "fog" in send:
    mode = 2
elif "partly" in send or "sun" in send:
    mode = 1

uno = serial.Serial("/dev/ttyUSB1", 115200, timeout = 1)
uno.write(bytes((str(mode) + "\n"), "utf-8"))
uno.close()