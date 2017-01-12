/*global $, debounce */ // assume jquery
/*jslint browser:true */ // assume 'document'
/* jshint unused:false */
/*eslint-disable no-unused-vars*/
/*eslint-disable no-unreachable*/
/*eslint-disable strict */
// /*jslint plusplus: true */ // doesn't work with sublime jslint plugin:

var LIVE = false, // const? JSHint doesn't like it
    LOCAL = false,
    MAX_LEVELS = 4,
    FADEIN = 100,
    FADEOUT = 100,
    config,
    pages,
    answers = [],
    wrongClicks = 0,
    current,
    timerClick,
    timerPuzzle,
    isTimeUp = false,
    nextPageTimeout,
    timeUpTimeout,
    nextCircle = 1,
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

function logObj(o) { // log formatted object to console
    return JSON.stringify(o, null, 4);
}

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

function isoDate() { // return date string in format yyyy-mm-ddThh:mm:ss, suitable for parsing by xtime.cpp
    var date = new Date(); // date.toISOString() is UTC/GMT with milliseconds, e.g. '2016-09-21T10:47:54.671Z'
    return date.toISOString().substring(0, 19); // strip milliseconds. timezone not needed, is GMT
}

function timeUp() {
    clearTimeout(timeUpTimeout); // in case triggered manually for testing
    isTimeUp = true;
    console.log('timeUp(): isTimeUp:' + isTimeUp);
}

// function startTimer(page) {
//     timerClick.now(); // start timer for practices *and* real exercises
//     timerPuzzle.now(); // start timer for the whole game (for 'elapsed' field)
//     config.timeStarted = isoDate();
//     console.log('config.timeStarted: ' + config.timeStarted);
//     timeUpTimeout = setTimeout(timeUp, config.timeLimit);
// }

function containerClick(e) {
    e.preventDefault();
    $('#pages').off('click', 'button', containerClick); // prevent double-click
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
    }
}
    // console.log('containerClick(e): ' + e.handleObj.selector); //logObj(e));
    // console.log('containerClick(e): unbind');// + logObj(this));// + logObj(e));


// if necessary, shrink an element by setting margins so that all body content fits in the viewport height
function scaleElementCB(el) { // attempt at generic scaling function
        // + arg for min height?
    var heightExtra = $('body').outerHeight(true) - el.outerHeight(true);
    var widthExtra = $('body').outerWidth(true) - el.outerWidth(true);
    var minHeight = 200; // minumum height the element will be scaled to
    var padHeight = 50; // shouldn't need pad height if html has adequate margins!

    // work out the desired height of element
    // given the available window height and the other things that need to fit
    var targetHeight = $(window).height() - heightExtra - padHeight;
    if (targetHeight < minHeight) {
        targetHeight = minHeight;
    }

    // what width would the element need to be to have the target height?
    var elementHWRatio = el.height() / el.width(); // the element's aspect ratio, regardless of current size
    var targetWidth = targetHeight / elementHWRatio;

    // set both margins to decrease to the target width and therefore the target height
    var setMargins = ($(window).width() - widthExtra - targetWidth) / 2;
    if (setMargins < 0) {
        setMargins = 0;
    }
    el.css('margin-left', setMargins);
    el.css('margin-right', setMargins);
    // console.log('heightExtra: ' + heightExtra + ' ((\'body\').height(): ' + $('body').height() + ' - el.height(): ' + el.height() + ')');
    // console.log('widthExtra: ' + widthExtra.toFixed(2) + ' ($(\'body\').width(): ' + $('body').width() + ' - el.width(): ' + el.width() + ')');
    // console.log('targetHeight : ' + targetHeight + '($(window).height(): ' + $(window).height() + ' - heightExtra: ' + heightExtra + ')');
    // console.log('elementHWRatio: ' + elementHWRatio.toFixed(2) + ', targetWidth: ' + targetWidth.toFixed(2) + ', setMargins: ' + setMargins.toFixed(2));
}

function scaleElement(elementSelector) {
    console.log('scaleElement()');
    scaleElementCB($(elementSelector));
}

function scaleImages() {
    scaleElement('#puzzle');
}

