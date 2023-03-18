import subprocess

cmd_args = []

def process_discord_cmd(str1):
    arr = str1.split(" ")
    #print(arr)
    if arr[0] != "$uns":
        return ""
    for x in arr:
        if x == "":
            continue
        cmd_args.append(x)

    #print(cmd_args)
    return run_process(arr)

def run_process(arr1):
  output = ""
  cmd_str = "cd bin/Release/ && ./uns "
  for i in range(1, len(arr1)):
      cmd_str += arr1[i] + " "
  #print(cmd_str)
  result = subprocess.Popen(cmd_str, shell=True, stdout=subprocess.PIPE)
  for line in result.stdout:
    #print(line.decode('ascii'), end="")
    output += line.decode("ascii")
  return output

#process_discord_cmd("hello  -u -s hello")
