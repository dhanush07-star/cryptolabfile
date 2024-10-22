import random
from Crypto.Util.number import getPrime, getRandomRange
from sympy import isprime, primitive_root

def generate_keypair():
    p = getPrime(128)
    print(p)
    alpha = getRandomRange(1,p-2)
    private_b = getRandomRange(1,p-2)
    public_b = pow(alpha, private_b, p)
    return (p, alpha, private_b, public_b)

def encrypt(p, g, y, m):
    k = getRandomRange(1, p - 2)
    c1 = pow(g, k, p)
    c2 = (m * pow(y, k, p)) % p
    return (c1, c2)

def decrypt(p, x, c):
    c1, c2 = c
    s = pow(c1, x, p)
    s_inv = pow(s, -1, p)  
    m = (c2 * s_inv) % p
    return m
if __name__ == "__main__":
    p, alpha, private_b, public_b = generate_keypair()
    message = 15 
    ciphertext = encrypt(p, alpha, public_b, message)
    print(f"Ciphertext: {ciphertext}")
    decrypted_message = decrypt(p, private_b, ciphertext)
    print(f"Decrypted message: {decrypted_message}")
