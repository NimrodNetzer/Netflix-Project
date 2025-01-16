const {getUserById} = require('../services/user')

const isAuthenticated = async (req, res, next) => {
    const userId = req.headers['user-id']; // Check for the user ID in headers
    if (!userId) {
        return res.status(401).json({ message: 'Unauthorized: Missing user ID in headers.' });
    }
    const user = await getUserById(userId);
    if(!user)
        return res.status(404).json({message : "Unauthorized: Unknown user ID in headers."});
    req.userId = userId;

    next(); // Proceed to the next middleware or controller
};
module.exports = isAuthenticated;
