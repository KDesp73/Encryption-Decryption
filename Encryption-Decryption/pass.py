import string
import random
import hashlib
from tqdm import tqdm

characters = list(string.ascii_letters + string.digits + "!@#$%^&*(){}[]")
print(len(characters))
def generate_random_password():
	#length = (input("Enter password length: "))
    length = 4#int(input("Enter password length: "))
    
    random.shuffle(characters)
    password = []
    for i in range(length):
        password.append(random.choice(characters))

    random.shuffle(password)
    #print("".join(password))
    pasw = "".join(passdord)
    #print(pasw)
    return pasw
  
def str2hash(md5sring): # = "GeeksforGeeks"
    result = hashlib.md5(md5sring.encode())
    #print(result.hexdigest())
    
password_list = []
number =  int(input("numbers of passwords: "))
for i in tqdm(range(0,number)):
    password_list.append(generate_random_password())

for i in tqdm(range(0,len(password_list))):
    str2hash(password_list[i])