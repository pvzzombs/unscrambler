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
        #counter = 0
        results = []
        result_str = process_discord_cmd(message.content)
        lines = result_str.split("\n")
        for i in range(0, len(lines), 100):
            temp = ""
            for j in range(i, min(i+100, len(lines))):
                #results.append(result_str[c:c+1000])
                temp += lines[j] + "\n"
            results.append(temp)
        for x in results:
            await message.channel.send(x)

    #await client.process_commands(message)

client.run(os.getenv('TOKEN'))

