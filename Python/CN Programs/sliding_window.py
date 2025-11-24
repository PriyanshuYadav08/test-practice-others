import random
import time

LOSS_PROB = 0.25
WINDOW_SIZE = 4
TOTAL_FRAMES = 10

def maybe_lose(tag, seq):
    if random.random() < LOSS_PROB:
        print(f"Channel: {tag} {seq} LOST")
        return True
    return False

# ---------- TOP-LEVEL SIMULATION (NO MAIN) ----------

print("=== SELECTIVE REPEAT PROTOCOL SIMULATION ===")

base = 0
next_seq_num = 0
acked = [False] * TOTAL_FRAMES

while base < TOTAL_FRAMES:
    # send all not-yet-acked frames in window
    while next_seq_num < base + WINDOW_SIZE and next_seq_num < TOTAL_FRAMES:
        if not acked[next_seq_num]:
            print(f"Sender: Sending frame {next_seq_num}")
            if not maybe_lose("Frame", next_seq_num):
                print(f"Receiver: Frame {next_seq_num} received. Sending ACK {next_seq_num}")
                if not maybe_lose("ACK", next_seq_num):
                    print(f"Sender: ACK {next_seq_num} received")
                    acked[next_seq_num] = True
        next_seq_num += 1

    time.sleep(1)

    # selective retransmission of only those not acked in window
    for i in range(base, min(base + WINDOW_SIZE, TOTAL_FRAMES)):
        if not acked[i]:
            print(f"\nSender: TIMEOUT for frame {i}. Resending frame {i}")
            if not maybe_lose("Frame", i):
                print(f"Receiver: Frame {i} received. Sending ACK {i}")
                if not maybe_lose("ACK", i):
                    print(f"Sender: ACK {i} received")
                    acked[i] = True

    # slide window for all contiguous acked frames
    while base < TOTAL_FRAMES and acked[base]:
        base += 1

print("\nAll frames transmitted using Selective Repeat.")
