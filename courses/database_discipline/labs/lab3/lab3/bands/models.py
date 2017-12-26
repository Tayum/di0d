# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey has `on_delete` set to the desired behavior.
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from __future__ import unicode_literals

from django.db import models


class Albums(models.Model):
    id_album = models.AutoField(primary_key=True)
    name = models.CharField(max_length=50, blank=True, null=True)
    format = models.CharField(max_length=6, blank=True, null=True)
    number_of_tracks = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'albums'


class Artists(models.Model):
    id_artist = models.AutoField(primary_key=True)
    name = models.CharField(max_length=50, blank=True, null=True)
    number_of_members = models.IntegerField(blank=True, null=True)
    description = models.TextField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'artists'


class SongReleases(models.Model):
    id_song_release = models.AutoField(primary_key=True)
    id_artist = models.ForeignKey(Artists, models.DO_NOTHING, db_column='id_artist')
    id_album = models.ForeignKey(Albums, models.DO_NOTHING, db_column='id_album')
    id_song = models.ForeignKey('Songs', models.DO_NOTHING, db_column='id_song')
    date_release = models.DateField()

    class Meta:
        managed = True
        db_table = 'song_releases'


class Songs(models.Model):
    id_song = models.AutoField(primary_key=True)
    name = models.CharField(max_length=50, blank=True, null=True)
    number_in_album = models.IntegerField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'songs'
