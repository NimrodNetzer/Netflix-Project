
const validateUserIdHeader = (req, res, next) => {
    const userId = req.headers['user-id'];
    if (!userId) {
        return res.status(401).json({ error: 'Token is not provided.' });
    }
    next();
};

module.exports = {validateUserIdHeader};