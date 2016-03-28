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

// er... 
// http://www.levihackwith.com/how-to-make-gulp-copy-a-directory-and-its-contents/

// Mon Mar 28 13:29:42 2016
// gulp-sftp seems broken to me:
// 1) sending __dirname + '/test/**/*' works, but sending __dirname + '/dist/**/*' doesn't - "file not found"?
// 2) even when it works, you get "directory exists" error if it already exists - shouldn't be an error
// 3) trying to use "auth" option to get auth info from file .ftppass - SyntaxError: Unexpected token }



var gulp = require('gulp');
var sftp = require('gulp-sftp');
//var src = __dirname + '/dist/**/*';
var src = __dirname + '/test/**/*';

function done() {
    'use strict';
    console.log("connection closed");
}


// sftp webman@xrat
gulp.task('ftp-xrat', function () {
    'use strict'; // ???
    var dest = '/user/webman/public_html/';
    console.log("Sending '" + src + "' to '" + dest + "'");
    return gulp.src(src, {base: 'test'})
        .pipe(sftp({
            host: 'xrat',
            user: '',
            pass: '',
            //remotePath: '~/public_html', // doesn't understand '~'
            remotePath: dest,
            callback: done
        }));
});


// sftp drkvogel@web456.webfaction.com
gulp.task('ftp-webfaction', function () {
    'use strict'; // ???
    var dest = '/home/drkvogel/webapps/main/matrix/';
    console.log("Sending '" + src + "' to '" + dest + "'");
    return gulp.src(src, {base: 'test'})
        .pipe(sftp({
            host: 'web456.webfaction.com',
            // user: '',
            // pass: '',
            user: '',
            pass: '', // what about public key?
            // //remotePath: '~/public_html', // doesn't understand '~'
            remotePath: dest,
            callback: done
            //, auth: "webfaction"
        }));
});


//gulp.start('ftp-xrat');
gulp.start('ftp-webfaction');