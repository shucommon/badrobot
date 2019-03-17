import pygame
from pygame.sprite import Sprite

class Alien(Sprite):
    def __init__(self, ai_setting, screen):
        super(Alien, self).__init__()
        self.screen = screen
        self.ai_setting = ai_setting

        # load ship image, get it's rect info
        self.image = pygame.image.load('images/alien.bmp')
        self.rect = self.image.get_rect()

        # alien is around top left at first
        self.rect.x = self.rect.width
        self.rect.y = self.rect.height

        # store alien accurate position
        self.x = float(self.rect.x)

    def check_edges(self):
        """ if alien is in screen edge, return True """
        screen_rect = self.screen.get_rect()
        if self.rect.right >= screen_rect.right:
            return True
        elif self.rect.left <= 0:
            return True

    def update(self):
        """ move right or left of the alien """
        self.x += (self.ai_setting.alien_speed_factor * self.ai_setting.fleet_direction)
        self.rect.x = self.x

    def blitme(self):
        """ print ship in set position """
        self.screen.blit(self.image, self.rect)
