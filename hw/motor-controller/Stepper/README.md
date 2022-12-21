# MP6500

1/8 microstepping isn't particularly good for smooth operation, the DRV8825 drivers can both go up to 1/32
microstepping and handle 1.7A (the MP6500 is 1.5A max).

You just have to hardwire the MS pins for the microstepping you want, most likely 1/8th for the MP6500
driver as anything less will be very noisy. I'd normally suggest 1/16th as a good starting point for experimenting
with micro-stepping.

Select 1.5A (2.0A is pointless as its beyond the rating of the chip). Z is a misprint for "high-Z" meaning
high impedance, i.e. don't connect the pin for this setting.

Your supply is overkill, NEMA17 motors take around 5 to 6W. You'll probably only see 0.3A drain from
24V