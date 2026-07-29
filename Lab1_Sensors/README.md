<img src="https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png">

# Lab 1 Notes

Keep a digital log of your work using the readme file where appropriate.

Q1.1
Il= 14/(14+14) = 0.5A
Vl = 0.5*14 = 7 V
Pl = I^2 * R = 0.5^2 * 14 = 3.5W

Q1.2
| Parameter | Theoritcal | Sim |
|----------|------|------|
| Il | 0.5A | 0.5A |
| Vl | 7V | 7V |
| Pl | 3.5W | 3.5W |

Q1.3
Time Step (assuming 1/20th of the period of 500 Hz): 
 (1/20)*(1/500)=0.0001s or 100 microseconds
Stop Time (assuming we’d like to capture 200 cycles):
0.4s

Q1.4
Time constant of circuit with 4mH inductor: 
T = L/R = (4*10^-3)/0.2 = 0.02s
Time constant of circuit with 25.3µF capacitor: 
T = RC = (25.3*10^-6)*790=0.019987s ~= 0.02s
Would simulation reach steady-state: 
steady state = 5T = 0.1s; stop time is 0.4s so yes will reach steady state;

Q 1.5: Calculate the theoretical load current (IL(RMS)): 

Resistor circuit = I = V/R = 14/12.5 = 1.12A
Inductor circuit = I = V/Z = 14/(4*10^(-3) * 500*2*pi) = 1.1140846A
Capacitor circuit = I = 1.11A

load voltage (VL(RMS)):

Resistor circuit = V = 14VRMS
Inductor circuit = V = 14VRMS
Capacitor circuit V = IZ = 1.11*(1/((500*2*pi)*(25.3*10^(-6)))) = 13.9653745V

peak instantaneous power (PL(t)):

Resistive P = 2*Vrms*Irms = (14*1.12)*2 = 31.36W
Inductor P = Vrms*Irms = 14*1.1140846 = 15.5971844W
Capacitor P = Vrms*Irms = 13.9653745V*1.11275212 = 15.5400001W

average power delivered by the source (Pin):

Resistive = Vrms*Irms = 14*1.12=-15.68W
Inductor = 0
Capcitor = 0

| Parameter | Theoritcal(resistor) | Sim(resistor) | Theoritcal(inductor) | Sim(inductor) | Theoritcal(capacitor) | Sim(capacitor) |
|----------|------|------|------|------|------|------|
| IL(RMS) | 1.12A | 1.1131A | 1.1140846A | 1.1251A | 1.11275212A | 1.112A |
| VL(RMS) | 14V | 13.914V | 14V | 13.908V | 13.9653745V | 14.105V |
| PL(t) | 31.36W | 31.158374W | 15.5971844W | 15.015064W | 15.5400001W | 15.207276W |
| (Pin) | -15.68W | -15.48W | 0W | -269.97mW | 0W | -267.27mW |

How can we minimise the granularity and improve the accuracy? What would be 
a drawback of doing so? Simulate the resistive load by setting the timestep to a 
finer value and state your observations.

The accuracy will be improved by lowering the timestep, however this would increase simulation time. I observed that the value got closer to theoretical as the timestep improved.

Q1.7:
Never reaches steady state, this is because there is no damping and energy never gets lost after the transient.

Q2.1:
Max RMS load voltage:
15.4Vrms
Min RMS load voltage:
12.6Vrms
Max RMS load current:
7.5VA/12.6Vrms = 0.595238095A
Minimum RMS load current:
2.5VA/15.4Vrms = 0.162337662A

Q2.2:
Il =  14/Z = 14/sqrt(25^2+(500*2*pi*4*10^-3)^2) = 0.500346767A
W = I^2*R = 0.500346767^2  * 25= 6.25867218W
VAR = I^2*Q = 0.500346767^2  *(500*2*pi*4*10^-3) = 3.14595177
VA = sqrt(S^2 + P^2) = sqrt(3.14595177^2 + 6.25867218^2) = 7.00485474

| Parameter | Theoritcal | Sim |
|----------|------|------|
| Il | 0.500346767A | 496.43mA |
| W | 6.25867218W | 6.1612W |
| VAR | 3.14595177 | 3.21595904W |
| VA | 7.00485474W | 6.95002W |

Q2.3:
Il =  14/Z = 14/sqrt(75^2+(500*2*pi*4*10^-3)^2) = 0.184100378A
W = I^2*R = 0.184100378^2  * 75 = 2.54197119W
VAR = I^2*Q = 0.184100378^2  * (500*2*pi*4*10^-3) = 0.425911361VAR
VA = sqrt(S^2 + P^2) = sqrt(0.425911361^2 + 2.54197119^2) = 2.57740529VA

| Parameter | Theoritcal | Sim |
|----------|------|------|
| Il | 0.184100378A | 182.89mA |
| W |  2.54197119W | 2.5086W |
| VAR | 0.425911361VAR | 0.512719662 |
| VA | 2.57740529VA | 2.56046VA |

Q3