# Project-INF7345
Reproduce the results obtained by the authors of this paper [An Analytical Study on the 802.16m Sleep Mode with M/G/l Queuing Model](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=6336535)


## Execution
```bash
make
./80216mSleepModeMG1
```
Open ProjetAna.m with Matlab


## Todo
- [x] Write the ned file : Network Architecture (Generator, Base Station, Mobile Station)
- [x] Generator.cpp
- [x] BaseStation.cpp 
- [x] MobileStation.cpp
- [x] omnetpp.ini 
- [x] Write Stats : finish() to recolte average delays, power saving factor

- [x] Find a way to get Analitics data



## Plots 
- [ ] Power Saving Factor (Sim)
- [x] Power Saving Factor (Ana)
- [x] Average Packet Transmission delays (Sim)
- [x] Average Packet Transmission delays (Ana)

## Good to know
- Arriaval as Exponatial distribution
- Packect transmision time follow a B Pareto distribution
- Base station buffer size is infinite
- Sleep cycle constant
- Two delay (Buffer delay and transmission delay???)
- Possible sleep cycle (ms) : 20, 40, 80, 160, 320, 640, 1280
- [Bounded Pareto Wikipedia](https://en.wikipedia.org/wiki/Pareto_distribution#Bounded_Pareto_distribution)
