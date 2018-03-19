$(function() {
  $('#id_search_form').on('submit', function(event) {
    event.preventDefault();
    // search_mode is valued "10" through hidden field
    // (check "Search" form in albums.html)
    var search_mode = $('#id_search_mode');
    search_mode = search_mode.val();
    // "Studio", "EP" or "Live" values are valid
    var search_query_type = $('#id_search_query_type');
    search_query_type = search_query_type.val();
    $.ajax({
      url: '/bands/api/?search_mode=' + search_mode + '&format=' + search_query_type,
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
          var albums = results.albums;
          renderedHTML = Mustache.render(template, {
            albums: albums,
            empty: false
          });
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
