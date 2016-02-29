//helper function, unrelated
function getObjectLength(obj)
{
    var length= 0;
    for(var key in obj)
    {
        if(obj.hasOwnProperty(key))
            length++;
    }
    return length;
}

///TIMER/////////////////
var hmTimer = function()
{
    this.startts = 0;
    this.lapts = 0;
    this.hasPerformance = false;
    this.hasPossibleError = false;

    if (typeof window.performance !== 'undefined' && typeof window.performance.now !== 'undefined')
        this.hasPerformance = true;
    this.hasPossibleError = false;
    this.isValid = false;
};

hmTimer.prototype.getTime = function()
{
    if (this.hasPerformance)
        nowish = window.performance.now();
    else
        nowish = new Date().getTime();
    return nowish;
};

hmTimer.prototype.findnow = function()
{
    var nowish = 0;
    var count = 0;
    do
    {
        nowish = this.getTime();
        var testVal = this.getTime();
        var diff = testVal - nowish;
        count++;
    }
    while (((diff < 0) || (diff > 2)) && (count < 10))

    if (count >= 6)
        this.hasPossibleError = true; //keep the start val :(
    return nowish;
};

hmTimer.prototype.now = function()
{
    this.startts = this.findnow();
    this.lapts = 0;
    this.isValid = false;
};

hmTimer.prototype.lap = function()
{
    if (this.startts == 0)
        return;
    this.lapts = this.findnow();
    this.isValid = true;
};


hmTimer.prototype.getElapsed = function()
{
    if (!this.isValid)
        return -1;
    if (this.startts == 0)
        return -1;
    if (this.lapts == 0)
        return -1;

    var diff = this.lapts - this.startts;
    if (diff < 0)
        this.hasPossibleError = true;
    return Math.round(Number(diff)); //round the number in case it is preformce.
};

hmTimer.prototype.gethasPerformance = function()
{
     if (this.hasPerformance)
        return 1;
    return 0;
};

hmTimer.prototype.gethasPossibleError = function()
{
    if (this.hasPossibleError)
        return 1;
    return 0;
};

hmTimer.prototype.copy = function()
{
    var copy = new hmTimer();
    copy.startts = this.startts;
    copy.lapts = this.lapts;

    copy.hasPerformance = this.hasPerformance;
    copy.hasPosibleError = this.hasPosibleError;
    return copy;
};

hmTimer.prototype.getStart = function()
{
    return this.startts;
};

hmTimer.prototype.getLap = function()
{
    return this.lapts;
};

hmTimer.prototype.isValid = function()
{
    return this.isValid;
};

