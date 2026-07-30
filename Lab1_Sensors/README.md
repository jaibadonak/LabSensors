<img src="https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png">

# Lab 1 Notes — Voltage and Current Sensors

Keep a digital log of your work using the readme file where appropriate.

---

## Part 1: Revising Basics

### Q1.1 — DC circuit ($V_{dc}$ = 14 V, $R_s$ = 14 Ω, $R_L$ = 14 Ω)

$$I_L = \frac{14}{14 + 14} = 0.5\ \text{A}$$

$$V_L = 0.5 \times 14 = 7\ \text{V}$$

$$P_L = I^2 R = 0.5^2 \times 14 = 3.5\ \text{W}$$

### Q1.2 — Simulation vs theory

| Parameter | Theoretical | Simulated |
|---|---|---|
| $I_L$ | 0.5 A | 0.5 A |
| $V_L$ | 7 V | 7 V |
| $P_L$ | 3.5 W | 3.5 W |

### Q1.3 — Timestep and stop time

**Time step** (1/20th of the period of 500 Hz):

$$\tfrac{1}{20} \times \tfrac{1}{500} = 100\ \mu\text{s}$$

**Stop time** (200 cycles):

$$200 \times \tfrac{1}{500} = 0.4\ \text{s}$$

### Q1.4 — Time constants

**Circuit with 4 mH inductor** (0.2 Ω series):

$$\tau = \frac{L}{R} = \frac{4 \times 10^{-3}}{0.2} = 0.02\ \text{s}$$

**Circuit with 25.3 µF capacitor** (790 Ω parallel):

$$\tau = RC = 790 \times 25.3 \times 10^{-6} = 0.019987\ \text{s} \approx 0.02\ \text{s}$$

**Would simulation reach steady-state:** yes — $5\tau = 0.1\ \text{s}$, and stop time is 0.4 s.

### Q1.5 — Theoretical calculations

$X_L = 2\pi(500)(4\text{m}) = 12.566\ \Omega$  
$X_C = \dfrac{1}{2\pi(500)(25.3\mu)} = 12.5815\ \Omega$

**Load current $I_{L(RMS)}$**

| Circuit | Working | Result |
|---|---|---|
| Resistive | $I = V/R = 14/12.5$ | 1.12 A |
| Inductive | $I = V/X_L = 14/12.566$ | 1.1140846 A |
| Capacitive | source current | 1.11 A |

**Load voltage $V_{L(RMS)}$**

| Circuit | Working | Result |
|---|---|---|
| Resistive | source voltage | 14 V |
| Inductive | source voltage | 14 V |
| Capacitive | $V = IX_C = 1.11 \times 12.5815$ | 13.9654 V |

**Peak instantaneous power $P_{L(t)}$**

| Circuit | Working | Result |
|---|---|---|
| Resistive | $2 V_{rms} I_{rms} = 2(14)(1.12)$ | 31.36 W |
| Inductive | $V_{rms} I_{rms} = 14 \times 1.1140846$ | 15.5972 W |
| Capacitive | $V_{rms} I_{rms} = 13.9654 \times 1.11$ | 15.5016 W |

**Average power delivered by source $P_{in}$**

| Circuit | Working | Result |
|---|---|---|
| Resistive | $V_{rms} I_{rms} = 14 \times 1.12$ | 15.68 W |
| Inductive | purely reactive | 0 W |
| Capacitive | purely reactive | 0 W |

**Results table** (LTspice reports source power as negative by convention)

| Parameter | Theo (R) | Sim (R) | Theo (L) | Sim (L) | Theo (C) | Sim (C) |
|---|---|---|---|---|---|---|
| $I_{L(RMS)}$ | 1.12 A | 1.1131 A | 1.1140846 A | 1.1251 A | 1.11 A | 1.112 A |
| $V_{L(RMS)}$ | 14 V | 13.914 V | 14 V | 13.908 V | 13.9654 V | 14.105 V |
| Peak $P_{L(t)}$ | 31.36 W | 31.158374 W | 15.5972 W | 15.015064 W | 15.5016 W | 15.207276 W |
| $P_{in}$ | −15.68 W | −15.48 W | 0 W | −269.97 mW | 0 W | −267.27 mW |

### Q1.6 — Minimising granularity

The accuracy will be improved by lowering the timestep, however this would increase simulation time. I observed that the value got closer to theoretical as the timestep improved.

### Q1.7 — Removing the damping resistors

Never reaches steady state, this is because there is no damping and energy never gets lost after the transient.

---

## Part 2: Modelling Your AC Load

