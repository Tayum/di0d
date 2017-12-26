#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
from .models import *
from django.apps import apps

dir_path = r"C:\\Users\\Student\\Documents\\Different\\Course_3\\databases_discipline\\projects\\lab3\\"
artists_path = dir_path + "artists.xml"
albums_path = dir_path + "albums.xml"
songs_path = dir_path + "songs.xml"


class DatabaseManagement:
    # Allowed table_name values: artists / albums / songs /
    # / song_releases (with indices in "Foreign Key" fields as values)
    def read_entries(self, model_name):
        entry_type = apps.get_model('bands', model_name)
        rows = entry_type.objects.values_list()
        col_names = [f.name for f in entry_type._meta.get_fields()]

        # delete a 'songreleases' field (wtf is that?)
        if model_name != "SongReleases":
            col_names.pop(0)

        object_to_return = dict()
        object_to_return['rows'] = rows
        object_to_return['description'] = col_names

        return object_to_return

    def read_all_entries(self):
        object_to_return = dict()

        object_to_return['artists'] = Artists.objects.values_list('id_artist', 'name')
        object_to_return['albums'] = Albums.objects.values_list('id_album', 'name')
        object_to_return['songs'] = Songs.objects.values_list('id_song', 'name')

        return object_to_return

    # song_release (with info inserted into "Foreign Key" fields
    # from corresponding tables as values)
    # SELECT id_song_release, id_artist, id_album, id_song, DATE_FORMAT(date_release, "%Y-%m-%d") FROM song_release;
    def read_facts(self):
        rows = SongReleases.objects.values_list(
            'id_song_release', 'id_artist__name', 'id_album__name', 'id_song__name', 'date_release')

        col_names = [f.name for f in SongReleases._meta.get_fields()]
        object_to_return = dict()
        object_to_return['rows'] = rows
        object_to_return['description'] = col_names

        return object_to_return

    # single song_release entry, selected by id_song_release field
    def read_fact_by_id(self, id_song_release):
        rows = SongReleases.objects.filter(id_song_release=id_song_release).values_list()

        col_names = [f.name for f in SongReleases._meta.get_fields()]

        object_to_return = dict()
        object_to_return['rows'] = rows
        object_to_return['description'] = col_names

        return object_to_return

    def delete_fact(self, id_song_release):
        SongReleases.objects.filter(id_song_release=id_song_release).delete()

    def create_fact(self, id_artist, id_album, id_song, date_release):
        artist = Artists.objects.get(id_artist=id_artist)
        album = Albums.objects.get(id_album=id_album)
        song = Songs.objects.get(id_song=id_song)

        SongReleases.objects.create(id_artist=artist, id_album=album,
                                    id_song=song, date_release=date_release)

    def update_fact(self, id_fact, id_artist, id_album, id_song, date_release):
        SongReleases.objects.filter(id_song_release=id_fact).update(id_artist=id_artist, id_album=id_album,
                                                                    id_song=id_song, date_release=date_release)

    # @TODO read them properly from database?
    def read_album_formats(self):
        formats = ["EP", "Studio", "Live"]
        return formats


