import random

alphabet = ["a", "b", "c", "d", "e"]
import os

os.mkdir("data")
with open("data/dummy.txt", "w") as f:
    for i in range(100):
        f.write(random.choice(alphabet) * random.randrange(1, 1000, 1))

