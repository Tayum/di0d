from django.shortcuts import render
from django.http import JsonResponse
from django.contrib import messages
import datetime

from . import database_management as dbmngm
from . import api as api_module


# a bypass to have an ability to add fields to "object()"
class Object(object):
    pass


db_management = dbmngm.DatabaseManagement()
apis = api_module.ApiFunctions()


def errorpage(request):
    response = render(request, 'bands/404.html', {'status_code': 404, 'request_path': request.path_info})
    response.status_code = 404
    return response


def index(request):
    if request.method == "GET":
        return render(request, 'bands/index.html')
    elif request.method == "POST":
        if request.POST.get("q", "") == "load":
            db_management.load_data()
            messages.success(request, "The data was successfully loaded into the database.")
            return render(request, 'bands/facts.html', {
                          'facts': db_management.read_facts()
            })


def facts(request):
    if request.method == "POST":
        if request.POST.get("q", "") == "delete":
            id = request.POST.get("id", "")
            db_management.delete_fact(id)
            messages.success(request, "The fact with <" + id + "> ID was successfully deleted.")
        if request.POST.get("q", "") == "save":
            id = request.POST.get("id", "")
            # Create new "fact"
            if id == "-1":
                db_management.create_fact(request.POST.get("artist"),
                                          request.POST.get("album"),
                                          request.POST.get("song"),
                                          request.POST.get("year", "") + "-" +
                                          request.POST.get("month", "") + "-" +
                                          request.POST.get("day", ""))
                messages.success(request, "The new fact was successfully created.")
            # Update existing fact
            else:
                db_management.update_fact(id,
                                          request.POST.get("artist"),
                                          request.POST.get("album"),
                                          request.POST.get("song"),
                                          request.POST.get("year", "") + "-" +
                                          request.POST.get("month", "") + "-" +
                                          request.POST.get("day", ""))
                messages.success(request, "The existing fact with <" + id + "> ID was successfully updated.")

    return render(request, 'bands/facts.html', {
        'facts': db_management.read_facts()
    })


def savefact(request):
    now = datetime.datetime.now()
    tables = db_management.read_all_entries()
    # form the fields that are in common for both "update" and "create" queries:
    obj_to_pass = dict()
    obj_to_pass['id_fact'] = -1
    obj_to_pass['artists'] = tables.artists
    obj_to_pass['albums'] = tables.albums
    obj_to_pass['songs'] = tables.songs
    obj_to_pass['dayrange'] = range(1, 32)
    obj_to_pass['monthrange'] = range(1, 13)
    obj_to_pass['yearrange'] = range(1900, now.year + 1)
    # if it's "modify" ("update") query (...):
    if request.GET.get('q', '') == "to_save":
        fact_info = db_management.read_entries("song_releases",
                                               "WHERE id_song_release = " + request.GET.get('id', '-1'))
        # (...) and if there was found a fact with such ID
        if fact_info.rows:
            # Get the fact itself (its fields) without "description" of them
            fact_info = fact_info.rows[0]
            fact_to_update = Object()
            fact_to_update.id_fact = fact_info[0]
            fact_to_update.id_artist = fact_info[1]
            fact_to_update.id_album = fact_info[2]
            fact_to_update.id_song = fact_info[3]
            # fact_info[4] is DATE type field
            fact_to_update.date_release = Object()
            fact_to_update.date_release.year = fact_info[4].year
            fact_to_update.date_release.month = fact_info[4].month
            fact_to_update.date_release.day = fact_info[4].day

            obj_to_pass['id_fact'] = fact_to_update.id_fact
            obj_to_pass['fact_to_update'] = fact_to_update
    # else it's "create new" query (all required fields were
    # already assigned at the top):
    return render(request, 'bands/savefact.html', obj_to_pass)


def entries(request):
    return render(request, 'bands/entries.html')


def albums(request):
    formats = db_management.read_album_formats()
    formats = formats.replace("'", "").split(',')
    return render(request, 'bands/albums.html', {
        'albums': db_management.read_entries("albums", ""),
        'formats': formats
    })


def artists(request):
    return render(request, 'bands/artists.html', {
        'artists': db_management.read_entries("artists", "")
    })


def api(request):
    # search_mode:
    # * 0 - Artists: Text Search (Whole Phrase)
    # * 1 - Artists: Text Search (Mandatory Occurrence)
    # * 10 - Albums: ENUM Search
    # * 100 - Artists: Number Search
    # * 101 - Albums: Number Search
    # * 102 - Songs: Number Search
    object_to_return = None
    if request.GET.get('search_mode', "") == "0" or request.GET.get('search_mode', "") == "1":
        object_to_return = apis.artists__text_search(request)
    elif request.GET.get('search_mode', "") == "10":
        object_to_return = apis.albums__enum(request)
    elif request.GET.get('search_mode', "") == "100":
        object_to_return = apis.entries__number_search(request, "artists", "number_of_members")
    elif request.GET.get('search_mode', "") == "101":
        object_to_return = apis.entries__number_search(request, "albums", "number_of_tracks")
    elif request.GET.get('search_mode', "") == "102":
        object_to_return = apis.entries__number_search(request, "songs", "number_in_album")
    return JsonResponse(object_to_return)
