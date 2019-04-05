from django.db import models
from django.contrib.auth.models import User

# Create your models here.
class Topic(models.Model):
    """ user study theme """
    text = models.CharField(max_length=200)
    date_added = models.DateTimeField(auto_now_add=True)
    owner = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        """ return model char description """
        return self.text

class Entry(models.Model):
    """ a specific knowledge about a theme """
    topic = models.ForeignKey(Topic, on_delete=models.CASCADE)
    #topic = models.ForeignKey(Topic, on_delete=models.DO_NOTHING)
    text = models.TextField()
    date_added = models.DateTimeField(auto_now_add=True)

    class Meta:
        verbose_name_plural = 'entries'

    def __str__(self):
        if len(self.text) > 50:
            return self.text[:50] + "..."
        else:
            return self.text[:50]
