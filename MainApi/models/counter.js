const mongoose = require('mongoose');
// Counter Schema for Tracking Incrementing IDs
const counterSchema = new mongoose.Schema({
    _id: { type: String, required: true }, // Name of the counter (e.g., "userId", "movieId")
    seq: { type: Number, default: 0 },    // Sequence value
});

const Counter = mongoose.model('Counter', counterSchema);

// Function to Get the Next Incrementing ID
async function getNextSequence(counterName) {
    const counter = await Counter.findByIdAndUpdate(
        counterName,
        { $inc: { seq: 1 } },   // Increment the sequence value
        { new: true, upsert: true } // Create the counter if it doesn't exist
    );
    return counter.seq;
}

module.exports = {getNextSequence}