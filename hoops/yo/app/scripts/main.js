/*global $ */
/*jslint browser:true */ // define 'document'
/* jshint unused:false */
/*eslint-disable no-unused-vars*/
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:

// http://stackoverflow.com/questions/950087/include-a-javascript-file-in-another-javascript-file
(function () { // Immediately-Invoked Function Expression (IIFE) / Anonymous closure: hide vars from global namespace
    // used to set "use strict" for whole scope so jslint doesn't complain, but then have to indent whole scope...
    'use strict';

    var LIVE = false, // const? JSHint doesn't like it
        FADEIN = 300,
        FADEOUT = 300,
        config,
        pages,
        current,
        timer,
        isTimeUp = false,
        nextPageTimeout,
        timeUpTimeout,
        enabled = false, // enable UI
        levels = [],
        answers = [],
        navNext = '<span><button class=\"btn\" id=\"next\" href=\"#\">Next &gt;&gt;</button></span>', // pull-left pull-right
        navPrev = '<span><button class=\"btn\" id=\"prev\" href=\"#\">&lt;&lt; Prev</button></span>',
        navPrevNext = '<span style="margin-right: 40px;"><button class=\"btn\" id=\"prev\" href=\"#\">&lt;&lt; Prev</button></span>' +
                          '<span id=\"next\" class=\"\"><button class=\"btn\" id=\"next\" href=\"#\">Next &gt;&gt;</button></span>';

    //var Timer = require('./timer'); // require is a node thing, unless you use requirejs
    // copied/adapted from Jonathan's bb-quizzes/snap/Snap_files/Timer.js

    var Timer = function() {
        this.isValid = false;
        this.startts = 0;
        this.lapts = 0;
        this.hasPossibleError = false;
        this.hasPerformance = false;
        if (typeof window.performance !== 'undefined' && typeof window.performance.now !== 'undefined') {
            this.hasPerformance = true;
        }
    };

    // adding to prototype saves memory when lots of instances - referenced not copied
    Timer.prototype.getTime = function() {
        var nowish;
        if (this.hasPerformance) {
            nowish = window.performance.now(); // https://developers.google.com/web/updates/2012/08/When-milliseconds-are-not-enough-performance-now
        } else {
            nowish = new Date().getTime();
        }
        return nowish;
    };

    Timer.prototype.findnow = function() {
        var nowish = 0,
            count = 0,
            diff = 0,
            testVal = 0;
        do {
            nowish = this.getTime();
            testVal = this.getTime();
            diff = testVal - nowish;
            count++; // jslint complains about ++
        } while (((diff < 0) || (diff > 2)) && (count < 10));
        if (count >= 6) {
            this.hasPossibleError = true; //keep the start val :(
        }
        return nowish;
    };

    Timer.prototype.now = function() {
        this.startts = this.findnow();
        this.lapts = 0;
        this.isValid = false;
    };

    Timer.prototype.lap = function() {
        if (this.startts === 0) {
            return;
        }
        this.lapts = this.findnow();
        this.isValid = true;
    };

    Timer.prototype.getElapsed = function() {
        if (!this.isValid || this.startts === 0 || this.lapts === 0) {
            return -1;
        }

        var diff = this.lapts - this.startts;
        if (diff < 0) {
            this.hasPossibleError = true;
        }
        return Math.round(Number(diff)); //round the number in case it is preformce. (???)
    };

    Timer.prototype.gethasPerformance = function() {
        return this.hasPerformance ? 1 : 0;
    };

    Timer.prototype.gethasPossibleError = function() {
        return this.hasPossibleError ? 1 : 0;
    };

    Timer.prototype.copy = function() {
        var copy = new Timer();
        copy.startts = this.startts;
        copy.lapts = this.lapts;
        copy.hasPerformance = this.hasPerformance;
        copy.hasPosibleError = this.hasPosibleError;
        return copy;
    };

    Timer.prototype.getStart = function() {
        return this.startts;
    };

    Timer.prototype.getLap = function() {
        return this.lapts;
    };

    Timer.prototype.isValid = function() {
        return this.isValid;
    };
    // module.exports = Timer; // module.exports is Node.js, for the server!


    // function preload() {
    //     //images[25] = new Image();
    //     //ges[25].src = 'Snap/snap_images/Rear.GIF';
    // }

    // function obj(o) { // log formatted object to console
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

    function scaleImagesAY() {
        console.log('scaleImagesAY()');
        // copied from matrix

        // // we know the natural sizes of the images already
        // var topWidth, topHeight, botWidth, botHeight;
        // if (currentPage().templateId === 'quiz2x2') {
        //     topWidth = 420;
        //     topHeight = 340;
        //     botWidth = 680;
        //     botHeight = 365;
        // } else if (currentPage().templateId === 'quiz3x3') {
        //     topWidth = 510;
        //     topHeight = 405;
        //     botWidth = 755;
        //     botHeight = 295;
        // }

        // var widthExtra = // total width of elements, excluding centre images
        //     ($('.container').outerWidth(true) - $('.container').width()) +
        //     ($('#pages').outerWidth(true) - $('#pages').width());

        // var heightExtra = // total height of elements, excluding centre images
        //     ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
        //     ($('.botText').is(':visible') ? $('.botText').height() : 0);

        // // natural image dimensions; .width(), .height() are current dimensions
        // var naturalFullWidth = widthExtra + botWidth; // bottom image is widest
        // var naturalFullHeight = heightExtra + topHeight + botHeight;

        // // allow 200px for text at bottom
        // // .gridContainer needs to be scaled from natural width/height to fit in
        // // (window height - 200px) x window width

        // // vertical shrink = (window height - 200px) / naturalFullHeight
        // // horizontal shrink = window width / naturalFullWidth
        // var scaleV = ($(window).height() - 200) / naturalFullHeight;
        // var scaleH = $(window).width() / naturalFullWidth;

        // // select lower of these scaling values
        // var scale = scaleV <= scaleH ? scaleV : scaleH;

        // // work out desired dimensions of whole quiz
        // var targetWidth = naturalFullWidth * scale; // forget about width, it always fits, down to 300px
        // var targetHeight = naturalFullHeight * scale;

        // // work out desired height of .gridContainer
        // var targetMiddleHeight = targetHeight - heightExtra;

        // // need h/w ratio of .gridContainer. Typical dimensions: 162 x 144. 162 / 144 == 1.125
        // var middleHWRatio = 1.125;

        // // what innerWidth of .gridContainer would create targetMiddleHeight?
        // var targetMiddleWidth = targetMiddleHeight * middleHWRatio;

        // // set these margins on .gridContainer to make the targetWidth and targetHeight
        // var setMargins = ($(window).width() - widthExtra - targetMiddleWidth) / 2;
        // $('.gridContainer').css('margin-left', setMargins);
        // $('.gridContainer').css('margin-right', setMargins);

        // console.log('setMargins: ' + setMargins +
        //     ', targetWidth: ' + targetWidth + ', targetHeight: ' + targetHeight +
        //     ', targetMiddleWidth: ' + targetMiddleWidth
        //      + 'setMargins: ' + setMargins);
    }

    // shrink images to try to fit height into viewport, but don't worry about width
    function scaleImagesCBsimple() { //
        console.log('scaleImagesCBsimple()');
        //showInfo('$(window).width(): ' + $(window).width() + ', $(window).height()' + $(window).height() + ', margins: ' + margin);
        var widthExtra =
            ($('.container').outerWidth(true) - $('.container').width()) +
            ($('#pages').outerWidth(true) - $('#pages').width()); // missing some widths?
        var heightExtra = // required height of .gridContainer
            ($('#answers').is(':visible') ? $('#answers').height() : 0) +
            ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
            ($('.botTxt').is(':visible') ? $('.botTxt').height() : 0) +
            ($('.topTxt').is(':visible') ? $('.topTxt').height() : 0) +
            ($('.navTxt').is(':visible') ? $('.navTxt').height() : 0) +
            ($('.navCtl').is(':visible') ? $('.navCtl').height() : 0)
            + 75 // fixme arbitrary amount, what should this really be?
            ;
            // missing some heights?
        var setMargins = ($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;
        console.log('setMargins ' + setMargins + ', heightExtra: ' + heightExtra + ', widthExtra: ' + widthExtra);
             //'($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;' +

        if (setMargins > 0) {
            $('.middleImg').css('margin-left', setMargins);
            $('.middleImg').css('margin-right', setMargins);
        } else { // don't set negative margins. content should shrink width-wise if needed
            $('.middleImg').css('margin-left', 0);
            $('.middleImg').css('margin-right', 0);
        }
    }

    function startTimer(page) {
        if (page.name.slice(0, 2) === 'ex') {
            timer.now(); // start timer for all real exercises
            if (page.name === 'ex1') {
                config.timeStarted = new Date($.now());
                console.log('config.timeStarted: ' + config.timeStarted);
                timeUpTimeout = setTimeout(timeUp, config.timeLimit); // 120000ms == 2 minutes
            }
        }
    }

    function containerClick(e) {
        e.preventDefault();

        // if (!enabled) {
        //     console.log('input disabled');
        //     //return;
        // }
        console.log('unbind clicks');
        $('#pages').off('click', 'a, button, div.row div', containerClick); // prevent double-click

        var clickedEl = $(this),
            elId = clickedEl.attr('id');
        console.log('containerClick(): current: ' + current + ', clickedEl: ' + elId); // now gets id from loaded page

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
                answered(num);
            }
        }
    }

    function RandIntArray(data) {
        this.pop = function() {
            if (data.length <= 0) {
                return null; //throw new Exception('tried to pop empty stack');
            }
            var randIndex = Math.floor((Math.random() * data.length));
            return data.splice(randIndex, 1);
        };
    }

    function randLevels() { // copy jon's levelData::rndFixedLevels()
        var MAX_LEVELS = 18;
        var pseudoRandLevelList = [1, 3, 2, 1, 4, 2, 5, 2, 2, 3, 1, 5, 4, 4, 5, 4, 1, 5]; // [MAX_LEVELS]
        var nonRandlevels = []; //, randLevels = [];

        nonRandlevels.push(new RandIntArray([0, 1, 2, 3]));
        nonRandlevels.push(new RandIntArray([4, 5, 6, 7]));
        nonRandlevels.push(new RandIntArray([8, 9]));
        nonRandlevels.push(new RandIntArray([10, 11, 12, 13]));
        nonRandlevels.push(new RandIntArray([14, 15, 16, 17]));

        for (var i = 0; i < MAX_LEVELS; i++) {
             var wantedLevel = pseudoRandLevelList[i];
             levels[i] = nonRandlevels[wantedLevel - 1].pop();
        }
    }

    function getNextImage() {
        // var images = ['t3bw21y', 't3ybw21', 't3w2by1', 't3w2y1b',
        //               't32wy1b', 't3w2b1y', 't32by1w', 't3yw21b',
        //               't3yw2b1', 't3w2yb1',
        //               't3wb2y1', 't3y2wb1', 't3yb21w', 't32yb3w',
        //               't3wy2b1', 't3y2b1w', 't3ywb21', 't3wyb21'];
        // return levels.pop();
        return config.images[levels.pop()] + '.png';
    }

    function showPage(page) { // prevPage() and nextPage() should handle hiding current
        console.log('showPage(\'' + page.name + '\'): current: ' + current + ', templateId: ' + page.templateId); // page: ' + obj(page)); isTimeUp:' + isTimeUp);
        if (page.hasOwnProperty('suppressAbandon')) {//console.log('page.hasOwnProperty(\'suppressAbandon\')');
            $('#abandon-div').hide(); //fadeOut(FADEOUT);
        } else {
            $('#abandon-div').fadeIn(FADEOUT);
        }
        var info = current + '/' + pages.length + ': ' + page.name; showInfo(info);
        switch (page.templateId) {
        case 'game':
            if (page.name.slice(0, 2) === 'ex') {
                timer.now(); // start timer for all real exercises
                if (page.name === 'ex1') {
                    console.log('start game timer');
                    timeUpTimeout = setTimeout(timeUp, config.timeLimit); // 120000ms == 2 minutes
                }
            }
            // img-a - top-constant.png
            // $('#img-b').attr('src', 'images/' + page.image); // or $('#imgdiv-b img')
            $('.botTxt').html('How many moves would it take to make picture A look like picture B?');
            for (var i = 1; i <= 6; i++) {
                var id = '#ans' + i;
                $(id).removeClass('disabled');
            }
            if (page.name === 'intro4') { // practice example
                $('#img-a').attr('src', 'images/t3bw21y.png');
                $('#img-b').attr('src', 'images/t3yw2b1.png'); // or $('#imgdiv-b img')
                $('.navCtl').html(navPrev);
            } else {
                $('#img-a').attr('src', 'images/top-constant.png');  // top-constant is t3bw2y1
                $('#img-b').attr('src', 'images/' + getNextImage()); // pseudo-random
                $('.navCtl').html('');
            }
            startTimer(page); // timer to show chosen answer before next, and start game timer
            break;
        case 'home':
        case 'abandon':
            break; // don't do nuttin
        case 'intro': // these are templateIds remember, not page names
            $('.topTxt').html(page.topTxt);
            $('.middleImg img#introImg').attr('src', 'images/' + page.images.top); // e.g. intro1.png - not split and don't have A, B labels
            $('.botTxt').html(page.botTxt);
            $('.navTxt').html(page.navTxt);
            if (page.name === 'intro1') {
                $('.navCtl').html(navNext);
            } else {
                $('.navCtl').html(navPrevNext);
            }
            if (page.name === 'intro5') {
                var ans = answers.pop();
                console.log('ans: ' + ans);
                $('#intro-answer').html(ans + (parseInt(ans) === 2 ? ' - Correct!' : ''));
            }
            break;
        case 'getReady':
            $('.navTxt').html(page.navTxt);
            $('.navCtl').html(navNext);
            break;
        case 'thanks':
            clearTimeout(timeUpTimeout);
            clearTimeout(nextPageTimeout);
            finished();
            break;
        default:
            throw new Error('unrecogised id');
        }

        //scaleImages();
        scaleImagesCBsimple();
        //showDiv((page.templateId));
        $('#' + page.templateId).fadeIn(FADEIN, showPageFinished);
        //showInfo('height: ' + $(window).height()); //attr('height'));
    }

    function showPageFinished() {
        console.log('bind clicks'); // (re-)bind clicks
        $('#pages').on('click', 'a, button, div.row div', containerClick); // prevent double-click
    }


    function prevPage() {
        console.log('prevPage(): current: ' + current); // + ', currentPage(): ' + obj(currentPage());
        $('#' + currentPage().templateId).fadeOut(FADEOUT, prevPageFinished);
    }

    function prevPageFinished() { // eslint throws no-use-before-define, but this is OK in ES5 due to hoisting
        console.log('prevPageFinished()');
        if (current > 0) {
            current -= 1;
        }
        showPage(currentPage());
    }

    function nextPage() { // console.log('nextPage(): current: ' + current);// + obj(currentPage());
        console.log('nextPage(): isTimeUp:' + isTimeUp);
        $('#' + currentPage().templateId).fadeOut(FADEOUT, nextPageFinished);
    }

    function nextPageFinished() {
        console.log('nextPageFinished()');
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

    function showModal(modal) {
        $('#modals').show();
        $('#' + modal).show(); //fadeIn(FADEIN); //console.log('showModal(\'' + modal + '\')');
    }

    function hideModal(modal) {
        $('#modals').hide();
        $('#' + modal).hide(); //fadeOut(FADEOUT);
    }

    // don't need timing stuff
    //$('#results').val(JSON.stringify(answers));
    //var possibleE = test_timer.gethasPossibleError() + reaction_timer.gethasPossibleError() + demo_timer.gethasPossibleError() + total_timer.gethasPossibleError();
    // if (possibleE > 0)
    //     possibleE = 1;
    // writeValue("timererror",possibleE); // document.getElementById(id).value = value;
    // writeValue("performanceTimer",total_timer.gethasPerformance());
    function finished() {
        console.log('finished(): answers: ' + JSON.stringify(answers));
        clearTimeout(timeUpTimeout);

        // fill in form
        document.getElementById('responses').value = JSON.stringify(answers); //$('input[name="results"]').val() = JSON.stringify(answers);
        document.getElementById('timeStarted').value = config.timeStarted;

        // submit automatically
        window.onbeforeunload = null;
        $(window).on('beforeunload', function(){
            $('*').css('cursor', 'progress');
        });
        document.getElementById('feedbackForm').submit(); // action set in init() from config.json
    }
    //$("body").css("cursor", "progress"); // $("body").css("cursor", "default");

    function timeUp() {
        clearTimeout(timeUpTimeout); // in case triggered manually for testing
        isTimeUp = true;
        console.log('timeUp(): isTimeUp:' + isTimeUp);
    }

    function answered(num) {
        console.log('answered: ' + num);
        var page = currentPage();
        var correct = Number(num) === page.correct;
        var timeTaken;
        if (page.name.slice(0, 2) === 'ex') { // real exercise
            timer.lap();
            timeTaken = timer.getElapsed();
            showTime(timeTaken, correct);
            var answer = {
                page: page.name,
                answer: num,
                correct: correct,
                time: timeTaken
            };
            answers.push(answer);
        } else if (page.name.slice(0, 5) === 'intro') {
            answers.push(num);
        }

        if (correct) { // http://stackoverflow.com/a/33457014/535071
            console.log('Correct!');
        } else {
            console.log('Wrong! correct is: ' + page.correct);
        }
        //nextPageTimeout = setTimeout(nextPage, config.nextDelay); // //nextPage(); function object without () otherwise called immediately
        $('#' + currentPage().templateId).fadeOut(FADEOUT, answeredFinished);
    }

    function answeredFinished() {
        console.log('answeredFinished()');
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

    function init() {
        timer = new Timer();
        isTimeUp = false;
        current = 0;

        //levels = randLevels();
        randLevels();
        console.log('levels: ' + levels);

        // set the results form target
        var formAction = config.formAction;
        var loc = location.toString().split('://')[1]; // strip off http://, https://
        if (loc.substr(0, 9) === 'localhost') { // served from gulp
            console.log('loc === localhost');
            formAction = 'http://localhost:8001/' + formAction; // gulp-connect-php - local PHP server
        } // else, is on same server, relative link OK
        formAction = 'http://red.ctsu.ox.ac.uk/~cp/cjb/bbquiz/'; // scratch that, point to red
        $('#feedbackForm').attr('action', formAction);
        console.log('formAction: ' + formAction);

        showPage(currentPage());
    }

    function getConfig() {
        $.getJSON('./config.json', function (data) {
            console.log('getConfig(): got JSON');
            config = data;
            pages = data.pages;
            init();
        }).fail(function (jqxhr, textStatus, errorThrown) { // jqxhr not needed here, but position of args important, not name
            var err = 'error getting JSON: ' + textStatus + ', errorThrown: ' + errorThrown;
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
        console.log('unbind clicks');
        $('#pages').off('click', 'a, button, div.row div', containerClick); // in case resized, or showPage() called another way
        showPage(currentPage()); // ?
    };

    $().ready(function () { //$(document).ready(
        console.log('Document ready');
        $('#devBar').hide();
        if (LIVE) {
            window.onbeforeunload = null;
            window.history.forward();   //prevent repeat after back button - may not work.
            window.onbeforeunload = function() {
                return 'The answers to the questions or tests you are doing at the moment will be lost - is this what you want to do?';
            };
        }
        getConfig();
    });
}());

console.log('main.js ready');


    // http://stackoverflow.com/questions/130396/are-there-constants-in-javascript
    // var WIDTH2X2 = 210; // Width of squares in 2x2 grid is 210px // const?
    // var WIDTH3X3 = 170; // Width of squares in 3x3 grid is 170px // const?

    // js docstring?
    // function setBackground(sel, sheet, pos) { // jQuery selector, sprite sheet, offset pos (px)
    //     var img = 'url("images/' + sheet + '")'; // DON'T include ';' at end of rule, fails silently! (?)
    //     $(sel).css('background-image', img);    // e.g. background-image: url('images/intro1.png');
    //     $(sel).css('background-position', pos); // e.g. background-position: -210px 0px;
    // }

    // function checkImages(page, topExpected, botExpected) {
    //     // for top grids, last (unfilled) tile is yet to be chosen thus redundant in data
    //     if (page.images.top.length !== topExpected) {
    //         throw new Error('Expected ' + topExpected + ' images for top grid in ' + page.name);
    //     }
    //     if (page.images.bottom.length !== botExpected) {
    //         throw new Error('Expected ' + botExpected + ' images for bottom grid in ' + page.name);
    //     }
    // }

    // function applyStyles(page) {
    //     //console.log('applyStyles(): current: ' + current + ', templateId: ' + page.templateId); //');// page: ' + obj(page));
    //     var base, sel, pos, width, img;
    //     // var top = page.images.top;
    //     // var bot = page.images.bottom;

    //     // TODO passing page object - good idea? i.e. is this a copy or a reference (or reference to a copy)?
    //     // saves a few lines a reuses putting checks into a function, but have to pass it page name, top, bottom
    //     // if (page.templateId === 'quiz2x2') {
    //     //     checkImages(page, 3, 6); //var TOP_EXPECTED = 3, BOT_EXPECTED = 6;
    //     //     width = WIDTH2X2;
    //     //     base = 'div#quiz2x2 ';
    //     //     $('div.grid2x2 #missing2x2').css('display', 'none');
    //     // } else if (page.templateId === 'quiz3x3') {
    //     //     checkImages(page, 8, 8); //var TOP_EXPECTED = 8, BOT_EXPECTED = 8;
    //     //     width = WIDTH3X3;
    //     //     base = 'div#quiz3x3 ';
    //     //     $('div.grid3x3 #missing3x3').css('display', 'none');
    //     // } else {
    //     //     throw new Error('templateId: "' + page.templateId + '" not expected');
    //     // }

    //     // could refactor the next two bits into one function (setBackground(), above)
    //     // div#quiz2x2 div.grid2x2 div.row div, div#quiz3x3 div.grid3x3 div.row div
    //     // sel = base + '#top' + i;
    //     // pos = '-' + (width * top[i]) + 'px 0px';
    //     // setBackground(sel, page.sheet, pos); //console.log('sel: ' + sel + ', img: ' + img + ', pos: ' + pos);
    // }

        //console.log('unbind clicks');
        //$('#pages').off('click', 'a, button, div.row div', containerClick); // in case resized, or showPage() called another way
            // seems to cause multiple clicks, erratic behaviour
