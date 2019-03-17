class GameStats():
    def __init__(self, ai_setting):
        """ init stat """
        self.ai_setting = ai_setting
        self.game_active = True
        self.reset_stats()

    def reset_stats(self):
       """ init stat may changes during game """
       self.ships_left = self.ai_setting.ship_limit
