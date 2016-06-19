var SerialSynapse = require("serial-synapse");
var SynapseServer = require("serial-synapse-socket");
var SynapseServer = require('../synapse-socket');
var SerialPort = require('serialport').SerialPort;
var parsers = require('serialport').parsers;

//Create the synapse object
var robot = new SerialSynapse();
var robotFunctions = require('./Robot_Functions');

//Load all the functions
robotFunctions.commands.forEach(function(command){
	robot.addCommand(command);
});
robotFunctions.updateHandlers.forEach(function(handler){
	robot.addUpdateHandler(handler);
});

robot.connection = new SerialPort(process.argv[2],
	{
		baudrate: 9600,
		parser: parsers.readline('\r\n')
	}
);

//Create the server and we're done!
var server = new SynapseServer({
	port: 8080,
	synapse: robot
});
console.log("Listening on port 8080 for commands!");
//That's it. We're done - connect and communicate!