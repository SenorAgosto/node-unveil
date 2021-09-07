# node-unveil

Expose OpenBSD's [unveil(2)](https://man.openbsd.org/unveil) to node.

## Dependencies

- node
- node-gyp

You can install node on OpenBSD with `pkg_add node`.
You can install node-gyp with `npm install node-gyp`.

## Build

    $ node-gyp configure
    $ node-gyp rebuild

## Tests

Running the following should print some output to the console without errors.

    $ node tests/good.js

Running the following should cause an ENOENT error to be raised.

    $ node tests/bad.js
