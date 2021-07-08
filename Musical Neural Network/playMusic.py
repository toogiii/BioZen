import pygame

def play_music(file):
    clock = pygame.time.Clock()
    try:
        pygame.mixer.music.load(file)
    except pygame.error:
        return
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy():
        clock.tick(30)
        
midi_file = r"Evolution of Music/60min.mid"
freq = 44100
bitsize = -16
channels = 2
buffer = 1024
pygame.mixer.init(freq, bitsize, channels, buffer)

pygame.mixer.music.set_volume(1.0)
try:
    play_music(midi_file)
except KeyboardInterrupt:
    pygame.mixer.music.fadeout(1000)
    pygame.mixer.music.stop()
    raise SystemExit