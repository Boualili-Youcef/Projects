
const mongoose = require('mongoose');

const orderSchema = new mongoose.Schema({
	products: [{ product: { type: mongoose.Schema.Types.ObjectId, ref: 'Product' }, quantity: Number }],
	total: { type: Number, required: true },
	userId: { type: mongoose.Schema.Types.ObjectId, ref: 'User', required: true },
	createdAt: { type: Date, default: Date.now }
});

module.exports = mongoose.model('Order', orderSchema);