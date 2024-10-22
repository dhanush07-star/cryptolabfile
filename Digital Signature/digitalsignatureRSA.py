import random
from hashlib import sha1

def is_prime(n, k=128):
    if n <= 1:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0:
        return False

    r, d = 0, n - 1
    while d % 2 == 0:
        r += 1
        d //= 2

    for _ in range(k):
        a = random.randint(2, n - 2)
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

def generate_large_prime(bits):
    while True:
        prime_candidate = random.getrandbits(bits)
        if is_prime(prime_candidate):
            return prime_candidate

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def mod_inverse(e, phi):
    t, new_t = 0, 1
    r, new_r = phi, e
    while new_r != 0:
        quotient = r // new_r
        t, new_t = new_t, t - quotient * new_t
        r, new_r = new_r, r - quotient * new_r
    if r > 1:
        raise ValueError("e is not invertible")
    if t < 0:
        t += phi
    return t

def generate_rsa_keys(bits=128):
    p = generate_large_prime(bits // 2)
    q = generate_large_prime(bits // 2)
    n = p * q
    phi = (p - 1) * (q - 1)

    e = 65537
    d = mod_inverse(e, phi)

    return (e, n), (d, n)

def rsa_sign(message, private_key):
    d, n = private_key
    hashed_message = int.from_bytes(sha1(message.encode()).digest(), byteorder='big') & ((1 << 8) - 1)
    signature = pow(hashed_message, d, n)
    return signature

def rsa_verify(message, signature, public_key):
    e, n = public_key
    hashed_message = int.from_bytes(sha1(message.encode()).digest(), byteorder='big') & ((1 << 8) - 1)
    decrypted_hash = pow(signature, e, n)
    print("hashed_message: ",hashed_message)
    print("   ")
    print("decrypted_hash: ",decrypted_hash)
    return decrypted_hash == hashed_message

if __name__ == "__main__":
    public_key, private_key = generate_rsa_keys(bits=16)
    print("Public Key:", public_key)
    print("Private Key:", private_key)

    message = "Dhanush"

    signature = rsa_sign(message, private_key)
    print("Signature:", signature)

    is_valid = rsa_verify(message, signature, public_key)
    print("Signature valid:", is_valid)
