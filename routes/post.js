var express = require('express');
var router = express.Router();
var app = require('express')();
var http = require('http').Server(app);
var path = require('path');
var AWS = require('aws-sdk');
var http = require('http');
var mqtt = require('mqtt');
var child_process = require('child_process');

router.get('/', function(req, res, next) {
var mess_post = req.param('data');

var sendIftttTNotification = new http.ClientRequest({
    hostname: "maker.ifttt.com",
    port: 80,
    path: "Your_APIkey_Ifttt",
    method: "POST"
})

let awsConfig = {
    "region": "us-east-1",
    "endpoint": "http://dynamodb.us-east-1.amazonaws.com"
};
AWS.config.update(awsConfig);
var docClient = new AWS.DynamoDB.DocumentClient();

var input = {
	"Number": mess_post,
    "Detect": "fire",  
    "Time": new Date().toString()
};
var params = {
    TableName: "FinalProjectDyn",
    Item:  input
};
    docClient.put(params, function (err, data) {
        if (err) {
            console.error("sorry, your request could not be processed because of: " + JSON.stringify(err, null, 2));
            res.send("sorry, your request could not be processed because of: " + JSON.stringify(err, null, 2));                      
        } else {
            console.log("dynamodb data input was successful" );
            console.log("display inputted data: " + mess_post);

        	const util = require('util');
			const exec = util.promisify(require('child_process').exec);
			async function sns_aws() {
				const { stdout, stderr } = await exec('aws sns publish --topic-arn arn:aws:sns:us-east-1:396664334562:ProjectMercuSNS --message "detect fire at home"');
				console.log('Message id already processed:', stdout);
				console.log('Message id could not be processed:', stderr);    
                }
			sns_aws();
            sendIftttTNotification.end()
            console.log('I am calling you');

            async function things() {
             const { stdout, stderr } = await exec('curl -v -X POST -d "{\"Detect\": 50}" http://127.0.0.1:8080/api/v1/devprojectmercu/telemetry --header "Content-Type:application/json"');
             console.log('Message id already processed:', stdout);
             console.log('Message id could not be processed:', stderr);    
            }
            things();

            res.send("thank you, your request was successfully processed");            
        }
    });
});
module.exports = router;