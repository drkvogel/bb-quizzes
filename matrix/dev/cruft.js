

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


        //$('#3x2-map').imageMapResize(); // https://github.com/davidjbradshaw/image-map-resizer
        //$('#4x2-map').imageMapResize();
        //imageMapResize();
        // var windowToTile = 0.1; // ratio of width of window to width of tile
        // $(window).width();
        // $(window).height();
        //$(document).keydown(mykeydown()); //
        //$("body").on('keydown', mykeydown); //

    // js docstring?
 //    function setBackground(sel, sheet, pos) { // jQuery selector, sprite sheet, offset pos (px)
 //        var height = document.documentElement.clientHeight;
 //        //var img = 'url("images/' + sheet + '")'; // DON'T include ';' at end of rule, fails silently! (?)
 //        var img = 'images/' + sheet; // DON'T include ';' at end of rule, fails silently! (?)
 //        // $(sel).css('background-image', img);    // e.g. background-image: url('images/intro1.png');
 //        // $(sel).css('background-position', pos); // e.g. background-position: -210px 0px;
 //        // style="position:absolute;top:0px;left: -840px;"
 // //       var scale = 1.0, tileWidth, tileHeight; //var tileWidth = 210; //var tileHeight = 170;
 // //       var windowToTile = 1.0; // ratio of width of window to width of tile
 //        var scale = height / 860.0; // rough monitor height
 //        $(sel).attr('src', img);
 //        $(sel).css('position', 'absolute');
 //        $(sel).css('top', '0px');
 //        $(sel).css('left', parseInt(pos) * scale);

 //        $(sel).attr('width', 1260 * scale); // $ file intro1.png: intro1.png: PNG image data, 1260 x 170, 8-bit colormap, interlaced
 //        $(sel).attr('height', tileHeight(currentPage()) * scale);
 //        $(sel).parent().css('width', tileWidth(currentPage()) * scale); // <div style="width: 210px;height: 170px;overflow:hidden;position:relative;">
 //        $(sel).parent().css('height', tileHeight(currentPage()) * scale);
 //        $(sel).parent().css('padding', '0');
 //   //     $(sel).attr('width', tileWidth); // 6 x 210
 //   //     $(sel).attr('height', tileHeight);
 //   //     $(sel).parent().css('width', tileWidth); // <div style="width: 210px;height: 170px;overflow:hidden;position:relative;">
 //   //     $(sel).parent().css('height', tileHeight);
 //        //$(sel).css('background-size', '50%'); // CSS3
 //    }

 //    function checkImages(page, topExpected, botExpected) {
 //        // for top grids, last (unfilled) tile is yet to be chosen thus redundant in data
 //        if (page.images.top.length !== topExpected) {
 //            throw new Error('Expected ' + topExpected + ' images for top grid in ' + page.name);
 //        }
 //        if (page.images.bottom.length !== botExpected) {
 //            throw new Error('Expected ' + botExpected + ' images for bottom grid in ' + page.name);
 //        }
 //    }

 //    function applyStyles(page) {
 //        //console.log('applyStyles(): current: ' + current + ', templateId: ' + page.templateId); //');// page: ' + obj(page));
 //        var base, sel, pos, width;
 //        var top = page.images.top;
 //        var bot = page.images.bottom;
 //        // TODO passing page object - good idea? i.e. is this a copy or a reference (or reference to a copy)?
 //        // saves a few lines a reuses putting checks into a function, but have to pass it page name, top, bottom
 //        if (page.templateId === 'quiz2x2') {
 //            checkImages(page, 3, 6); //var TOP_EXPECTED = 3, BOT_EXPECTED = 6;
 //            width = WIDTH2X2;
 //            base = 'div#quiz2x2 ';
 //            $('div.grid2x2 #missing2x2').css('display', 'none');
 //        } else if (page.templateId === 'quiz3x3') {
 //            checkImages(page, 8, 8); //var TOP_EXPECTED = 8, BOT_EXPECTED = 8;
 //            width = WIDTH3X3;
 //            base = 'div#quiz3x3 ';
 //            $('div.grid3x3 #missing3x3').css('display', 'none');
 //        } else {
 //            throw new Error('templateId: "' + page.templateId + '" not expected');
 //        }
 //        // could refactor the next two bits into one function (setBackground(), above)
 //        // div#quiz2x2 div.grid2x2 div.row div, div#quiz3x3 div.grid3x3 div.row div
 //        for (var i = 0; i < top.length; i++) { // safer to iterate like this with arrays - but why use arrays anyway?
 //            sel = base + '#top' + i;
 //            //pos = '-' + (width * top[i]) + 'px 0px';
 //            pos = '-' + (width * top[i]);// + 'px';
 //            setBackground(sel, page.sheet, pos); //console.log('sel: ' + sel + ', img: ' + img + ', pos: ' + pos);
 //        }
 //        for (i = 0; i < bot.length; i++) {
 //            sel = base + '#bot' + i;
 //            pos = '-' + (width * bot[i]);// + 'px 0px';
 //            setBackground(sel, page.sheet, pos); //console.log('sel: ' + sel + ', img: ' + img + ', pos: ' + pos);
 //        }
 //    }

        // if (correct) { // http://stackoverflow.com/a/33457014/535071
        //     //console.log('Correct!');
        // } else {
        //     //console.log('Wrong! correct is: ' + page.correct);
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
