var fs = require('fs');
var unveil = require('../build/Release/unveil');

// unveil_path() returns 0 on success, errno otherwise
unveil.unveil_path('/tmp/', 'crw');
unveil.disable();

// access a file outside /tmp/ should cause ENOENT
fs.appendFileSync('test.txt', 'hello!', 'utf-8');

// we should never get here on OpenBSD, process will be killed by OS
console.log('we did a naughty');
