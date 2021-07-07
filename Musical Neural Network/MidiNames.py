import glob
files = []
for filename in glob.iglob(r'C:\Users\garvg\Downloads\CymaticsLofiToolkit-V1-m2d\Cymatics - Lofi Toolkit\MIDI\*', recursive=True):
    files.append(filename[81:])

print('"' + '",\n"'.join(files) + '"')
#C:\Users\garvg\Downloads\CymaticsLofiToolkit-V1-m2d\Cymatics - Lofi Toolkit\MIDI\