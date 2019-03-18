class GameStats():
    def __init__(self, ai_setting):
        """ init stat """
        self.high_score = 0
        self.ai_setting = ai_setting
        self.game_active = False
        self.reset_stats()

    def reset_stats(self):
       """ init stat may changes during game """
       self.ships_left = self.ai_setting.ship_limit
       self.score = 0
       self.level = 1
