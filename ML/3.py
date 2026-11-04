# https://www.kaggle.com/datasets/shrutimechlearn/churn-modelling

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score, confusion_matrix

df = pd.read_csv("Churn_Modelling.csv")

df.head()

df.shape

df.dtypes

df.info()

df.describe()

df.isnull().sum()

df = df.drop(["RowNumber", "CustomerId", "Surname"], axis = 1)

df.columns

df = pd.get_dummies(df)

df.head(3)

x = df.drop("Exited", axis = 1)
y = df["Exited"]

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 0.2, random_state = 42)

scaler = StandardScaler()
x_train = scaler.fit_transform(x_train)
x_test = scaler.transform(x_test)

nn = MLPClassifier(
    hidden_layer_sizes=(64, 32),
    activation='relu',
    solver='adam',
    max_iter=1000,
    random_state=42
)
nn.fit(x_train, y_train)

y_pred = nn.predict(x_test)

print("Accuracy = ", accuracy_score(y_test, y_pred))
print("Confusion matrix: ", confusion_matrix(y_test, y_pred))

sample = x_test[[0]]

predictionnn = nn.predict(sample)

print("Actual: ")
if(y_test.iloc[[0]].item() == 0):
    print("Did not leave")
else:
    print("Left")

print("NN: ")
if(predictionnn == 0):
    print("Did not leave")
else:
    print("Left")