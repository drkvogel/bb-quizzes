/*global $ */ // assume jquery
/*jslint browser:true */ // assume 'document'
/* jshint unused:false */
/*eslint-disable no-unused-vars*/
/*eslint-disable strict */
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:

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
    levels = [], // ?
    nextCircle = 1,
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

function showTime(text, isCorrect) {
    var sel = '#prevTime';
    $(sel).css('color', isCorrect ? 'green' : 'red');
    $(sel).html(text + 'ms');
}

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
    $('#pages').on('click', 'a, button, div.row div', containerClick); // prevent double-click
    if (currentPage().name === 'thanks') { // redundant?
        console.log('currentPage().name === \'thanks\'');
        setTimeout(finished, 3000);
    }
}

function showPage(page) { // prevPage() and nextPage() should handle hiding current //console.log('showPage(\'' + page.name + '\'): current: ' + current + ', templateId: ' + page.templateId); // page: ' + obj(page)); isTimeUp:' + isTimeUp);
    if (page.hasOwnProperty('suppressAbandon')) {//console.log('page.hasOwnProperty(\'suppressAbandon\')');
        $('#abandon-div').hide(); //fadeOut(FADEOUT);
    } else {
        $('#abandon-div').fadeIn(FADEIN);
    }
    var info = current + '/' + pages.length + ': ' + page.name + ', timeUp: ' + String(isTimeUp);
    showInfo(info);
    switch (page.templateId) {
    case 'game':
        $('.botTxt').html('<text>');
        if (page.type === 'practice') { // practice example
            startTimer(page); // timer to show chosen answer before next, and start game timer
        }
        $('#svg1').attr('data', 'images/' + page.name + '.svg');
        $('.navCtl').html('');
        $('.botTxt').html(page.botTxt); //console.log('puzzle.b: ' + puzzle.b + ', correct: ' + puzzle.c); //puzzle = config.practice; ??
        break;
    case 'home':
    case 'abandon':
        break; // don't do nuttin
    case 'intro': // these are templateIds remember, not page names
        $('.topTxt').html(page.topTxt);
        $('.botTxt').html(page.botTxt);
        $('.navTxt').html(page.navTxt);
        if (page.name === 'intro1') {
            $('.navCtl').html(config.navNext);
        } else {
            $('.navCtl').html(config.navPrevNext);
        }
        if (page.name === 'intro5') {
            var ans = answers.pop(); console.log('intro5 ans: ' + ans);
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
        setTimeout(finished, 3000);
        $('*').css('cursor', 'progress');
        break;
    default:
        throw new Error('unrecogised id');
    }
    $('#' + page.templateId).fadeIn(FADEIN, showPage2);
}
    //scaleImages();
    //showInfo('height: ' + $(window).height()); //attr('height'));

function prevPage2() { // eslint throws no-use-before-define, but this is OK in ES5 due to hoisting
    if (current > 0) {
        current -= 1;
    } //console.log('prevPage2()');
    showPage(currentPage());
}

function prevPage() { //console.log('prevPage(): current: ' + current); // + ', currentPage(): ' + obj(currentPage());
    $('#' + currentPage().templateId).fadeOut(FADEOUT, prevPage2);
}

function nextPage2() { //console.log('nextPage2(): current + 1 < pages.length: ' + String(current + 1 < pages.length));
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

function nextPage() { // console.log('nextPage(): current: ' + current + 'isTimeUp:' + isTimeUp); // + obj(currentPage());
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

/*                  lines   circles
-----------------------------------
practice-a.svg      laprX   aprX
part-a.svg          laaX    aaX
practice-b.svg      lbprX   bprX
part-b.svg          lbbX    bbX     */
function attachEventHandlers(game) {
    var id = '';

    // switch (game):
    // case "part-a":
    // practice-a.svg      laprX   aprX
    // for (var i = 0; i <= 6) {
    //     id = "lapr" + String(i);
    // }
    // for (var i = 0; i <= 7) {
    //     id = "apr" + String(i);
    // }

    // part-a.svg          laaX    aaX
    // for (var i = 1; i <= 25; i++) {
    //     id = 'apr' + String(i);
    //     var circle = svgDoc.getElementById(id); // get inner element by id
    //     circle.addEventListener('mousedown', function () {// add behaviour
    //         alert('I am ' + id);
    //     }, false);
    // }
    // practice-b.svg      lbprX   bprX
    // part-b.svg          lbbX    bbX
}


function fillRed(id) {
    // console.log('fillRed(): ' + id)
    $(id).attr('fill', 'red');
}

function fillWhite(id) {
    $(id).attr('fill', 'white');
}

function fillYellow(id) {
    $(id).attr('fill', 'yellow');
}

function wrong(id) { // console.log('wrong(): ' + id);
    var group = document.getElementById('svg1').contentDocument.getElementById(id);
    var circles = group.getElementsByTagName('circle');
    var circle = circles[0];
    fillRed(circle);
    setTimeout(function() { fillWhite(circle); }, 100);
    setTimeout(function() { fillRed(circle); }, 200);
    setTimeout(function() { fillWhite(circle); }, 300);
    setTimeout(function() { fillRed(circle); }, 400);
    setTimeout(function() { fillWhite(circle); }, 500);
    // for (var i = 0; i < 5; i++) {
    //     setTimeout(function() { fillWhite(circle); }, 500);
    //     $(id).attr('fill', 'red');
    // };
}

// function circleClick(id) {
//     //?
// }

function correct(num) {
    var svg = document.getElementById('svg1');
    var id = currentPage().prefix + String(num);
    console.log('correct(): id: ' + id);
    //var circle = svg.contentDocument.getElementById('aa' + String(num));
    var group = svg.contentDocument.getElementById(num);
    var circles = group.getElementsByTagName('circle');
    var circle = circles[0];
    fillYellow(circle);
    //var line = svg.contentDocument.getElementById('laa' + String(num + 1));
    var line = svg.contentDocument.getElementById('laa0');
    //line.style.display = 'inline'; //? // $('#l' + id).show(); // $(line).show();
    $(line).attr('display', 'inline');
}

// "name" : "part-a",
// "type" : "game",
// "templateId" : "game",
// "numCircles" : 25,
// "prefix" : "aa"
function addListeners(game) {
    console.log('addListeners()');
    var svg1 = document.getElementById('svg1');
    svg1.addEventListener('load', function () { // add load event listener to object, as will load svg asynchronously
        console.log('svg loaded');
        var svgDoc = svg1.contentDocument; // get inner DOM of svg
        var prefix = 'g' + currentPage().prefix;
        console.log('prefix: ' + prefix);
        for (var i = 1; i < currentPage().numCircles; i++) {
            var id = prefix + String(i);
            // var ix = i;
            //console.log('add event listener to ' + id);
            try {
                var group = svgDoc.getElementById(id); // get inner element by id
                if (i === nextCircle) { // global
                    console.log('i === next: ' + i);
                    group.addEventListener('mousedown', function () { // yellow fill for correct answer
                        correct(this.id); // works, this.id is id of circle
                    }, false);
                } else {
                    group.addEventListener('mousedown', function () {// add behaviour
                        wrong(this.id); // red flash
                    }, false);
                }
            } catch (err) {
                console.log('error adding listener to ' + id + ': ' + err);
            }
        }
    }, false);
}

        // // dev - add listener to group
        // var group = svgDoc.getElementById('g3'); // get inner element by id
        // group.addEventListener('mousedown', function () {
        //     console.log('group clicked');
        //     wrong(this.id); // flash circle, not group
        // }, false);
                        // this.id == window.id? no, closed over id set on definition ... ?
                        // or id of circle? which is why this.ix didn't work....
                        // http://javascriptissexy.com/understand-javascripts-this-with-clarity-and-master-it/

function init() {
    timer = new Timer(); // globals
    timerWholeTest = new Timer(); // globals
    isTimeUp = false;
    current = 0;
    addListeners(); //attachEventHandlers('part-a');
    var msg;
    if (LOCAL) {
        config.seshID = 4321;
        msg = 'this is a local web application for local people';
        $('#feedbackForm').attr('action', 'http://localhost/backend-doesnt-exist'); //'http://xrat.ctsu.ox.ac.uk/~cp/bbquiz/');
    } else {
        if (!urlParams.hasOwnProperty('sesh_id')) { // probably on testing server
            config.seshID = -4321; //throw new Error(msg);
            msg = 'not LOCAL and sesh_id not found in urlParams, set config.seshID to ' + config.seshID;
            $('#feedbackForm').attr('action', 'complete.php');
        } else {
            msg = 'config.sesh_id: ' + config.seshID;
            config.seshID = urlParams.sesh_id;
            $('#feedbackForm').attr('action', config.formAction); // set the results form target
        }
    }
    console.log(msg); //console.log('formAction: ' + config.formAction);
    $('#home .debug').html('<code>' + msg + '</code>');
    showPage(currentPage());
    config.tinstruct = isoDate(); console.log('config.tinstruct: ' + config.tinstruct);
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
    if (e.which === 68) { //console.log(''d' pressed');
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

console.log('main.js ready');

            //urlParams['sesh_id'];
            // error  ['sesh_id'] is better written in dot notation                    dot-notation
