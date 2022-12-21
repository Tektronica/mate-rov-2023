# Stepper Motor

Typical stepper is 200 pulse/rev (1.8 deg) in full step mode and 400 (0.9 deg) in half step mode. Both of these modes are based on the rotor/stator geometry so are very repeatable. These modes use a square wave drive. Micro stepping uses a more sinusoidal drive to essentially interpolate between the motor poles. The pulses per rev will always be some multiple of 200. A typical micro stepper controller will provide up to 3200 steps/rev (16x).
