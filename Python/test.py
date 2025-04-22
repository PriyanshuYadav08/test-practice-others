import numpy as np
import matplotlib.pyplot as plt

# Set random seed for reproducibility
np.random.seed(42)

# Number of simulations
n_simulations = 10000

# Define component parameters (mean and std dev for load and strength)
components = {
    "Girder": {"load_mean": 100, "load_std": 15, "strength_mean": 150, "strength_std": 25},
    "Bolt":   {"load_mean": 50,  "load_std": 10, "strength_mean": 90,  "strength_std": 15},
    "Pier":   {"load_mean": 200, "load_std": 30, "strength_mean": 300, "strength_std": 40}
}

# Store simulation results for each component
component_results = {}

# Simulate each component's load and strength
for name, data in components.items():
    load = np.random.normal(data["load_mean"], data["load_std"], n_simulations)
    strength = np.random.normal(data["strength_mean"], data["strength_std"], n_simulations)
    failures = load > strength  # Component fails if load > strength
    pf = np.sum(failures) / n_simulations  # Probability of failure
    component_results[name] = {
        "load": load,
        "strength": strength,
        "failures": failures,
        "pf": pf,
        "margin": strength - load
    }

# Calculate system-level failure (series system: any one failure causes system failure)
system_failures = np.zeros(n_simulations, dtype=bool)
for comp in component_results.values():
    system_failures |= comp["failures"]  # Logical OR across all failures

system_pf = np.sum(system_failures) / n_simulations

# Display results
print("Component-wise Failure Probabilities:")
for name, res in component_results.items():
    print(f"  {name}: {res['pf']:.4f}")

print(f"\nSystem Failure Probability: {system_pf:.4f}")

# Plot margin of safety for each component
plt.figure(figsize=(12, 6))
for i, (name, res) in enumerate(component_results.items()):
    plt.hist(res["margin"], bins=50, alpha=0.6, label=f"{name} (Pf={res['pf']:.2%})")

plt.title("Margin of Safety Distribution for Bridge Components")
plt.xlabel("Margin of Safety (Strength - Load)")
plt.ylabel("Frequency")
plt.axvline(0, color='red', linestyle='--', label='Failure Threshold')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()