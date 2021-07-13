from noaa_sdk import NOAA

n = NOAA()

location = open('loc.txt', 'r')
coords = location.read().split('\n')
lat = float(coords[0])
lon = float(coords[1])
location.close()

weather = open('weather.txt', 'w')

observations = n.get_observations_by_lat_lon(lat, lon)
for observation in observations:
    print(observation['textDescription'])
    weather.write(observation['textDescription'])
    break

weather.close()