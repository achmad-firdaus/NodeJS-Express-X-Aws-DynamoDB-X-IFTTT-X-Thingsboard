var mqtt = require('mqtt');

// Don't forget to update accessToken constant with your device access token
const thingsboardHost = "demo.thingsboard.io";
const accessToken = "token_FGA_ESP";
const DataKebakaran = 1, NonKebakaran = 0;

// Initialization of temperature and humidity data with random values
var data = {
    DataDashboard: DataKebakaran
};
var data1 = {
    DataDashboard: NonKebakaran
};
// Initialization of mqtt client using Thingsboard host and device access token
console.log('Connecting to: %s using access token: %s', thingsboardHost, accessToken);
var client  = mqtt.connect('mqtt://'+ thingsboardHost, { username: accessToken });

// Triggers when client is successfully connected to the Thingsboard server
client.on('connect', function () {
    console.log('Client connected!');
    // Uploads firmware version and serial number as device attributes using 'v1/devices/me/attributes' MQTT topic
    client.publish('v1/devices/me/attributes', JSON.stringify({"firmware_version":"1.0.1", "serial_number":"SN-001"}));
    // Schedules telemetry data upload once per second
    console.log('Uploading temperature and humidity data once per second...');
    setInterval(publishTelemetry, 1000);
    setInterval(publishTelemetry1, 1000);

});

// Uploads telemetry data using 'v1/devices/me/telemetry' MQTT topic
function publishTelemetry() {
    client.publish('v1/devices/me/telemetry', JSON.stringify(data));
    console.log(JSON.stringify(data));
    setInterval(ENDData, 5000);
}
function publishTelemetry1() {
    client.publish('v1/devices/me/telemetry', JSON.stringify(data));
    console.log(JSON.stringify(data));
    setInterval(ENDData, 1000);
}

function ENDData(){
        console.log();
    console.log('Disconnecting...');
    client.end();
    console.log('Exited!');
    process.exit(2);
}

//Catches uncaught exceptions
process.on('uncaughtException', function(e) {
    console.log('Uncaught Exception...');
    console.log(e.stack);
    process.exit(99);
});