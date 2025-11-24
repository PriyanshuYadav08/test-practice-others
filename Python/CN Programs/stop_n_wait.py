import random
import time

LOSS_PROB = 0.3      # probability of loss of frame/ACK
NUM_FRAMES = 5       # number of frames to send

def send_frame(seq):
    print(f"Sender: Sending frame with seq = {seq}")
    if random.random() < LOSS_PROB:
        print(f"Channel: Frame {seq} LOST")
        return False
    print(f"Channel: Frame {seq} delivered to Receiver")
    return True

def send_ack(seq):
    print(f"Receiver: Sending ACK {seq}")
    if random.random() < LOSS_PROB:
        print(f"Channel: ACK {seq} LOST")
        return False
    print(f"Channel: ACK {seq} delivered to Sender")
    return True

# ---------- TOP-LEVEL SIMULATION (NO MAIN) ----------

print("=== STOP-AND-WAIT PROTOCOL SIMULATION ===")

seq = 0          # alternating bit (0/1)
frame_no = 0

while frame_no < NUM_FRAMES:
    print("\n----------------------------------")
    print(f"Sender: Preparing Frame {frame_no} with seq={seq}")

    frame_delivered = send_frame(seq)

    if frame_delivered:
        print(f"Receiver: Frame with seq={seq} received correctly.")
        ack_delivered = send_ack(seq)
    else:
        ack_delivered = False

    if ack_delivered:
        print(f"Sender: ACK {seq} received. Frame {frame_no} successfully transmitted.")
        frame_no += 1
        seq = 1 - seq   # toggle seq
    else:
        print("Sender: Timeout/ACK lost. Resending same frame...")

    time.sleep(1)

print("\nAll frames sent using Stop-and-Wait.")
