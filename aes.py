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

    _key = "1234567890abcdef1234567890abcdef"  # should be size 32 bytes to AES_256
    msg = "Hello"

    _encrypted = encrypt(key=_key, raw=msg)

    print(f"Decrypted: `{decrypt(key=_key, enc=_encrypted)}`")

    _encrypted = 'c70258f05ca77310b5c0094283d3df96' + '671d3e17dacb2b3f23f5b70559645930'          # IV + Encrypted

    print(f"Decrypted from the encrypted one - {decrypt(key=_key, enc=_encrypted)}")
