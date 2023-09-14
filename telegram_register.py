
from telegram import Update
from telegram.ext import (
    Application,
    CallbackContext,
    CommandHandler,
)


BOT_TOKEN = "6155546088:AAF_sBuYKbMSi3XxJUwdSixd-BNaVbB7o3Q"


application = Application.builder().token(BOT_TOKEN).build()


async def start(update: Update, context: CallbackContext):
    await update.message.reply_text("Hello! I'm quakey! You are registered for the early earthquake detection service. To cancel, enter the command /stop")
    user_id = update.effective_user.id
    with open("user_id.txt", "a+") as f:
        f.write(f"'{str(user_id)}',")
    print("Registered", update.message.from_user.first_name)

application.add_handler(CommandHandler('start', start))
application.run_polling()
