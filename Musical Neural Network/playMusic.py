import pygame
import inference

def play_music(composer):
    composer.compose_music("out.mid")
    clock = pygame.time.Clock()
    try:
        pygame.mixer.music.load("out.mid")
    except pygame.error:
        return
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy():
        clock.tick(30)
    
while True:
    gan_composer = inference.get_composer(r"C:\Users\garvg\OneDrive\Documents\GitHub\BioZen\Musical Neural Network\Lambdas\210min.params")
    freq = 44100
    bitsize = -16
    channels = 2
    buffer = 1024
    pygame.mixer.init(freq, bitsize, channels, buffer)
    
    pygame.mixer.music.set_volume(1.0)
    try:
        play_music(gan_composer)
    except KeyboardInterrupt:
        pygame.mixer.music.fadeout(1000)
        pygame.mixer.music.stop()
        raise SystemExit