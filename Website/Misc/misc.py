import pandas as pd
import random

def getName():
    name = ""
    for i in range(5):
        name += chr(random.randint(65, 90))
    return name

def getScore():
    return random.randint(0, 200000)


data = pd.read_csv("gs://example_educational_bucket/scores.csv")
print(data)

newNames = []
newScores = []

for i in range(100):
    newNames.append(getName())
    newScores.append(getScore())

data['name'] = newNames
data['score'] = newScores

data.to_csv('gs://example_educational_bucket/scores.csv', index=False)
print(data)
