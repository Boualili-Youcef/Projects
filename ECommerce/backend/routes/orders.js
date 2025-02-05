const express = require('express');
const Order = require('../models/Order');
const router = express.Router();

// POST create a new order
router.post('/', async (req, res) => {
	try {
		const order = new Order(req.body);
		await order.save();
		res.status(201).json(order);
	} catch (error) {
		res.status(500).json({ error: error.message });
	}
});

// GET orders for a specific user
router.get('/:userId', async (req, res) => {
	try {
		const orders = await Order.find({ userId: req.params.userId });
		res.json(orders);
	} catch (error) {
		res.status(500).json({ error: error.message });
	}
});

// GET all orders (Admin)
router.get('/admin', async (req, res) => {
	try {
		const orders = await Order.find();
		res.json(orders);
	} catch (error) {
		res.status(500).json({ error: error.message });
	}
});

module.exports = router;
