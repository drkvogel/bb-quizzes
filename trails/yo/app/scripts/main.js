/*global $ */ // assume jquery
/*jslint browser:true */ // assume 'document'
/* jshint unused:false */
/*eslint-disable no-unused-vars*/
/*eslint-disable strict */
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:


// (function () { // IIFE / Anonymous closure: hide vars from global namespace
//     // set "use strict" for whole scope
//     'use strict';

    var LIVE = false, // const? JSHint doesn't like it
        LOCAL = false,
        MAX_LEVELS = 4,
        FADEIN = 100,
        FADEOUT = 100,
        config,
        pages,
        current,
        puzzleCount = 0,
        timer,
        timerWholeTest,
        isTimeUp = false,
        nextPageTimeout,
        timeUpTimeout,
        enabled = false, // enable UI
        levels = [],
        answers = [],
        puzzle = null,
        seshID = null,
        tinstruct = null,
        tstart = null,
        tfinish = null,
        tinsert = null,
        ntests = null,
        responses = null,
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
    //         count++; // jslint complains about ++
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

    function showInfo(text) {
        $('#info').html(text);
    }

    function showTime(text, correct) {
        var sel = '#prevTime';
        $(sel).css('color', correct ? 'green' : 'red');
        $(sel).html(text + 'ms');
    }

    // function RandIntArray(data) { // remove a randomly-chosen element from the list and return it
    //     this.pop = function() {
    //         if (data.length <= 0) {
    //             return null; //throw new Exception('tried to pop empty stack');
    //         }
    //         var randIndex = Math.floor((Math.random() * data.length));
    //         return data.splice(randIndex, 1);
    //     };
    // }

    // function randLevels() { // copy jon's levelData::rndFixedLevels()
    //     var pseudoRandLevelList = [5, 1, 4, 5, 4, 4, 5, 1, 3, 2, 2, 5, 2, 4, 1, 2, 3, 1]; // reversed from Jon's; hardest first
    //     var nonRandlevels = [];

    //     nonRandlevels.push(new RandIntArray([0, 1, 2, 3]));
    //     nonRandlevels.push(new RandIntArray([4, 5, 6, 7]));
    //     nonRandlevels.push(new RandIntArray([8, 9]));
    //     nonRandlevels.push(new RandIntArray([10, 11, 12, 13]));
    //     nonRandlevels.push(new RandIntArray([14, 15, 16, 17]));

    //     for (var i = 0; i < MAX_LEVELS; i++) {
    //          var wantedLevel = pseudoRandLevelList[i];
    //          levels[i] = nonRandlevels[wantedLevel - 1].pop(); // easiest end popped off first
    //     }
    // }

    // function scaleImagesAY() {
    //     console.log('scaleImagesAY()');

    //     // we know the natural sizes of the images already (748 x 291)
    //     var topWidth = 748, topHeight = 291, botWidth = 748, botHeight = 291;

    //     var widthExtra = // total width of elements, excluding centre images
    //         ($('.container').outerWidth(true) - $('.container').width()) +
    //         ($('#pages').outerWidth(true) - $('#pages').width());

    //     var heightExtra = // total height of elements, excluding centre images
    //         ($('.container').outerHeight(true) - $('.container').height()) +
    //         ($('.topTxt').is(':visible') ? $('.topTxt').height() : 0) +
    //         ($('#imgdiv-a').is(':visible') ? $('#imgdiv-a').outerHeight(true) - $('#imgdiv-a').height() : 0) +
    //         ($('#imgdiv-b').is(':visible') ? $('#imgdiv-b').outerHeight(true) - $('#imgdiv-b').height() : 0) +
    //         ($('.botTxt').is(':visible') ? $('.botTxt').height() : 0) +
    //         ($('#answers').is(':visible') ? $('#answers').height() : 0) +
    //         ($('.navTxt').is(':visible') ? $('.navTxt').height() : 0) +
    //         ($('.navCtl').is(':visible') ? $('.navCtl').height() : 0);
    //         // ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +

    //     // natural image dimensions; .width(), .height() are current dimensions
    //     var naturalFullWidth = widthExtra + topWidth;
    //     var naturalFullHeight = heightExtra + topHeight + botHeight;

    //     // allow 200px for text at bottom
    //     // var textExtra = 200;

    //     // .middleImg needs to be scaled from natural width/height to fit in (window height - textExtra) x window width

    //     // vertical shrink = (window height - 200px) / naturalFullHeight
    //     // horizontal shrink = window width / naturalFullWidth
    //     // var scaleV = ($(window).height() - textExtra) / naturalFullHeight;
    //     var scaleV = ($(window).height()) / naturalFullHeight;
    //     var scaleH = $(window).width() / naturalFullWidth;

    //     // select lower of these scaling values
    //     var scale = scaleV <= scaleH ? scaleV : scaleH;

    //     // work out desired dimensions of whole quiz
    //     var targetWidth = naturalFullWidth * scale; // forget about width, it always fits, down to 300px
    //     var targetHeight = naturalFullHeight * scale;

    //     // work out desired height of .middleImg
    //     var targetMiddleHeight = targetHeight - heightExtra;

    //     // // need h/w ratio of .middleImg. Typical dimensions: ? TODO
    //     var hwRatio = 1.15; //1.95; //??
    //     var middleHWRatio = hwRatio;

    //     // what innerWidth of .middleImg would create targetMiddleHeight?
    //     var targetMiddleWidth = targetMiddleHeight * middleHWRatio;

    //     // set these margins on .middleImg to make the targetWidth and targetHeight
    //     var setMargins = ($(window).width() - widthExtra - targetMiddleWidth) / 2;
    //     if (setMargins > 0) { // check > 0 - even in this algorithm, shouldn't be?
    //         $('.middleImg').css('margin-left', setMargins);
    //         $('.middleImg').css('margin-right', setMargins);
    //     } else {
    //         $('.middleImg').css('margin-left', 0);
    //         $('.middleImg').css('margin-right', 0);
    //     }

    //     // show working
    //     console.log();
    //     console.log();
    //     console.log('working for');
    //     console.log('document: ' + document.body.clientWidth + ' x '  + document.body.clientHeight);
    //     console.log('window: ' + window.innerWidth + ' x '  + window.innerHeight);
    //     console.log();
    //     console.log('topWidth: ' + topWidth + ', topHeight: ' + topHeight + ', botWidth: ' + botWidth + ', botHeight: ' + botHeight);


    //         // ($('.container').outerWidth(true) - $('.container').width()) +
    //         // ($('#pages').outerWidth(true) - $('#pages').width());
    //     console.log('widthExtra = ');
    //     console.log('    (container.outerWidth [' + $('.container').outerWidth(true) +
    //         '] - container.width [' + $('.container').width() + ']) [' +
    //         ($('.container').outerWidth(true) - $('.container').width()) + '] + ');
    //     console.log('    pages.outerWidth [' + $('#pages').outerWidth(true) +
    //         '] - pages.width [' + $('#pages').width() + ']) [' + ($('#pages').outerWidth(true) - $('#pages').width()) + '] + ');
    //     console.log('   == ' + widthExtra);

    //     console.log('heightExtra =');
    //     console.log('    (container.outerHeight [' + $('.container').outerHeight(true) + '] - ' +
    //         ' container.height [' +  $('.container').height() + ']) [' + ($('.container').outerHeight(true) - $('.container').height()) + '] + ');
    //     console.log('    topTxt.height [' + $('.topTxt').height() + '] + ');
    //     console.log('    (#imgdiv-a.outerHeight [' + $('#imgdiv-a').outerHeight(true) + '] - #imgdiv-a.height [' + $('#imgdiv-a').height() + ']) [' +
    //         ($('#imgdiv-a').is(':visible') ? $('#imgdiv-a').outerHeight(true) - $('#imgdiv-a').height() : 0) + '] + ');
    //     console.log('     (#imgdiv-b.outerHeight [' + $('#imgdiv-b').outerHeight(true) + '] - #imgdiv-b.height [' + $('#imgdiv-b').height() + ']) [' +
    //         ($('#imgdiv-b').is(':visible') ? $('#imgdiv-b').outerHeight(true) - $('#imgdiv-b').height() : 0)  + '] + ');
    //     console.log('    botTxt.height [' + $('.botTxt').height() + ']  + ');
    //     console.log('    #answers.height [' + $('#answers').height() + '] +');
    //     console.log('    navTxt.height [' + $('.navTxt').height() + '] +');
    //     console.log('    navCtl.height [' + $('.navCtl').height() + '] +');
    //     console.log('   == ' + heightExtra);
    //         // ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +

    //     console.log('naturalFullWidth =');
    //     console.log('    widthExtra [' + widthExtra + '] + topWidth [' + topWidth + '] == ' + naturalFullWidth);
    //     console.log('naturalFullHeight =');
    //     console.log('    heightExtra [' + heightExtra + '] + topHeight [' + topHeight + '] + botHeight [' + botHeight + ']');
    //     console.log('    == ' + naturalFullHeight);

    //     // allow 200px for text at bottom // var textExtra = 200;
    //     // .middleImg needs to be scaled from natural width/height to fit in (window height - textExtra) x window width
    //     // vertical shrink = (window height - 200px) / naturalFullHeight
    //     // horizontal shrink = window width / naturalFullWidth
    //     // var scaleV = ($(window).height() - textExtra) / naturalFullHeight;
    //     console.log('scaleV = window.height [' + $(window).height() + '] / naturalFullHeight [' + naturalFullHeight + '] == ' + scaleV.toFixed(2));
    //     console.log('scaleH = window.width [' + $(window).width() + '] / naturalFullWidth [' + naturalFullWidth + '] == ' + scaleH.toFixed(2));
    //     console.log('scale = scaleV [' + scaleV.toFixed(2) + '] <= scaleH  [' + scaleH.toFixed(2) + '] ? ' + scale.toFixed(2));

    //     console.log('targetWidth = naturalFullWidth [' + naturalFullWidth + '] * scale [' + scale.toFixed(2) + '] == ' + targetWidth.toFixed(2));
    //     console.log('targetHeight = naturalFullHeight [' + naturalFullHeight + '] * scale [' + scale.toFixed(2) + '] == ' + targetHeight.toFixed(2));
    //     console.log('targetMiddleHeight = targetHeight [' + targetHeight + '] - heightExtra [' + heightExtra + '] == ' + targetMiddleHeight);

    //     // var hwRatio = 1.15; //1.95; //??// var middleHWRatio = hwRatio;
    //     // what innerWidth of .middleImg would create targetMiddleHeight?
    //     console.log('targetMiddleWidth = targetMiddleHeight [' + targetMiddleHeight + '] * middleHWRatio [' + middleHWRatio + '] == ' + targetMiddleWidth.toFixed(2));
    //     // var targetMiddleWidth = targetMiddleHeight * middleHWRatio;

    //     // set these margins on .middleImg to make the targetWidth and targetHeight
    //     //var setMargins = ($(window).width() - widthExtra - targetMiddleWidth) / 2;
    //     console.log('setMargins = window.width [' + $(window).width() + '] - widthExtra [' + widthExtra +
    //         '] - targetMiddleWidth [' + targetMiddleWidth.toFixed(2) + ']) / 2 == ' + setMargins.toFixed(2));

    //     console.log('setMargins > 0: ' + (setMargins.toFixed(2) > 0));
    //     if (setMargins > 0) { // check > 0 - even in this algorithm, shouldn't be?
    //         console.log('    middleImg.margin-left = ' + setMargins.toFixed(2));
    //         console.log('    middleImg.margin-right = ' + setMargins.toFixed(2));
    //     } else {
    //         console.log('    middleImg.margin-left = 0');
    //         console.log('    middleImg.margin-right = 0');
    //     }


    //     // var msg = 'setMargins: ' + setMargins +
    //     //     ', targetWidth: ' + targetWidth + ', targetHeight: ' + targetHeight +
    //     //     ', targetMiddleWidth: ' + targetMiddleWidth;
    //     // console.log(msg);
    // }

