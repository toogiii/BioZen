import serial

weather = open('weather.txt', 'r')
send = weather.read().lower()
weather.close()
mode = 0

# Modes: Sunny, Cloudy, Rainy, Stormy
if "storm" in send:
    mode = 3
elif "rain" in send:
    mode = 1
#elif "cloud" in send or "fog" in send:
#    mode = 2
elif "partly" in send or "sun" in send or "clear" in send:
    mode = 2


print(mode)
uno = serial.Serial("/dev/ttyUSB1", 9600, timeout = 100)
uno.write(bytes(str(mode) + "\n", "utf-8"))
uno.close()