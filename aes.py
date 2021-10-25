import re
from Crypto import Random
from Crypto.Cipher import AES


def encrypt(key, raw):
    raw = raw + '\0' * (AES.block_size - len(raw) % AES.block_size)
    raw = raw.encode('utf-8')

    iv = Random.new().read(AES.block_size)
    print(f"Key:{key}")
    print(f"IV:{iv.hex()}")

    key = key.encode('utf-8')
    # print(f"Key:{key.hex()}:{len(key)}")

    cipher = AES.new(key, AES.MODE_CBC, iv)

    encrypted = cipher.encrypt(raw)
    print(f"encrypted:{encrypted.hex()}")
    return (iv + encrypted).hex()


def decrypt(key, enc):
    enc = bytes.fromhex(enc)
    iv = enc[:16]
    cipher = AES.new(key.encode('utf-8'), AES.MODE_CBC, iv)
    return re.sub(b'\x00*$', b'', cipher.decrypt(enc[16:])).decode('utf-8')


if __name__ == '__main__':

    _key = "1234567890abcdef1234567890abcdef" # should be size 32 bytes to AES_256
    e_msg = "This is a small and portable implementation of the AES ECB, CTR and CBC encryption algorithms written in C.\
        You can override the default key-size of 128 bit with 192 or 256 bit by defining the symbols AES192 or AES256 in"

    _encrypted = encrypt(key=_key, raw=e_msg)

    print(f"Decrypted: `{decrypt(key=_key, enc=_encrypted)}`")
