#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import MySQLdb as mdb

dir_path = r"C:\\Users\\Student\\Documents\\Different\\Course_3\\databases_discipline\\projects\\lab2\\"
artists_path = dir_path + "artists.xml"
albums_path = dir_path + "albums.xml"
songs_path = dir_path + "songs.xml"


# a bypass to have an ability to add fields to "object()"
class Object(object):
    pass


class DatabaseManagement:
    def __init__(self):
        self.connection = None

    def _open_connection(self):
        try:
            self.connection = mdb.connect('localhost', 'test', 'test1', 'bands')
        except mdb.Error as e:
            print("Error %d: %s" % (e.args[0], e.args[1]))
            sys.exit(1)

    def _close_connection(self):
        if self.connection:
            self.connection.close()

    def load_data(self):
        self._open_connection()

        with self.connection:
            cursor = self.connection.cursor()
            cursor.execute("DROP TABLE IF EXISTS song_releases")
            cursor.execute("TRUNCATE TABLE artists")
            cursor.execute("TRUNCATE TABLE albums")
            cursor.execute("TRUNCATE TABLE songs")
            cursor.execute("CREATE TABLE song_releases ("
                           "id_song_release INT PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                           "id_artist INT NOT NULL,"
                           "id_album INT NOT NULL,"
                           "id_song INT NOT NULL,"
                           "date_release DATE NOT NULL,"
                           "CONSTRAINT FK_Artist FOREIGN KEY(id_artist) "
                           "REFERENCES artists(id_artist),"
                           "CONSTRAINT FK_Album FOREIGN KEY(id_album) "
                           "REFERENCES albums(id_album),"
                           "CONSTRAINT FK_Song FOREIGN KEY(id_song) "
                           "REFERENCES songs(id_song)"
                           ")")
            cursor.execute("LOAD XML LOCAL INFILE '" + artists_path + "' "
                           "INTO TABLE artists "
                           "ROWS IDENTIFIED BY '<artist>'")
            cursor.execute("LOAD XML LOCAL INFILE '" + albums_path + "' "
                           "INTO TABLE albums "
                           "ROWS IDENTIFIED BY '<album>'")
            cursor.execute("LOAD XML LOCAL INFILE '" + songs_path + "' "
                           "INTO TABLE songs "
                           "ROWS IDENTIFIED BY '<song>'")

        self._close_connection()

    # Allowed table_name values: artist / album / song /
    # / song_release (with indices in "Foreign Key" fields as values)
    # options is a string that specifies options for performing "Search"
    # e.g. (for artists table): "WHERE members>2 AND members<5"
    def read_entries(self, table_name, options):
        self._open_connection()

        with self.connection:
            cursor = self.connection.cursor()
            query = "SELECT * FROM " + table_name
            if options:
                query += " " + options
            cursor.execute(query)

            all_descriptions = cursor.description
            rows = cursor.fetchall()
            col_names = []
            for desc in all_descriptions:
                col_names.append([desc[0]])

            object_to_return = Object()
            object_to_return.rows = rows
            object_to_return.description = col_names

        self._close_connection()
        return object_to_return

    def read_all_entries(self):
        self._open_connection()

        with self.connection:
            cursor = self.connection.cursor()
            object_to_return = Object()

            cursor.execute("SELECT id_artist, name FROM artists")
            object_to_return.artists = cursor.fetchall()
            cursor.execute("SELECT id_album, name FROM albums")
            object_to_return.albums = cursor.fetchall()
            cursor.execute("SELECT id_song, name FROM songs")
            object_to_return.songs = cursor.fetchall()

        self._close_connection()
        return object_to_return

    # song_release (with info inserted into "Foreign Key" fields
    # from corresponding tables as values)
    # SELECT id_song_release, id_artist, id_album, id_song, DATE_FORMAT(date_release, "%Y-%m-%d") FROM song_release;
    def read_facts(self):
        self._open_connection()

        with self.connection:
            cursor = self.connection.cursor()
            cursor.execute("SELECT song_releases.id_song_release, "
                           "artists.name, albums.name, songs.name, song_releases.date_release "
                           "FROM (((song_releases "
                           "INNER JOIN artists ON song_releases.id_artist=artists.id_artist) "
                           "INNER JOIN albums ON song_releases.id_album=albums.id_album) "
                           "INNER JOIN songs ON song_releases.id_song=songs.id_song)")

            all_descriptions = cursor.description
            rows = cursor.fetchall()
            col_names = []
            for desc in all_descriptions:
                col_names.append([desc[0]])

            object_to_return = Object()
            object_to_return.rows = rows
            object_to_return.description = col_names

        self._close_connection()
        return object_to_return

    def delete_fact(self, id_song_release):
        self._open_connection()

        with self.connection:
            cursor = self.connection.cursor()
            cursor.execute("DELETE FROM song_releases WHERE id_song_release = " + id_song_release)

        self._close_connection()

    def create_fact(self, id_artist, id_album, id_song, date_release):
        self._open_connection()

        with self.connection:
            cursor = self.connection.cursor()
            cursor.execute("INSERT INTO song_releases (id_artist, id_album, id_song, date_release) " +
                           "VALUES(" + id_artist +
                           "," + id_album +
                           "," + id_song +
                           ",'" + date_release + "')")

        self._close_connection()

    def update_fact(self, id_fact, id_artist, id_album, id_song, date_release):
        self._open_connection()

        with self.connection:
            print(date_release)
            cursor = self.connection.cursor()
            cursor.execute("UPDATE song_releases SET "
                           "id_artist = " + id_artist +
                           ", id_album = " + id_album +
                           ", id_song = " + id_song +
                           ", date_release = '" + date_release + "' " +
                           "WHERE id_song_release = " + id_fact)

        self._close_connection()

    def read_album_formats(self):
        self._open_connection()

        with self.connection:
            cursor = self.connection.cursor()
            cursor.execute("SELECT TRIM(TRAILING ')' "
                           "FROM TRIM(LEADING '(' "
                           "FROM TRIM(LEADING 'enum' "
                           "FROM column_type))) "
                           "column_type "
                           "FROM  information_schema.columns "
                           "WHERE table_schema = 'bands' AND table_name = 'albums' AND column_name = 'format'")
            # A string with all possible ENUM values of "format" field
            formats = cursor.fetchall()[0][0].decode("utf-8")

        self._close_connection()
        return formats
