/*global $ */
/*jslint node: true */
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:

// include data.js?

(function () { // Immediately-Invoked Function Expression (IIFE)
    // used to set "use strict" for whole scope so jslint doesn't complain, but then have to indent whole scope...
    "use strict";

    var numPages = 19; // temp
    //var pages = ['loading', 'home', 'intro1', 'intro2', 'quiz2x2', 'matrix_ex1', 'matrix_ex2', 'matrix_ex3', 'matrix_ex4', 'matrix_ex5', 'matrix_ex6', 'matrix_ex7'];
    //var pages = ['loading', 'home', 'quiz2x2', 'matrix_ex1', 'matrix_ex2', 'matrix_ex3', 'matrix_ex4', 'matrix_ex5', 'matrix_ex6', 'matrix_ex7'];
    var pages = ['loading', 'home', 'quiz2x2', 'quiz3x3', 'quiz2x2', 'quiz3x3'];
    var current = 0; // 'home'; 'quiz2x2', 'quiz3x3', 'thanks', 'abandon'

    // function preload() {
    //     //images[25] = new Image();
    //     //ges[25].src = 'Snap/snap_images/Rear.GIF';
    // }

    function currentPage() {
        console.log('currentPage[' + current + ']:' + pages[current]);
        return pages[current];
    }

    function hidePage(page) {
        console.log('hidePage(\'' + page + '\'');
        document.getElementById(page.template).style.display = "none";
    }

    function showPage(page) {
        hidePage(currentPage());
        var pageId = '#' + page;
        console.log('showPage(' + page + '), pageId: ' + pageId);
        document.getElementById(page).style.display = "inline"; //$('#content-container').html($(pageId));
    }

    function prevPage() {
        hidePage(currentPage());
        if (current > 0) {
            current -= 1;
        }
        console.log('prevPage(): current: ' + current + ', currentPage(): ' + currentPage());
        showPage(currentPage());
    }

    function nextPage() {
        hidePage(currentPage());
        if (current < numPages) {
            current += 1;
        }
        console.log('nextPage(): current: ' + current + ', currentPage(): ' + currentPage());
        showPage(currentPage());
    }

    $('#content-container').on('click', 'a, button', function (e) { // delegate events
        e.preventDefault();
        var pageId = $('.page').attr('id');
        var clickedEl = $(this);
        console.log('$(\'#content-container\').on(\'click\', \'a, button\'): pageId: ' + pageId); // now gets id from loaded page
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

    function getConfig() {
        $.getJSON('./config.json', function (data) {
            console.log('got JSON');
            pages = data.pages;

        }).fail(function (jqXHR, textStatus, errorThrown) {
            var err = 'error getting JSON: ' + textStatus + ", errorThrown: " + errorThrown;
            console.log(err);
        });
    }
    
    $().ready(function () { //$(document).ready(
        console.log('Document ready');
        getConfig();
        showPage('home');
    });
}());

        //console.log(data.pages);
        //console.log(data.pages.length);
        // for (var i=0; i<data.pages.length; i++) { // array iterate
        //     console.log(data.pages[i].template);
        //     console.log(data.pages[i].sheet);
        //     console.log(JSON.stringify(data.pages[i], null, 4)); // null, 4 args tell it to indent with 4 spaces
        // }
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
        "template": "",     // template div to use
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
