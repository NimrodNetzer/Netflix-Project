const express = require('express');
const socketClient = require('../socketClient'); // Adjust the path as necessary

const addWatchedMovie = async (req, res) => {
    const { id } = req.params; // Movie ID from URL
    const userId = req.headers['user-id']; // User ID from request headers

    if (!userId) {
        return res.status(400).json({ error: 'User ID is required' });
    }

    try {
        // Construct the WATCH command in the expected format
        const command = `WATCH ${userId} ${id}\n`;
        console.log(`Sending command to server: ${command}`);

        // Use the socket client to send the command
        const response = await socketClient.send(command);

        console.log(`Response from server: ${response}`);
        if (response.includes('200 OK')) {
            res.status(200).json({ message: 'Movie marked as watched successfully' });
        } else {
            res.status(400).json({ error: 'Failed to mark movie as watched', details: response });
        }
    } catch (error) {
        console.error('Error communicating with the server:', error);
        res.status(500).json({ error: 'Failed to mark movie as watched', details: error.message });
    }
};

const router = express.Router();
router.post('/watched/:id', addWatchedMovie);

module.exports = router;
