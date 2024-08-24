# PGM-index_with_NDN

Using PGM-index to predict NDN

## How to use

On WSL2-ub22.04


```bash
cd examples

g++ t.cpp -std=c++17 -I../include -O3 -o t -DDEBUG

python3 t.py
```

## License

modified from:

https://github.com/gvinciguerra/PGM-index/tree/master

This project is licensed under the terms of the Apache License 2.0.

If you use the library please put a link to the [website](https://pgm.di.unipi.it) and cite the following paper:

> Paolo Ferragina and Giorgio Vinciguerra. The PGM-index: a fully-dynamic compressed learned index with provable worst-case bounds. PVLDB, 13(8): 1162-1175, 2020.

```tex
@article{Ferragina:2020pgm,
  Author = {Paolo Ferragina and Giorgio Vinciguerra},
  Title = {The {PGM-index}: a fully-dynamic compressed learned index with provable worst-case bounds},
  Year = {2020},
  Volume = {13},
  Number = {8},
  Pages = {1162--1175},
  Doi = {10.14778/3389133.3389135},
  Url = {https://pgm.di.unipi.it},
  Issn = {2150-8097},
  Journal = {{PVLDB}}}
```