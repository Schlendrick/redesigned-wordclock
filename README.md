# rgb_wordclock_redesigned

Wordclock based on the popular WS2812B RGB LED strips with the ESP32 Controller.

## ToDo

- [x] Order ESP32
- [x] Download newest Arduino IDE and install ESP32 software from GitHub
- [x] Download Atom
- [ ] Make code running on ESP32
- [ ] Replace DCF77 recipient (Onboard Wifi sync)
- [ ] Turn the clock automatic off at night
- [ ] Show the temperature (Onboard Temperatur Sensor)
- [ ] Smartphone app to control the clock
- [ ] Replace WS2812B to newer Version LED (e.g.WS2813) to save energy

## Build

## Known Issues

## LED Mapping

`alt_layout1.h`

```
111                                        110                      .                        .

       99 100 101 102 103 104 105 106 107 108 109                      E S K I S T A F Ü N F
       98  97  96  95  94  93  92  91  90  89  88                      Z E H N Z W A N Z I G
       77  78  79  80  81  82  83  84  85  86  87                      D R E I V I E R T E L
       76  75  74  73  72  71  70  69  68  67  66                      V O R F U N K N A C H
       55  56  57  58  59  60  61  62  63  64  65                      H A L B A E L F Ü N F
       54  53  52  51  50  49  48  47  46  45  44                      E I N S X Ä M Z W E I
       33  34  35  36  37  38  39  40  41  42  43                      D R E I A U J V I E R
       32  31  30  29  28  27  26  25  24  23  22                      S E C H S N L A C H T
       11  12  13  14  15  16  17  18  19  20  21                      S I E B E N Z W Ö L F
       10  9   8   7   6   5   4   3   2    1   0                      Z E H N E U N K U H R

112                                        113                      .                         .
```
