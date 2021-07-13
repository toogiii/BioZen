import datetime
from astral.sun import sun
from datetime import datetime
from astral import Observer

uno = serial.Serial("/dev/ttyUSB1", 115200, timeout = 1)


location = open('loc.txt', 'r')
coords = location.read().split('\n')
lat = float(coords[0])
lon = float(coords[1])
location.close()

current_time = datetime.now().astimezone()
obs = Observer(latitude=lat, longitude=lon)
s = sun(obs, date=current_time, tzinfo=current_time.tzinfo)
sunrise = s['sunrise']
sunset = s['sunset']

sun = 0

if abs(sunrise - current_time) < 30:
    sun = 6
elif abs(sunset - current_time) < 30:
    sun = 7
elif current_time - sunset > 0 or sunrise - current_time > 0:
    sun = 8
elif current_time - sunset < 0 or sunrise - current_time < 0:
    sun = 9
    
uno.write(bytes((sun + "\n"), "utf-8"))
uno.close()    
