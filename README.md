# FinMathLib
Implemented with core OOP principles with unit testing and optimised with multiprocessing, FinMathLib is a C++ financial mathematics library that provides features in derivatives pricing, portfolio management, delta hedging simulations and various financial mathematics methods. 



## Features Summary

The derivatives pricing supports individual product pricing as well as multi-product (portfolio) pricing. The engine mainly uses Monte Carlo simulation with multiprocessing while leveraging a multi-dimensional Brownian motion stock models. GPU-accelerated Monte Carlo simulation is also supported and variance reduction methods such as control variate and anti-variate can be used. Other pricing methods include Simpson’s rule integration, Black-Scholes formulas and binomial trees.

Supported products:

- [x] American options
- [x] Arithemetic options
- [x] Asian options
- [x] Barrier options
- [x] Basket options
- [x] Digital options
- [x] European options
- [x] Geometric options
- [x] Margrabe options



Portfolio management features utilise pointers to maintain its sophisticated data structures that can support mixtures of stocks, bonds and derivatives products. As mentioned above, portfolio pricing with Monte Carlo method is supported.


Delta hedging simulator provides simulations results in view of transaction costs, inconstant interest rates, inconstant volatilities and hedging frequencies.



Additional features include financial mathematics methods such as multivariate integral and derivative computation, vectorisation supported C-style matrix data structure, statistical distributions methods and plotting features in HTML which are all developed from scratch.



## Compiling instructions

To compile the code, you can simply run:

```bash
make clean all
```







