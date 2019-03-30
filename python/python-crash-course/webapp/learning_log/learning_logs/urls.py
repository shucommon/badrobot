"""定义learning_logs的URL模式"""
from django.conf.urls import url
from . import views

app_name = 'learning_logs'

urlpatterns = [
    # 主页
    url(r'^$', views.index, name='index'),
    # show topics
    url(r'^topics/$', views.topics, name='topics'),
    # specific topic
    url(r'^topics/(?P<topic_id>\d+)/$', views.topic, name='topic'),
]
