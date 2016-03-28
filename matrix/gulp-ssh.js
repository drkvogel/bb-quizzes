'use strict'

// https://www.npmjs.com/package/gulp-ssh
 
var fs = require('fs');
var gulp = require('gulp');
var GulpSSH = require('gulp-ssh');

var src = __dirname + '/dist/**/*';
var dest = '/home/drkvogel/webapps/main/matrix/';
 
var config = {
  host: 'web456.webfaction.com',
  port: 22,
  username: 'drkvogel',
  privateKey: fs.readFileSync('/home/kvogel/.ssh/id_rsa')
} 
 
// var gulpSSH = new GulpSSH({
//   ignoreErrors: false,
//   sshConfig: config
// })
 
gulp.task('exec', function () {
  return gulpSSH
    .exec(['uptime', 'ls -a', 'pwd'], {filePath: 'commands.log'})
    .pipe(gulp.dest('logs'))
});
 
gulp.task('dest', function () {
  return gulp
    .src(['./**/*.js', '!**/node_modules/**'])
    .pipe(gulpSSH.dest(dest)) //'/home/iojs/test/gulp-ssh/'
});
 
gulp.task('sftp-read', function () {
  return gulpSSH.sftp('read', dest, {filePath: 'index.js'}) //'/home/iojs/test/gulp-ssh/index.js'
    .pipe(gulp.dest('logs'))
});
 
gulp.task('sftp-write', function () {
  return gulp.src('index.js')
    .pipe(gulpSSH.sftp('write', dest)) // '/home/iojs/test/gulp-ssh/test.js'
});
 
gulp.task('shell', function () {
  return gulpSSH
    .shell(['cd /home/iojs/test/thunks', 'git pull', 'npm install', 'npm update', 'npm test'], {filePath: 'shell.log'})
    .pipe(gulp.dest('logs'))
});


function obj(o) { // log formatted object to console
    return JSON.stringify(o, null, 4);
}

// load config from file, which is .gitignored, to avoid auth info in repo
var configFile = './.ftppass';
var config = require(configFile); // was JSON, now JS
console.log("loaded config from: '" + configFile + "'");
//console.log(obj(config));

// use gulpSSH.dest(), not .write(), to push multiple files to a remote host
gulp.task('sftp-push-webfaction', function () {
  var gulpSSH = new GulpSSH({
    ignoreErrors: false,
    sshConfig: config.webfaction
  })
  return gulp
    .src(src) //.src(['./**/*.js', '!**/node_modules/**'])
    .pipe(gulpSSH.dest(dest)) //'/home/iojs/test/gulp-ssh/'
});

gulp.task('sftp-push-xrat', function () {
  var gulpSSH = new GulpSSH({
    ignoreErrors: false,
    sshConfig: config.xrat
  })
  return gulp
    .src(src) //.src(['./**/*.js', '!**/node_modules/**'])
    .pipe(gulpSSH.dest(dest)) //'/home/iojs/test/gulp-ssh/'
});


gulp.start('sftp-push-webfaction');




// gulp.task('sftp-push-webfaction', function () {
//   //src = './matrix.md'
//   console.log("Sending '" + src + "' to '" + dest + "'");
//   return gulp.src(src)
//   //  .pipe(gulpSSH.sftp('write', dest + "matrix.md")) // works, for one file - must specify filename
//     .pipe(gulpSSH.sftp('write', dest + "**/*")) 
// });