// from hoops-doc.md
// ### Element heights (top to bottom)
//     html                -
//     body                -
//     #devBar             hidden
//     div.container       padding-top: 15px
//     div#pages           -
//     div#game            -
//     div.middleImg       -
//     table.toptable
//     td#imgdiv-a
//     img#img-a
//     td#imgdiv-b
//     img#img-b
//     div.middleImg       -
//     div.botText         72px minimum (if not wrapped) (if visible)
//     div#answers         -
//     div.navCtl
//     div#pages           -
//     div#abandon-div     34px (if visible)
//     div.container       padding-bottom: 20px
//     body                -
//     html                -

        // var widthExtra =
        //     ($('.container').outerWidth(true) - $('.container').width()) +
        //     ($('#pages').outerWidth(true) - $('#pages').width()); // missing some widths?
        // var heightExtra = // required height of .gridContainer
        //     ($('#answers').is(':visible') ? $('#answers').height() : 0) +
        //     ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
        //     ($('.botTxt').is(':visible') ? $('.botTxt').height() : 0) +
        //     ($('.topTxt').is(':visible') ? $('.topTxt').height() : 0) +
        //     ($('.navTxt').is(':visible') ? $('.navTxt').height() : 0) +
        //     ($('.navCtl').is(':visible') ? $('.navCtl').height() : 0)
        //     + 75 // fixme arbitrary amount, what should this really be?
        //     ;
        //     // missing some heights?
        // var setMargins = ($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;
        // //console.log('scaleImagesCBsimple(): setMargins ' + setMargins + ', heightExtra: ' + heightExtra + ', widthExtra: ' + widthExtra);
        //      //'($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;' +


    // shrink images to try to fit height into viewport, but don't worry about width
    // function scaleImagesCBsimple() { //
    //     //showInfo('$(window).width(): ' + $(window).width() + ', $(window).height()' + $(window).height() + ', margins: ' + margin);
    //     var VERT_PAD = 75;
    //     var widthExtra =
    //         ($('.container').outerWidth(true) - $('.container').width()) +
    //         ($('#pages').outerWidth(true) - $('#pages').width()); // missing some widths?
    //     var heightExtra = // required height of .gridContainer
    //         ($('#answers').is(':visible') ? $('#answers').height() : 0) +
    //         ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
    //         ($('.botTxt').is(':visible') ? $('.botTxt').height() : 0) +
    //         ($('.topTxt').is(':visible') ? $('.topTxt').height() : 0) +
    //         ($('.navTxt').is(':visible') ? $('.navTxt').height() : 0) +
    //         ($('.navCtl').is(':visible') ? $('.navCtl').height() : 0)
    //         //+ 75 // fixme arbitrary amount, what should this really be?
    //         + VERT_PAD
    //         ;
    //         // missing some heights?
    //     var setMargins = ($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;
    //     //console.log('scaleImagesCBsimple(): setMargins ' + setMargins + ', heightExtra: ' + heightExtra + ', widthExtra: ' + widthExtra);
    //          //'($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;' +

    //     if (setMargins > 0) {
    //         $('.middleImg').css('margin-left', setMargins);
    //         $('.middleImg').css('margin-right', setMargins);
    //     } else { // don't set negative margins. content should shrink width-wise if needed
    //         $('.middleImg').css('margin-left', 0);
    //         $('.middleImg').css('margin-right', 0);
    //     }
    // }

    // function scaleImages() {
    //     //scaleImagesCBsimple();
    //     scaleImagesAY();
    // }

    function isoDate() { // return date string in format yyyy-mm-ddThh:mm:ss, suitable for parsing by xtime.cpp
        var date = new Date(); // date.toISOString() is UTC/GMT with milliseconds, e.g. '2016-09-21T10:47:54.671Z'
        return date.toISOString().substring(0, 19); // strip milliseconds
            // timezone not needed, is GMT
    }

    function startTimer(page) {
        if (page.name.slice(0, 2) === 'ex') {
            timer.now(); // start timer for all real exercises
            if (levels.length === MAX_LEVELS - 1) { // first puzzle just been popped off
                timerWholeTest.now(); // start timer for the whole test (for "elapsed" field)
                config.timeStarted = isoDate();
                console.log('config.timeStarted: ' + config.timeStarted);
                timeUpTimeout = setTimeout(timeUp, config.timeLimit);
            }
        }
    }

        // if (!enabled) {
        //     console.log('input disabled');
        //     //return;
        // }
        //console.log('unbind clicks');
    function containerClick(e) {
        e.preventDefault();
        $('#pages').off('click', 'a, button, div.row div', containerClick); // prevent double-click

        var clickedEl = $(this),
            elId = clickedEl.attr('id'); //console.log('containerClick(): clickedEl: ' + elId); // now gets id from loaded page

        switch (clickedEl.attr('id')) {
        case 'prev':
            prevPage();
            break;
        case 'next':
        case 'start':
            nextPage();
            break;
        case 'yes':     // fixme what are these for?
        case 'no':
            console.log('elid: ' + clickedEl.attr('id') + ', html: ' + clickedEl.html());
            break;
        default:
            var slice = elId.slice(0, 3);
            if (slice === 'ans') { // bottom grid only
                $('#' + elId).addClass('disabled'); // remember to add '#' back onto ID to make selector
                var num = elId[3]; // number in id following 'bot' == number of bottom tile selected
                answered(Number(num)); // otherwise gets quoted in JSON and has to be translated from string on backend
            }
        }
    }

    function getNextPuzzle() {
        return config.puzzles[levels.pop()];
    }

    function showPage2() {
        console.log('showPage2: currentPage().name: ' + currentPage().name); // (re-)scaleImages();bind clicks
        //scaleImages();
        $('#pages').on('click', 'a, button, div.row div', containerClick); // prevent double-click
        if (currentPage().name === 'thanks') { // redundant?
            console.log('currentPage().name === \'thanks\'');
            setTimeout(finished, 3000);
        }
    }

    function showPage(page) { // prevPage() and nextPage() should handle hiding current
        //console.log('showPage(\'' + page.name + '\'): current: ' + current + ', templateId: ' + page.templateId); // page: ' + obj(page)); isTimeUp:' + isTimeUp);
        if (page.hasOwnProperty('suppressAbandon')) {//console.log('page.hasOwnProperty(\'suppressAbandon\')');
            $('#abandon-div').hide(); //fadeOut(FADEOUT);
        } else {
            $('#abandon-div').fadeIn(FADEOUT);
        }
        var info = current + '/' + pages.length + ': ' + page.name + ', timeUp: ' + String(isTimeUp);
        showInfo(info);
        switch (page.templateId) {
        case 'game':
             $('.botTxt').html('<text>');
            for (var i = 1; i <= 6; i++) {
                var id = '#ans' + i;
                $(id).removeClass('disabled');
            }
            if (page.name === 'intro4') { // practice example
                puzzle = config.practice;
                // $('#img-a').attr('src', 'images/' + puzzle.a);
                // $('#img-b').attr('src', 'images/' + puzzle.b); // or $('#imgdiv-b img')
                $('#svg1').attr('data', 'images/' + 'practice-a.svg'); // or $('#imgdiv-b img')
                $('.navCtl').html(config.navPrev);
            } else {
                // puzzle = getNextPuzzle();
                // if (puzzle === undefined) { // nothing left on stack, finished all puzzles
                //     showPage(pageNamed('thanks'));
                //     return;
                // }
                // //var image = puzzle.i; var txt = 'getNextPuzzle(): ' + image; showInfo(txt); console.log(txt);
                // $('#img-a').attr('src', 'images/top-constant.png');  // top-constant is t3bw2y1
                // $('#img-b').attr('src', 'images/' + puzzle.b); // pseudo-random
                $('#svg1').attr('data', 'images/' + 'part-a.svg'); // or $('#imgdiv-b img')
                $('.navCtl').html('');
                //console.log('puzzle.b: ' + puzzle.b + ', correct: ' + puzzle.c);
            }
            startTimer(page); // timer to show chosen answer before next, and start game timer
            break;
        case 'home':
        case 'abandon':
            break; // don't do nuttin
        case 'intro': // these are templateIds remember, not page names
            $('.topTxt').html(page.topTxt);
            //$('.middleImg img#introImg').attr('src', 'images/' + page.images.top); // e.g. intro1.png - not split and don't have A, B labels
            $('.botTxt').html(page.botTxt);
            $('.navTxt').html(page.navTxt);
            if (page.name === 'intro1') {
                $('.navCtl').html(config.navNext);
            } else {
                $('.navCtl').html(config.navPrevNext);
            }
            if (page.name === 'intro5') {
                var ans = answers.pop();
                console.log('intro5 ans: ' + ans);
                $('#intro-answer').html(ans + (parseInt(ans) === 2 ? ' - Correct!' : ''));
            }
            break;
        case 'getReady':
            $('.navTxt').html(page.navTxt);
            $('.navCtl').html(config.navStart);
            break;
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

        //scaleImages();
        $('#' + page.templateId).fadeIn(FADEIN, showPage2);
        //scaleImages();
        //showInfo('height: ' + $(window).height()); //attr('height'));
    }

    function prevPage2() { // eslint throws no-use-before-define, but this is OK in ES5 due to hoisting
        if (current > 0) {
            current -= 1;
        } //console.log('prevPage2()');
        showPage(currentPage());
    }

    function prevPage() { //console.log('prevPage(): current: ' + current); // + ', currentPage(): ' + obj(currentPage());
        $('#' + currentPage().templateId).fadeOut(FADEOUT, prevPage2);
    }

    function nextPage2() {
        //console.log('nextPage2(): current + 1 < pages.length: ' + String(current + 1 < pages.length));
        var page;
        if (isTimeUp) {                             // time up
            clearTimeout(nextPageTimeout);
            page = pageNamed('thanks');
        } else if (currentPage().name === 'ex') {   // live game
            page = currentPage();
        } else if (current + 1 < pages.length) {    // intro screens
            current += 1;
            page = currentPage();
        } else {
            console.log('nextPage(): hit the end at current: ' + current);
            page = currentPage();
        }
        showPage(page);
    }

    function nextPage() { // console.log('nextPage(): current: ' + current);// + obj(currentPage());
        //console.log('nextPage(): isTimeUp:' + isTimeUp);
        $('#' + currentPage().templateId).fadeOut(FADEOUT, nextPage2);
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

    function timeUp() {
        clearTimeout(timeUpTimeout); // in case triggered manually for testing
        isTimeUp = true;
        console.log('timeUp(): isTimeUp:' + isTimeUp);
    }

    function answered2() {
        //console.log('answered2()');
        if (isTimeUp) {
            clearTimeout(nextPageTimeout);
            showPage(pageNamed('thanks'));
        } else if (currentPage().name.slice(0, 5) === 'intro') {
            current += 1;
            showPage(currentPage());
        } else {
            showPage(currentPage());
        }
    }

    function answered(ans) {
        var page = currentPage();
        var isCorrect = ans === puzzle.c;
        console.log('answered: ' + ans + ', correct: ' + puzzle.c + ', isCorrect: ' + isCorrect + ', elapsed? ' + timer.getElapsed());
        var timeTaken;
        if (page.name.slice(0, 2) === 'ex') { // real exercise
            timer.lap();
            timerWholeTest.lap();
            timeTaken = timer.getElapsed();
            showTime(timeTaken, isCorrect);
            var answer = {
                count: ++puzzleCount,                   // should be number of puzzles taken
                duration: timeTaken,                    // Time taken to answer puzzle
                puzzle: puzzle.n,                       // number of puzzle, not image name - config.json should be only mapping
                elapsed: timerWholeTest.getElapsed(),   // Cumulative time elapsed
                answer: ans,                            // Answer given by user, ans should be Number() type
                correct: puzzle.c                       // correct answer, not bool
            };
            answers.push(answer);
        } else if (page.name.slice(0, 5) === 'intro') {
            answers.push(ans);
        }
        $('#' + currentPage().templateId).fadeOut(FADEOUT, answered2);
    }

    function abandonClick() {
        console.log('abandon');
        showModal('abandon-modal');
    }

    function navClick(e) {
        console.log('navClick()');
        e.preventDefault();
        var pageId = $('.page').attr('id'),
            clickedEl = $(this); //console.log('pageId: '+pageId); // now gets id from loaded page
        console.log('pageId: ' + pageId + ': elid: ' + clickedEl.attr('id')); //console.log('elid: '+clickedEl.attr('id')+', html: ''+clickedEl.html()+''');
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
        console.log('modalClick()');
        var pageId = $('.page').attr('id'),
            clickedEl = $(this); //console.log('pageId: '+pageId); // now gets id from loaded page
        console.log('pageId: ' + pageId + ': elid: ' + clickedEl.attr('id')); //console.log('elid: '+clickedEl.attr('id')+', html: ''+clickedEl.html()+''');
        switch (clickedEl.attr('id')) {
        case 'abandon-yes':
            hideModal('abandon-modal');
            $('#' + currentPage().templateId).hide();
            showPage(pageNamed('thanks'));
            break;
        case 'abandon-no':
            hideModal('abandon-modal');
            break;
        case 'tryagain-ok':
            hideModal('tryagain-modal');
            break;
        case 'timeup-ok':
            hideModal('timeup-modal');
            break;
        default:
            console.log('got unexpected element id: ' + clickedEl.attr('id')); //+', html: ''+clickedEl.html()+''');
        }
    }

    function addListeners() {
        var svg1 = document.getElementById('svg1');
        svg1.addEventListener('load', function () { // add load event listener to object, as will load svg asynchronously
            var svgDoc = svg1.contentDocument; // get inner DOM of svg
            var blue = svgDoc.getElementById('blue'); // get inner element by id
            blue.addEventListener('mousedown', function () {// add behaviour
                // alert('I am blue');
            }, false);
            var yell = svgDoc.getElementById('yell'); // get inner element by id
            yell.addEventListener('mousedown', function () {// add behaviour
                // alert('I am yellow');
            }, false);
            var line = svgDoc.getElementById('line'); // get inner element by id
            line.addEventListener('mousedown', function () {// add behaviour
                // alert('I am a line');
            }, false);
        }, false);
    }

    function init() {
        timer = new Timer(); // globals
        timerWholeTest = new Timer(); // globals
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
            config.seshID = urlParams.sesh_id; //urlParams['sesh_id'];
                // error  ["sesh_id"] is better written in dot notation                    dot-notation
            $('#feedbackForm').attr('action', config.formAction); // set the results form target
        }
        msg = 'config.sesh_id: ' + config.seshID;
        //console.log('formAction: ' + config.formAction);
        console.log(msg);
        $('#home .debug').html('<code>' + msg + '</code>');

        //randLevels(); console.log('levels: ' + levels);

        showPage(currentPage());
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

    $('body').on('keydown', keydown); //$('#pages').on('click', 'a, button, div.row div', containerClick); // delegate events
    $('#devBar').on('click', 'a, button', navClick);
    $('#abandon-btn').on('click', abandonClick);
    $('#modals').on('click', 'button', modalClick);

    window.onresize = function(event) {
        //scaleImages();
    };

    (window.onpopstate = function() { // why in IIFE?
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
        // console.log('test: ' + test);
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
//}()); // IIFE

console.log('main.js ready');
