from django.conf.urls import url

from . import views


app_name = 'bands'
urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^facts/$', views.facts, name='facts'),
    url(r'^savefact/$', views.savefact, name='savefact'),
    url(r'^entries/$', views.entries, name='entries'),
    url(r'^albums/$', views.albums, name='albums'),
    url(r'^artists/$', views.artists, name='artists'),
    url(r'^api/$', views.api, name='api')

]