function showPage2() {
    $('#pages').on('click', 'button', containerClick); // prevent double-click
    if (currentPage().name === 'thanks') { // redundant?
        setTimeout(finished, 3000);
    }
    switch (currentPage().templateId) {
    case 'game':
        scaleImages();
        //debounce(scaleImages, 100);
        timerPuzzle.now(); // start timer for all real exercises
        timerClick.now();
        if (!config.hasOwnProperty('timeStarted')) {
            config. timeStarted = isoDate();
            console.log('config.timeStarted: ' + config.timeStarted);
        }
        timeUpTimeout = setTimeout(timeUp, config.timeLimit);
        break;
    default:
        break;
    }
    console.log(' '); // (re-)scaleImages();bind clicks
}
    // console.log('showPage2: currentPage().name: ' + currentPage().name); // (re-)scaleImages();bind clicks
    // console.log('showPage2: bind'); // (re-)scaleImages();bind clicks

function showPage(page) { // prevPage() and nextPage() should handle hiding current
    console.log('showPage(): name: ' + page.name + ', current: ' + current + ', templateId: ' + page.templateId); // page: ' + obj(page)); isTimeUp:' + isTimeUp);
    if (page.hasOwnProperty('suppressAbandon')) {//console.log('page.hasOwnProperty(\'suppressAbandon\')');
        $('#abandon-div').hide(); //fadeOut(FADEOUT);
    } else {
        $('#abandon-div').fadeIn(FADEIN);
    }
    var info = current + '/' + pages.length + ': ' + page.name + ', timeUp: ' + String(isTimeUp);
    showInfo(info);
    switch (page.templateId) {
    case 'game':
        var img = 'images/' + page.name + '.svg'; console.log('showPage(): loading img == ' + img);
        $('#svg1').attr('data', img);
        //$('#svg1').load(scaleImages());

        if (page.type === 'practice') { // practice example
            $('.botTxt').html(page.botTxt); //console.log('puzzle.b: ' + puzzle.b + ', correct: ' + puzzle.c); //puzzle = config.practice; ??
            $('.topTxt').html(page.topTxt);
        } else {
            $('.navCtl').html('');
            $('.topTxt').html('');
            $('.botTxt').html(''); //console.log('puzzle.b: ' + puzzle.b + ', correct: ' + puzzle.c); //puzzle = config.practice; ??
        }
        $('#abandon-btn').show();
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
        throw new Error('unrecogised page.templateId');
    }
    $('#' + page.templateId).fadeIn(FADEIN, showPage2);
}
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
    } else if (current + 1 < pages.length) { //
        current += 1;
        page = currentPage();
    } else {
        console.log('nextPage2(): hit the end at current: ' + current);
        page = currentPage();
    }
    console.log('nextPage2(): ' + current);
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

function finished() { // fill in form and submit automatically
    clearTimeout(timeUpTimeout);
    document.getElementById('sesh_id').value = config.seshID;
    document.getElementById('tinstruct').value = config.tinstruct;
    document.getElementById('tstart').value = config.timeStarted;
    document.getElementById('tfinish').value = isoDate(); // now
    document.getElementById('ntests').value = answers.length; // number of clicks, more like
    document.getElementById('responses').value = JSON.stringify(answers); //$('input[name='results']').val() = JSON.stringify(answers);
    window.onbeforeunload = null;
    $(window).on('beforeunload', function(){
        $('*').css('cursor', 'default');
    });
    document.getElementById('feedbackForm').submit(); // action set in init() from config.json
    console.log('finished(): answers: ' + JSON.stringify(answers));
    // console.log('finished(): auto-submit disabled for testing ' + JSON.stringify(answers));
}

function abandonClick() {
    console.log('abandon');
    showModal('abandon-modal');
}

