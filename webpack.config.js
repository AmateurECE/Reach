const path = require('path');
var nodeExternals = require('webpack-node-externals');

const serverConfig = {
    mode: "production",
    entry: './reach/js/main.js',
    target: "node",
    externals: nodeExternals(),
    output: {
        path: path.resolve('./reach/build'),
        filename: 'reach.js'
    },
    module: {
        rules: [
            { test: /\.js$/, use: 'babel-loader' }
        ]
    },
    stats: {
        colors: true
    },
    devtool: 'source-map',
};

const spaConfig = {
    mode: "production",
    entry: './static/js/main.js',
    output: {
        path: path.resolve('./static/build'),
        filename: 'bundle.js'
    },
    module: {
        rules: [
            { test: /\.js$/, use: 'babel-loader' }
        ]
    },
    stats: {
        colors: true
    },
    devtool: 'source-map',
};

module.exports = [serverConfig, spaConfig];
