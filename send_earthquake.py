import bluetooth
# import serial
import time
# from telegram import Bot
from telegram.error import TelegramError
from telegram.ext import ApplicationBuilder
import asyncio


addr = "00:19:12:10:0A:73"
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((addr, 1))
semaphore = asyncio.Semaphore(10)

async def send_message_to_user(user_id, message, bot):

    async with semaphore:
        try:
            await bot.send_message(chat_id=user_id, text=message)
            
        except TelegramError as e:
            print(f'Error sending message to user {user_id}: {e}')

async def send_message_to_users(user_ids, message, bot):
    tasks = [send_message_to_user(user_id, message, bot) for user_id in user_ids]
    await asyncio.gather(*tasks)

async def main():
    while True:
        print("unga bunga")
        BOT_TOKEN = "6155546088:AAF_sBuYKbMSi3XxJUwdSixd-BNaVbB7o3Q"
        builder = ApplicationBuilder().token(BOT_TOKEN)
        builder.connection_pool_size(500)  
        builder.pool_timeout(1000)  
        # builder.read_timeout(60)  
        # builder.write_timeout(60)
        bot = builder.build().bot
        # bot = Bot(token=BOT_TOKEN)
        # serial_port = serial.Serial('/dev/cu.usbserial-120', 115200)
        data = sock.recv(4096).decode()
        print("another unga bunga")
        
        if(data == ""):
            print("no data")
        else:
            print(data)
        
        # data = serial_port.readline().decode('utf').rstrip()
        if(data == '1'):
            with open("user_id.txt", "r") as f:
                f_string = f.read()
                f_string = '[' + f_string + ']'
                user_ids = eval(f_string)
                await send_message_to_users(user_ids, "EARTHQUAKEE! RUNNNN (This is a test), go under the table now :sus:", bot)
                # message="EARTHQUAKEE! RUNNNN, go under the table now :sus:"
                # asyncio.run(send_message_to_users(user_ids, message, bot))


asyncio.run(main())