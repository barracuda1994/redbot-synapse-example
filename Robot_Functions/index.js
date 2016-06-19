module.exports = {
	commands:
		[
			require('./drive.js'),
			require('./brake.js'),
			require('./setLeftMotor.js'),
			require('./setRightMotor.js')
		],
	updateHandlers:
		[
			require('./accelerometer'),
			require('./button')
		]
}