function devClick(e) {
    console.log('devClick(): unbind');
    e.preventDefault();
    $('#pages').off('click', 'button', containerClick); // otherwise will be duplicated in showPage2()
    var pageId = $('.page').attr('id'), clickedEl = $(this); // now gets id from loaded page
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

function fillRed(id) {
    $(id).attr('fill', 'red');
}

function fillWhite(id) {
    $(id).attr('fill', 'white');
}

function fillYellow(id) {
    $(id).attr('fill', 'yellow');
}

function logEvent(element) { // for practices and real puzzles
    var page = currentPage();
    timerClick.lap();
    timerPuzzle.lap();
    var answer = {
        wrongClicks: wrongClicks,               // number of wrong clicks before correct
        duration: timerClick.getElapsed(),      // Time taken to click on next correct element
        elapsed: timerPuzzle.getElapsed()       // cumulative time elapsed
    }; // name of puzzle/practice, id of element clicked on by user can be determined by position in list
    console.log('logEvent(): element: ' + element + ', answer: ' + logObj(answer));
    answers.push(answer);
    timerClick.now();
}
    //showTime(timeTaken, isCorrect);

function wrong() { // console.log('wrong(): ' + this.id);
    wrongClicks++; // only log correct
    var group = document.getElementById('svg1').contentDocument.getElementById(this.id);
    var circles = group.getElementsByTagName('circle');
    var circle = circles[0];
    fillRed(circle);
    setTimeout(function() { fillWhite(circle); }, 100);
    setTimeout(function() { fillRed(circle); }, 200);
    setTimeout(function() { fillWhite(circle); }, 300);
    setTimeout(function() { fillRed(circle); }, 400);
    setTimeout(function() { fillWhite(circle); }, 500);
}
    // for (var i = 0; i < 5; i++) {
    //     setTimeout(function() { fillWhite(circle); }, 500);
    //     $(id).attr('fill', 'red');
    // };

function correct() { // console.log('correct(): id: ' + this.id); // 'this' refers to the object (group) that invoked it
    logEvent(this.id); // only log correct, and number of wrong before it
    wrongClicks = 0;
    var svg = document.getElementById('svg1');
    var group = svg.contentDocument.getElementById(this.id); // as callback is a closure, has access to enclosing scope (this)
    var circles = group.getElementsByTagName('circle');
    var circle = circles[0];
    fillYellow(circle);

    var num = Number(this.id.slice(1)); //console.log('correct(): num: ' + num + ', clicked: ' + this.id);
    var ellipse = svg.contentDocument.getElementById('e' + String(num)); // correct node
    $(ellipse).remove();
    if (nextCircle !== 1) {
        var line = svg.contentDocument.getElementById('l' + String(num - 1)); // why did I make ids 0-indexed?
        $(line).attr('display', 'inline'); // $(line).show() ?
    }
    if (nextCircle < currentPage().numCircles) {
        nextCircle++;
        changeListeners();
    } else { // reset 1st circle
        nextCircle = 1;
        var first = document.getElementById('svg1').contentDocument.getElementById('g1');
        first.removeEventListener('mousedown', wrong);
        first.addEventListener('mousedown', correct);
        $('#pages').off('click', 'button', containerClick); // otherwise will be duplicated in showPage2()
        $('#abandon-btn').hide();
        setTimeout(nextPage, 1000);
    }
}

// To remove event handlers, the function specified with the addEventListener() method must be an external, 'named' function
function changeListeners() {
    var oldId = 'g' + String(nextCircle - 1), newId = 'g' + String(nextCircle);
    var svgDoc = document.getElementById('svg1').contentDocument; // get inner DOM of svg
    var oldGroup = svgDoc.getElementById(oldId);
    oldGroup.removeEventListener('mousedown', correct);
    var newGroup = svgDoc.getElementById(newId);
    newGroup.removeEventListener('mousedown', wrong); // no longer wrong
    newGroup.addEventListener('mousedown', correct); // works, this.id is id of group
}
    //console.log('changeListeners(): nextCircle: ' + nextCircle);
    //console.log('changeListeners(): oldId: ' + oldId, ', newId: ' + newId);

function addListeners() {
    console.log('addListeners()');
    var svg1 = document.getElementById('svg1');
    svg1.addEventListener('load', function () { // will be invoked each time svg loaded
        console.log('addListeners(): svg1 loaded');
        var svgDoc = svg1.contentDocument; // get inner DOM of svg
        var prefix = 'g';// + currentPage().prefix;
        for (var i = 1; i <= currentPage().numCircles; i++) {
            var id = prefix + String(i); //console.log('add event listener to ' + id);
            try {
                var group = svgDoc.getElementById(id); // get inner element by id
                if (i === nextCircle) { // global //console.log('i === next: ' + i);
                    group.addEventListener('mousedown', correct, false);
                } else {
                    group.addEventListener('mousedown', wrong, false);
                }
            } catch (err) {
                console.log('error adding listener to ' + id + ': ' + err);
            }
        }
        scaleImages();
    }, false);
}
    // this.id == window.id? no, closed over id set on definition ... ?
    // or id of circle? which is why this.ix didn't work....
    // http://javascriptissexy.com/understand-javascripts-this-with-clarity-and-master-it/

function keydown(e) {
    //console.log('keyboard event: ' + e.which);
    if (e.which === 68) { //console.log(''d' pressed');
        e.preventDefault(); // don't trap other keypresses e.g. ctrl-shift-i for dev tools
        if ($('#devBar').css('display') === 'none') {
            $('#devBar').show();
        } else {
            $('#devBar').hide();
        }
    }
}

function init() {
    timerClick = new Timer(); // globals
    timerPuzzle = new Timer(); // globals
    timerPuzzle.now();
    isTimeUp = false;
    current = 0;

    var msg;
    var loc = location.toString().split('://')[1].split('.')[0]; // strip off http://, https://
    console.log('loc: ' + loc);
    // switch (loc.substr(0, 3) {
    switch (loc) {
        case 'oqs':         // assume oqs[web].ndph.ox.ac.uk
            if (!urlParams.hasOwnProperty('sesh_id')) { // probably on testing server
                throw new Error('not local and sesh_id not found in urlParams');
            }
            config.seshID = urlParams.sesh_id;
            msg = 'config.sesh_id: ' + config.seshID;
            $('#feedbackForm').attr('action', config.formAction); // set the results form target
            break;
        case 'loc':         // assume localhost, served from gulp
            msg = 'this is a local web application for local people';
            $('#feedbackForm').attr('action', config.formAction); // set the results form target
            break;
        default:
            config.seshID = -1111;
            $('#feedbackForm').attr('action', config.formAction); // set the results form target
            //$('#feedbackForm').attr('action', 'complete.php');
    }

    // if (LOCAL) {
    //     config.seshID = -1111;
    //     $('#feedbackForm').attr('action', config.formAction); // set the results form target
    // }
    console.log(msg); //console.log('formAction: ' + config.formAction);
    //$('#home .debug').html('<code>' + msg + '</code>');

    // event handlers
    $('body').on('keydown', keydown);
    $('#devBar').on('click', 'a, button', devClick); // delegate events
    $('#abandon-btn').on('click', abandonClick);
    $('#modals').on('click', 'button', modalClick);

    if (LIVE) {
        window.onbeforeunload = null;
        window.history.forward();   //prevent repeat after back button - may not work.
        window.onbeforeunload = function() {
            return 'The answers to the questions or tests you are doing at the moment will be lost - is this what you want to do?';
        };
    }
    config.tinstruct = isoDate(); console.log('config.tinstruct: ' + config.tinstruct);
    addListeners(); // attach EventHandlers('part-a');

    window.addEventListener('resize', debounce(scaleImages, 100));
    window.addEventListener('orientationchange', debounce(scaleImages, 100));

    showPage(currentPage());
}
    // window.onresize = function(event) {
    //     console.log('onresize');
    //     scaleImages();
    // };
    //$('#devBar').hide();
    // var loc = location.toString().split('://')[1]; // strip off http://, https://
    // if (loc.substr(0, 9) === 'localhost') { // served from gulp
    //     LOCAL = true;
    // }

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

// get url params
// TODO - is onpopstate supported in all browswers? http://stackoverflow.com/questions/15896434/window-onpopstate-on-page-load
(window.onpopstate = function() { // why in IIFE?
    var match,
        pl = /\+/g,  // Regex for replacing addition symbol with a space
        search = /([^&=]+)=?([^&]*)/g,
        decode = function(s) { return decodeURIComponent(s.replace(pl, ' ')); },
        query = window.location.search.substring(1);
    while (match = search.exec(query)) { // eslint-disable-line no-cond-assign
       urlParams[decode(match[1])] = decode(match[2]);
    }
    for (var urlParam in urlParams) {
        console.log('urlParam: ' + urlParam + ' is ' + urlParams[urlParam]);
    }
})();

$().ready(function () { //$(document).ready(
    console.log('Document ready');
    getConfig();
});

console.log('main.js ready');

