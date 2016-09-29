/*global $ */
/*jslint browser:true */ // define 'document'
///* jshint unused:false */
///*eslint-disable no-unused-vars*/
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:

// http://stackoverflow.com/questions/950087/include-a-javascript-file-in-another-javascript-file
(function () { // Immediately-Invoked Function Expression (IIFE) / Anonymous closure: hide vars from global namespace
    // used to set "use strict" for whole scope so jslint doesn't complain, but then have to indent whole scope...
    'use strict';

    var LIVE = false, // const? JSHint doesn't like it
        LOCAL = false,
        // MAX_LEVELS = 15,
        FADEIN = 100,
        FADEOUT = 100,
        config,
        pages,
        current,
        timer,
        timerWholeTest,
        isTimeUp = false,
        nextPageTimeout,
        timeUpTimeout,
        // enabled = false, // enable UI
        // levels = [],
        answers = [],
        // seshID = null,
        // tinstruct = null,
        // tstart  null,
        // tfinish = null,
        // tinsert = null,
        // ntests = null,
        // responses = null,
        urlParams = {};

    // //var Timer = require('./timer'); // require is a node thing, unless you use requirejs
    // // copied/adapted from Jonathan's bb-quizzes/snap/Snap_files/Timer.js

    // var Timer = function() {
    //     this.isValid = false;
    //     this.startts = 0;
    //     this.lapts = 0;
    //     this.hasPossibleError = false;
    //     this.hasPerformance = false;
    //     if (typeof window.performance !== 'undefined' && typeof window.performance.now !== 'undefined') {
    //         this.hasPerformance = true;
    //     }
    // };

    // // adding to prototype saves memory when lots of instances - referenced not copied
    // Timer.prototype.getTime = function() {
    //     var nowish;
    //     if (this.hasPerformance) {
    //         nowish = window.performance.now(); // https://developers.google.com/web/updates/2012/08/When-milliseconds-are-not-enough-performance-now
    //     } else {
    //         nowish = new Date().getTime();
    //     }
    //     return nowish;
    // };

    // Timer.prototype.findnow = function() {
    //     var nowish = 0,
    //         count = 0,
    //         diff = 0,
    //         testVal = 0;
    //     do {
    //         nowish = this.getTime();
    //         testVal = this.getTime();
    //         diff = testVal - nowish;
    //         count++;
    //     } while (((diff < 0) || (diff > 2)) && (count < 10));
    //     if (count >= 6) {
    //         this.hasPossibleError = true; //keep the start val :(
    //     }
    //     return nowish;
    // };

    // Timer.prototype.now = function() {
    //     this.startts = this.findnow();
    //     this.lapts = 0;
    //     this.isValid = false;
    // };

    // Timer.prototype.lap = function() {
    //     if (this.startts === 0) {
    //         return;
    //     }
    //     this.lapts = this.findnow();
    //     this.isValid = true;
    // };

    // Timer.prototype.getElapsed = function() {
    //     if (!this.isValid || this.startts === 0 || this.lapts === 0) {
    //         return -1;
    //     }
    //     var diff = this.lapts - this.startts;
    //     if (diff < 0) {
    //         this.hasPossibleError = true;
    //     }
    //     return Math.round(Number(diff)); //round the number in case it is preformce. (???)
    // };

    // Timer.prototype.gethasPerformance = function() {
    //     return this.hasPerformance ? 1 : 0;
    // };

    // Timer.prototype.gethasPossibleError = function() {
    //     return this.hasPossibleError ? 1 : 0;
    // };

    // Timer.prototype.copy = function() {
    //     var copy = new Timer();
    //     copy.startts = this.startts;
    //     copy.lapts = this.lapts;
    //     copy.hasPerformance = this.hasPerformance;
    //     copy.hasPosibleError = this.hasPosibleError;
    //     return copy;
    // };

    // Timer.prototype.getStart = function() {
    //     return this.startts;
    // };

    // Timer.prototype.getLap = function() {
    //     return this.lapts;
    // };

    // Timer.prototype.isValid = function() {
    //     return this.isValid;
    // };
    // // module.exports = Timer; // module.exports is Node.js, for the server!

    // function preload() {
    //     //images[25] = new Image();
    //     //ges[25].src = 'Snap/snap_images/Rear.GIF';
    // }

    // function logObj(o) { // log formatted object to console
    //     return JSON.stringify(o, null, 4);
    // }

    function currentPage() {
        return pages[current]; //console.log('currentPage[' + current + ']:' + obj(pages[current]));
    }

    function pageNamed(name) {
        for (var i = 0; i < pages.length; i++) { // http://stackoverflow.com/questions/500504/why-is-using-for-in-with-array-iteration-such-a-bad-idea
            if (pages[i].name === name) {
                return pages[i];
            }
        }
        throw new Error('unknown page: ' + name);
    }

    // function hideDiv(id) {
    //     $('#' + id).fadeOut('fast'); //document.getElementById(id).style.display = 'none'; //console.log('hideDiv(): id: ' + id);
    // }

    // function showDiv(id) {
    //     $('#' + id).slideDown(); //document.getElementById(id).style.display = 'inline'; //console.log('showDiv(): id: ' + id);
    // }

    // function hidePage(page) {
    //     hideDiv(page.templateId); //console.log('hidePage(): templateId: ' + page.templateId); //+ obj(page) + '\'');
    // }

    // http://stackoverflow.com/questions/130396/are-there-constants-in-javascript
    // var WIDTH2X2 = 210; // Width of squares in 2x2 grid is 210px // const?
    // var HEIGHT2X2 = 170; // Height of squares in 2x2 grid is 170px // const?
    // var WIDTH3X3 = 170; // Width of squares in 3x3 grid is 170px // const?
    // var HEIGHT3X3 = 135; // Height of squares in 3x3 grid is 135px // const?

    // function tileWidth(page) {
    //     switch(page.templateId) {
    //     case 'quiz2x2':
    //         return WIDTH2X2;
    //     case 'quiz3x3':
    //         return WIDTH3X3;
    //     default:
    //         throw new Error('bad page.templateId: ' + page.templateId);
    //     }
    // }

    // function tileHeight(page) {
    //     switch(page.templateId) {
    //     case 'quiz2x2':
    //         return HEIGHT2X2;
    //     case 'quiz3x3':
    //         return HEIGHT3X3;
    //     default:
    //         throw new Error('bad page.templateId: ' + page.templateId);
    //     }
    // }
    // // function applyStyles(page) {
    //     var base = 'images/' + page.name + '/' + page.name;
    //     $('#top').attr('src', base + '-problem.png');
    //     $('#bot').attr('src', base + '-palette.png');
    // }
    function setImage(sel, page, extn) {
        var base = 'images/' + page.name + '/' + page.name; //console.log('setImage(' + sel + ', ' + page.name + ', ' + extn + ')');
        $(sel).attr('src', base + extn); //console.log('base + extn: ' + base + extn + ')');
    }

    function showInfo(text) {
        $('#info').html(text);
    }

    function showTime(text, correct) {
        var sel = '#prevTime';
        $(sel).css('color', correct ? 'green' : 'red');
        $(sel).html(text + 'ms');
    }

    function isoDate() { // return date string in format yyyy-mm-ddThh:mm:ss, suitable for parsing by xtime.cpp
        var date = new Date(); // date.toISOString() is UTC/GMT with milliseconds, e.g. '2016-09-21T10:47:54.671Z'
        return date.toISOString().substring(0, 19); // strip milliseconds
            // timezone not needed, is GMT
    }

    function startTimer(page) {
        if (page.name.slice(0, 2) === 'ex') {
            timer.now(); // start timer for all real exercises
            if (page.name === 'ex1') {
                config.timeStarted = isoDate();
                console.log('config.timeStarted: ' + config.timeStarted);
                timerWholeTest.now(); // start timer for the whole test (for "elapsed" field)
                timeUpTimeout = setTimeout(timeUp, config.timeLimit); // 120000ms == 2 minutes
            }
        }
    }

    function showText(page) {
        var sel = '#' + page.templateId + ' .botText p';
        if (page.name.slice(0, 5) === 'intro') { //console.log('sel: \'' + sel + '\', text: ' + page.text);
            $(sel).html(page.text);
        } else {
            $(sel).html('');
        }
    }

    // scale images to try to fit all content in the viewport

// devBar          usually hidden
// padding         fixed?
// topTxt          fixed, unless width small enough to cause text to wrap
// gridContainer   the element we want to scale so that it's height combined with the other elements' heights will fit in the viewport
// botTxt          fixed, unless width small enough to cause text to wrap
// navCtl          fixed
// padding         fixed?

    // get natural width/height (naturalFullWidth/Height)
    // get window width/height ($(window).width()/height)

    // # allow 200px for text at bottom
    // # window - 200px height needs to fit natural width/height

    // vertical shrink = (window height - 200px) / naturalFullHeight
    // horizontal shrink = window width / naturalFullWidth

    // scale = vShrink < hShrink ? vShrink : hShrink

    // targetHeight = naturalFullHeight * scale
    // targetWidth = naturalFullWidth * scale # forget about width as width always fits, down to 300px

    // targetMiddleHeight = targetHeight - heightExtras

    // # need h/w ratio of .gridContainer
    // # Typical dimensions: 162 x 144
    // # 162 / 144 == 1.125
    // middleHWRatio = 1.125

    // # what innerWidth of .gridContainer would create targetMiddleHeight?
    // targetMiddleWidth = targetMiddleHeight * middleHWRatio [1.125]

    // # set these margins on .gridContainer to make the targetWidth and targetHeight
    // margins = (window.width - widthExtra) / 2

    // natural image dimensions; $('.bot').width() etc is current width
    function scaleImagesAY() { // Alan's calculation based on dimensions of unscaled layout
        console.log('scaleImagesAY()');

        // we know the natural sizes of the images already
        var topHeight, botWidth, botHeight; // topWidth not needed as bottom image widest
        if (currentPage().templateId === 'quiz2x2') {
            // topWidth = 420;
            topHeight = 340;
            botWidth = 680;
            botHeight = 365;
        } else if (currentPage().templateId === 'quiz3x3') {
            // topWidth = 510;
            topHeight = 405;
            botWidth = 755;
            botHeight = 295;
        }

        var widthExtra = // total width of elements, excluding centre images
            ($('.container').outerWidth(true) - $('.container').width()) +
            ($('#pages').outerWidth(true) - $('#pages').width());

        var heightExtra = // total height of elements, excluding centre images
            ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
            ($('.botText').is(':visible') ? $('.botText').height() : 0);

        // natural image dimensions; .width(), .height() are current dimensions
        var naturalFullWidth = widthExtra + botWidth; // bottom image is widest
        var naturalFullHeight = heightExtra + topHeight + botHeight;

        // allow 200px for text at bottom
        // .gridContainer needs to be scaled from natural width/height to fit in
        // (window height - 200px) x window width

        // vertical shrink = (window height - 200px) / naturalFullHeight
        // horizontal shrink = window width / naturalFullWidth
        var scaleV = ($(window).height() - 200) / naturalFullHeight;
        var scaleH = $(window).width() / naturalFullWidth;

        // select lower of these scaling values
        var scale = scaleV <= scaleH ? scaleV : scaleH;

        // work out desired dimensions of whole quiz
        //var targetWidth = naturalFullWidth * scale; // forget about width, it always fits, down to 300px
        var targetHeight = naturalFullHeight * scale;

        // work out desired height of .gridContainer
        var targetMiddleHeight = targetHeight - heightExtra;

        // need h/w ratio of .gridContainer. Typical dimensions: 162 x 144. 162 / 144 == 1.125
        var middleHWRatio = 1.125;

        // what innerWidth of .gridContainer would create targetMiddleHeight?
        var targetMiddleWidth = targetMiddleHeight * middleHWRatio;

        // set these margins on .gridContainer to make the targetWidth and targetHeight
        var setMargins = ($(window).width() - widthExtra - targetMiddleWidth) / 2;
        $('.gridContainer').css('margin-left', setMargins);
        $('.gridContainer').css('margin-right', setMargins);

        // var msg = 'setMargins: ' + setMargins +
        //     ', targetWidth: ' + targetWidth + ', targetHeight: ' + targetHeight +
        //     ', targetMiddleWidth: ' + targetMiddleWidth;
        //console.log(msg);
    }
    //var setMargin = ($(window).width() - ($(window).height() - heightExtra) - margins) / 2;

    // function scaleImagesCBsimple() { // my calculation, mostly works
    //     console.log('scaleImagesCBsimple()');
    //     var widthExtra =
    //         ($('.container').outerWidth(true) - $('.container').width()) +
    //         ($('#pages').outerWidth(true) - $('#pages').width());
    //         // missing some widths?
    //     var heightExtra = // required height of .gridContainer
    //         ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
    //         ($('.botText').is(':visible') ? $('.botText').height() : 0) + 75;
    //         // missing some heights?
    //     var setMargins = ($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;

    //     if (setMargins > 0) {
    //         $('.gridContainer').css('margin-left', setMargins);
    //         $('.gridContainer').css('margin-right', setMargins);
    //     } else { // don't set negative margins. content should shrink width-wise if needed
    //         $('.gridContainer').css('margin-left', 0);
    //         $('.gridContainer').css('margin-right', 0);
    //     }
    // }

    function scaleImages() {
        //scaleImagesCBsimple()
        scaleImagesAY();
    }

    // .css('width') is text e.g. '1200px'; .width() is numeric e.g. 1200. .attr('width') is undefined
    // https://api.jquery.com/visible-selector/
    // body shouldn't have any border or margin

        //console.log('#abandon-div h: ' + $('#abandon-div').height() + ', visible: ' + $('#abandon-div').is(':visible')); // works
        //console.log('.botText h: ' + $('.botText').height() + ', visible: ' + $('.botText').is(':visible')); // works
        //console.log('heightExtra: ' + String(heightExtra));
        //console.log('$(document).height(): ' + $(document).height() + ', $(window).height(): ' + $(window).height());
        //console.log('$(\'body\').height(): ' + $('body').height()); // == $(window).height()

        // why am I subtracting all the margins etc from the total width/height to find the width/height of the gridContainer, instead of just using the width/height of the gridContainer?
        //var setMargin = ($(window).width() - ($('.gridContainer').height()) - margins) / 2; // pretty erratic.... seems like race condition to set and read the height of the element
        // get the margin widths to subtract from the viewport width - height
        // body > div.container > div#pages > div#quiz2x2.quiz > div.gridContainer > .grid2x2 .grid3x2
        // console.log('margins = ' + '($(\'.container\').outerWidth(true)[' + $('.container').outerWidth(true) + '] - $(\'.container\').width())[' + $('.container').width() + '] + ' +
        //     '($(\'#pages\').outerWidth(true)[' + $('#pages').outerWidth(true) + '] - $(\'#pages\').width()[' + $('#pages').width() + ']) == ' + margins);
        // console.log('setMargin = ($(window).width()[' + $(window).width() + '] - ($(window).height()[' + $(window).height() +
        //     '] - $(\'.botText\').height()[' + $('.botText').height() + ']) - margins[' + margins + ']) / 2 == ' + setMargin);
        // console.log('$(window).width(): ' + $(window).width() + ', $(window).height()' + $(window).height() + ', margins: ' + margins + ', setMargin: ' + setMargin);
        // var margins = $('body').css('width') + $('div.container').css('width') + $('div#pages').css('width');
        // ', .container margin: ' + String($('.container').outerWidth(true) + $('.container').innerWidth())+
        //var setMargin = ($(window).width() - ($(window).height() - $('.botText').height()) - margins) / 2;
        //heightExtra = 0;
        //console.log('$(\'body\').height(): ' + $('body').height()); // == $(window).height()
        //$('.container').attr('width', $(window).height()); // doesn't work but setting margin-left and margin-right makes it shrink
    function showPage2() {
        console.log('showPage2: currentPage().name: ' + currentPage().name); // (re-)scaleImages();bind clicks
        scaleImages();
        // re-enable event handler
        $('#pages').on('click', 'a, area, button', containerClick); // eslint-disable-line no-use-before-define
        //var heightScrolled = $(document).height() - $(window).height(); console.log('heightScrolled: ' + heightScrolled);
        switch (currentPage().templateId) { // only after page is set visible?
        case 'quiz2x2':
            $('#3x2-map').imageMapResize(); // https://github.com/davidjbradshaw/image-map-resizer
            break;
        case 'quiz3x3':
            $('#4x2-map').imageMapResize();
            break;
        }
        if (currentPage().name === 'thanks') { // redundant?
            console.log('currentPage().name === \'thanks\'');
            setTimeout(finished, 3000);
        }
    }

    function showPage(page) { // prevPage() and nextPage() should handle hiding current
        console.log('showPage(\'' + page.name + '\'): current: ' + current + ', templateId: ' + page.templateId); //');// page: ' + obj(page)); //console.log('showPage(): isTimeUp:' + isTimeUp);
        if (page.hasOwnProperty('suppressAbandon')) {//console.log('page.hasOwnProperty(\'suppressAbandon\')');
            $('#abandon-div').hide(); //fadeOut(FADEOUT);
        } else {
            $('#abandon-div').fadeIn(FADEOUT);
        }
        var info = current + '/' + pages.length + ': ' + page.name + ', timeUp: ' + String(isTimeUp);
        showInfo(info);
        switch (page.templateId) {
        case 'quiz2x2':
        case 'quiz3x3':
            setImage('#' + page.templateId + ' .top', page, '-problem.png');
            setImage('#' + page.templateId + ' .bot', page, '-palette.png');
            startTimer(page);
            showText(page);
            break;
        case 'home':
        case 'getReady':
        case 'abandon':
            break; // don't do nuttin
        case 'thanks':
            clearTimeout(timeUpTimeout);
            clearTimeout(nextPageTimeout);
            $('*').css('cursor', 'progress');
            console.log('setTimeout(finished, 3000)');
            setTimeout(finished, 3000);
            break;
        default:
            throw new Error('unrecogised id');
        }

        //showDiv(page.templateId);
        $('#' + page.templateId).fadeIn(FADEIN, showPage2);
        //scaleImagesCBsimple();
        //scaleImagesAY();
        //scaleImagesCBnew();

        // var heightScrolled = $(document).height() - $(window).height();
        // console.log('heightScrolled: ' + heightScrolled);

        // switch (page.templateId) { // only after page is set visible?
        // case 'quiz2x2':
        //     $('#3x2-map').imageMapResize(); // https://github.com/davidjbradshaw/image-map-resizer
        //     break;
        // case 'quiz3x3':
        //     $('#4x2-map').imageMapResize();
        //     break;
        // }
    }



    function prevPage2() {
        if (current > 0) {
            current -= 1;
        }
        showPage(currentPage());
    }

    function prevPage() {
        //hidePage(currentPage()); //console.log('prevPage(): current: ' + current); // + ', currentPage(): ' + obj(currentPage());
        $('#' + currentPage().templateId).fadeOut(FADEOUT, prevPage2);
    }

    function nextPage2() {
        console.log('nextPage2()');
        if (isTimeUp) {
            clearTimeout(nextPageTimeout);
            showPage(pageNamed('thanks'));
        } else if (current + 1 < pages.length) {
            current += 1;
            showPage(currentPage());
        } else {
            console.log('nextPage(): hit the end at current: ' + current);
        }
    }

    function nextPage() { console.log('nextPage(): current: ' + current);// + obj(currentPage());
        //hidePage(currentPage()); //console.log('nextPage(): isTimeUp:' + isTimeUp);
        //clearTimeout(nextPageTimeout);
        $('#' + currentPage().templateId).fadeOut(FADEOUT, nextPage2);
        // if (isTimeUp) {
        //     clearTimeout(nextPageTimeout);
        //     showPage(pageNamed('thanks'));
        // } else if (current + 1 < pages.length) {
        //     current += 1;
        //     showPage(currentPage());
        // } else {
        //     console.log('nextPage(): hit the end at current: ' + current);
        // }
    }

    function answered(ans) {
        console.log('answered()');
        var page = currentPage();
        setImage('#' + page.templateId + ' .top', page, '-sol' + ans + '.png'); //console.log('got num: ' + num);

        //var correct = Number(num) === page.correct;
        var isCorrect = ans === page.correct;
        var timeTaken;
        if (page.name.slice(0, 2) === 'ex') { // real exercise
            timer.lap();
            timerWholeTest.lap();
            timeTaken = timer.getElapsed();
            showTime(timeTaken, isCorrect);
            var answer = {
                // count: ++puzzleCount,                   // should be number of puzzles taken
                // puzzle: puzzle.n,                       // number of puzzle, not image name - config.json should be only mapping
                // correct: puzzle.c                       // correct answer, not bool

                // page: page.name,
                duration: timeTaken,                    // Time taken to answer puzzle
                elapsed: timerWholeTest.getElapsed(),   // Cumulative time elapsed
                answer: ans,                            // Answer given by user, ans should be Number() type
                correct: page.correct
            };
            answers.push(answer);
        } else if (page.name.slice(0, 5) === 'intro') {
            if (!isCorrect) {
                showInfo('try again'); // TODO
                showModal('tryagain-modal');
                return;
            }
        }
        // if (correct) { // http://stackoverflow.com/a/33457014/535071
        //     //console.log('Correct!');
        // } else {
        //     //console.log('Wrong! correct is: ' + page.correct);
        // }
        nextPageTimeout = setTimeout(nextPage, config.nextDelay); // //nextPage(); function object without () otherwise called immediately
    }

    function containerClick(e) {
        e.preventDefault();
        var clickedEl = $(this),
            elId = clickedEl.attr('id');
        console.log('containerClick(): current: ' + current + ', clickedEl: ' + elId, 'type: ' + clickedEl.prop('tagName')); // now gets id from loaded page
        //$('#pages').on('click', 'a, button, div.row div', containerClick); // re-enable
        //$('#pages').off('click', 'a, button, div.row div', containerClick); // prevent double-click
        $('#pages').off('click', 'a, area, button'); // delegate events
        console.log('$(\'#pages\').off(\'click\'');
        switch (clickedEl.attr('id')) {
        case 'prev':
            prevPage();
            break;
        case 'next':
        case 'start':
            nextPage();
            break;
        case 'yes':
        case 'no':
            //console.log('elid: ' + clickedEl.attr('id') + ', html: ' + clickedEl.html());
            break;
        default:
            // if parent is a row or grandparent is 3x2 or 4x2 grid
            var slice = elId.slice(0, 3);
            if (slice === 'bot') { // bottom grid only
                var num = elId[3]; // number in id following 'bot' == number of bottom tile selected
                answered(Number(num));
            }
        }
    }

    function showModal(modal) {
        $('#modals').show();
        $('#' + modal).show(); //fadeIn(FADEIN); //console.log('showModal(\'' + modal + '\')');
    }

    function hideModal(modal) {
        $('#modals').hide();
        $('#' + modal).hide(); //fadeOut(FADEOUT);
    }

    function finished() {
        console.log('finished(): answers: ' + JSON.stringify(answers));
        clearTimeout(timeUpTimeout);

        // fill in form and submit automatically
        document.getElementById('sesh_id').value = config.seshID;
        document.getElementById('tinstruct').value = config.tinstruct;
        document.getElementById('tstart').value = config.timeStarted;
        document.getElementById('tfinish').value = isoDate(); // now
        document.getElementById('ntests').value = answers.length;
        document.getElementById('responses').value = JSON.stringify(answers); //$('input[name="results"]').val() = JSON.stringify(answers);
        window.onbeforeunload = null;
        $(window).on('beforeunload', function(){
            $('*').css('cursor', 'default');
        });
        document.getElementById('feedbackForm').submit(); // action set in init() from config.json
    }
    //$('input[name="results"]').val() = JSON.stringify(answers);
    //$("body").css("cursor", "progress"); // $("body").css("cursor", "default");

    function timeUp() {
        clearTimeout(timeUpTimeout); // in case triggered manually for testing
        isTimeUp = true;
        console.log('timeUp(): isTimeUp:' + isTimeUp);
    }
        // showModal('timeup-modal'); //alert("Time's up!");
        // hidePage(currentPage());
        // showPage(pageNamed('thanks'));

    function abandonClick() {
        showModal('abandon-modal'); //console.log('abandon');
    }

    function navClick(e) {
        e.preventDefault();
        console.log('navClick()');
        var clickedEl = $(this); //console.log('pageId: '+pageId); // now gets id from loaded page
        //var pageId = $('.page').attr('id');
        //console.log('page: ' + currentPage() + ': elid: ' + clickedEl.attr('id')); //console.log('elid: '+clickedEl.attr('id')+', html: ''+clickedEl.html()+''');
        switch (clickedEl.attr('id')) {
        case 'prev':
            prevPage();
            break;
        case 'next':
        case 'start':
            nextPage();
            break;
        case 'timeUp':
            clearTimeout(timeUpTimeout);
            timeUp();
            break;
        default:
            console.log('got unexpected element id: ' + clickedEl.attr('id')); //+', html: ''+clickedEl.html()+''');
        }
    }

    function modalClick(e) { // TODO merge into navClick or something
        e.preventDefault();
        var clickedEl = $(this); //console.log('pageId: '+pageId); // now gets id from loaded page
        //pageId = $('.page').attr('id'),
        //console.log('pageId: ' + pageId + ': elid: ' + clickedEl.attr('id')); //console.log('elid: '+clickedEl.attr('id')+', html: ''+clickedEl.html()+''');
        switch (clickedEl.attr('id')) {
        case 'abandon-yes':
            hideModal('abandon-modal');
            //hidePage(currentPage());
            $('#' + currentPage().templateId).hide();
            // TODO clear timeouts / called finished()
            showPage(pageNamed('thanks'));
            break;
        case 'abandon-no':
            hideModal('abandon-modal');
            break;
        case 'tryagain-ok':
            //clearTile();
            setImage('#' + currentPage().templateId + ' .top', currentPage(), '-problem.png');
            hideModal('tryagain-modal');
            break;
        case 'timeup-ok':
            hideModal('timeup-modal');
            break;
        default:
            console.log('got unexpected element id: ' + clickedEl.attr('id')); //+', html: ''+clickedEl.html()+''');
        }
    }

    function init() {
        // globals
        timer = new Timer();
        timerWholeTest = new Timer();
        isTimeUp = false;
        current = 0;
        var msg;

        if (LOCAL) {
            config.seshID = 4321;
            $('#feedbackForm').attr('action', 'http://xrat.ctsu.ox.ac.uk/~cp/bbquiz/');
        } else {
            if (!urlParams.hasOwnProperty('sesh_id')) {
                msg = 'not LOCAL and sesh_id not found in urlParams';
                $('#home .debug').html('<code>' + msg + '</code>');
                throw new Error(msg);
            }
            config.seshID = urlParams.sesh_id; //urlParams['sesh_id']; // error  ["sesh_id"] is better written in dot notation                    dot-notation
            $('#feedbackForm').attr('action', config.formAction);
        }
        msg = 'config.sesh_id: ' + config.seshID; console.log(msg);
        $('#home .debug').html('<code>' + msg + '</code>');
        $('#button').css('display', LIVE ? 'none' : 'inline');

        // var formAction = config.formAction;
        // var loc = location.toString().split('://')[1]; // strip off http://, https://
        // //if (loc.substr(0, 9) === 'localhost') { // served from gulp
        // if (LOCAL) {
        //     console.log('loc === localhost');
        //     formAction = 'http://localhost:8000/' + formAction; // gulp-connect-php - local PHP server
        // } // else, is on same server, relative link OK


        showPage(currentPage());
        imageMapResize(); // eslint-disable-line no-undef
        config.tinstruct = isoDate();
        console.log('config.tinstruct: ' + config.tinstruct);
    }

    function getConfig() {
        $.getJSON('./config.json', function (configData) {
            console.log('getConfig(): got config.json');
            config = configData;
            pages = configData.pages;
            init();
        }).fail(function (jqxhr, textStatus, errorThrown) { // jqxhr not needed here, but position of args important, not name
            var err = 'error getting config.json: ' + textStatus + ', errorThrown: ' + errorThrown;
            console.log(err);
        });
    }

    function keydown(e) {
        console.log('keyboard event: ' + e.which);
        if (e.which === 68) { //console.log('"d" pressed');
            e.preventDefault(); // don't trap other keypresses e.g. ctrl-shift-i for dev tools
            if ($('#devBar').css('display') === 'none') {
                $('#devBar').show();
            } else {
                $('#devBar').hide();
            }
        }
    }

    // bind event handlers to elements
    $('body').on('keydown', keydown); // $("body").keyup(keyup()); // throws error as doesn't exist at this moment?
    //$('#pages').on('click', 'a, area, button', containerClick); // delegate events
        // Thu Sep 29 03:19:33 2016 don't bind here as it's set in showPage2(), otherwise you'll get multiple calls to containerClick()!
        // took me a good hour or so to find that in the middle of the night...
    $('#devBar').on('click', 'a, button', navClick); // need this?
    $('#abandon-btn').on('click', abandonClick); // need this?
    $('#modals').on('click', 'button', modalClick);

    window.onresize = function(event) { // eslint-disable-line no-unused-vars
        console.log('onresize');
        showPage(currentPage()); // ?
    };

    (window.onpopstate = function() {
        var match,
            pl = /\+/g,  // Regex for replacing addition symbol with a space
            search = /([^&=]+)=?([^&]*)/g,
            decode = function(s) { return decodeURIComponent(s.replace(pl, ' ')); },
            query = window.location.search.substring(1);
        // eslint-disable-next-line no-cond-assign <--- doesn't work, but eslint-disable-line does:
        while (match = search.exec(query)) { // eslint-disable-line no-cond-assign
           urlParams[decode(match[1])] = decode(match[2]);
        }
        for (var urlParam in urlParams) {
            console.log('urlParam: ' + urlParam + ' is ' + urlParams[urlParam]);
        }
    })();

    $().ready(function () { //$(document).ready(
        console.log('Document ready');
        //hideDiv('devBar');
        $('#devBar').hide();
        if (LIVE) {
            window.onbeforeunload = null;
            window.history.forward();   //prevent repeat after back button - may not work.
            window.onbeforeunload = function() {
                return 'The answers to the questions or tests you are doing at the moment will be lost - is this what you want to do?';
            };
        }
        var loc = location.toString().split('://')[1]; // strip off http://, https://
        if (loc.substr(0, 9) === 'localhost') { // served from gulp
            LOCAL = true;
        }
        console.log('LOCAL: ' + LOCAL);
        getConfig();
    });
}());

console.log('main.js ready');

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
