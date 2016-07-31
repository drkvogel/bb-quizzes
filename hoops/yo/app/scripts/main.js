/*global $ */
/*jslint browser:true */ // define 'document'
/* jshint unused:false */
/*eslint-disable no-unused-vars*/
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:

// http://stackoverflow.com/questions/950087/include-a-javascript-file-in-another-javascript-file
(function () { // Immediately-Invoked Function Expression (IIFE)
    // used to set "use strict" for whole scope so jslint doesn't complain, but then have to indent whole scope...
    'use strict';

    var LIVE = false; // const? JSHint doesn't like it

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
            diff = 0;
        do {
            nowish = this.getTime();
            var testVal = this.getTime();
            diff = testVal - nowish;
            count++;
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

    var config,
        pages,
        current,
        timer,
        isTimeUp = false,
        nextPageTimeout,
        timeUpTimeout,
        answers = [];

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
        //for (var page in pages) { // http://stackoverflow.com/questions/500504/why-is-using-for-in-with-array-iteration-such-a-bad-idea
        for (var i = 0; i < pages.length; i++) {
            if (pages[i].name === name) {
                return pages[i];
            }
        }
        throw new Error('unknown page: ' + name);
    }

    function hideDiv(id) {
        //document.getElementById(id).style.display = 'none'; //console.log('hideDiv(): id: ' + id);
        $('#' + id).fadeOut('fast');
        //$('#' + id).slideUp();
    }

    function showDiv(id) {
        //document.getElementById(id).style.display = 'inline'; //console.log('showDiv(): id: ' + id);
        //$('#' + id).fadeIn('fast');
        $('#' + id).slideDown();
    }

    function hidePage(page) {
        hideDiv(page.templateId); //console.log('hidePage(): templateId: ' + page.templateId); //+ obj(page) + '\'');
    }

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

    function showInfo(text) {
        $('#info').html(text);
    }

    function showTime(text, correct) {
        var sel = '#prevTime';
        $(sel).css('color', correct ? 'green' : 'red');
        $(sel).html(text + 'ms');
    }

    function scaleImages() {
        // set the margins/padding to (screen width - height) / 2 ?
        // setting margin-left and margin-right seems to make it shrink...
        var margin = ($(window).width() - $(window).height()) / 2;
        showInfo('$(window).width(): ' + $(window).width() + ', $(window).height()' + $(window).height() + ', margins: ' + margin);
        $('.middleImg').css('margin-left', margin);
        $('.middleImg').css('margin-right', margin);
    }

    function showPage(page) { // prevPage() and nextPage() should handle hiding current
        console.log('showPage(\'' + page.name + '\'): current: ' + current + ', templateId: ' + page.templateId); //');// page: ' + obj(page));
        console.log('showPage(): isTimeUp:' + isTimeUp);

        if (page.hasOwnProperty('suppressAbandon')) {//console.log('page.hasOwnProperty(\'suppressAbandon\')');
            hideDiv('abandon-div');
        } else {
            showDiv('abandon-div');
        }

        var info = current + '/' + pages.length + ': ' + page.name;
        showInfo(info);

        var navNext = '<span id=\"next\" class=\"\"><button class=\"btn\" id=\"next\" href=\"#\">Next &gt;&gt;</button></span>';
        var navPrevNext = '<span class=\"prev\" class=\"col-md-2\"><button class=\"btn pull-left\" id=\"prev\" href=\"#\">&lt;&lt; Prev</button></span><span id=\"next\" class=\"\"><button class=\"btn pull-right\" id=\"next\" href=\"#\">Next &gt;&gt;</button></span>';
        var navPrev = '<span class=\"prev\" class=\"col-md-2\"><button class=\"btn pull-left\" id=\"prev\" href=\"#\">&lt;&lt; Prev</button></span>';
        // pull-left pull-right

        switch (page.templateId) {
        case 'game':
            //applyStyles(page);
            if (page.name.slice(0, 2) === 'ex') {
                timer.now(); // start timer for all real exercises
                if (page.name === 'ex1') {
                    console.log('start game timer');
                    timeUpTimeout = setTimeout(timeUp, config.timeLimit); // 120000ms == 2 minutes
                }
            }
            // img-a - top-constant.png
            $('#img-b').attr('src', 'images/' + page.image);
            // or $('#imgdiv-b img').attr('src', 'images/' + page.image);
            $('.botTxt').html('How many moves would it take to make picture A look like picture B?');
            for (var i = 1; i <= 6; i++) {
                var id = '#ans' + i;
                $(id).removeClass('disabled');
            }
            if (page.name === 'intro4') {
                $('.navCtl').html(navPrev);
            } else {
                $('.navCtl').html('');
            }
            break;
        case 'home':
        case 'getReady':
        case 'abandon':
            break; // don't do nuttin
        case 'intro': // these are templateIds remember, not page names
            $('.topTxt').html(page.topTxt);
            $('.middleImg img').attr('src', 'images/' + page.images.top); // example image: intro1.png? not split and don't have A, B labels
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
                $('#intro-answer').html(ans + (parseInt(ans) === 2 ? ' - Correct!' : '')); //$('#intro-answer').html(JSON.stringify(answers));
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

        scaleImages();
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

    function nextPage() { // console.log('nextPage(): current: ' + current);// + obj(currentPage());
        console.log('nextPage(): isTimeUp:' + isTimeUp);
        hidePage(currentPage());
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
        console.log('showModal(\'' + modal + '\')');
        showDiv('modals');
        showDiv(modal);
    }

    function hideModal(modal) {
        console.log('hideModal(\'' + modal + '\')');
        hideDiv('modals');
        hideDiv(modal);
    }

    function finished() {
        console.log('finished(): answers: ' + JSON.stringify(answers));
        //$('input[name="results"]').val() = JSON.stringify(answers);
        clearTimeout(timeUpTimeout);

        //$('#results').val(JSON.stringify(answers));
        //var possibleE = test_timer.gethasPossibleError() + reaction_timer.gethasPossibleError() + demo_timer.gethasPossibleError() + total_timer.gethasPossibleError();
        // if (possibleE > 0)
        //     possibleE = 1;

        // writeValue("timererror",possibleE); // document.getElementById(id).value = value;
        // writeValue("performanceTimer",total_timer.gethasPerformance());

        // <input type="hidden" name="sid" value="1">
        // <input type="hidden" name="pid" value="213421343">
        // <input type="hidden" name="lsq" value="661">
        // <input type="hidden" name="seqord" value="3">
        // <input type="hidden" name="studytypeuid" value="1002">
        // <input type="hidden" id="timererror" name="timererror" value="-1">
        // <input type="hidden" id="performanceTimer" name="performanceTimer" value="-1">
        // <input type="hidden" name="datestarted" value="2016-02-29 14:47:31 GMT">
        // <input type="hidden" id="abandon" name="abandon" value="0">
        // <input type="hidden" id="mean" name="mean" value="-1">
        // <input type="hidden" id="demoelapsed" name="demoelapsed" value="-1">
        // <input type="hidden" id="totelapsed" name="totelapsed" value="-1">
        // <input type="hidden" id="testelapsed" name="testelapsed" value="-1"

        // fill in form
        document.getElementById('responses').value = JSON.stringify(answers);
        document.getElementById('timeStarted').value = config.timeStarted;

        // submit automatically
        window.onbeforeunload = null;
        $(window).on('beforeunload', function(){
            $('*').css('cursor', 'progress');
        });
        document.getElementById('feedbackForm').submit(); // action set in init() from config.json
    }
    //$("body").css("cursor", "progress"); // $("body").css("cursor", "default");

    // function finished() {
    //     console.log('finished(): answers: ' + JSON.stringify(answers));
    //     //$('input[name="results"]').val() = JSON.stringify(answers);
    //     $('#results').val(JSON.stringify(answers));
    //     clearTimeout(timeUpTimeout);
    //     // TODO send via $.ajax();
    // }

    function timeUp() {
        clearTimeout(timeUpTimeout); // in case triggered manually for testing
        isTimeUp = true;
        console.log('timeUp(): isTimeUp:' + isTimeUp);
    }

    function answered(num) {
        //console.log('got num: ' + num);
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

        nextPageTimeout = setTimeout(nextPage, config.nextDelay); // //nextPage(); function object without () otherwise called immediately
    }

    function containerClick(e) {
        e.preventDefault();
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
        case 'yes':
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

    function abandonClick() {
        console.log('abandon');
        showModal('abandon-modal');
    }

    function navClick(e) {
        e.preventDefault();
        console.log('navClick()');
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
        console.log('navClick()');
        var pageId = $('.page').attr('id'),
            clickedEl = $(this); //console.log('pageId: '+pageId); // now gets id from loaded page
        console.log('pageId: ' + pageId + ': elid: ' + clickedEl.attr('id')); //console.log('elid: '+clickedEl.attr('id')+', html: ''+clickedEl.html()+''');
        switch (clickedEl.attr('id')) {
        case 'abandon-yes':
            hideModal('abandon-modal');
            hidePage(currentPage());
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

        $('#button').css('display', LIVE ? 'none' : 'inline');

        var formAction = config.formAction;
        var loc = location.toString().split('://')[1]; // strip off http://, https://
        if (loc.substr(0, 9) === 'localhost') { // served from gulp
            console.log('loc === localhost');
            formAction = 'http://localhost:8000/' + formAction; // gulp-connect-php - local PHP server
        } // else, is on same server, relative link OK
        $('#feedbackForm').attr('action', formAction);

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
        e.preventDefault();
        console.log('keyboard event: ' + e.which);
        if (e.which === 68) { //console.log('"d" pressed');
            if ($('#buttons').css('display') === 'none') {
                showDiv('buttons');
            } else {
                hideDiv('buttons');
            }
        }
    }

    $('body').on('keydown', keydown);
    $('#pages').on('click', 'a, button, div.row div', containerClick); // delegate events
    $('#buttons').on('click', 'a, button', navClick); // need this?
    $('#abandon-btn').on('click', abandonClick); // need this?
    $('#modals').on('click', 'button', modalClick);

    window.onresize = function(event) {
        showPage(currentPage()); // ?
        showInfo('height: ' + $(window).height()); //attr('height'));
        //$('.container').attr('width', $(window).height()); // sets it but nothing else, doesn't change width

        scaleImages();
    };

    $().ready(function () { //$(document).ready(
        console.log('Document ready');
        hideDiv('buttons');
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
