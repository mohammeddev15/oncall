from flask import Flask, request, jsonify
import json, os, uuid
from pathlib import Path

app = Flask(__name__)

DATA_FILE = Path(__file__).parent / 'orders.json'

def load_orders():
    if not DATA_FILE.exists():
        return []
    try:
        text = DATA_FILE.read_text(encoding='utf-8').strip()
        if not text:
            return []
        data = json.loads(text)
        if not isinstance(data, list):
            raise ValueError("الملف يجب أن يحتوي على قائمة")
        return data
    except Exception as e:
        print(f"⚠️ فشل قراءة orders.json: {e}")
        # احتفظ بنسخة بدل المسح
        backup = DATA_FILE.with_suffix('.bak')
        DATA_FILE.rename(backup)
        print(f"تم حفظ النسخة التالفة في {backup}")
        return []

def save_orders(orders_list):
    # كتابة مؤقتة ثم استبدال، يمنع تلف الملف لو انقطع البرنامج
    temp = DATA_FILE.with_suffix('.tmp')
    with open(temp, 'w', encoding='utf-8') as f:
        json.dump(orders_list, f, indent=2, ensure_ascii=False)
    os.replace(temp, DATA_FILE)

orders = load_orders()
print(f"تم تحميل {len(orders)} طلب")

@app.route('/orders', methods=['GET'])
def get_orders():
    return jsonify(orders)

@app.route('/order', methods=['POST'])
def create_order():
    data = request.get_json()
    if not data:
        return jsonify({"error": "No data provided"}), 400

    data['id'] = str(uuid.uuid4())
    data['status'] = 'pending'

    orders.append(data)
    save_orders(orders)
    return jsonify(data), 201

if __name__ == '__main__':
    app.run(debug=True)
