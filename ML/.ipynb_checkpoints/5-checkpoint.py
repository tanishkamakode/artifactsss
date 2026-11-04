# https://www.kaggle.com/datasets/kyanyoga/sample-sales-data

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans

df = pd.read_csv("sales_data_sample.csv", encoding = "latin1")

df.head()

df.shape

df.info()

df.describe()

df.isnull().sum()

df = df.dropna()

df.isnull().sum()

x = df[["QUANTITYORDERED", "PRICEEACH", "SALES", "MSRP"]]

scaler = StandardScaler()
x = scaler.fit_transform(x)

wcss = []

for i in range(1, 11):
    kmeans = KMeans(n_clusters = i, random_state = 42)
    kmeans.fit(x)
    wcss.append(kmeans.inertia_)

plt.plot(range(1, 11), wcss, marker = "o")
plt.xlabel("Number of clusters")
plt.ylabel("WCSS value")
plt.title("Kmeans clustering")
plt.show()

kmeans = KMeans(n_clusters = 3, random_state = 42)
kmeans.fit(x)

df["Cluster"] = kmeans.labels_
df.head(3)

df.groupby("Cluster")[["QUANTITYORDERED", "PRICEEACH", "SALES", "MSRP"]].mean()

sns.scatterplot(data = df, x = "QUANTITYORDERED", y = "SALES", hue = "Cluster")
plt.xlabel("Quantity")
plt.ylabel("Sales")
plt.title("Clusters Formed")
plt.show()