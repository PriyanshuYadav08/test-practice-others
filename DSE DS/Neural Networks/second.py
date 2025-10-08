# train_tb_default_pytorch.py
# Binary classification (Default vs Not) for TB patients using PyTorch (ReLU)
# Adjust 'selected_cols' if you want different features.

import pandas as pd
import numpy as np
import torch
from torch import nn
from torch.utils.data import Dataset, DataLoader
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, roc_auc_score, classification_report, confusion_matrix
import os
import sys

# ---------- Configuration ----------
FILE_PATH = "NNdataset.csv"   # change if needed
SHEET_NAME = "MAIN DATA"
MODEL_SAVE_PATH = "/mnt/data/tb_default_model.pth"
RANDOM_STATE = 42
TEST_SIZE = 0.20
BATCH_SIZE = 64
EPOCHS = 15
LR = 1e-3

# 10-15 features chosen (change as needed)
selected_cols = [
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

# ---------- Helpers ----------
def safe_read_excel(path, sheet):
    if not os.path.exists(path):
        raise FileNotFoundError(f"File not found: {path}")
    return pd.read_excel(path, sheet_name=sheet)

def map_target_generic(x):
    """Robust mapping to 0/1 for many possible encodings. Returns np.nan if unknown."""
    if pd.isna(x):
        return np.nan
    s = str(x).strip().lower()
    # Known positive indicators for 'default'
    positives = {"yes","y","default","defaulter","defaulter (yes)","defaulted","1","true","t","defaulted (yes)"}
    negatives = {"no","n","0","false","f","treatment_complete","treatment complete","completed","cured","not defaulted","not defaulted (no)"}
    # Direct matches
    if s in positives:
        return 1
    if s in negatives:
        return 0
    # Substring checks
    if "default" in s:
        return 1
    if "complete" in s or "cured" in s or "treatment complete" in s:
        return 0
    # numeric-like
    try:
        iv = int(s)
        if iv == 1:
            return 1
        if iv == 0:
            return 0
    except:
        pass
    return np.nan

def map_yesno(x):
    s = str(x).strip().lower()
    if s in ("yes","y","1","true","t"):
        return 1
    if s in ("no","n","0","false","f"):
        return 0
    return 0

# ---------- Load ----------
print("Loading Excel:", FILE_PATH)
df_all = safe_read_excel(FILE_PATH, SHEET_NAME)
print("Sheet rows:", len(df_all))
existing_cols = [c for c in selected_cols if c in df_all.columns]
print("Using columns:", existing_cols)

df = df_all[existing_cols].copy()

# ---------- Target ----------
if "Default or not" not in df.columns:
    print("ERROR: 'Default or not' column missing. Available columns:", df.columns.tolist())
    sys.exit(1)

print("\nOriginal target value counts (sample):")
print(df["Default or not"].value_counts(dropna=False).head(50).to_string())

# Map target robustly
df["target_mapped"] = df["Default or not"].apply(map_target_generic)
print("\nAfter mapping, counts (including NaN):")
print(df["target_mapped"].value_counts(dropna=False).to_string())

# If mapping produced only one class, stop and prompt user to inspect raw values
if df["target_mapped"].nunique(dropna=True) <= 1:
    print("\nERROR: target mapping produced <=1 class. Please inspect 'Default or not' unique values above.")
    print("You can modify map_target_generic() in the script to handle your dataset's encodings.")
    sys.exit(1)

# Drop rows without mapped target
df = df.dropna(subset=["target_mapped"])
df["target_mapped"] = df["target_mapped"].astype(int)

# ---------- Feature preprocessing ----------
numeric_cols = [c for c in ["Age", "Weight", "FollowupDone_Count", "YEAR", "MONTH"] if c in df.columns]
cat_cols = [c for c in ["Gender", "HIV_Status", "DiabetesStatus", "basisOfDiagnosis_TestName",
                        "Microbiologically_Confirmed", "SiteOfDisease", "DiagnosingFacilityPHIType",
                        "TypeOfCase", "ContactTracing_Done"] if c in df.columns]

# Ensure numeric types and fill missing with median
for c in numeric_cols:
    df[c] = pd.to_numeric(df[c], errors='coerce')
    med = df[c].median()
    df[c] = df[c].fillna(med)

# Fill categorical missing
for c in cat_cols:
    df[c] = df[c].fillna("Unknown").astype(str).str.strip()

# Map boolean-like to numeric
if "Microbiologically_Confirmed" in df.columns:
    df["Microbiologically_Confirmed"] = df["Microbiologically_Confirmed"].apply(map_yesno)

if "ContactTracing_Done" in df.columns:
    df["ContactTracing_Done_bin"] = df["ContactTracing_Done"].apply(map_yesno)
    # replace original in cat_cols
    cat_cols = [x for x in cat_cols if x != "ContactTracing_Done"]
    cat_cols.append("ContactTracing_Done_bin")

# One-hot encode categorical features (drop_first to reduce dimensionality)
df_ohe = pd.get_dummies(df[numeric_cols + cat_cols], drop_first=True)

X = df_ohe.values.astype(np.float32)
y = df["target_mapped"].values.astype(np.float32)

print("\nFinal feature matrix shape:", X.shape)
print("Default positive ratio (defaults=1): {:.4f}".format(y.mean()))

# ---------- Train/test split ----------
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=TEST_SIZE, stratify=y, random_state=RANDOM_STATE
)

scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# ---------- PyTorch Dataset ----------
class TBDefaultDataset(Dataset):
    def _init_(self, X, y):
        self.X = torch.from_numpy(X).float()
        self.y = torch.from_numpy(y).float().unsqueeze(1)
    def _len_(self):
        return len(self.y)
    def _getitem_(self, idx):
        return self.X[idx], self.y[idx]

train_dataset = TBDefaultDataset(X_train, y_train)
test_dataset = TBDefaultDataset(X_test, y_test)
train_loader = DataLoader(train_dataset, batch_size=BATCH_SIZE, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=BATCH_SIZE, shuffle=False)

# ---------- Model ----------
class Net(nn.Module):
    def _init_(self, input_dim):
        super()._init_()
        self.net = nn.Sequential(
            nn.Linear(input_dim, 64),
            nn.ReLU(),
            nn.Dropout(0.2),
            nn.Linear(64, 32),
            nn.ReLU(),
            nn.Dropout(0.1),
            nn.Linear(32, 1),
            nn.Sigmoid()
        )
    def forward(self, x):
        return self.net(x)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = Net(X_train.shape[1]).to(device)
criterion = nn.BCELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=LR)

# ---------- Training ----------
for epoch in range(1, EPOCHS + 1):
    model.train()
    losses = []
    for xb, yb in train_loader:
        xb, yb = xb.to(device), yb.to(device)
        preds = model(xb)
        loss = criterion(preds, yb)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        losses.append(loss.item())
    avg_loss = np.mean(losses)

    # Quick eval on test set
    model.eval()
    all_preds = []
    all_true = []
    with torch.no_grad():
        for xb, yb in test_loader:
            xb = xb.to(device)
            p = model(xb).cpu().numpy().flatten()
            all_preds.extend(p.tolist())
            all_true.extend(yb.numpy().flatten().tolist())
    pred_labels = [1 if p >= 0.5 else 0 for p in all_preds]
    acc = accuracy_score(all_true, pred_labels)
    try:
        auc = roc_auc_score(all_true, all_preds)
    except:
        auc = float("nan")
    print(f"Epoch {epoch:02d} | loss: {avg_loss:.4f} | test_acc: {acc:.4f} | test_auc: {auc:.4f}")

# ---------- Final evaluation ----------
model.eval()
all_preds = []
all_true = []
with torch.no_grad():
    for xb, yb in test_loader:
        xb = xb.to(device)
        p = model(xb).cpu().numpy().flatten()
        all_preds.extend(p.tolist())
        all_true.extend(yb.numpy().flatten().tolist())
pred_labels = [1 if p >= 0.5 else 0 for p in all_preds]

print("\nFinal Test Accuracy:", accuracy_score(all_true, pred_labels))
try:
    print("Final Test ROC AUC:", roc_auc_score(all_true, all_preds))
except:
    print("Final Test ROC AUC: could not compute (maybe single-class).")
print("\nClassification report:")
print(classification_report(all_true, pred_labels, digits=4))
print("\nConfusion matrix:")
print(confusion_matrix(all_true, pred_labels))

# ---------- Save model + metadata ----------
torch.save({
    "model_state_dict": model.state_dict(),
    "scaler_mean": scaler.mean_.tolist(),
    "scaler_var": scaler.var_.tolist(),
    "feature_columns": df_ohe.columns.tolist()
}, MODEL_SAVE_PATH)
print(f"\nModel + metadata saved to: {MODEL_SAVE_PATH}")