

/*
function scaleImagesAY() { // copied from hoops main.js for cribbing
    console.log('scaleImagesAY()');

    // we know the natural sizes of the images already (748 x 291)
    // var topWidth = 748,
    //     topHeight = 291,
    //     botWidth = 748,
    //     botHeight = 291;

    var widthExtra = // total width of elements, excluding centre images
    $('.container').outerWidth(true) - $('.container').width() + ($('#pages').outerWidth(true) - $('#pages').width());

    var heightExtra = // total height of elements, excluding centre images
    $('.container').outerHeight(true) - $('.container').height() + ($('.topTxt').is(':visible') ? $('.topTxt').height() : 0) + ($('#imgdiv-a').is(':visible') ? $('#imgdiv-a').outerHeight(true) - $('#imgdiv-a').height() : 0) + ($('#imgdiv-b').is(':visible') ? $('#imgdiv-b').outerHeight(true) - $('#imgdiv-b').height() : 0) + ($('.botTxt').is(':visible') ? $('.botTxt').height() : 0) + ($('#answers').is(':visible') ? $('#answers').height() : 0) + ($('.navTxt').is(':visible') ? $('.navTxt').height() : 0) + ($('.navCtl').is(':visible') ? $('.navCtl').height() : 0);
    // ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +

    // natural image dimensions; .width(), .height() are current dimensions
    var naturalFullWidth = widthExtra + topWidth;
    var naturalFullHeight = heightExtra + topHeight + botHeight;

    // allow 200px for text at bottom
    // var textExtra = 200;

    // .middleImg needs to be scaled from natural width/height to fit in (window height - textExtra) x window width

    // vertical shrink = (window height - 200px) / naturalFullHeight
    // horizontal shrink = window width / naturalFullWidth
    // var scaleV = ($(window).height() - textExtra) / naturalFullHeight;
    var scaleV = $(window).height() / naturalFullHeight;
    var scaleH = $(window).width() / naturalFullWidth;

    // select lower of these scaling values
    var scale = scaleV <= scaleH ? scaleV : scaleH;

    // work out desired dimensions of whole quiz
    var targetWidth = naturalFullWidth * scale; // forget about width, it always fits, down to 300px
    var targetHeight = naturalFullHeight * scale;

    // work out desired height of .middleImg
    var targetMiddleHeight = targetHeight - heightExtra;

    // // need h/w ratio of .middleImg. Typical dimensions: ? TODO
    var hwRatio = 1.15; //1.95; //??
    var middleHWRatio = hwRatio;

    // what innerWidth of .middleImg would create targetMiddleHeight?
    var targetMiddleWidth = targetMiddleHeight * middleHWRatio;

    // set these margins on .middleImg to make the targetWidth and targetHeight
    var setMargins = ($(window).width() - widthExtra - targetMiddleWidth) / 2;
    if (setMargins > 0) {
        // check > 0 - even in this algorithm, shouldn't be?
        $('.middleImg').css('margin-left', setMargins);
        $('.middleImg').css('margin-right', setMargins);
    } else {
        $('.middleImg').css('margin-left', 0);
        $('.middleImg').css('margin-right', 0);
    }

    // show working
    console.log();
    console.log();
    console.log('working for');
    console.log('document: ' + document.body.clientWidth + ' x ' + document.body.clientHeight);
    console.log('window: ' + window.innerWidth + ' x ' + window.innerHeight);
    console.log();
    console.log('topWidth: ' + topWidth + ', topHeight: ' + topHeight + ', botWidth: ' + botWidth + ', botHeight: ' + botHeight);

    // ($('.container').outerWidth(true) - $('.container').width()) +
    // ($('#pages').outerWidth(true) - $('#pages').width());
    console.log('widthExtra = ');
    console.log('    (container.outerWidth [' + $('.container').outerWidth(true) + '] - container.width [' + $('.container').width() + ']) [' + ($('.container').outerWidth(true) - $('.container').width()) + '] + ');
    console.log('    pages.outerWidth [' + $('#pages').outerWidth(true) + '] - pages.width [' + $('#pages').width() + ']) [' + ($('#pages').outerWidth(true) - $('#pages').width()) + '] + ');
    console.log('   == ' + widthExtra);

    console.log('heightExtra =');
    console.log('    (container.outerHeight [' + $('.container').outerHeight(true) + '] - ' + ' container.height [' + $('.container').height() + ']) [' + ($('.container').outerHeight(true) - $('.container').height()) + '] + ');
    console.log('    topTxt.height [' + $('.topTxt').height() + '] + ');
    console.log('    (#imgdiv-a.outerHeight [' + $('#imgdiv-a').outerHeight(true) + '] - #imgdiv-a.height [' + $('#imgdiv-a').height() + ']) [' + ($('#imgdiv-a').is(':visible') ? $('#imgdiv-a').outerHeight(true) - $('#imgdiv-a').height() : 0) + '] + ');
    console.log('     (#imgdiv-b.outerHeight [' + $('#imgdiv-b').outerHeight(true) + '] - #imgdiv-b.height [' + $('#imgdiv-b').height() + ']) [' + ($('#imgdiv-b').is(':visible') ? $('#imgdiv-b').outerHeight(true) - $('#imgdiv-b').height() : 0) + '] + ');
    console.log('    botTxt.height [' + $('.botTxt').height() + ']  + ');
    console.log('    #answers.height [' + $('#answers').height() + '] +');
    console.log('    navTxt.height [' + $('.navTxt').height() + '] +');
    console.log('    navCtl.height [' + $('.navCtl').height() + '] +');
    console.log('   == ' + heightExtra);
    // ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +

    console.log('naturalFullWidth =');
    console.log('    widthExtra [' + widthExtra + '] + topWidth [' + topWidth + '] == ' + naturalFullWidth);
    console.log('naturalFullHeight =');
    console.log('    heightExtra [' + heightExtra + '] + topHeight [' + topHeight + '] + botHeight [' + botHeight + ']');
    console.log('    == ' + naturalFullHeight);

    // allow 200px for text at bottom // var textExtra = 200;
    // .middleImg needs to be scaled from natural width/height to fit in (window height - textExtra) x window width
    // vertical shrink = (window height - 200px) / naturalFullHeight
    // horizontal shrink = window width / naturalFullWidth
    // var scaleV = ($(window).height() - textExtra) / naturalFullHeight;
    console.log('scaleV = window.height [' + $(window).height() + '] / naturalFullHeight [' + naturalFullHeight + '] == ' + scaleV.toFixed(2));
    console.log('scaleH = window.width [' + $(window).width() + '] / naturalFullWidth [' + naturalFullWidth + '] == ' + scaleH.toFixed(2));
    console.log('scale = scaleV [' + scaleV.toFixed(2) + '] <= scaleH  [' + scaleH.toFixed(2) + '] ? ' + scale.toFixed(2));

    console.log('targetWidth = naturalFullWidth [' + naturalFullWidth + '] * scale [' + scale.toFixed(2) + '] == ' + targetWidth.toFixed(2));
    console.log('targetHeight = naturalFullHeight [' + naturalFullHeight + '] * scale [' + scale.toFixed(2) + '] == ' + targetHeight.toFixed(2));
    console.log('targetMiddleHeight = targetHeight [' + targetHeight + '] - heightExtra [' + heightExtra + '] == ' + targetMiddleHeight);

    // var hwRatio = 1.15; //1.95; //??// var middleHWRatio = hwRatio;
    // what innerWidth of .middleImg would create targetMiddleHeight?
    console.log('targetMiddleWidth = targetMiddleHeight [' + targetMiddleHeight + '] * middleHWRatio [' + middleHWRatio + '] == ' + targetMiddleWidth.toFixed(2));
    // var targetMiddleWidth = targetMiddleHeight * middleHWRatio;

    // set these margins on .middleImg to make the targetWidth and targetHeight
    //var setMargins = ($(window).width() - widthExtra - targetMiddleWidth) / 2;
    console.log('setMargins = window.width [' + $(window).width() + '] - widthExtra [' + widthExtra + '] - targetMiddleWidth [' + targetMiddleWidth.toFixed(2) + ']) / 2 == ' + setMargins.toFixed(2));

    console.log('setMargins > 0: ' + (setMargins.toFixed(2) > 0));
    if (setMargins > 0) {
        // check > 0 - even in this algorithm, shouldn't be?
        console.log('    middleImg.margin-left = ' + setMargins.toFixed(2));
        console.log('    middleImg.margin-right = ' + setMargins.toFixed(2));
    } else {
        console.log('    middleImg.margin-left = 0');
        console.log('    middleImg.margin-right = 0');
    }

    // var msg = 'setMargins: ' + setMargins +
    //     ', targetWidth: ' + targetWidth + ', targetHeight: ' + targetHeight +
    //     ', targetMiddleWidth: ' + targetMiddleWidth;
    // console.log(msg);
}*/


