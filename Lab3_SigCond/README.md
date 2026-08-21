<img src="https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png">

# Lab 3 Notes

Keep a digital log of your work using the readme file where appropriate.
Q1.1
<img width="1512" height="2016" alt="IMG_0923" src="https://github.com/user-attachments/assets/75b3db85-0eda-47ed-bc53-6a711891d896" />

Q1.1 Simulated
<img width="1896" height="402" alt="image" src="https://github.com/user-attachments/assets/636e680f-1dfb-4856-9918-e03b1edda3a7" />
Q1.2:
It clips due to the limits(rails) of the opamp being 0-5V, which limits the range of the voltage output to them(or a bit below in real life).

Q1.3:
<img width="1896" height="402" alt="image" src="https://github.com/user-attachments/assets/acf312ef-9f2d-48e3-bae2-0c9a3eeefd51" />
VOH datasheet = 3.5V;
Simulated is roughly 3.5V as well.

Q1.4:
Minimum VOL from plot = ~0.7V

Q1.5:
V+ = (2.1 + 10Vs)/11

Vo = V+*(1/11)
(2.1 + 10Vs) = Vo

<img width="3024" height="4032" alt="IMG_0925"  src="https://github.com/user-attachments/assets/dda0658c-07ab-458b-b131-2a3431de6335" />


Q1.5 Simulated:
<img width="1896" height="402" alt="image" src="https://github.com/user-attachments/assets/f4699bc2-7f9a-4995-9f09-40fc1eb3670a" />

Q2.1
Rs = 0.5Ohm
Il(max) = 0.595238095A
VisRMS(max) = 0.595238095A*0.5 = 0.297619048V
Vis(pk) = 0.42090V  
G = 1V/0.42090V = 2.376
R2/R1 = 2.376 
R1 = 10kOhm
R2 = 2.376*10K = 23.76k
R2 = 24kOhm


Q2.2:
| Source VA | (V_{ac(rms)}) |       (R_L) | (I_{L(rms)}) | (V_{is(pk)}) Theo | (V_{is(pk)}) Sim | (V_{io(pk)}) Theo | (V_{io(pk)}) Sim |
| --------- | ------------: | ----------: | -----------: | ----------------: | ----------------: | ----------------:  | ----------------: |
| 7.5 VA    |        12.6 V | **17.03 Ω** | **0.5952 A** |      **0.4209 V** |        ** V** |        **3.10 V** |        ** V** |
| 7.5 VA    |        15.4 V | **29.02 Ω** | **0.4870 A** |      **0.3444 V** |       ** V** |        **3.10 V** |        ** V** |
| 2.5 VA    |        15.4 V | **94.03 Ω** | **0.1623 A** |      **0.1148 V** |       ** V** |       **2.373 V** |       ** V** |
No clipping is expected. The maximum theoretical output is approximately 3.1 V and the minimum is approximately 1.1 V, both within the usable output range of the LM324 with a 5 V supply.

Q2.3:  
If the corresponding resistor pairs are not equal, the resistor ratios will no longer match. This reduces the differential amplifier's common-mode rejection.

As a result, voltages that should cancel can appear at the output, causing gain and offset errors in Vio. Therefore, resistor tolerance directly affects the accuracy of the current measurement.
Q2.4:
To improve accuracy at light loads, you could use a higher amplifier gain so the small shunt voltage produces a larger output signal. A switchable/variable gain could be used, with high gain for low currents and lower gain for high currents to prevent clipping.
