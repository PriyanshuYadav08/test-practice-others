import random
import time

LOSS_PROB = 0.2
WINDOW_SIZE = 4
TOTAL_FRAMES = 10

def maybe_lose(tag, seq):
    if random.random() < LOSS_PROB:
        print(f"Channel: {tag} {seq} LOST")
        return True
    return False

# ---------- TOP-LEVEL SIMULATION (NO MAIN) ----------

print("=== GO-BACK-N PROTOCOL SIMULATION ===")

base = 0              # first unacknowledged frame
next_seq_num = 0      # next frame to send
acked = [False] * TOTAL_FRAMES

while base < TOTAL_FRAMES:
    # send frames in window
    while next_seq_num < base + WINDOW_SIZE and next_seq_num < TOTAL_FRAMES:
        print(f"Sender: Sending frame {next_seq_num}")
        if not maybe_lose("Frame", next_seq_num):
            print(f"Receiver: Frame {next_seq_num} received. Sending cumulative ACK {next_seq_num}")
            if not maybe_lose("ACK", next_seq_num):
                print(f"Sender: ACK {next_seq_num} received")
                acked[next_seq_num] = True
        next_seq_num += 1

    time.sleep(1)

    # check timeout for base
    if not acked[base]:
        print(f"\nSender: TIMEOUT for frame {base}. Go back and resend from {base}")
        for i in range(base, next_seq_num):
            if i >= TOTAL_FRAMES:
                break
            print(f"Sender: Resending frame {i}")
            if not maybe_lose("Frame", i):
                print(f"Receiver: Frame {i} received. Sending cumulative ACK {i}")
                if not maybe_lose("ACK", i):
                    print(f"Sender: ACK {i} received")
                    acked[i] = True

    # slide window
    while base < TOTAL_FRAMES and acked[base]:
        base += 1

print("\nAll frames transmitted using Go-Back-N.")
