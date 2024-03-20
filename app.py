from flask import Flask, request, jsonify, render_template
from flask_cors import CORS
import time

app = Flask(__name__)
CORS(app)
received_data = []

@app.route("/", methods=["POST"])
def receive_data():
    if request.method == "POST":
        data = request.form.get("message")
        print(f"Received Data: {data}")
        timestamp = time.strftime('%H:%M:%S')  # Get the current time
        received_data.append({"timestamp": timestamp, "data": data})
        return "Data received successfully"
    else:
        return "Invalid request"

@app.route("/get_data", methods=["GET"])
def get_data():
    return jsonify(received_data)

@app.route("/webpage")
def webpage():
    return render_template("webpage.html")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=False, threaded=True, use_reloader=False)
