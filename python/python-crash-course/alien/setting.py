class Settings():
    """ store alien invasion all settings """

    def __init__(self):
        """ init game setting """
        # screen setting
        self.screen_width = 1200
        self.screen_height = 800
        self.bg_color = (230, 230, 230)

        # ship setting
        self.ship_speed_factor = 3.5
        self.ship_limit = 3

        # bullet setting
        self.bullet_speed_factor = 5
        self.bullet_width = 3
        self.bullet_height = 15
        self.bullet_color = 60, 60, 60
        self.bullets_allowed = 10

        # alien setting
        self.alien_speed_factor = 1
        self.fleet_drop_speed = 100
        # fleet_direction 1 move right, -1 left
        self.fleet_direction = 1
