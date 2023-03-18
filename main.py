import discord
import os

from uns import *

intent = discord.Intents.default()
#intent.members = True
intent.message_content = True

client = discord.Client(intents=intent)

@client.event
async def on_ready():
    print('We have logged in as {0.user}'.format(client))

@client.event
async def on_message(message):
    if message.author == client.user:
        return

    if message.content.startswith('$uns'):
        await message.channel.send(process_discord_cmd(message.content))

    #await client.process_commands(message)

client.run(os.getenv('TOKEN'))

