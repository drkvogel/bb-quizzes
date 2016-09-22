    //var Timer = require('./timer'); // require is a node thing, unless you use requirejs
    // copied/adapted from Jonathan's bb-quizzes/snap/Snap_files/Timer.js

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
