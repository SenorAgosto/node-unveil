var fs = require('fs');
var unveil = require('../build/Release/unveil');

unveil.unveil_path('/tmp/', 'crw');
unveil.disable();

fs.appendFileSync('/tmp/test.txt', 'hello!', 'utf-8');
console.log('/tmp/test.txt was created');

fs.unlink('/tmp/test.txt', (err) => {
	if(err) throw err;
	console.log('/tmp/test.txt was deleted');
});
