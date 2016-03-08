// cbird@q108-vlubuntu:~/Projects/bb-quizzes/yo-test$ node

// vinyl-ftp - ftp only! bullshit!
// var fs = require('vinyl-fs');
// var ftp = require('vinyl-ftp');

// var conn = new ftp({host:'xrat', user:'webman', password:'T00n4rmy', parallel: 1, log: 'vinyl-ftp.log'});

// fs.src(['./bower.json'], { buffer: 'false'})
//     .pipe(conn.dest('./public_html'));


// You can gulp --gulpfile a.js or node a.js if at the bottom you add gulp.start('the task name')

// $ gulp --gulpfile ftp.js

//var sys = require('sys'); // sys.exit() is Python!
//console.log("This file is: " + __filename);
//console.log("This dir is: " + __dirname);
//process.exit(0);


// doesn't refresh file - says uploaded but it's not:
// [17:12:28] SFTP error or directory exists: Error: Failure /user/webman/public_html/bower.json2
// [17:12:28] gulp-sftp: Uploaded: bower.json => /user/webman/public_html/bower.json2/bower.json
// [17:12:28] gulp-sftp: 1 file uploaded successfully

// https://github.com/gtg092x/gulp-sftp/issues/33 +1'd this


var gulp = require('gulp');
var sftp = require('gulp-sftp');
var src = __dirname + '/bower.json';
var dest = '/user/webman/public_html/';

function done() {
    'use strict';
    console.log("connection closed");
}

console.log("Sending '" + src + "' to '" + dest);

gulp.task('ftp', function () {
    'use strict'; // ???
    return gulp.src(src)
        .pipe(sftp({
            host: 'xrat',
            user: 'webman',
            pass: 'T00n4rmy',
            //remotePath: '~/public_html', // doesn't understand '~'
            remotePath: dest,
            callback: done
        }));
});

gulp.start('ftp');