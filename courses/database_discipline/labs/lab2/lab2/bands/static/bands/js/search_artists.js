$(function() {
  $('#id_search_form').on('submit', function(event) {
    event.preventDefault();
    // 0 is "Whole Phrase",
    // 1 is "Mandatory Occurrence"
    var search_mode = $('#id_search_mode');
    search_mode = search_mode.val();
    var search_query = $('#id_search_query');
    search_query = search_query.val();
    $.ajax({
      url: '/bands/api/?search_mode=' + search_mode + '&query=' + search_query,
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
          var artists = results.artists;
          renderedHTML = Mustache.render(template, {
            artists: artists,
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
