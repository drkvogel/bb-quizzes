

// const int levelData::m_answers[MAX_LEVELS] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5};
// int levelData::m_rndLevel[MAX_LEVELS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
// int levelData::m_sudoRndLevelList[MAX_LEVELS] = {1, 3, 2, 1, 4, 2, 5, 2, 2, 3, 1, 5, 4, 4, 5, 4, 1, 5};

// m_levelData = levelData::getRandomiseWithFixedDifficulty();
//     pLevelData->rndFixedLevels();

// void levelData::rndFixedLevels() {
//     rndIntArray m_newRndLevel[5];

//     for (int i=0; i<MAX_LEVELS; i++) {
//         int forLevel = m_answers[ i ];
//         m_newRndLevel[ forLevel-1 ].push( i ); // populate m_newRndLevel with wanted 'level' (number of moves, i.e. the answer)
//     }

//     for (int i=0; i<MAX_LEVELS; i++) {
//         int wantedLevel = m_sudoRndLevelList[ i ];
//         m_rndLevel[ i ] = m_newRndLevel[ wantedLevel-1 ].pop();
//     }
// }

// class rndIntArray {
//     rndIntArray(int size = 18) {
//         srand(time(NULL));
//         m_size = size;
//         m_used = 0;
//         m_data = NULL; // int *m_data;
//     }
//     void push(int newInt) {
//         checkGrow();                            // check if the size of the array needs to grow
//         m_data[m_used] = newInt;                // push the value onto the stack
//         m_used++;
//     }
//     int pop() {
//         if (isEmpty())
//             throw Exception_rndIntArray_Empty();
//         int index = 0;
//         if (m_used > 1)
//             index = (rand() % (m_used-1));      // pick a random element from the list
//         int result = m_data[index];             // that's your popped result
//         for (int i=index;i<m_used-1;i++)
//             m_data[i] = m_data[i+1];            // shuffle the others left to fill gap
//         m_used--;                               // number of elements is one less
//         return result;
//     }
//     bool isEmpty() { return (m_used==0); }
//     int *m_data;
//     int m_size;
//     int m_used;
// };

// function RandIntArray(size) {
//     this.RandIntArray = function() {
//         //alert("contructor");
//         console.log("contructor");
//     };
//     this.pop = function() {
//         //alert("pop");
//         console.log("pop");
//     };
//     this.hello = function() {
//         console.log('hello from var RandIntArray');
//     };
// }
//RandIntArray.hello(); // TypeError: RandIntArray.hello is not a function

// var RandIntArray2 = {
//     push: function(newInt) {
//         //
//     },
//     pop: function () {
//         //
//     },
//     hello: function() {
//         console.log('hello from var RandIntArray2');
//     }
// };
//RandIntArray2.hello();

function RandIntArray3(_size) {
    var size, data;
    console.log("constructor");
    size = _size;
    // this.constructor = function() {
    //     console.log("contructor");
    // };
    this.pop = function() {
        console.log("pop");
    };
    this.hello = function() { // TypeError: RandIntArray.hello is not a function
        console.log('hello from function RandIntArray3');
    };
}
// RandIntArray3.constructor = function() {
//     console.log("constructor");
// };
RandIntArray3.prototype.hello = function() {
    console.log('hello from function RandIntArray3');
};
// var rand3 = new RandIntArray3();
// rand3.hello();

////

function RandIntArrayCppStyle(_data,_size) {
    var size, used, data = []; //new Array();

    console.log("RandIntArray constructor");
    size = _size;
    used = 0;

    data = _data;
    size = data.length;
    console.log('data: ' + String(data));
    console.log('data.length: ' + String(data.length));
    console.log('size: ' + String(size));

    this.push = function(newInt) {
        console.log('push(): ' + String(newInt));
        data[used] = newInt;
        used++;
    };
    this.pop = function() {
        if (used <= 0) {
            return null; //throw new Exception('tried to pop empty stack');
        }
        used--;
        console.log("pop()" + String(data[used]));
        return data[used];
    };
    this.list = function() {
        for (var i=0; i<used; i++) {
            console.log('data[' + String(i) + ']: ' + String(data[i]));
        }
        // body...
    };
}
// RandIntArray3.prototype.hello = function() {
//     console.log('hello2 from function RandIntArray');
// };
    //var size, used, data = []; //new Array();
    // console.log("RandIntArray constructor");

    // //data = _data;
    // //size = data.length;
    // console.log('data: ' + String(data));
    // console.log('data.length: ' + String(data.length));
    //console.log('size: ' + String(size));

    // this.push = function(newInt) {
    //     console.log('push(): ' + String(newInt));
    //     data[used] = newInt;
    //     used++;
    // };
        //console.log("pop() random idx: " + String(randIndex) + " (" + String(data[randIndex]) + "), data.length: " + String(data.length));

