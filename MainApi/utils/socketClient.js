const net = require('net');

const socketClient = {
    send: (message) => {
        return new Promise((resolve, reject) => {
            // Create a new socket connection
            const client = new net.Socket();
            const serverIp = '127.0.0.1'; // Replace with the server's IP
            const serverPort = 8080; // Replace with the server's port

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