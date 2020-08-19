const path = require('path');
module.exports = {
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
    externals: {
        'd3': 'd3'
    }
};
