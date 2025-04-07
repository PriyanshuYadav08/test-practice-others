import numpy as np
import matplotlib.pyplot as plt

n_simulations = 10000

components = {
    "Girder": {
        "load_mean": 100, "load_std": 15,
        "strength_mean": 150, "strength_std": 25
    },
    "Bolt": {
        "load_mean": 50, "load_std": 10,
        "strength_mean": 100, "strength_std": 15
    },
    "Pier": {
        "load_mean": 200, "load_std": 30,
        "strength_mean": 300, "strength_std": 40
    }
}

component_results = {}

for name, data in components.items():
    load = np.random.normal(data["load_mean"], data["load_std"], n_simulations)
    strength = np.random.normal(data["strength_mean"], data["strength_std"], n_simulations)
    
    failures = load > strength
    pf = np.sum(failures) / n_simulations
    
    component_results[name] = {
        "pf": pf,
        "load": load,
        "strength": strength,
        "margin": strength - load
    }

system_failures = np.zeros(n_simulations, dtype=bool)

for comp in component_results.values():
    system_failures |= (comp["load"] > comp["strength"])
    
system_pf = np.sum(system_failures) / n_simulations

print("Component Failure Probabilities = ")
for name, res in component_results.items():
    print(f"  {name}: {res['pf']:.4f}")
print(f"\nSystem Failure Probability (Series System) = {system_pf:.4f}")

for name, res in component_results.items():
    plt.figure()
    plt.hist(res["margin"], bins=50, color='skyblue', edgecolor='black')
    plt.title(f"{name} - Margin of Safety")
    plt.xlabel("Strength - Load")
    plt.ylabel("Frequency")
    plt.axvline(0, color='red', linestyle='--', label='Failure Threshold')
    plt.legend()
    plt.grid(True)
    plt.show()