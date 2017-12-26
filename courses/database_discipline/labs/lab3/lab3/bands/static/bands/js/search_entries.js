$(function() {
  $('#id_search_form').on('submit', function(event) {
    event.preventDefault();

    // 100 is "Artists (number of members)"
    // 101 is "Albums (number of tracks)"
    // 102 is "Songs (number in album)"
    var search_mode = $('#id_search_mode');
    search_mode = search_mode.val();
    var search_query_min = $('#id_search_query_min');
    search_query_min = search_query_min.val();
    var search_query_max = $('#id_search_query_max');
    search_query_max = search_query_max.val();
    $.ajax({
      url: '/bands/api/?search_mode=' + search_mode + '&min=' + search_query_min + '&max=' + search_query_max,
      method: 'GET',
      dataType: 'json',
      contentType: 'application/json',
      success: function(results) {
        var template = document.getElementById("search_script").innerHTML;
        var renderedHTML = null;
        var isEmpty = results.empty;
        if (isEmpty) {
          renderedHTML = Mustache.render(template, {
            empty: true
          });
        }
        else {
          // columns_infoes is object, that has array of objects with the only field inside: "name" (which is name of the column)
          var columns_infoes = results.columns_infoes;
          var entries_type = results.entries_type;
          // 100 is "Artists"
          // 101 is "Albums"
          // 102 is "Songs"
          switch(entries_type) {
              case "100":
                var artists = results.entries;
                renderedHTML = Mustache.render(template, {
                  columns_infoes: columns_infoes,
                  artists: artists,
                  empty: false
                });
                break;
              case "101":
                var albums = results.entries;
                renderedHTML = Mustache.render(template, {
                  columns_infoes: columns_infoes,
                  albums: albums,
                  empty: false
                });
                break;
              case "102":
                var songs = results.entries;
                renderedHTML = Mustache.render(template, {
                  columns_infoes: columns_infoes,
                  songs: songs,
                  empty: false
                });
                break;
              default:
                renderedHTML = Mustache.render(template, {
                  empty: true
                });
                break;
          }
        }
        document.getElementById("search_result").innerHTML = renderedHTML;
      },
      error: function(XMLHttpRequest, textStatus, errorThrown) {
        var template = document.getElementById("search_script").innerHTML;
        var renderedHTML = Mustache.render(template, {
          empty: true
        });
        document.getElementById("search_result").innerHTML = renderedHTML;
      }
    });
  });
});
