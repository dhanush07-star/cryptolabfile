import math
import random

def isprime(a):
    for i in range(2,int(a**0.5)+1):
        if a %i == 0:
            return False
    return True 

# print(isprime(13))

def diffie_hellman(p,alpha,A_key_private,B_key_private):
    A_pubic = pow(alpha,A_key_private) % p
    B_pubic =  pow(alpha,B_key_private) % p
    shared_secret_a =pow(pow(alpha,A_key_private),B_key_private) % p
    shared_secret_b =pow(pow(alpha,B_key_private),A_key_private) % p

    return shared_secret_a, shared_secret_b

if __name__ == "__main__":
    # p = int(input("choose a prime no: ")) 
    # alpha = int(input("choose a random no from 2 to p - 2: ")) 
    
    while True:
        p = random.randint(2,2000)
        if isprime(p):
            print("Prime Number :")
            print(p)
            break

    while True:
        alpha = random.randint(2, p - 2)
        if alpha > 2 and alpha < (p-1):
            print("alpha")
            print(alpha)
            break
  
    while True:
        A_key_private = random.randint(1, p - 1)
        if A_key_private >= 1 and A_key_private <= p-1:
            print("A_key_private")
            print(A_key_private)
            break
    while True:
        B_key_private = random.randint(1, p - 1)
        if B_key_private >= 1 and B_key_private <= p-1:
            print("B_key_private")
            print(B_key_private)
            break
    
    shared_secret_a ,shared_secret_b = diffie_hellman(p,alpha,A_key_private,B_key_private)
    print(f"Shared secret A:{shared_secret_a}")
    print(f"Shared secret B:{shared_secret_b}")  
    assert shared_secret_a==shared_secret_b,"Shared secrets do not match!"
    print("Shared secrets match and Key exchange is successful!")
   