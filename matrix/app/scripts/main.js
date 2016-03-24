/*global $ */
/*jslint node: true */
/*jslint browser:true */ // define 'document'
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:

// include data.js?

(function () { // Immediately-Invoked Function Expression (IIFE)
    // used to set "use strict" for whole scope so jslint doesn't complain, but then have to indent whole scope...
    "use strict";

    var config, 
        pages,
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
    var WIDTH2X2 = 210; // Width of squares in 2x2 grid is 210px // const?
    var WIDTH3X3 = 170; // Width of squares in 3x3 grid is 170px // const?

    // background-image: url('images/intro1.png');
    // background-position: -210px 0px;

    // js docstring?
    function setBackground(sel, sheet, pos) { // jQuery selector, sprite sheet, offset pos (px)
        var img = "url('images/" + sheet + "')"; // DON'T include ';' at end of rule, fails silently! (?)
        $(sel).css("background-image", img);
        $(sel).css("background-position", pos);
    }

    function check_images(page, top_expected, bot_expected, name) {
        // for top grids, last (unfilled) tile is yet to be chosen thus redundant in data
        if (page.images.top.length      != top_expected) throw new Error("Expected " + top_expected + " images for top grid in " + page.name);
        if (page.images.bottom.length   != bot_expected) throw new Error("Expected " + bot_expected + " images for bottom grid in " + page.name);
    }

    function applyStyles(page) {
        console.log('applyStyles(): current: ' + current + ", templateId: " + page.templateId); //');// page: ' + obj(page));
        var img, base, sel, pos, width;
        var top = page.images.top;
        var bot = page.images.bottom;

        // TODO passing page object - good idea? i.e. is this a copy or a reference (or reference to a copy)?
        // saves a few lines a reuses putting checks into a function, but have to pass it page name, top, bottom
        if (page.templateId == "quiz2x2") {
            check_images(page, 3, 6); //var TOP_EXPECTED = 3, BOT_EXPECTED = 6;
            width = WIDTH2X2;
            base = "div#quiz2x2 ";
            $("div.grid2x2 #missing2x2").css("display", "none");
        } else if (page.templateId == "quiz3x3") {
            // if (top.length != 8) throw new Error("Expected 9 images for top grid in " + page.name);
            // // last tile not yet chosen
            // if (bot.length != 8) throw new Error("Expected 8 images for bottom grid in " + page.name);
            check_images(page, 8, 8); //var TOP_EXPECTED = 8, BOT_EXPECTED = 8;
            width = WIDTH3X3;
            base = "div#quiz3x3 ";
            $("div.grid3x3 #missing3x3").css("display", "none");
        } else {
            throw new Error("templateId: '" + page.templateId + "' not expected");
        }
        
        // Tue Mar 22 02:03:27 2016
        // could refactor the next two bits into one function (setBackground(), above)

        // div#quiz2x2 div.grid2x2 div.row div, div#quiz3x3 div.grid3x3 div.row div
        for (var i=0; i<top.length; i++) { // safer to iterate like this with arrays - but why use arrays anyway?
            sel = base + "#top" + i;
            pos = "-" + (width * top[i]) + "px 0px";
            setBackground(sel, page.sheet, pos); // jQuery selector, sprite sheet, offset pos (px)
            //console.log("sel: " + sel + ", img: " + img + ", pos: " + pos);
        }

        for (i=0; i<bot.length; i++) {
            sel = base + "#bot" + i;
            pos = "-" + (width * bot[i]) + "px 0px";
            setBackground(sel, page.sheet, pos); // jQuery selector, sprite sheet, offset pos (px)
            //console.log("sel: " + sel + ", img: " + img + ", pos: " + pos);
        }
    }

            // .fail(function (jqxhr, textStatus, errorThrown) { // jqxhr not needed here, but position of args important, not name
            //     var err = 'error setting CSS: ' + textStatus + ", errorThrown: " + errorThrown;
            //     console.log(err);
            // });
    function showInfo(text) {
        $("#info").html(text);
    }

    function showPage(page) { // prevPage() and nextPage() should handle hiding current
        console.log("showPage(" + page.name + "): current: " + current + ", templateId: " + page.templateId); //');// page: ' + obj(page));
        var info  = current + "/" + pages.length + ": " + page.name;
        showInfo(info);
        switch (page.templateId) {
        case "quiz2x2":
        case "quiz3x3":
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
        if (current + 1 < numPages) {
            hidePage(currentPage());
            current += 1;
        } else {
            console.log("nextPage(): hit the end at current: " + current);    
        }
        console.log("nextPage(): current: " + current);// + obj(currentPage());
        showPage(currentPage());
    }

    function containerClick(e) {
        e.preventDefault();
        console.log(); //" page: " + obj(pages[current]));
        var pageId = $('.page').attr('id'),
            clickedEl = $(this),
            elId = clickedEl.attr('id');
        console.log("containerClick(): current: " + current + ", clickedEl: " + elId); // now gets id from loaded page
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
            var slice = elId.slice(0, 3);
            if ("bot" == slice) { // bottom grid only
                var num = elId[3];
                var page = currentPage();
                var sel, pos;
                console.log("got num: " + num);
                page.answer = num;

                if ("quiz2x2" == page.templateId) {
                    sel = "div#quiz2x2 #missing2x2";
                    pos = "-" + (WIDTH2X2 * page.images.bottom[num]) + "px 0px";
                } else if ("quiz3x3" == page.templateId) {
                    sel = "div#quiz3x3 #missing3x3";
                    pos = "-" + (WIDTH3X3 * page.images.bottom[num]) + "px 0px";                    
                } else {
                    throw new Error("bad page.templateId: " + page.templateId);
                }
                setBackground(sel, page.sheet, pos); // jQuery selector, sprite sheet, offset pos (px)
                $(sel).css("display", "inline");
                //$("div.grid3x3 #missing3x3").css("display", "");

                if (num == page.correct) {
                    console.log("Correct!");
                    console.log("Setting timeout...");
                    setTimeout(nextPage, config.nextDelay); // function object without () otherwise called immediately
                    //nextPage();
                } else {
                    console.log("Wrong! correct is: " + page.correct);
                }

            } else {
                var err = 'got unexpected element id: ' + clickedEl.attr('id');
                console.log(err); //throw new Error(err);
            }
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
            config = data;
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

    $('#buttons').on('click', 'a, button', navClick); // need this?

    var LIVE = false; // const? JSHint doesn't like it

    $().ready(function () { //$(document).ready(
        console.log('Document ready');
        $("#button").css("display", LIVE ? "none" : "inline");
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
