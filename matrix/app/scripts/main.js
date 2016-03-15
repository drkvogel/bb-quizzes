/*global $ */
/*jslint node: true */
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:

// include data.js?

(function () { // Immediately-Invoked Function Expression (IIFE)
    // used to set "use strict" for whole scope so jslint doesn't complain, but then have to indent whole scope...
    "use strict";

    var numPages = 19; // temp
    //var pages = ['loading', 'home', 'intro1', 'intro2', 'quiz2x2', 'matrix_ex1', 'matrix_ex2', 'matrix_ex3', 'matrix_ex4', 'matrix_ex5', 'matrix_ex6', 'matrix_ex7'];
    var pages = ['loading', 'home', 'quiz2x2', 'matrix_ex1', 'matrix_ex2', 'matrix_ex3', 'matrix_ex4', 'matrix_ex5', 'matrix_ex6', 'matrix_ex7'];
    var current = 1; // 'home';
    //'quiz2x2', 'quiz3x3', 'thanks', 'abandon'

    // function preload() {
    //     //images[25] = new Image();
    //     //ges[25].src = 'Snap/snap_images/Rear.GIF';
    // }

    function currentPage() {
        return pages[current];
    }

    function hidePage(page) {
        document.getElementById(page).style.display = "none";
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
        console.log('pageId: ' + pageId); // now gets id from loaded page
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

    console.log('Starting Matrix Puzzle');
    $(document).ready(function () {
        console.log(' Fri Mar  4 12:11:23 2016 Ready');
        showPage('home');
    });

}());