import hashlib

def main():
    # Read the input from the file
    file =  open("input.txt", "r")
    data = file.read().strip()
    hash_object = hashlib.sha256(data.encode())
    sha256_hash = hash_object.hexdigest()
    file.close()
    # Write the hash value to a file
    file1 = open("output.txt", "w+")
    file1.write(sha256_hash)
    file1.close()

if __name__ == "__main__":
    main()
