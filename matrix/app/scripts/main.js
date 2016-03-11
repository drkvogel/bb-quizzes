/*global $ */

/*jslint node: true */

(function () { // Immediately-Invoked Function Expression (IIFE)
    // used to set "use strict" for whole scope so jslint doesn't complain
    // but then have to indent whole scope...
    "use strict";

    // doesn't work with sublime jslint plugin: /*jslint plusplus: true */

    //"use strict";

    console.log('Starting Matrix Puzzle');

    // data.js

    var numPages = 19; // temp
    var pages = ['loading', 'home', 'intro1', 'intro2', 'thanks', 'abandon', 'quiz2x2', 'quiz3x3', 'matrix_ex1', 'matrix_ex2', 'matrix_ex3', 'matrix_ex4', 'matrix_ex5', 'matrix_ex6', 'matrix_ex7'];
    var current = 0; // 'home';

    // function preload() {
    //     //images[25] = new Image();
    //     //ges[25].src = 'Snap/snap_images/Rear.GIF';
    // }

    function hidePage(page) {
        document.getElementById(page).style.display = "none";
    }

    function showPage(page) {
        hidePage(pages[current]);
        var pageId = '#' + page;
        console.log('showPage(' + page + '), pageId: ' + pageId);
        //$('#content-container').html($(pageId));
        document.getElementById(page).style.display = "inline";
    }

    function prevPage() {
        hidePage(pages[current]);
        if (current > 0) {
            current -= 1;
        }
        console.log('prevPage(): current: ' + current + ', pages[current]: ' + pages[current]);
        showPage(pages[current]);
    }

    function nextPage() {
        hidePage(pages[current]);
        if (current < numPages) {
            current += 1;
        }
        console.log('nextPage(): current: ' + current + ', pages[current]: ' + pages[current]);
        showPage(pages[current]);
    }

    $('#content-container').on('click', 'a, button', function (e) { // delegate events
        e.preventDefault();
        var pageId = $('.page').attr('id');
        console.log('pageId: ' + pageId); // now gets id from loaded page
        var clickedEl = $(this);
        nextPage();
        switch (clickedEl.attr('id')) {
        case 'prev':
        case 'next':
        case 'yes':
        case 'no':
            console.log('elid: ' + clickedEl.attr('id') + ', html: ' + clickedEl.html() + '');
            break;
        default:
            console.log('got unexpected element id: ' + clickedEl.attr('id')); //+', html: ''+clickedEl.html()+''');
        }
    });

    $('#buttons').on('click', 'a, button', function (e) { // delegate events
        e.preventDefault();
        var pageId = $('.page').attr('id'); //console.log('pageId: '+pageId); // now gets id from loaded page
        var clickedEl = $(this);
        console.log('pageId: ' + pageId + ': elid: ' + clickedEl.attr('id')); //console.log('elid: '+clickedEl.attr('id')+', html: ''+clickedEl.html()+''');
        switch (clickedEl.attr('id')) {
        case 'prev':
            prevPage();
            break;
        case 'next':
            nextPage();
            break;
        case 'yes':
            console.log('yes');
            break;
        case 'no':
            console.log('no');
            break;
        default:
            console.log('got unexpected element id: ' + clickedEl.attr('id')); //+', html: ''+clickedEl.html()+''');
        }
    });

    $(document).ready(function () {
        console.log(' Fri Mar  4 12:11:23 2016 Ready');
        showPage('home');
        //$('#content-container').html($('#thanks'));
    });

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

}());