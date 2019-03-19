import pygame

class Music():
    def __init__(self):
        self.bgm_name = "music/bgm.mp3"
        #self.boom_name = "music/boom.mp3"
        self.boom_name = "music/boom.wav"
        #self.bullet_name = "music/bullet.mp3"
        self.bullet_name = "music/bullet.wav"

        self.init_sound()

    def init_sound(self):
        pygame.mixer.music.load(self.bgm_name)
        self.boom = pygame.mixer.Sound(self.boom_name)
        self.bullet = pygame.mixer.Sound(self.bullet_name)

    def play_bgm(self):
        # -1 plays infinitely
        pygame.mixer.music.play(-1)

    def pause_bgm(self):
        # -1 plays infinitely
        pygame.mixer.music.pause()

    def unpause_bgm(self):
        # -1 plays infinitely
        pygame.mixer.music.unpause()

    def stop_bgm(self):
        pygame.mixer.music.stop()

    def play_boom(self):
        pygame.mixer.Sound.play(self.boom)

    def play_bullet(self):
        pygame.mixer.Sound.play(self.bullet)

