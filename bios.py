import discord
from discord.ext import commands
import mysql.connector
from datetime import datetime, timedelta
import random
import string
import asyncio

db = mysql.connector.connect(
    host="193.143.69.195",
    user="jerano",
    password="jerano2002",
    database="key_system"
)

cursor = db.cursor()

# Discord bot setup
intents = discord.Intents.default()
intents.message_content = True
bot = commands.Bot(command_prefix='/', intents=intents)

def generate_key():
    chars = string.ascii_uppercase + string.digits
    return "TEMP-" + ''.join(random.choice(chars) for _ in range(6))

@bot.command()
async def createkey(ctx, duration: str):
    if not ctx.author.guild_permissions.administrator:
        await ctx.send("You don't have permission to use this command.")
        return
    
    valid_durations = ['1D', '1W', '1M', 'L']
    if duration.upper() not in valid_durations:
        await ctx.send("Invalid duration. Use 1D, 1W, 1M, or L for lifetime.")
        return
    
    key = generate_key()
    expires_at = None
    
    if duration.upper() == '1D':
        expires_at = datetime.now() + timedelta(days=1)
    elif duration.upper() == '1W':
        expires_at = datetime.now() + timedelta(weeks=1)
    elif duration.upper() == '1M':
        expires_at = datetime.now() + timedelta(days=30)
    
    sql = "INSERT INTO keys (key_value, expires_at, duration_type, discord_id) VALUES (%s, %s, %s, %s)"
    val = (key, expires_at, duration.upper(), str(ctx.author.id))
    cursor.execute(sql, val)
    db.commit()
    
    await ctx.send(f"Key created: `{key}`\nDuration: {duration}\nExpires: {expires_at or 'Never'}")

@bot.event
async def on_ready():
    print(f'Logged in as {bot.user}')

bot.run('')
