from flask import Flask, request, jsonify
import logging

app = Flask(__name__)

# Configurer les logs
logging.basicConfig(level=logging.DEBUG)

# ❌ Endpoint VULNÉRABLE (aucune validation)
@app.route('/vulnerable', methods=['POST'])
def vulnerable():
    data = request.get_json()
    app.logger.debug(f"Received data on /vulnerable: {data}")
    return jsonify({"received": data}), 200  # Accepte tout

# ✅ Endpoint SÉCURISÉ (validation des entrées)
@app.route('/secure', methods=['POST'])
def secure():
    data = request.get_json()
    app.logger.debug(f"Received data on /secure: {data}")
    
    if not isinstance(data, dict) or 'number' not in data:
        app.logger.error("Missing number field")
        return jsonify({'error': 'Missing number field'}), 400
    if not isinstance(data['number'], int):
        app.logger.error("Number must be an integer")
        return jsonify({'error': 'Number must be an integer'}), 400

    # Provoquer un crash intentionnel si le nombre est négatif
    if data['number'] < 0:
        app.logger.error("Intentional crash triggered due to negative number")
        raise ValueError("Intentional crash triggered due to negative number")

    return jsonify({"message": f"Valid input: {data['number']}"}), 200

if __name__ == '__main__':
    app.run(debug=True)