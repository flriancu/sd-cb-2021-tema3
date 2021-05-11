import os
import string


def get_alphabet():
    return string.ascii_lowercase + string.ascii_uppercase + string.digits + ".-'?! "


def get_special_tokens():
    return "_~:\r\n"


def detect_non_ascii():
    input_dir = os.path.join("checker", "_test", "input")

    for file_name in os.listdir(input_dir):
        file_path = os.path.join(input_dir, file_name)
        if not os.path.isfile(file_path) or not file_path.endswith(".txt"):
            continue

        with open(file_path, "r", encoding="cp1252") as fi:
            rows = fi.readlines()

        charset = get_alphabet() + get_special_tokens()
        for i, r in enumerate(rows):
            for j, c in enumerate(r):
                if c not in charset:
                    print(f"file {file_name}, row {i+1}, col {j+1}")

if __name__ == "__main__":
    detect_non_ascii()
