node-gyp rebuild -target=2.0.5 -arch=x64 -dist-url=https://atom.io/download/atom-shell

electron-packager . --electron-version=2.0.5

npm install electron-prebuilt
npm install electron-packager
npm install electron-squirrel-startup
npm install --save-dev electron-winstaller
node package.js

