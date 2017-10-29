import bands.database_management as dbmngm


db_management = dbmngm.DatabaseManagement()


class ApiFunctions:
    # search_mode is        0               1
    # type of search is     Whole Phrase    Mandatory Occurrence
    # * Artists: Text Search
    @staticmethod
    def artists__text_search(request):
        empty = True
        # words to operate "Search" functions with
        query = request.GET.get('query', "")

        search_mode = request.GET.get('search_mode', "")
        artists_arr = None
        if query != "":
            if search_mode == "0":
                artists_arr = db_management.read_entries("artists",
                                                         "WHERE MATCH (description)"
                                                         "AGAINST ('\"" + query + "\"' IN BOOLEAN MODE)")
            elif search_mode == "1":
                artists_arr = db_management.read_entries("artists",
                                                         "WHERE MATCH (description)"
                                                         "AGAINST ('+" + query + "' IN BOOLEAN MODE)")
        else:
            artists_arr = db_management.read_entries("artists", "")
        if artists_arr.rows:
            empty = False

        return {
            'artists': artists_arr.rows,
            'empty': empty
        }

    # * Albums: ENUM Search
    @staticmethod
    def albums__enum(request):
        empty = True

        format = request.GET.get('format', "")
        if format != "":
            albums_arr = db_management.read_entries("albums", "WHERE format='" + format + "'")
        else:
            albums_arr = db_management.read_entries("albums", "")
        if albums_arr.rows:
            empty = False

        return {
            'albums': albums_arr.rows,
            'empty': empty
        }

    # table_name is                             artists               albums              songs
    # field_name is                             number_of_members     number_of_tracks    number_in_album
    # entries_type (check search_entries.js) is 100                   101                 102
    # * Number Search
    @staticmethod
    def entries__number_search(request, table_name, field_name):
        empty = True

        # for "entries_type" field check (search_entries.js)
        entries_type = None
        if table_name == "artists":
            entries_type = "100"
        elif table_name == "albums":
            entries_type = "101"
        elif table_name == "songs":
            entries_type = "102"

        min_value = request.GET.get('min', "")
        max_value = request.GET.get('max', "")

        if min != "" and max != "":
            entries_arr = db_management.read_entries(table_name,
                                                     "WHERE " + field_name + ">" + min_value +
                                                     " AND " + field_name + "<" + max_value)
        else:
            entries_arr = db_management.read_entries(table_name, "")
        if entries_arr.rows:
            empty = False

        return {
            'entries_type': entries_type,
            'columns_infoes': entries_arr.description,
            'entries': entries_arr.rows,
            'empty': empty
        }
