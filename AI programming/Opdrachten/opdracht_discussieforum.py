import numpy as np
import matplotlib.pyplot as plt

# --- Vaste parameters van de paden ---
# Pad 1: De "beste" bestemming (kortste afstand)
tau_1_fixed = 10.0  # Feromonen op Pad 1
dist_1 = 2.0        # Afstand van Pad 1 (Heuristiek)
eta_1_fixed = 1.0 / dist_1 # Aantrekkelijkheid (inverse afstand) van Pad 1

# Pad 2: Een "slechte" bestemming (langere afstand)
tau_2_fixed = 5.0   # Feromonen op Pad 2
dist_2 = 5.0        # Afstand van Pad 2 (Heuristiek)
eta_2_fixed = 1.0 / dist_2 # Aantrekkelijkheid (inverse afstand) van Pad 2

# --- Exponenten (vaste waarden voor dit experiment) ---
alpha = 1.0 # Feromoon exponent
beta = 2.0  # Heuristiek exponent

def calculate_probability(tau_x, eta_x, tau_n, eta_n, alpha, beta):
    """Berekent de waarschijnlijkheid om pad x te kiezen ten opzichte van alle paden n."""
    numerator = (tau_x**alpha) * (eta_x**beta)
    denominator = numerator + (tau_n**alpha) * (eta_n**beta)
    return numerator / denominator

# ====================================================================
# OPDRACHT 1: Wijzig de Feromoonintensiteit (tau)
# ====================================================================

tau_range = np.linspace(1, 50, 50) # Bereik van feromonen (ondergrens=1, bovengrens=50)

# De feromoonwaarde van Pad 1 (het beste pad) varieert.
# De feromoonwaarde van Pad 2 blijft op zijn vaste waarde (tau_2_fixed).

prob_tau = []
for tau in tau_range:
    # Bereken P(Pad 1 | Pad 1 varieert, Pad 2 is fixed)
    P_1 = calculate_probability(tau, eta_1_fixed, tau_2_fixed, eta_2_fixed, alpha, beta)
    prob_tau.append(P_1)

# Visualisatie
plt.figure(figsize=(10, 6))
plt.plot(tau_range, prob_tau, label=f'P(Pad 1) met constante Heuristiek (d1={dist_1}, d2={dist_2})', color='darkblue')
plt.title(f'Waarschijnlijkheid van het kiezen van het Beste Pad (d={dist_1}) bij variërende Feromonen\n(Alpha={alpha}, Beta={beta})')
plt.xlabel('Feromoonintensiteit op Pad 1 (τ_1)')
plt.ylabel('Waarschijnlijkheid P(Pad 1)')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.show()

print(f"--- Resultaten Feromoonvariatie (Alpha={alpha}, Beta={beta}) ---")
print(f"Laagste τ_1 (1.0): P(Pad 1) = {prob_tau[0]:.4f}")
print(f"Hoogste τ_1 (50.0): P(Pad 1) = {prob_tau[-1]:.4f}")
print("===============================================================\n")

# ====================================================================
# OPDRACHT 2: Wijzig de Heuristiek (Afstand)
# ====================================================================

# We variëren de afstand van Pad 1 van de beste (1.0) tot een slechte waarde (10.0)
dist_range = np.linspace(1.0, 10.0, 50) # Variatiebereik van de Afstand (Heuristiek) op Pad 1
eta_range = 1.0 / dist_range # Aantrekkelijkheid (eta) is de inverse van de afstand

# De heuristiek (afstand) van Pad 1 varieert.
# De feromoonwaarde op Pad 1 blijft op zijn vaste waarde (tau_1_fixed).

prob_eta = []
for eta in eta_range:
    # Bereken P(Pad 1 | Pad 1 varieert, Pad 2 is fixed)
    P_1 = calculate_probability(tau_1_fixed, eta, tau_2_fixed, eta_2_fixed, alpha, beta)
    prob_eta.append(P_1)

# Visualisatie
plt.figure(figsize=(10, 6))
plt.plot(dist_range, prob_eta, label=f'P(Pad 1) met constante Feromonen (τ1={tau_1_fixed}, τ2={tau_2_fixed})', color='darkred')
plt.title(f'Waarschijnlijkheid van het kiezen van Pad 1 bij variërende Afstand (Heuristiek)\n(Alpha={alpha}, Beta={beta})')
plt.xlabel('Afstand van Pad 1 (Heuristiek d_1)')
plt.ylabel('Waarschijnlijkheid P(Pad 1)')
plt.gca().invert_xaxis() # Kortste afstand (beste oplossing) staat links
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.show()

print(f"--- Resultaten Heuristiekvariatie (Alpha={alpha}, Beta={beta}) ---")
print(f"Kortste d_1 (1.0): P(Pad 1) = {prob_eta[0]:.4f}")
print(f"Langste d_1 (10.0): P(Pad 1) = {prob_eta[-1]:.4f}")
print("===============================================================\n")

# ====================================================================
# OPDRACHT 3: Simultaane Wijziging (Feromoon en Heuristiek)
# ====================================================================

# We laten nu zowel de feromonen als de afstand van Pad 1 variëren.
# We gebruiken hetzelfde bereik voor de feromonen als in Opdracht 1.
# We gebruiken het bereik voor de afstand (d) van Opdracht 2, maar converteren naar eta.

tau_simultaan = np.linspace(1, 50, 50)  # Bereik van feromonen (1.0 t/m 50.0)
dist_simultaan = np.linspace(10.0, 1.0, 50) # Bereik van afstanden (10.0 t/m 1.0)
eta_simultaan = 1.0 / dist_simultaan

prob_simultaan = []
for tau, eta in zip(tau_simultaan, eta_simultaan):
    # Bereken P(Pad 1 | Pad 1 varieert, Pad 2 is fixed)
    P_1 = calculate_probability(tau, eta, tau_2_fixed, eta_2_fixed, alpha, beta)
    prob_simultaan.append(P_1)

# Visualisatie
fig, ax1 = plt.subplots(figsize=(10, 6))

ax1.plot(tau_simultaan, prob_simultaan, color='darkgreen', label='P(Pad 1) met simultane variatie')
ax1.set_xlabel('Feromoonintensiteit op Pad 1 (τ_1) en Inverse Afstand')
ax1.set_ylabel('Waarschijnlijkheid P(Pad 1)', color='darkgreen')
ax1.tick_params(axis='y', labelcolor='darkgreen')

# Maak een tweede Y-as om de corresponderende afstand weer te geven
ax2 = ax1.twiny()
ax2.plot(tau_simultaan, dist_simultaan, linestyle='None') # Plot is niet nodig, alleen de as
ax2.set_xlabel('Afstand van Pad 1 (d_1)', color='gray')
ax2.tick_params(axis='x', labelcolor='gray')

plt.title(f'Waarschijnlijkheid van het kiezen van Pad 1 bij simultane variatie van Feromonen en Afstand\n(Alpha={alpha}, Beta={beta})')
ax1.grid(True, linestyle='--', alpha=0.7)
plt.show()

print(f"--- Resultaten Simultane Variatie (Alpha={alpha}, Beta={beta}) ---")
print(f"Lage τ_1 (1.0) en Lage d_1 (10.0): P(Pad 1) = {prob_simultaan[0]:.4f}")
print(f"Hoge τ_1 (50.0) en Hoge d_1 (1.0): P(Pad 1) = {prob_simultaan[-1]:.4f}")
print("===============================================================\n")