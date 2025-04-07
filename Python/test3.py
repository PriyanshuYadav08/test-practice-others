import numpy as np
import matplotlib.pyplot as plt

# Set seed for reproducibility
np.random.seed(42)

# Number of simulations
n_simulations = 10000

# Define bridge components with mean and std dev for load and strength
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

# Store failure results
component_results = {}

# Run simulation for each component
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

# Calculate system-level failure (series system: any component fails)
system_failures = np.zeros(n_simulations, dtype=bool)
for comp in component_results.values():
    system_failures |= (comp["load"] > comp["strength"])
system_pf = np.sum(system_failures) / n_simulations

# Prepare output summary
output_summary = {
    "Component Failure Probabilities": {name: round(res["pf"], 4) for name, res in component_results.items()},
    "System Failure Probability": round(system_pf, 4)
}

output_summary