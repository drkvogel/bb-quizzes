// cbird@q108-vlubuntu:~/Projects/bb-quizzes/yo-test$ node

var gulp = require('gulp');
var sftp = require('gulp-sftp');

gulp.task('default', function () {
    'use strict'; // ???
    return gulp.src('bower.json')
        .pipe(sftp({
            host: 'xrat',
            user: 'webman',
            pass: 'T00n4rmy'
        }));
});


// vinyl-ftp - ftp only! bullshit!
// var fs = require('vinyl-fs');
// var ftp = require('vinyl-ftp');

// var conn = new ftp({host:'xrat', user:'webman', password:'T00n4rmy', parallel: 1, log: 'vinyl-ftp.log'});

// fs.src(['./bower.json'], { buffer: 'false'})
//     .pipe(conn.dest('./public_html'));