import sqlite3
from telegram import Update, ReplyKeyboardMarkup
from telegram.ext import ApplicationBuilder, CommandHandler, MessageHandler, ContextTypes, filters

TOKEN = "YOUR_TELEGRAM_TOKEN"
ADMIN_ID = 123456789  

# ===== DB =====
conn = sqlite3.connect("coffee.db", check_same_thread=False)
cursor = conn.cursor()

cursor.execute("""
CREATE TABLE IF NOT EXISTS orders (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER,
    item TEXT,
    price INTEGER
)
""")
conn.commit()

# ===== MENU =====
menu = {
    "Латте": 60,
    "Капучино": 55,
    "Еспресо": 40,
    "Американо": 45,
    "Мокачіно": 65
}

# ===== UI =====
keyboard = [
    ["☕ Меню", "🛒 Замовити"],
    ["📊 Моя статистика", "🔥 Топ продажі"],
    ["ℹ️ Про нас"]
]

markup = ReplyKeyboardMarkup(keyboard, resize_keyboard=True)

user_cart = {}

# ===== START =====
async def start(update: Update, context: ContextTypes.DEFAULT_TYPE):
    user_id = update.effective_user.id
    user_cart[user_id] = []

    await update.message.reply_text(
        "☕ Advanced Coffee Bot\nОбери дію:",
        reply_markup=markup
    )

# ===== HANDLER =====
async def handle(update: Update, context: ContextTypes.DEFAULT_TYPE):
    text = update.message.text
    user_id = update.effective_user.id

    if user_id not in user_cart:
        user_cart[user_id] = []

    # --- MENU ---
    if text == "☕ Меню":
        msg = "☕ Меню:\n"
        for i, p in menu.items():
            msg += f"- {i}: {p} грн\n"
        await update.message.reply_text(msg)

    # --- ORDER ---
    elif text == "🛒 Замовити":
        buttons = [[i] for i in menu.keys()]
        await update.message.reply_text(
            "Оберіть каву:",
            reply_markup=ReplyKeyboardMarkup(buttons, resize_keyboard=True)
        )

    # --- ADD ITEM ---
    elif text in menu:
        user_cart[user_id].append(text)

        cursor.execute(
            "INSERT INTO orders (user_id, item, price) VALUES (?, ?, ?)",
            (user_id, text, menu[text])
        )
        conn.commit()

        await update.message.reply_text(f"✔ {text} додано")

    # --- MY STATS ---
    elif text == "📊 Моя статистика":
        cursor.execute("SELECT SUM(price) FROM orders WHERE user_id=?", (user_id,))
        total = cursor.fetchone()[0] or 0

        await update.message.reply_text(f"📊 Ви витратили: {total} грн")

    # --- TOP SALES (ADMIN ONLY) ---
    elif text == "🔥 Топ продажі":
        if user_id != ADMIN_ID:
            await update.message.reply_text("⛔ Немає доступу")
            return

        cursor.execute("""
            SELECT item, COUNT(item) as cnt
            FROM orders
            GROUP BY item
            ORDER BY cnt DESC
        """)

        rows = cursor.fetchall()

        msg = "🔥 Топ продажі:\n"
        for r in rows:
            msg += f"- {r[0]}: {r[1]} разів\n"

        await update.message.reply_text(msg)

    # --- ABOUT ---
    elif text == "ℹ️ Про нас":
        await update.message.reply_text(
            "☕ Advanced CoffeeShop Bot\nМіні бізнес-система з аналітикою"
        )

    else:
        await update.message.reply_text("Оберіть кнопку 👇")

# ===== RUN =====
app = ApplicationBuilder().token(TOKEN).build()

app.add_handler(CommandHandler("start", start))
app.add_handler(MessageHandler(filters.TEXT & ~filters.COMMAND, handle))

print("☕ Advanced Coffee Bot running...")
app.run_polling()
