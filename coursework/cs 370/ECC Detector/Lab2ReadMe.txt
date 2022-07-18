# Lab Assignment 2 CS 370 Professor Xie 
Group: Devon Hood, Ruben Rubalcaba 

## Usage

```Logic Works 
Hamming Code circuit implementation, in this lab uses 8 data bits chosen by the user. Then creates 4 parity bits created from the XOR of each data bit it is assigned to. It also has a fifth parity bit that is built off the XOR of all the parity bits which will balance the number of binary 1's to be an even amount of 1's. After creation, bits are pushed through the transmission bus in which the user can test flipping a bit. The Detector and corrector part within the main memory, accumulates 5 check bits, 4 of those check bits are the XOR of the assigned parity and data bits, with that last check bit being the accumulation of the preceeding 4 check bits. The detector check bits if no errors will all equal zero which means no errors. If a bit is flipped then the corrector, will take the bit location whjich is the c1,c2,c4,c8 and input into the inner decoder to flip that bit back. However if there is more than one error, it may not be corrected and the ending Hex display will display an E.
```

