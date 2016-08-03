/*global $ */
/*jslint browser:true */ // define 'document'
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
        $('#' + id).fadeOut('fast'); //document.getElementById(id).style.display = 'none'; //console.log('hideDiv(): id: ' + id);
    }

    function showDiv(id) {
        $('#' + id).slideDown(); //document.getElementById(id).style.display = 'inline'; //console.log('showDiv(): id: ' + id);
    }

    function hidePage(page) {
        hideDiv(page.templateId); //console.log('hidePage(): templateId: ' + page.templateId); //+ obj(page) + '\'');
    }

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
        var base = 'images/' + page.name + '/' + page.name;
        //console.log('setImage(' + sel + ', ' + page.name + ', ' + extn + ')');
        //console.log('base + extn: ' + base + extn + ')');
        $(sel).attr('src', base + extn);
    }

    function showInfo(text) {
        $('#info').html(text);
    }

    function showTime(text, correct) {
        var sel = '#prevTime';
        $(sel).css('color', correct ? 'green' : 'red');
        $(sel).html(text + 'ms');
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

        var topWidth, topHeight, botWidth, botHeight;
        if (currentPage().templateId == 'quiz2x2') {
            topWidth = 420;
            topHeight = 340;
            botWidth = 680;
            botHeight = 365;
        } else if (currentPage().templateId == 'quiz3x3') {
            topWidth = 510;
            topHeight = 405;
            botWidth = 755;
            botHeight = 295;
        }
        // 2x2, 3x2: img.top natural: 420 x 340, img.bot natural: 680 x 365
        // 3x3, 4x2: img.top natural: 510 x 405, img.bot natural: 755 x 295


        // get natural width/height (naturalFullWidth/Height)
        // get window width/height ($(window).width()/height)
        // natural image dimensions; $('.bot').width() etc is current width
        var widthExtra =
            ($('.container').outerWidth(true) - $('.container').width()) +
            ($('#pages').outerWidth(true) - $('#pages').width());

        var heightExtra =
            ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
            ($('.botText').is(':visible') ? $('.botText').height() : 0);

        var naturalFullWidth = widthExtra + botWidth; // bottom image is widest
        var naturalFullHeight = heightExtra + topHeight + botHeight; // combined height of both images

        // allow 200px for text at bottom
        // .gridContainer needs to be scaled from natural width/height to fit in
        // (window height - 200px) x window width

        // vertical shrink = (window height - 200px) / naturalFullHeight
        // horizontal shrink = window width / naturalFullWidth
        var scaleV = ($(window).height() - 200) / naturalFullHeight;
        var scaleH = $(window).width() / naturalFullWidth;

        // scale = vShrink < hShrink ? vShrink : hShrink
        var scale = scaleV <= scaleH ? scaleV : scaleH;

        // work out desired dimensions of whole quiz
        var targetWidth = naturalFullWidth * scale; // forget about width, it always fits, down to 300px
        var targetHeight = naturalFullHeight * scale;

        // work out desired height of .gridContainer
        var targetMiddleHeight = targetHeight - heightExtra;

        // need h/w ratio of .gridContainer. Typical dimensions: 162 x 144. 162 / 144 == 1.125
        var middleHWRatio = 1.125;

        // what innerWidth of .gridContainer would create targetMiddleHeight?
        var targetMiddleWidth = targetMiddleHeight * middleHWRatio;

        // set these margins on .gridContainer to make the targetWidth and targetHeight
        var setMargins = ($(window).width - widthExtra) / 2;
        //setMargin = 0; // dummy

        $('.gridContainer').css('margin-left', setMargins);
        $('.gridContainer').css('margin-right', setMargins);

        //console.log('newWidth: ' + newWidth + ', newHeight: ' + newHeight);
    }
    //var setMargin = ($(window).width() - ($(window).height() - heightExtra) - margins) / 2;

    function scaleImagesCBnew() { // based on current dimensions
        console.log('scaleImagesCBnew()');
        var margins =
            ($('.container').outerWidth(true) - $('.container').width()) +
            ($('#pages').outerWidth(true) - $('#pages').width());
        var heightExtra =
            ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
            ($('.botText').is(':visible') ? $('.botText').height() : 0);
        var setMargins = ($(window).width() - ($(window).height() - heightExtra) - margins) / 2;

        if (setMargins > 0) {
            $('.gridContainer').css('margin-left', setMargins);
            $('.gridContainer').css('margin-right', setMargins);
        } else {
            $('.gridContainer').css('margin-left', 0);
            $('.gridContainer').css('margin-right', 0);
        }
    }

    function scaleImagesCBsimple() { // my calculation, mostly works
        console.log('scaleImagesCBsimple()');
        var widthExtra =
            ($('.container').outerWidth(true) - $('.container').width()) +
            ($('#pages').outerWidth(true) - $('#pages').width());
            // missing some widths?
        var heightExtra = // required height of .gridContainer
            ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +
            ($('.botText').is(':visible') ? $('.botText').height() : 0) + 100;
            // missing some heights?
        var setMargins = ($(window).width() - ($(window).height() - heightExtra) - widthExtra) / 2;

        if (setMargins > 0) {
            $('.gridContainer').css('margin-left', setMargins);
            $('.gridContainer').css('margin-right', setMargins);
        } else { // don't set negative margins. content should shrink width-wise if needed
            $('.gridContainer').css('margin-left', 0);
            $('.gridContainer').css('margin-right', 0);
        }
    }

    // .css('width') is text e.g. '1200px'; .width() is numeric e.g. 1200. .attr('width') is undefined
    // https://api.jquery.com/visible-selector/
    // body shouldn't have any border or margin

        //var heightScrolled = $(document).height() - $(window).height();
        //console.log('#abandon-div h: ' + $('#abandon-div').height() + ', visible: ' + $('#abandon-div').is(':visible')); // works
        //console.log('.botText h: ' + $('.botText').height() + ', visible: ' + $('.botText').is(':visible')); // works
        //console.log('heightExtra: ' + String(heightExtra));
        //console.log('$(document).height(): ' + $(document).height() + ', $(window).height(): ' + $(window).height());
        //console.log('$(\'body\').height(): ' + $('body').height()); // == $(window).height()
        //console.log('heightScrolled: ' + heightScrolled);

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

    function showPage(page) { // prevPage() and nextPage() should handle hiding current
        console.log('showPage(\'' + page.name + '\'): current: ' + current + ', templateId: ' + page.templateId); //');// page: ' + obj(page)); //console.log('showPage(): isTimeUp:' + isTimeUp);

        if (page.hasOwnProperty('suppressAbandon')) {//console.log('page.hasOwnProperty(\'suppressAbandon\')');
            hideDiv('abandon-div');
        } else {
            showDiv('abandon-div');
        }

        var info = current + '/' + pages.length + ': ' + page.name;
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
            finished();
            break;
        default:
            throw new Error('unrecogised id');
        }

        showDiv(page.templateId);
        scaleImagesCBsimple();
        //scaleImagesAY();
        //scaleImagesCBnew();

        switch (page.templateId) { // only after page is set visible?
        case 'quiz2x2':
            $('#3x2-map').imageMapResize(); // https://github.com/davidjbradshaw/image-map-resizer
            break;
        case 'quiz3x3':
            $('#4x2-map').imageMapResize();
            break;
        }
    }

    function prevPage() {
        hidePage(currentPage()); //console.log('prevPage(): current: ' + current); // + ', currentPage(): ' + obj(currentPage());
        if (current > 0) {
            current -= 1;
        }
        showPage(currentPage());
    }

    function nextPage() { // console.log('nextPage(): current: ' + current);// + obj(currentPage());
        hidePage(currentPage()); //console.log('nextPage(): isTimeUp:' + isTimeUp);
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

    function answered(num) {
        var page = currentPage();
        setImage('#' + page.templateId + ' .top', page, '-sol' + num + '.png'); //console.log('got num: ' + num);

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
            if (!correct) {
                showInfo('try again'); // TODO
                showModal('tryagain-modal');
                return;
            }
        }

        if (correct) { // http://stackoverflow.com/a/33457014/535071
            //console.log('Correct!');
        } else {
            //console.log('Wrong! correct is: ' + page.correct);
        }

        nextPageTimeout = setTimeout(nextPage, config.nextDelay); // //nextPage(); function object without () otherwise called immediately
    }

    function containerClick(e) {
        e.preventDefault();
        var clickedEl = $(this),
            elId = clickedEl.attr('id');
        //console.log('containerClick(): current: ' + current + ', clickedEl: ' + elId, 'type: ' + clickedEl.prop('tagName')); // now gets id from loaded page
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
                answered(num);
            }
        }
    }

    function showModal(modal) {
        showDiv('modals');  //console.log('showModal(\'' + modal + '\')');
        showDiv(modal);
    }

    function hideModal(modal) {
        hideDiv('modals');  //console.log('hideModal(\'' + modal + '\')');
        hideDiv(modal);
    }

    // function writeValue(id, value) {
    //     document.getElementById(id).value = value;
    // }

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

    function finished() {
        console.log('finished(): answers: ' + JSON.stringify(answers));
        clearTimeout(timeUpTimeout);

        // fill in form
        document.getElementById("responses").value = JSON.stringify(answers); //$('#results').val(JSON.stringify(answers));
        document.getElementById("timeStarted").value = config.timeStarted;
        //var possibleE = test_timer.gethasPossibleError() + reaction_timer.gethasPossibleError() + demo_timer.gethasPossibleError() + total_timer.gethasPossibleError();
        // if (possibleE > 0)
        //     possibleE = 1;

        // writeValue("timererror",possibleE); // document.getElementById(id).value = value;
        // writeValue("performanceTimer",total_timer.gethasPerformance());

        // submit automatically
        window.onbeforeunload = null;
        $(window).on('beforeunload', function(){
            $('*').css('cursor', 'progress');
        });
        document.getElementById("feedbackForm").submit(); // action set in init() from config.json
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
        var pageId = $('.page').attr('id');
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
        var clickedEl = $(this); //console.log('pageId: '+pageId); // now gets id from loaded page
        //pageId = $('.page').attr('id'),
        //console.log('pageId: ' + pageId + ': elid: ' + clickedEl.attr('id')); //console.log('elid: '+clickedEl.attr('id')+', html: ''+clickedEl.html()+''');
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
        imageMapResize();
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
            e.preventDefault();
            if ($('#devBar').css('display') === 'none') {
                showDiv('devBar');
            } else {
                hideDiv('devBar');
            }
        }
    }

    // bind event handlers to elements
    $('body').on('keydown', keydown); // $("body").keyup(keyup()); // throws error as doesn't exist at this moment?
    $('#pages').on('click', 'a, area, button', containerClick); // delegate events
    $('#devBar').on('click', 'a, button', navClick); // need this?
    $('#abandon-btn').on('click', abandonClick); // need this?
    $('#modals').on('click', 'button', modalClick);

    window.onresize = function(event) { // error  event is defined but never used no-unused-vars ?
        showPage(currentPage()); // ?
    };

    $().ready(function () { //$(document).ready(
        console.log('Document ready');
        hideDiv('devBar');
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
