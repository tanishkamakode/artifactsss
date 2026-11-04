# https://www.kaggle.com/datasets/yasserh/uber-fares-dataset

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import r2_score, root_mean_squared_error

df = pd.read_csv("uber.csv")

df.head()

df.shape

df.dtypes

df.info()

df.describe()

df.isnull().sum()

df = df.dropna()

df.isnull().sum()

df = df.drop(["Unnamed: 0", "key"], axis = 1)

df.columns

df["pickup_datetime"] = pd.to_datetime(df["pickup_datetime"])

df["year"] = df["pickup_datetime"].dt.year
df["month"] = df["pickup_datetime"].dt.month
df["day"] = df["pickup_datetime"].dt.day
df["hour"] = df["pickup_datetime"].dt.hour

df = df.drop("pickup_datetime", axis = 1)

df.head(3)

sns.boxplot(y=df["fare_amount"])
plt.title("Outliers")
plt.show()

df = df[df["fare_amount"] > 0]
Q1 = df["fare_amount"].quantile(0.25)
Q3 = df["fare_amount"].quantile(0.75)

IQR = Q3 - Q1

lower = Q1 - 1.5 * IQR
upper = Q3 + 1.5 * IQR

df = df[(df["fare_amount"] >= lower) & (df["fare_amount"] <= upper)]

sns.boxplot(y=df["fare_amount"])
plt.title("Outliers")
plt.show()

x = df.drop("fare_amount", axis = 1)
y = df["fare_amount"]

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 0.2, random_state = 42)

lr = LinearRegression()
lr.fit(x_train, y_train)

y_pred_lr = lr.predict(x_test)

r2_lr = r2_score(y_test, y_pred_lr)
rsme_lr = root_mean_squared_error(y_test, y_pred_lr)

print(r2_lr)
print(rsme_lr)

rf = RandomForestRegressor(n_estimators = 20, random_state = 42)
rf.fit(x_train, y_train)

y_pred_rf = rf.predict(x_test)

r2_rf = r2_score(y_test, y_pred_rf)
rsme_rf = root_mean_squared_error(y_test, y_pred_rf)

print(r2_rf)
print(rsme_rf)

if r2_lr > r2_rf and rsme_lr < rsme_rf:
    print("Linear Regression is better")
else:
    print("Random forest is better")

sample = x_test.iloc[[0]]

prediction_lr = lr.predict(sample)
prediction_rf = rf.predict(sample)

print("Actual fare: ", y_test.iloc[[0]].item())
print("Predicted by linear regression: ", prediction_lr[0])
print("Predicted by random forest: ", prediction_rf[0])