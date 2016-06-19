#include <RedBot.h>
#include <CmdMessenger.h>
#include <SimpleTimer.h>

CmdMessenger cmdMessenger = CmdMessenger(Serial);
RedBotMotors motors;
RedBotButton button;
RedBotAccel accelerometer = RedBotAccel();
SimpleTimer timer;

int lastValue = 0;

enum
{
	leftMotor,
	rightMotor,
	drive,
	halt
};

void setLeftMotor(){
	char* uuid = cmdMessenger.readStringArg();
	int power = cmdMessenger.readIntArg();
	
	motors.leftMotor(power);
	
	Serial.println(uuid);
}

void setRightMotor(){
	char* uuid = cmdMessenger.readStringArg();
	int power = cmdMessenger.readIntArg();
	
	motors.rightMotor(power);
	
	Serial.println(uuid);
}

void setDrive(){
	char* uuid = cmdMessenger.readStringArg();
	int power = cmdMessenger.readIntArg();
	
	motors.drive(power);
	
	Serial.println(uuid);
}

void haltMotors(){
	char* uuid = cmdMessenger.readStringArg();
	motors.brake();
	Serial.println(uuid);
}

void attachCommandCallbacks(){
	cmdMessenger.attach(leftMotor, setLeftMotor);
	cmdMessenger.attach(rightMotor, setLeftMotor);
	cmdMessenger.attach(drive, setDrive);
	cmdMessenger.attach(halt, haltMotors);
}

void reportAccellerometer(){
	accelerometer.read();
	Serial.print(10);
	Serial.print(",");
	Serial.print(accelerometer.x);
	Serial.print(",");
	Serial.print(accelerometer.y);
	Serial.print(",");
	Serial.print(accelerometer.z);
	Serial.print(",");
	Serial.print(accelerometer.angleXZ);
	Serial.print(",");
	Serial.print(accelerometer.angleYZ);
	Serial.print(",");
	Serial.println(accelerometer.angleXY);
}

void setup()
{
	Serial.begin(9600);
	attachCommandCallbacks();
	timer.setInterval(250, reportAccellerometer);

}

void loop()
{
	cmdMessenger.feedinSerialData();
	int buttonValue = button.read();
	if(lastValue != buttonValue){
		lastValue = buttonValue;
		Serial.print(12);
		Serial.print(",");
		Serial.println(buttonValue);
	}
	timer.run();
}
