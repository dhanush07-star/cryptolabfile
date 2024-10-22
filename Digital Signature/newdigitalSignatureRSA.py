import random
import math
from hashlib import sha1
from Crypto.Util.number import getPrime, getRandomRange
import hashlib


def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def generate_rsa_keys(bits=8):
    p = getPrime(bits)
    print("p: ",p)
    q = getPrime(bits)
    print("q: ",q)
    n = p * q
    phi = (p - 1) * (q - 1)

    while True:
        e = random.randint(2, phi - 1)
        if math.gcd(e, phi) == 1:
            break

  
    while True:
        d = random.randint(2, phi - 1)
        if (d * e) % phi == 1:
            break

    return (e, n), (d, n)

def rsa_sign(message, private_key):
    d, n = private_key
    if type(message) == int:
        message_bytes = message.to_bytes((message.bit_length() + 7) // 8, byteorder='big')
        hashed_message = int.from_bytes(hashlib.sha1(message_bytes).digest(), byteorder='big') & ((1 << 8) - 1)
    else:
        hashed_message = int.from_bytes(sha1(message.encode()).digest(), byteorder='big') & ((1 << 8) - 1)
    signature = pow(hashed_message, d, n)
    return signature

def rsa_verify(message, signature, public_key):
    e, n = public_key
    if type(message) == int:
        message_bytes = message.to_bytes((message.bit_length() + 7) // 8, byteorder='big')
        hashed_message = int.from_bytes(hashlib.sha1(message_bytes).digest(), byteorder='big') & ((1 << 8) - 1)
    else:
        hashed_message = int.from_bytes(sha1(message.encode()).digest(), byteorder='big') & ((1 << 8) - 1)
    decrypted_hash = pow(signature, e, n)
    print("hashed_message: ",hashed_message)
    print("   ")
    print("decrypted_hash: ",decrypted_hash)
    return decrypted_hash == hashed_message

if __name__ == "__main__":
    public_key, private_key = generate_rsa_keys(bits=8)
    print("Public Key:", public_key)
    print("Private Key:", private_key)

    message = input()

    signature = rsa_sign(message, private_key)
    print("Signature:", signature)

    is_valid = rsa_verify(message, signature, public_key)
    print("Signature valid:", is_valid)
