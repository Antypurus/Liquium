import re
import subprocess

rc_release_regex = re.compile('v([0-9]+\.[0-9]+\.[0-9]+)-rc([0-9]+)')

#fetch latest git tag
hash = subprocess.check_output(["git", "rev-list","--tags","--max-count=1"]).strip().decode("utf-8") 
release_version = subprocess.check_output(["git","describe","--tags","--abbrev=0", hash]).strip().decode("utf-8") 

#read patch version
file = open('./VERSION','r')
local_version = file.read();

tag_name = ""
match = rc_release_regex.match(release_version)
if(match):
    version = match.group(1)
    if(version == local_version):
        release_candidate = int(match.group(2))+1
        tag_name = ("v"+version+"-rc"+str(release_candidate))
    else:
        #new version detected roll back to release canditate 1. local version always preceeds tag version
        tag_name = ("v"+local_version+"-rc1")
else:
    release_candidate = 1
    tag_name = ("v"+local_version+"-rc"+str(release_candidate))

print(tag_name)