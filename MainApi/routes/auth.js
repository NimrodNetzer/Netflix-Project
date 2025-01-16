const isAuthenticated = (req, res, next) => {
    const userId = req.headers['user-id']; // Check for the user ID in headers
    if (!userId) {
        return res.status(401).json({ message: 'Unauthorized: Missing user ID in headers.' });
    }

    req.userId = userId; // Pass the userId to the request object for downstream handlers
    next(); // Proceed to the next middleware or controller
};
module.exports = isAuthenticated;
