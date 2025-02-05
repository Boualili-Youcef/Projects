const express = require('express');
const Product = require('../models/Product');
const router = express.Router();

// GET all products
router.get('/', async (req, res) => {
	try {
		const products = await Product.find();
		res.json(products);
	} catch (error) {
		res.status(500).json({ error: error.message });
	}
});

// POST add a new product (Admin)
router.post('/', async (req, res) => {
	try {
		const product = new Product(req.body);
		await product.save();
		res.status(201).json(product);
	} catch (error) {
		res.status(500).json({ error: error.message });
	}
});

// PUT update a product (Admin)
router.put('/:id', async (req, res) => {
	try {
		const product = await Product.findByIdAndUpdate(req.params.id, req.body, { new: true });
		res.json(product);
	} catch (error) {
		res.status(500).json({ error: error.message });
	}
});

// DELETE a product (Admin)
router.delete('/:id', async (req, res) => {
	try {
		await Product.findByIdAndDelete(req.params.id);
		res.json({ message: 'Product deleted' });
	} catch (error) {
		res.status(500).json({ error: error.message });
	}
});

module.exports = router;
