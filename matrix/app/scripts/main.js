console.log('Starting Matrix Puzzle');

$("#content-container").on('click', 'a', function(e) { // delegate events
	//$(this).parent().html('<a href="#">A New link</a>');
	// $(this).load("snip.html#snip1");  // try to load only div from file - doesn't work
	//$(this).load("snip.html"); 
	$(this).load("snip.html"); 
	e.preventDefault();
});


/*$(document).ready(function() {
	console.log("document ready!");

    //$("#list a").on("click", function(event) { // Attach a directly bound event handler
        // attached to each "#list a" at doc ready, but not to extra ones added afterwards
	$("#list").on("click", "a", function(event) { // event delegated to "#list" catches those appended "a"s
	    event.preventDefault();
	    console.log("text(): "+$(this).text());
        console.log("attr(): "+$(this).attr("href")); // http://api.jquery.com/attr/
	    //var elem = $(this); //console.log("getAttribute(): "+elem.getAttribute("href"));
	});

	$("#list").append('<li><a href="#">another one!</a></li>');
    $("#content").load("snip.html"); //$("body").append($.load("snip.html"));
		// can't be done from file on Chrome due to 
		// serve over HTTP e.g. with python -m SimpleHTTPServer
		// or start Chrome with --allow-file-access-from-files
		// http://stackoverflow.com/questions/4819060/allow-google-chrome-to-use-xmlhttprequest-to-load-a-url-from-a-local-file
});*/
