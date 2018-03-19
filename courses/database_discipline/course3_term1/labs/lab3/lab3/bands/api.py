from .models import *
from django.apps import apps
import bands.database_management as dbmngm


db_management = dbmngm.DatabaseManagement()


class SearchAPI:
    # search_mode is        0               1
    # type of search is     Whole Phrase    Mandatory Occurrence
    # * Artists: Text Search
    @staticmethod
    def artists__text_search(request):
        empty = True
        # words to operate "Search" functions with
        query = request.GET.get('query', "")

        search_mode = request.GET.get('search_mode', "")
        artists_arr = dict()
        if query != "":
            # @TODO Check: does this work properly?
            if search_mode == "0":
                artists_arr['rows'] = Artists.objects.filter(description__search="\"" + query + "\"").values_list()
                # artists_arr = db_management.read_entries("artists",
                #                                          "WHERE MATCH (description)"
                #                                          "AGAINST ('\"" + query + "\"' IN BOOLEAN MODE)")
            # @TODO Check: does this work properly?
            elif search_mode == "1":
                artists_arr['rows'] = Artists.objects.filter(description__search="+" + query).values_list()
                # artists_arr = db_management.read_entries("artists",
                #                                          "WHERE MATCH (description)"
                #                                          "AGAINST ('+" + query + "' IN BOOLEAN MODE)")
        else:
            artists_arr = db_management.read_entries("Artists")
        if artists_arr['rows']:
            empty = False

        return {
            'artists': list(artists_arr['rows']),
            'empty': empty
        }

    # * Albums: ENUM Search
    @staticmethod
    def albums__enum(request):
        empty = True
        albums_arr = dict()
        format = request.GET.get('format', "")
        if format != "":
            albums_arr['rows'] = Albums.objects.filter(format__iexact=format).values_list()
        else:
            albums_arr = db_management.read_entries("Albums")
        if albums_arr['rows']:
            empty = False

        return {
            'albums': list(albums_arr['rows']),
            'empty': empty
        }

    # For model_name                             Artists               Albums              Songs
    # field_name would be                        number_of_members     number_of_tracks    number_in_album
    # entries_type (check search_entries.js) is  100                   101                 102
    # * Number Search
    @staticmethod
    def entries__number_search(request, model_name):
        empty = True

        # for "entries_type" field check (search_entries.js)
        entries_type = None
        if model_name == "Artists":
            entries_type = "100"
        elif model_name == "Albums":
            entries_type = "101"
        elif model_name == "Songs":
            entries_type = "102"

        min_value = request.GET.get('min', "")
        max_value = request.GET.get('max', "")

        entries_arr = dict()
        if min != "" and max != "":
            # Info itself
            if model_name == "Artists":
                entries_arr['rows'] = Artists.objects.filter(
                    number_of_members__range=(min_value, max_value)).values_list()
            elif model_name == "Albums":
                entries_arr['rows'] = Albums.objects.filter(
                    number_of_tracks__range=(min_value, max_value)).values_list()
            elif model_name == "Songs":
                entries_arr['rows'] = Songs.objects.filter(number_in_album__range=(min_value, max_value)).values_list()

            # Descriptions (of fields)
            entry_type = apps.get_model('bands', model_name)
            entries_arr['description'] = [f.name for f in entry_type._meta.get_fields()]
            # delete a 'songreleases' field (wtf is that?)
            entries_arr['description'].pop(0)
        else:
            entries_arr = db_management.read_entries(model_name)
        if entries_arr['rows']:
            empty = False

        return {
            'entries_type': entries_type,
            'columns_infoes': entries_arr['description'],
            'entries': list(entries_arr['rows']),
            'empty': empty
        }
