# https://www.kaggle.com/datasets/balaka18/email-spam-classification-dataset-csv

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix

df = pd.read_csv("emails.csv")

df.head()

df.shape

df.dtypes

df.info()

df.describe()

df.isnull().sum()

df = df.dropna()

df.isnull().sum()

df = df.drop("Email No.", axis = 1)

df.columns

sns.countplot(x = df["Prediction"])
plt.title("Spam VS Not spam")
plt.show()

x = df.drop("Prediction", axis = 1)
y = df["Prediction"]

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 0.2, random_state = 42)

scaler = StandardScaler()
x_train = scaler.fit_transform(x_train)
x_test = scaler.transform(x_test)

knn = KNeighborsClassifier()
knn.fit(x_train, y_train)

y_pred_knn = knn.predict(x_test)

print("Accuracy: ", accuracy_score(y_test, y_pred_knn))
print("Precision: ", precision_score(y_test, y_pred_knn))
print("Recall: ", recall_score(y_test, y_pred_knn))
print("F1 Score: ", f1_score(y_test, y_pred_knn))

cm = confusion_matrix(y_test, y_pred_knn)
print("KNN Confusion Matrix:")
print(cm)

svm = SVC(kernel = "linear", random_state = 42)
svm.fit(x_train, y_train)

y_pred_svm = svm.predict(x_test)

print("Accuracy: ", accuracy_score(y_test, y_pred_svm))
print("Precision: ", precision_score(y_test, y_pred_svm))
print("Recall: ", recall_score(y_test, y_pred_svm))
print("F1 Score: ", f1_score(y_test, y_pred_svm))

cm = confusion_matrix(y_test, y_pred_svm)
print("SVM Confusion Matrix:")
print(cm)

sample = x_test[[0]]

prediction_knn = knn.predict(sample)
prediction_svm = svm.predict(sample)

print("Actual: ")
if(y_test.iloc[[0]].item() == 0):
    print("Not Spam")
else:
    print("Spam")

print("KNN: ")
if(prediction_knn == 0):
    print("Not spam")
else:
    print("Spam")

print("SVM: ")
if(prediction_svm == 0):
    print("Not spam")
else:
    print("Spam")