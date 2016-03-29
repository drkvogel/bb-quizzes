// >json and a javascript object are two different things, they just look the same.
// json must have **double** quotes for key **and** value, no comments 

        //console.log(data.pages);
        //console.log(data.pages.length);
        // for (var i=0; i<data.pages.length; i++) { // array iterate
        //     console.log(data.pages[i].template);
        //     console.log(data.pages[i].sheet);
        //     console.log(JSON.stringify(data.pages[i], null, 4)); // null, 4 args tell it to indent with 4 spaces
        // }

// jquery fail
// .fail(function (jqxhr, textStatus, errorThrown) { // jqxhr not needed here, but position of args important, not name
//     var err = 'error setting CSS: ' + textStatus + ", errorThrown: " + errorThrown;
//     console.log(err);
// });


/*
pages config format
n.b. don't put comments in actual JSON! Not allowed: http://stackoverflow.com/questions/244777/can-i-use-comments-inside-a-json-file?rq=1
//pages = $.parseJSON(data); // not necessary, .getJSON() returns parsed JSON
//for (var page in data) // list iterate
            window.alert(err);
        //data = NaN;

    var obj = jQuery.parseJSON( '{ "name": "John" }' );
    alert( obj.name === "John" );

    {
        "template": "",     // html template div to use (intro1-3, 2x2, 3x3, thanks, abandon etc)
        "sheet": "",        // sprite sheet to use
        "images": {         // indices into sprite sheet
            "top": [],      // top grid, where applicable
            "bottom": []    // bottom grid, where applicable
        } 
        "answer": -1,       // player's answer
        "correct": -1       // correct answer, -1 if not applicable (non-question page)
    },

    {
        "template": "",
        "sheet": "",  
        "images": {
            "top": [],
            "bottom": []
        }
        "answer": -1,
        "correct": -1
    },

*/


        //var page = $.get('./pages/pages.html', function(data) {$('#content-container').html($(data).filter('#intro2')); });
        // var page = $.get('./pages/pages.html', function(data) {
        //  $('#content-container').html($(data).filter('#intro2')); // gets whole page and then filters, not optimal
        // });

    // <div class='js-include' title='nav.html'></div>
    // $('.js-include').each(function(){
    //     var inc=$(this);
    //     $.get(inc.attr('title'), function(data){
    //         inc.replaceWith(data);
    //     });
    // });

    // replaceWith() will replace the current element, whereas html() simply replaces the contents.
    // Note that the replaceWith() will not actually delete the element but simply remove it from the DOM and return it to you in the collection.

        //$(this).parent().html('<a href='#'>A New link</a>');
        // $(this).load('snip.html#snip1');  // try to load only div from file - doesn't work
        //$(this).load('snip.html');
        //switch ($('.page').


    /*$(document).ready(function() {
        console.log('document ready!');

        //$('#list a').on('click', function(event) { // Attach a directly bound event handler
            // attached to each '#list a' at doc ready, but not to extra ones added afterwards
        $('#list').on('click', 'a', function(event) { // event delegated to '#list' catches those appended 'a's
            event.preventDefault();
            console.log('text(): '+$(this).text());
            console.log('attr(): '+$(this).attr('href')); // http://api.jquery.com/attr/
            //var elem = $(this); //console.log('getAttribute(): '+elem.getAttribute('href'));
        });

        $('#list').append('<li><a href='#'>another one!</a></li>');
        $('#content').load('snip.html'); //$('body').append($.load('snip.html'));
            // can't be done from file on Chrome due to
            // serve over HTTP e.g. with python -m SimpleHTTPServer
            // or start Chrome with --allow-file-access-from-files
            // http://stackoverflow.com/questions/4819060/allow-google-chrome-to-use-xmlhttprequest-to-load-a-url-from-a-local-file
    });*/


    // http://www.attackofdesign.com/using-jquery-to-include-files/

    // <div class='js-include' title='nav.html'></div>

    // js-include is simply a class name that we'll assign to every element that should trigger the include. And nav.html is the relative URL of the file that we're including.
    // Now, let's take a look at the jQuery code:

    // $('.js-include').each(function(){
    //     var inc=$(this);
    //     $.get(inc.attr('title'), function(data){
    //         inc.replaceWith(data);
    //     });
    // });
    // The first line just tells the script to execute the function once of each element that has the class js-include.
    // We then store the current element inside a variable
    // We use jQuery's get function with the following arguments: the div's title as the URL of the file to load, and a callback function
    // The callback function replaces the current DIV with the content that we just loaded.
