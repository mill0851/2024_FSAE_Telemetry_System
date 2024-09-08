# 2024_FSAE_Telemetry_System
This repository holds the code for an FSAE telemetry system
# Damper Travel
This directory holds the code necessary to collect data from a set of 4 linear potentiometers connected to the spring dampeners. It uses an onboard arduino uno to collect data, which is then emitted through an HC 12 radio module. On the other end is an arduino Mkrzero which has the same module and recieves the data. That data is then written to an SD card. This is currently a work in progress so expect it to change often. 