### Q2.1 — Measurement ranges

| Quantity | Working | Result |
|---|---|---|
| Max RMS load voltage | design spec | 15.4 V |
| Min RMS load voltage | design spec | 12.6 V |
| Max RMS load current | $7.5\ \text{VA} / 12.6\ \text{V}$ | 0.595238095 A |
| Min RMS load current | $2.5\ \text{VA} / 15.4\ \text{V}$ | 0.162337662 A |

### Q2.2 — $R_L$ = 25 Ω, L = 4 mH, $V_{ac}$ = 14 $V_{rms}$

$$I_L = \frac{14}{\sqrt{25^2 + 12.566^2}} = 0.500346767\ \text{A}$$

$$P = I^2 R = 0.500346767^2 \times 25 = 6.25867218\ \text{W}$$

$$Q = I^2 X_L = 0.500346767^2 \times 12.566 = 3.14595177\ \text{VAR}$$

$$S = \sqrt{P^2 + Q^2} = \sqrt{6.25867218^2 + 3.14595177^2} = 7.00485474\ \text{VA}$$

| Parameter | Theoretical | Simulated |
|---|---|---|
| Load current $I_{L(rms)}$ | 0.500346767 A | 496.43 mA |
| Real power (W) | 6.25867218 W | 6.1612 W |
| Reactive power (VAR) | 3.14595177 VAR | 3.21595904 VAR |
| Apparent power (VA) | 7.00485474 VA | 6.95002 VA |

### Q2.3 — $R_L$ = 75 Ω, L = 4 mH, $V_{ac}$ = 14 $V_{rms}$

$$I_L = \frac{14}{\sqrt{75^2 + 12.566^2}} = 0.184100378\ \text{A}$$

$$P = I^2 R = 0.184100378^2 \times 75 = 2.54197119\ \text{W}$$

$$Q = I^2 X_L = 0.184100378^2 \times 12.566 = 0.425911361\ \text{VAR}$$

$$S = \sqrt{P^2 + Q^2} = \sqrt{2.54197119^2 + 0.425911361^2} = 2.57740529\ \text{VA}$$

| Parameter | Theoretical | Simulated |
|---|---|---|
| Load current $I_{L(rms)}$ | 0.184100378 A | 182.89 mA |
| Real power (W) | 2.54197119 W | 2.5086 W |
| Reactive power (VAR) | 0.425911361 VAR | 0.512719662 VAR |
| Apparent power (VA) | 2.57740529 VA | 2.56046 VA |

---

## Part 3: Sensing AC Load Current

### Q3.1 — Shunt resistor value

$$R_s \le \frac{P_{max}}{I_{max}^2} = \frac{0.2}{0.595238095^2} = 0.564931855\ \Omega$$

**Shunt resistor ($R_s$): 0.5 Ω**

### Q3.2 — Determining test load resistances

**Case 1 — 7.5 VA at 12.6 V**

$$I_L = 7.5/12.6 = 0.595238095\ \text{A}$$
$$Z = 12.6/0.595238095 = 21.168\ \Omega$$
$$R_L = \sqrt{Z^2 - X_L^2} - R_s = \sqrt{21.168^2 - 12.566^2} - 0.5 = 16.5343933\ \Omega$$

**Case 2 — 7.5 VA at 15.4 V**

$$I_L = 7.5/15.4 = 0.487012987\ \text{A}$$
$$Z = 15.4/0.487012987 = 31.6213333\ \Omega$$
$$R_L = \sqrt{31.6213333^2 - 12.566^2} - 0.5 = 28.5171509\ \Omega$$

**Case 3 — 2.5 VA at 15.4 V**

$$I_L = 2.5/15.4 = 0.162337662\ \text{A}$$
$$Z = 15.4/0.162337662 = 94.864\ \Omega$$
$$R_L = \sqrt{94.864^2 - 12.566^2} - 0.5 = 93.5283\ \Omega$$

**Sensed voltage and dissipation**

$$V_{is(pk)} = R_s I_{L(rms)} \sqrt{2} \qquad P_{is} = I_{L(rms)}^2 R_s$$

| Source VA | $V_{ac(rms)}$ | $R_L$ | $I_{L(rms)}$ | $V_{is(pk)}$ Theo | $V_{is(pk)}$ Sim | $P_{is}$ Theo | $P_{is}$ Sim |
|---|---|---|---|---|---|---|---|
| 7.5 VA | 12.6 V | 16.5 Ω | 0.595 A | 0.421 V | 0.420 V | 0.1770125 W | 0.16245 W |
| 7.5 VA | 15.4 V | 28.5 Ω | 0.487 A | 0.344 V | 0.346 V | 0.1185845 W | 0.1169 W |
| 2.5 VA | 15.4 V | 93.5 Ω | 0.162 A | 0.115 V | 0.112 V | 0.013122 W | 0.013013 W |

