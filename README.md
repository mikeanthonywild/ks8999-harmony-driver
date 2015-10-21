# KS8999 PHY driver for MPLAB Harmony
PHY driver and MPLAB Harmony MAC/PHY modifications needed to get Micrel KS8999 ethernet switch working with PIC32MX. Due to a hard-coded dependancy on the MIIM (MII Management) interface, MPLab Harmony does not support Micrel's KS8999 ethernet switch because it lacks MIIM. This repository contains a working PHY driver and a set of patched PHY/MAC library files to remove the dependancy on MIIM.

## Method

The fix is actually very simple: in cases where Harmony issues an MIIM call, we override the return register with a spoofed value to ensure the MAC/PHY setup continues successfully. Given that the KS8999 can be completely configured using external PU/PD resistors, no further setup is needed.
