const path = require('path');
const CopyPlugin = require('copy-webpack-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const outputDir = path.join(__dirname, 'build/');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
	entry: './lib/js/src/Index.bs.js',
	mode: isProd ? 'production' : 'development',
	output: {
		path: outputDir,
		filename: 'Index.js'
	},
	plugins: [
		new HtmlWebpackPlugin({
			template: 'src/index.html',
			inject: false
		}),
		new CopyPlugin([
			{ from: '**/*.css', context: 'src/' },
		]),
	],
	devServer: {
		compress: true,
		contentBase: outputDir,
		port: process.env.PORT || 8000,
		historyApiFallback: true
	}
};