function scaleElementAY(elementSelector, naturalElementHeight, naturalElementWidth) { // attempt at generic scaling function
    var heightExtra = $('body').height() - $(elementSelector).height();
    var widthExtra = $('body').width() - $(elementSelector).width();

    var elementHWRatio = $(elementSelector).height() / $(elementSelector).width();
    // var widthExtra = // total width of elements, excluding centre images
    // $('.container').outerWidth(true) - $('.container').width() + ($('#pages').outerWidth(true) - $('#pages').width());

    // var heightExtra = // total height of elements, excluding centre images
    // $('.container').outerHeight(true) - $('.container').height() + ($('.topTxt').is(':visible') ? $('.topTxt').height() : 0) + ($('#imgdiv-a').is(':visible') ? $('#imgdiv-a').outerHeight(true) - $('#imgdiv-a').height() : 0) + ($('#imgdiv-b').is(':visible') ? $('#imgdiv-b').outerHeight(true) - $('#imgdiv-b').height() : 0) + ($('.botTxt').is(':visible') ? $('.botTxt').height() : 0) + ($('#answers').is(':visible') ? $('#answers').height() : 0) + ($('.navTxt').is(':visible') ? $('.navTxt').height() : 0) + ($('.navCtl').is(':visible') ? $('.navCtl').height() : 0);
    // ($('#abandon-div').is(':visible') ? $('#abandon-div').height() : 0) +

    // natural image dimensions; .width(), .height() are current dimensions
    var naturalFullWidth = widthExtra + naturalElementWidth;
    var naturalFullHeight = heightExtra + naturalElementHeight;

    // element needs to be scaled from natural width/height to fit in (window height - textExtra) x window width

    // vertical shrink = (window height - 200px) / naturalFullHeight
    // horizontal shrink = window width / naturalFullWidth
    var scaleV = $(window).height() / naturalFullHeight;
    var scaleH = $(window).width() / naturalFullWidth;

    // select lower of these scaling values
    var scale = scaleV <= scaleH ? scaleV : scaleH;

    // work out desired dimensions of whole quiz
    var targetWidth = naturalFullWidth * scale; // forget about width, it always fits, down to 300px
    var targetHeight = naturalFullHeight * scale;

    // work out desired height of .middleImg
    var targetMiddleHeight = targetHeight - heightExtra;

    // // need h/w ratio of .middleImg. Typical dimensions: ? TODO
    // var hwRatio = 1.15; //1.95; //??
    // var middleHWRatio = hwRatio;

    // what innerWidth of .middleImg would create targetMiddleHeight?
    var targetMiddleWidth = targetMiddleHeight * elementHWRatio;

    // set these margins on .middleImg to make the targetWidth and targetHeight
    var setMargins = ($(window).width() - widthExtra - targetMiddleWidth) / 2;
    if (setMargins > 0) { // check > 0 - even in this algorithm, shouldn't be?
        $(elementSelector).css('margin-left', setMargins);
        $(elementSelector).css('margin-right', setMargins);
    } else {
        $(elementSelector).css('margin-left', 0);
        $(elementSelector).css('margin-right', 0);
    }
}



            //urlParams['sesh_id'];
            // error  ['sesh_id'] is better written in dot notation                    dot-notation


/*                  lines   circles
-----------------------------------
practice-a.svg      laprX   aprX
part-a.svg          laaX    aaX
practice-b.svg      lbprX   bprX
part-b.svg          lbbX    bbX     */
// function attachEventHandlers(game) {
//     var id = '';

    // switch (game):
    // case 'part-a':
    // practice-a.svg      laprX   aprX
    // for (var i = 0; i <= 6) {
    //     id = 'lapr' + String(i);
    // }
    // for (var i = 0; i <= 7) {
    //     id = 'apr' + String(i);
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
//}

// eslint-disable-next-line no-cond-assign <--- doesn't work, but eslint-disable-line does:
