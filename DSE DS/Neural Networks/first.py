import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
from tensorflow.keras.optimizers import Adam
import matplotlib.pyplot as plt

df = pd.read_csv("NNdataset.csv")

cols = [
    'DiagnosingFacilityDistrict',
    'DiagnosingFacilityTBU',
    'DiagnosingFacilityPHI',
    'DiagnosingFacilityPHIType',
    'Treatment_Outcome',
    'Patient_Status',
    'Age',
    'Gender',
    'Weight',
    'HIV_Status',
    'DiabetesStatus',
    'basisOfDiagnosis_TestName',
    'basisOfDiagnosis_FinalInterpretation',
    'Microbiologically_Confirmed',
    'TypeOfCase',
    'SiteOfDisease',
    'EPSite',
    'FollowupDone_Count'
]
df = df[cols]

df = df.dropna(subset=['Microbiologically_Confirmed'])
df['Microbiologically_Confirmed'] = df['Microbiologically_Confirmed'].map({'Yes': 1, 'No': 0})

for col in df.columns:
    if df[col].dtype == 'object':
        df[col] = df[col].fillna('Unknown')
    else:
        df[col] = df[col].fillna(df[col].median())

X = df.drop('Microbiologically_Confirmed', axis=1)
y = df['Microbiologically_Confirmed']

categorical_cols = X.select_dtypes(include=['object']).columns
for col in categorical_cols:
    le = LabelEncoder()
    X[col] = le.fit_transform(X[col].astype(str))

scaler = StandardScaler()
numerical_cols = ['Age', 'Weight', 'FollowupDone_Count']
for col in numerical_cols:
    if col in X.columns:
        X[col] = scaler.fit_transform(X[[col]])

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = Sequential([
    Dense(64, input_dim=X_train.shape[1], activation='relu'),
    Dropout(0.3),
    Dense(32, activation='relu'),
    Dense(1, activation='sigmoid')  # Binary output
])

model.compile(optimizer=Adam(learning_rate=0.001),
              loss='binary_crossentropy',
              metrics=['accuracy'])

history = model.fit(
    X_train, y_train,
    epochs=75,
    batch_size=32,
    validation_split=0.2,
    verbose=1
)

y_pred = (model.predict(X_test) > 0.5).astype(int)
print("\nModel Evaluation:")
print(confusion_matrix(y_test, y_pred))
print(classification_report(y_test, y_pred))
print("Accuracy:", accuracy_score(y_test, y_pred))

plt.figure(figsize=(10,5))
plt.plot(history.history['accuracy'], label='Train Accuracy')
plt.plot(history.history['val_accuracy'], label='Validation Accuracy')
plt.title('Model Accuracy over Epochs')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.legend()
plt.show()

plt.figure(figsize=(10,5))
plt.plot(history.history['loss'], label='Train Loss')
plt.plot(history.history['val_loss'], label='Validation Loss')
plt.title('Model Loss over Epochs')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.legend()
plt.show()

model.save("tb_prediction_model.h5")
print("\n✅ Model saved as tb_prediction_model.h5")