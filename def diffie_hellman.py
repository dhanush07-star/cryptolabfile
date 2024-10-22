def diffie_hellman(p,alpha,A_key_private,B_key_private):
    A_pubic = pow(alpha,A_key_private) % p
    B_pubic =  pow(alpha,B_key_private) % p
    shared_secret_a =pow(pow(alpha,A_key_private),B_key_private) % p
    shared_secret_b =pow(pow(alpha,B_key_private),A_key_private) % p

    return shared_secret_a, shared_secret_b

if __name__ == "__main__":
    p = int(input("choose a prime no: ")) 
    alpha = int(input("choose a random no from 2 to p - 2: ")) 
                
    A_key_private = int(input("choose A's private key: "))                                
    B_key_private = int(input("choose B's private key: "))
    
    shared_secret_a ,shared_secret_b = diffie_hellman(p,alpha,A_key_private,B_key_private)
    print(f"Shared secret A:{shared_secret_a}")
    print(f"Shared secret B:{shared_secret_b}")  
    assert shared_secret_a==shared_secret_b,"Shared secrets do not match!"
    print("Shared secrets match and Key exchange is successful!")
   