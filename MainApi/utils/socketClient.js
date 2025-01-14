const net = require('net');
require('custom-env').env(process.env.NODE_ENV, './config');

const serverIp = process.env.RECOMMENDATION_IP;
const serverPort = process.env.RECOMMENDATION_PORT;

const socketClient = {
    send: (message) => {
        return new Promise((resolve, reject) => {
            // Create a new socket connection
            const client = new net.Socket();
            client.connect(serverPort, serverIp, () => {
                console.log(`Connected to Recommendation System at ${serverIp}:${serverPort}`);
                client.write(message); // Send the message
            });

            client.on('data', (data) => {
                resolve(data.toString()); // Resolve the response
                client.destroy(); // Close the connection
            });

            client.on('error', (err) => {
                reject(err); // Reject the promise on error
                client.destroy(); // Close the connection
            });

            client.on('close', () => {
                console.log('Connection closed');
            });
        });
    },
};

module.exports = socketClient;