function RandIntArray(data) {
    this.pop = function() {
        if (data.length <= 0) {
            return null; //throw new Exception('tried to pop empty stack');
        }
        var randIndex = Math.floor((Math.random() * data.length));
        return data.splice(randIndex, 1);
    };
    this.list = function() {
        for (var i = 0; i < data.length; i++) {
            process.stdout.write('[' + String(i) + ']: ' + String(data[i]) + ' '); //console.log('data[' + String(i) + ']: ' + String(data[i]));
        }
        console.log(''); // cause of process.stdout.write()
    };
}

function RandIntArray(data) {
    this.pop = function() {
        if (data.length <= 0) {
            return null; //throw new Exception('tried to pop empty stack');
        }
        var randIndex = Math.floor((Math.random() * data.length));
        return data.splice(randIndex, 1);
    };
    this.list = function() {
        for (var i = 0; i < data.length; i++) {
            process.stdout.write('[' + String(i) + ']: ' + String(data[i]) + ' '); //console.log('data[' + String(i) + ']: ' + String(data[i]));
        }
        console.log(''); // cause of process.stdout.write()
    };
}

//var myArray = [];              // empty array
//var myArray = [1,2,3];         // initialised array
//var myArray = new Array(18);   // array with 18 undefined elements

function randCppStyleTest () {
    var rand1 = new RandIntArray(18);   // array with 18 undefined elements
    //var init = [1,2,3,4,5];
    //var rand1 = new RandIntArray(init);   //
    console.log("");
    rand1.push(1); rand1.push(2); rand1.push(3); rand1.push(4); rand1.push(5); rand1.list();
    rand1.pop(); rand1.list();
    rand1.push(11); rand1.list();
}

function randTest () {
    //var rand1 = new RandIntArray(18);   // array with 18 undefined elements
    //var init = [1,2,3,4,5];
    var init = Array.apply(null, Array(18)).map(function (_, i) {return i;}); // [0, 1, 2, 3, 4, ...]
    var rand1 = new RandIntArray(init);   //
    console.log("");
    rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list();
    rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list();
    rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list();
    rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list(); rand1.pop(); rand1.list();
}

//    var m_newRndLevel = new Array(); // with 5 slots
//    var rndIntArray = Object.create(null);
    // for (var i = 0; i < MAX_LEVELS; i++) {
    //     var forLevel = m_answers[i] - 1;
    //     m_newRndLevel[forLevel].push(i);
    // }

function randLevels() { // copy jon's levelData::rndFixedLevels()
    var MAX_LEVELS = 18;
    var pseudoRandLevelList = [1, 3, 2, 1, 4, 2, 5, 2, 2, 3, 1, 5, 4, 4, 5, 4, 1, 5]; // [MAX_LEVELS]
    var levels = [], randLevels = [];

    levels.push(new RandIntArray([0, 1, 2, 3]));
    levels.push(new RandIntArray([4, 5, 6, 7]));
    levels.push(new RandIntArray([8, 9]));
    levels.push(new RandIntArray([10, 11, 12, 13]));
    levels.push(new RandIntArray([14, 15, 16, 17]));

    for (var i = 0; i < MAX_LEVELS; i++) {
         var wantedLevel = pseudoRandLevelList[i];
         randLevels[i] = levels[wantedLevel-1].pop();
    }
    return randLevels;
}

//randTest();
console.log('randLevels: ' + randLevels());



    // for... in should be avoided as the order is not guaranteed and inherited properties are also enumerated

    // int levelData::getGameLevel(int index) {
    //     assert(m_isInitalised);
    //     assert(index < MAX_LEVELS);
    //     return m_rndLevel[index];
    // }

    // int levelData::getExpectedAnswer(int index) {
    //     assert(m_isInitalised);
    //     assert(index < MAX_LEVELS);
    //     return m_answers[m_rndLevel[index]];
    // }
