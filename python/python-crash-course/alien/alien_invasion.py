import pygame
from setting import Settings
from ship import Ship
import game_functions as gf
from pygame.sprite import Group
from game_stats import GameStats
from button import Button
from scoreboard import Scoreboard

def run_game():
    pygame.init()
    ai_setting = Settings()
    screen = pygame.display.set_mode((ai_setting.screen_width, ai_setting.screen_height))
    pygame.display.set_caption("Alien Invasion")
    ship = Ship(ai_setting, screen)
    bullets = Group()
    aliens = Group()
    stats = GameStats(ai_setting)
    sb = Scoreboard(ai_setting, screen, stats)

    gf.create_fleet(ai_setting, screen, ship, aliens)

    play_button = Button(ai_setting, screen, "Play")

    while True:
        gf.check_events(ai_setting, screen, stats, sb, play_button, ship, aliens, bullets)
        if stats.game_active:
            ship.update()
            gf.update_bullets(ai_setting, screen, stats, sb, ship, aliens, bullets)
            gf.update_aliens(ai_setting, screen, stats, sb, ship, aliens, bullets)

        gf.update_screen(ai_setting, screen, stats, sb, ship, aliens, bullets, play_button)


run_game()
