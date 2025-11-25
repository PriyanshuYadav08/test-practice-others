def xor(a, b):
    """Perform XOR between two binary strings of equal length."""
    result = ""
    for i in range(len(a)):
        result += "0" if a[i] == b[i] else "1"
    return result


def mod2_division(dividend, divisor):
    """Perform modulo-2 division and return remainder."""
    divisor_len = len(divisor)
    temp = dividend[:divisor_len]

    i = divisor_len
    while i < len(dividend):
        if temp[0] == '1':
            temp = xor(temp, divisor)[1:] + dividend[i]
        else:
            temp = xor(temp, '0'*divisor_len)[1:] + dividend[i]
        i += 1

    # Final step
    if temp[0] == '1':
        temp = xor(temp, divisor)[1:]
    else:
        temp = xor(temp, "0"*divisor_len)[1:]

    return temp


def encode_data(data, generator):
    """Return codeword = data + CRC"""
    appended_zeros = len(generator) - 1
    dividend = data + "0"*appended_zeros
    remainder = mod2_division(dividend, generator)
    return data + remainder


def introduce_error(bits, position):
    """Flip 1 bit at a position to create error."""
    lst = list(bits)
    lst[position] = '1' if lst[position] == '0' else '0'
    return "".join(lst)


def check_data(received, generator):
    """Check if remainder is all zeros."""
    remainder = mod2_division(received, generator)
    return all(bit == '0' for bit in remainder)


# ----------- DEMO ----------

data = input("Enter data bits: ")
generator = input("Enter generator bits: ")

codeword = encode_data(data, generator)
print("\nTransmitted Codeword:", codeword)

# Introduce manual error (optional)
choice = input("Introduce error? (y/n): ").lower()
if choice == 'y':
    pos = int(input("Enter bit position to flip (0-indexed): "))
    received = introduce_error(codeword, pos)
else:
    received = codeword

print("Received Bits:", received)

if check_data(received, generator):
    print("Result: No error detected (CRC OK).")
else:
    print("Result: ERROR detected (CRC FAILED).")
