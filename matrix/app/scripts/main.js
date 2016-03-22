/*global $ */
/*jslint node: true */
/*jslint browser:true */ // define 'document'
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:

// include data.js?

(function () { // Immediately-Invoked Function Expression (IIFE)
    // used to set "use strict" for whole scope so jslint doesn't complain, but then have to indent whole scope...
    "use strict";

    var pages,
        numPages,
        current;
        //answers = [];

    // function preload() {
    //     //images[25] = new Image();
    //     //ges[25].src = 'Snap/snap_images/Rear.GIF';
    // }

    function obj(o) { // log formatted object to console
        return JSON.stringify(o, null, 4);
    }

    function currentPage() {
        //console.log('currentPage[' + current + ']:' + obj(pages[current]));
        return pages[current];
    }

    function hideDiv(id) {
        console.log('hideDiv(): id: ' + id);
        document.getElementById(id).style.display = "none";
    }

    function showDiv(id) {
        console.log('showDiv(): id: ' + id);
        document.getElementById(id).style.display = "inline";
    }

    function hidePage(page) {
        console.log('hidePage(): templateId: ' + page.templateId); //+ obj(page) + '\'');
        hideDiv(page.templateId);
    }

    // http://stackoverflow.com/questions/130396/are-there-constants-in-javascript
    const WIDTH2X2 = 210; // Width of squares in 2x2 grid is 210px
    const WIDTH3X3 = 170; // Width of squares in 3x3 grid is 170px

    // background-image: url('images/intro1.png');
    // background-position: -210px 0px;

    function setBackground(sel) {

    }

    function applyStyles(page) {
        console.log('applyStyles(): current: ' + current + ", templateId: " + page.templateId); //');// page: ' + obj(page));
        var img, base, sel, pos, width;
        var top = page.images.top;
        var bot = page.images.bottom;
        img = "url('images/" + page.sheet + "')"; // DON'T include ';' at end of rule, fails silently! (?)

        if (page.templateId == "quiz2x2") {
            if (top.length != 4) throw new Error("Expected 4 images for top grid in " + page.name);
            if (bot.length != 6) throw new Error("Expected 6 images for bottom grid in " + page.name);
            width = WIDTH2X2;
            base = "div#quiz2x2 ";
            $("div.grid2x2 #top4").css("display", "none");
        } else if (page.templateId == "quiz3x3") {
            if (top.length != 9) throw new Error("Expected 9 images for top grid in " + page.name);
            if (bot.length != 8) throw new Error("Expected 8 images for bottom grid in " + page.name);
            width = WIDTH3X3;
            base = "div#quiz3x3 ";
            $("div.grid3x3 #top9").css("display", "none");
        } else {
            throw new Error("templateId: '" + page.templateId + "' not expected");
        }
        
        // Tue Mar 22 02:03:27 2016
        // could refactor the next two bits into one function (setBackground(), above)

        // div#quiz2x2 div.grid2x2 div.row div, div#quiz3x3 div.grid3x3 div.row div
        for (var i=0; i<top.length; i++) { // safer to iterate like this with arrays - but why use arrays anyway?
            sel = base + "#top" + (i + 1);
            pos = "-" + (width * top[i]) + "px 0px";
            $(sel).css("background-image", img)
            $(sel).css("background-position", pos);
            console.log("sel: " + sel + ", img: " + img + ", pos: " + pos);
        }

        for (var i=0; i<bot.length; i++) {
            sel = base + "#bot" + (i + 1);
            pos = "-" + (width * bot[i]) + "px 0px";
            $(sel).css("background-image", img)
            $(sel).css("background-position", pos);
            console.log("sel: " + sel + ", img: " + img + ", pos: " + pos);
        }
    }

            // .fail(function (jqxhr, textStatus, errorThrown) { // jqxhr not needed here, but position of args important, not name
            //     var err = 'error setting CSS: ' + textStatus + ", errorThrown: " + errorThrown;
            //     console.log(err);
            // });

    function showPage(page) { // prevPage() and nextPage() should handle hiding current
        console.log('showPage(): current: ' + current + ", templateId: " + page.templateId); //');// page: ' + obj(page));
        switch (page.templateId) {
        case "quiz2x2":
            console.log("showPage(): '" + page.templateId + "' handled");
            applyStyles(page);
            break;
        case "quiz3x3":
            console.log("showPage(): '" + page.templateId + "' handled");
            applyStyles(page);
            break;
        case "home":
        case "getReady":
        case "abandon":
        case "thanks":
            console.log("showPage(): '" + page.templateId + "' handled - don't apply styles");
            break; // don't do nuttin
        default:
            throw new Error("unrecogised id");
        }
        showDiv((page.templateId));
    }

    function prevPage() {
        console.log('prevPage(): current: ' + current); // + ', currentPage(): ' + obj(currentPage());
        hidePage(currentPage());
        if (current > 0) {
            current -= 1;
        }
        showPage(currentPage());
    }

    function nextPage() {
        console.log("nextPage(): current: " + current);// + obj(currentPage());
        if (current < numPages) {
            hidePage(currentPage());
            current += 1;
        }
        console.log("nextPage(): current: " + current);// + obj(currentPage());
        showPage(currentPage());
    }

    function containerClick(e) {
        e.preventDefault();
        console.log("containerClick()");
        console.log("current: " + current); //" page: " + obj(pages[current]));
        var pageId = $('.page').attr('id'),
            clickedEl = $(this);
        //console.log('containerClick(): pageId: ' + pageId); // now gets id from loaded page
        console.log('containerClick(): clickedEl: ' + clickedEl.attr('id')); // now gets id from loaded page
        //nextPage();
        switch (clickedEl.attr('id')) {
        case 'prev':
            prevPage();
            break;
        case 'next':
            nextPage();
            break;
        case 'yes':
        case 'no':
            console.log('elid: ' + clickedEl.attr('id') + ', html: ' + clickedEl.html());
            break;
        default:
            // if parent is a row or grandparent is 3x2 or 4x2 grid?
            nextPage();
            // else

            //throw new Error('got unexpected element id: ' + clickedEl.attr('id')); //+', html: ''+clickedEl.html()+''');
        }
    }

    function navClick(e) {
        e.preventDefault();
        console.log("navClick()");
        var pageId = $('.page').attr('id'),
            clickedEl = $(this); //console.log('pageId: '+pageId); // now gets id from loaded page
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
    }

    function init() {
        current = 1; // skip home for now
        console.log('init(): numPages: ' + numPages + ', current: ' + current);
        showPage(currentPage());
    }

    function getConfig() {
        $.getJSON('./config.json', function (data) {
            console.log('getConfig(): got JSON');
            pages = data.pages;         // initialise pages
            numPages = pages.length;
            init();
        }).fail(function (jqxhr, textStatus, errorThrown) { // jqxhr not needed here, but position of args important, not name
            var err = 'error getting JSON: ' + textStatus + ", errorThrown: " + errorThrown;
            console.log(err);
        });
    }

    //$('#content-container').on('click', 'a, button, div', containerClick); // delegate events
    $('#content-container').on('click', 'a, button, div.row div', containerClick); // delegate events

    //$('#buttons').on('click', 'a, button', navClick); // need this?

    $().ready(function () { //$(document).ready(
        console.log('Document ready');
        getConfig();
    });
}());

// >json and a javascript object are two different things, they just look the same.
// json must have **double** quotes for key **and** value, no comments 

// julian cope
// toddla t

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
