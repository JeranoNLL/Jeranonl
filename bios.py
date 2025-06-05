import discord
from discord.ext import commands
from discord import app_commands
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

bot = commands.Bot(command_prefix='/', intents=intents)
tree = bot.tree  # Slash command interface

# --- Key Generator Function ---
def generate_key():
    chars = string.ascii_uppercase + string.digits
    return "TEMP-" + ''.join(random.choice(chars) for _ in range(6))

# --- Slash Command to Create Key ---
@tree.command(name="createkey", description="Create a temporary license key")
@app_commands.describe(duration="Duration: 1D (Day), 1W (Week), 1M (Month), L (Lifetime)")
async def createkey(interaction: discord.Interaction, duration: str):
    if not interaction.user.guild_permissions.administrator:
        await interaction.response.send_message("❌ You must be an administrator to use this command.", ephemeral=True)
        return

    valid_durations = ['1D', '1W', '1M', 'L']
    if duration.upper() not in valid_durations:
        await interaction.response.send_message("❌ Invalid duration. Use 1D, 1W, 1M, or L for lifetime.", ephemeral=True)
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
    val = (key, expires_at, duration.upper(), str(interaction.user.id))
    cursor.execute(sql, val)
    db.commit()

    await interaction.response.send_message(
        f"✅ **Key created!**\n"
        f"🔑 Key: `{key}`\n"
        f"⏳ Duration: `{duration.upper()}`\n"
        f"🗓 Expires: `{expires_at.strftime('%Y-%m-%d %H:%M:%S') if expires_at else 'Never'}`"
    )

# --- Slash Command to Reset HWID ---
@tree.command(name="resethwid", description="Reset the HWID associated with a license key")
@app_commands.describe(key="The license key to reset HWID for")
async def resethwid(interaction: discord.Interaction, key: str):
    if not interaction.user.guild_permissions.administrator:
        await interaction.response.send_message("❌ You must be an administrator to use this command.", ephemeral=True)
        return

    cursor.execute("SELECT hwid FROM keys WHERE key_value = %s", (key,))
    result = cursor.fetchone()

    if not result:
        await interaction.response.send_message("❌ Key not found.", ephemeral=True)
        return

    # Reset HWID to NULL
    cursor.execute("UPDATE keys SET hwid = NULL WHERE key_value = %s", (key,))
    db.commit()

    await interaction.response.send_message(f"✅ HWID for key `{key}` has been reset.")

# --- Bot Ready Event ---
@bot.event
async def on_ready():
    await tree.sync()
    print(f"✅ Logged in as {bot.user} (ID: {bot.user.id})")
    print("✅ Slash commands synced.")

# --- Bot Run ---
bot.run('MTM3OTg2OTY1MTgzMTM1NzU4MA.GPDyH1.dNE3D44eagKZayRi8kMY7MaqDmGQLLCZEzM_BI')