**Comments:** $P_{is}$ is kept below 200 mW under all conditions, with the worst case being 177 mW at maximum VA and minimum supply voltage.

### Q3.3 — Bigger vs smaller shunt

| Parameter | Bigger $R_s$ | Smaller $R_s$ |
|---|---|---|
| SNR | High | Low |
| Dissipation ($P_{is}$) | High | Low |
| Size | High | Low |
| Cost | High | Low |

**Shunt resistor ($R_s$) to be used in design: 0.5 Ω** (two 1 Ω metal film resistors in parallel)

**Justification:** 0.5 Ω is the largest practical value staying within the 200 mW budget, therefore maximising SNR. Two 1 Ω resistors in parallel halve the dissipation per part to ~89 mW, keeping each well inside a 1/4 W rating.

---

## Part 4: Sensing AC Source Voltage

### Q4.1 — Voltage divider resistors

Maximum load voltage:

$$V_{pk} = 15.4 \sqrt{2} = 21.7789\ \text{V}_{pk} \quad (43.56\ \text{V}_{pk\text{-}pk})$$

Target output is 2 $V_{pk\text{-}pk}$, i.e. 1 $V_{pk}$:

$$\frac{R_b}{R_a + R_b} = \frac{1}{21.7789} $$

$$\frac{R_a}{R_b} = 21.7789 - 1 = 20.7789$$

**$R_a / R_b$ ratio: 20.78**

**Voltage divider resistors: $R_a$ = 100 kΩ, $R_b$ = 4.7 kΩ** (E24 values, actual ratio 21.28)

Check:

$$V_{vs(pk)} = 21.7789 \times \frac{4700}{104700} = 0.9776\ \text{V}_{pk} = 1.955\ \text{V}_{pk\text{-}pk}$$

### Q4.2 — Verification

$$V_{vs(pk)} = V_{ac(rms)} \sqrt{2} \times \frac{R_b}{R_a + R_b} \qquad P_{vs} = \frac{V_{ac(rms)}^2}{R_a + R_b}$$

| Source VA | $V_{ac(rms)}$ | $R_L$ | $I_{L(rms)}$ | $V_{vs(pk)}$ Theo | $V_{vs(pk)}$ Sim | $P_{vs}$ Theo | $P_{vs}$ Sim |
|---|---|---|---|---|---|---|---|
| 7.5 VA | 12.6 V | 16.5 Ω | 0.595 A | 0.7998 V | 0.8 | 1.5163 mW | 1.491mW |
| 7.5 VA | 15.4 V | 28.5 Ω | 0.487 A | 0.9776 V | 0.973 | 2.2652 mW | 2.2286mW |
| 2.5 VA | 15.4 V | 93.5 Ω | 0.162 A | 0.9776 V | 0.973 | 2.2652 mW | 2.2222mW |

**Comments:** The 2 $V_{pk\text{-}pk}$ target is met at maximum input voltage (1.955 $V_{pk\text{-}pk}$, 2% under target so the ADC input cannot be overdriven). At minimum input the output falls to 1.600 $V_{pk\text{-}pk}$, so the signal conditioning stage must handle a 1.6–2.0 V input swing. $P_{vs}$ peaks at 2.27 mW, which is negligible.

### Q4.3 — Ohms vs kilo-ohms vs mega-ohms

| Parameter | Ohms | Kilo-Ohms | Mega-Ohms |
|---|---|---|---|
| SNR | High | Medium | Low |
| Dissipation ($P_{vs}$) | High | Low | Low |
| Sensitivity | Low | Medium | High |

**Voltage divider resistors to be used in design: $R_a$ = 100 kΩ, $R_b$ = 4.7 kΩ**

**Justification:** The kilo-ohm range is the compromise between dissipation and noise immunity. In the ohms range the divider would dissipate more watts and load the source significantly; in the mega-ohms range the high source impedance makes the node susceptible to noise pickup, humidity and user touch, and interacts with op-amp input bias current and the ADC sample-and-hold capacitor. At 104.7 kΩ total the divider draws 147 µA at max voltage(15.4V), 0.09% of the 162 mA minimum load current, so it does not perturb the measurement very much, while $R_b$ = 4.7 kΩ remains a low enough source impedance for the following signal conditioning stage.
