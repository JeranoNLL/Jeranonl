import discord
from discord.ext import commands
import mysql.connector
from datetime import datetime, timedelta
import random
import string

# --- MySQL Database Setup ---
db = mysql.connector.connect(
    host="193.143.69.195",
    user="jerano",
    password="jerano2002",
    database="key_system"
)
cursor = db.cursor()

# --- Discord Bot Setup ---
intents = discord.Intents.default()
intents.message_content = True
intents.guilds = True
intents.members = True

bot = commands.Bot(command_prefix='!', intents=intents)  # Changed prefix to '!'

# --- Key Generator Function ---
def generate_key():
    chars = string.ascii_uppercase + string.digits
    return "TEMP-" + ''.join(random.choice(chars) for _ in range(6))

# --- Prefix Command to Create Key ---
@bot.command(name="createkey")
@commands.has_permissions(administrator=True)
async def createkey(ctx, duration: str):
    duration = duration.upper()
    valid_durations = ['1D', '1W', '1M', 'L']

    if duration not in valid_durations:
        await ctx.send("❌ Invalid duration. Use 1D, 1W, 1M, or L for lifetime.")
        return

    key = generate_key()
    expires_at = None

    if duration == '1D':
        expires_at = datetime.now() + timedelta(days=1)
    elif duration == '1W':
        expires_at = datetime.now() + timedelta(weeks=1)
    elif duration == '1M':
        expires_at = datetime.now() + timedelta(days=30)

    sql = "INSERT INTO keys (key_value, expires_at, duration_type, discord_id) VALUES (%s, %s, %s, %s)"
    val = (key, expires_at, duration, str(ctx.author.id))
    cursor.execute(sql, val)
    db.commit()

    await ctx.send(
        f"✅ **Key created!**\n"
        f"🔑 Key: `{key}`\n"
        f"⏳ Duration: `{duration}`\n"
        f"📅 Expires: `{expires_at.strftime('%Y-%m-%d %H:%M:%S') if expires_at else 'Never'}`"
    )

# --- Prefix Command to Reset HWID ---
@bot.command(name="resethwid")
@commands.has_permissions(administrator=True)
async def resethwid(ctx, key: str):
    cursor.execute("SELECT hwid FROM keys WHERE key_value = %s", (key,))
    result = cursor.fetchone()

    if not result:
        await ctx.send(f"❌ Key `{key}` not found.")
        return

    cursor.execute("UPDATE keys SET hwid = NULL WHERE key_value = %s", (key,))
    db.commit()

    await ctx.send(f"✅ HWID for key `{key}` has been reset.")

# --- Bot Ready Event ---
@bot.event
async def on_ready():
    print(f"✅ Logged in as {bot.user} (ID: {bot.user.id})")
    print("✅ Bot is ready!")

# --- Bot Run ---
bot.run('')
