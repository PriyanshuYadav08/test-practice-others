import pandas as pd
from textblob import TextBlob
import matplotlib.pyplot as plt

df = pd.read_csv("data.csv", encoding='latin1')

comments = df[df['content'].notnull() & (df['content'].str.strip() != '')].copy()

def analyze_sentiment(text):
    blob = TextBlob(str(text))
    polarity = blob.sentiment.polarity
    if polarity > 0:
        return 'Positive'
    elif polarity < 0:
        return 'Negative'
    else:
        return 'Neutral'

comments['Sentiment'] = comments['content'].apply(analyze_sentiment)
comments['Polarity_Score'] = comments['content'].apply(lambda x: TextBlob(str(x)).sentiment.polarity)

sentiment_counts = comments['Sentiment'].value_counts()
print("Sentiment Distribution:\n", sentiment_counts)
print(f"\nAverage Polarity Score: {comments['Polarity_Score'].mean():.3f}")

plt.figure(figsize=(6,4))
sentiment_counts.plot(kind='bar', color=['green', 'red', 'gray'])
plt.title("Sentiment Distribution - Porsche YouTube Comments")
plt.xlabel("Sentiment")
plt.ylabel("Number of Comments")
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.show()

comments.to_excel("Porsche_Sentiment_Results.xlsx", index=False)
print("\nResults saved to Porsche_Sentiment_Results.xlsx")