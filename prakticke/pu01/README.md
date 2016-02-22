Cvičenie 1
==========

Vašou hlavnou úlohou na tomto cvičení je:
* vytvoriť si konto na https://github.com/ (ak ešte nemáte)
* vyplniť [registračný formulár](http://dai.fmph.uniba.sk/courses/lpi/register/),
  aby sme mohli spárovať vaše GitHub konto a vytvoriť vám repozitáre
* po vyriešení týchto cvík si **odložiť riešenie 2. príkladu**;
  na budúcich cvičeniach si ukážeme, ako sa odovzdá v github-e.

SAT solver
----------
SAT solverov je veľa, budeme používať [MiniSAT](http://minisat.se/).
Binárka pre Windows sa dá stiahnuť priamo na ich stránke, ale potrebuje ešte
2 knižnice (cygwin1.dll, cygz.dll). Všetky tri súbory sa nachádzajú v adresári
s [nástrojmi](../tools/).
[Návod na inštaláciu v macOS…](../../docs/macos-minisat.md)

Všetky potrebné súbory k tomuto cvičeniu si môžete stiahnuť pohromade
ako jeden zip súbor
[pu01.zip](https://github.com/FMFI-UK-1-AIN-412/lpi/archive/pu01.zip).

## 1. príklad

Chceme na párty pozvať aspoň niekoho z trojice Jim, Kim a Sára, bohužiaľ každý
z nich má nejaké svoje podmienky.

* Sára nepôjde na párty, ak pôjde Kim.
* Jim pôjde na párty, len ak pôjde Kim.
* Sára nepôjde bez Jima.

Zapísané vo výrokovej logike (premenná `kim` znamená, že Kim pôjde na párty,
atď.):
```
kim → ¬sarah
jim → kim
sarah → jim
kim ∨ jim ∨ sarah
```

Prerobené do CNF (konjunktívnej normálnej formy):
```
¬kim ∨ ¬sarah
¬jim ∨ kim
¬sarah ∨ jim
kim ∨ jim ∨ sarah
```

### DIMACS CNF formát ###
```
p cnf VARS CLAUSES
1 2 -3 0
...
```
```
p cnf 3 4
c -kim v -sarah
-1 -3 0
c -jim v kim
-2 1 0
c -sarah v jim
-3 2 0
c kim v jim v sarah
1 2 3 0
```

Aby bola práca s DIMACS CNF súbormi vo Windows jednoduchšia, budeme im dávať
príponu `.txt`, t.j. budeme sa tváriť, ako by to boli obyčajné textové súbory.

### SAT solver ###

Spustíme SAT solver, ako parameter dáme meno vstupného súboru. MiniSAT
normálne iba vypíše, či je vstup splniteľný. Ak chceme aj nejaký výstup, tak
dáme ešte meno výstupného súboru (MiniSAT ho vytvorí/prepíše.)
```
$ minisat party.txt party.out
...
SATISFIABLE
$ cat party.out
SAT
1 -2 -3 0
```

#### Hľadanie riešení ####

MiniSAT nájde len nejaké riešenie. Ak chceme nájsť ďalšie, môžeme mu povedať,
že toto konkrétne nechceme (nemajú naraz platiť tieto premenné). Toto riešenie
je `kim ∧ ¬jim ∧ ¬sarah`, znegovaním dostaneme `¬kim ∨ jim ∨ sarah`, čo je
priamo disjunktívna klauza a môžeme ju pridať k zadaniu:

```
p cnf 3 5
-1 -3 0
-2 1 0
-3 2 0
1 2 3 0
c nechceme riesenie 1 -2 -3
-1 2 3 0
```
```
$ minisat party.txt party.out
...
SATISFIABLE
$ cat party.out
SAT
1 2 -3 0
```

Ak to zopakujeme ešte raz, nenájdeme už žiadne riešenie:
```
p cnf 3 6
-1 -3 0
-2 1 0
-3 2 0
1 2 3 0
c nechceme riesenie 1 -2 -3
-1 2 3 0
c nechceme riesenie 1 2 -3
-1 -2 3 0
```
```
$ minisat party.txt party.out
...
UNSATISFIABLE
$ cat party.out
UNSAT
```

#### Dokazovanie ####

Vidíme, že v obidvoch riešeniach sme mohli pozvať Kim. Mali by sme teda byť
schopní **dokázať**, že **logickým dôsledkom** našich predpokladov (vstupné
štyri tvrdenia) je, že Kim pôjde na párty (hovoríme aj, že toto tvrdenie
**vyplýva** z predpokladov). So SAT solverom to môžeme spraviť tak, že
sa ho spýtame, či existuje možnosť, že naše predpoklady platia, ale Kim na
párty nepôjde (t.j. negácia tvrdenia, ktoré chceme dokázať). Ak SAT solver
riešenie nájde, tak nám našiel „protipríklad“: predpoklady platia, ale naše
tvrdenie nie. Ak SAT solver riešenie nenájde, tak to znamená, že vždy, keď
platili predpoklady, tak platilo aj naše tvrdenie.

```
p cnf 3 4
c nasa "teoria"
-1 -3 0
-2 1 0
-3 2 0
1 2 3 0

c chceme dokazat cielove tvrdenie "kim"
c zapiseme jeho negaciu "¬kim"
-1 0
```
```
$ minisat party.txt party.out
...
UNSATISFIABLE
$ cat party.out
UNSAT
```

*Poznámka:* Je dobré vždy najskôr napísať len „teóriu“ a overiť si, či je
**splniteľná** („bezosporná“), t.j. či má riešenie, a až potom pridať
negáciu dokazovaného tvrdenia.

*Otázka:* Je problém, že keď máme nesplniteľnú („spornú“) teóriu, tak SAT
solver vlastne povie, že z nej vyplýva čokoľvek?

## 2. Russian spy puzzle (2b)

(Andrei Voronkov, http://www.voronkov.com/lics.cgi)

> Máme tri osoby, ktoré sa volajú Stirlitz, Müller a Eismann.
> Vie sa, že práve jeden z nich je Rus,
> kým ostatní dvaja sú Nemci.
> Navyše každý Rus musí byť špión.
> 
> Keď Stirlitz stretne Müllera na chodbe, zavtipkuje:
> „Vieš, Müller, ty si taký Nemec, ako som ja Rus.“
> Je všeobecne známe, že Stirlitz vždy hovorí pravdu, keď vtipkuje.
> 
> Máme rozhodnúť, či Eismann nie je ruský špión.

*Na riešenie / testovanie tejto úlohy môžete použiť aj
[online editor / testovač](https://dai.fmph.uniba.sk/courses/lpi/russianSpy/).*

Prvá úloha pri zápise nejakého problému v logike je vždy vymyslieť,
ako budeme **reprezentovať** jednotlivé objekty, vlastnosti, vzťahy.
Musíme si dať pozor na to, aby naša reprezentácia:
  * nepripúšťala nejaké nečakané možnosti („Eismann
    nie je Rus ani Nemec“, „Eismann je zároveň Rus aj Nemec“), teda
    aby zohľadňovala naše intuitívne **znalosti na pozadí** (background
    knowledge), ale zároveň tiež, aby
  * nepredpokladala niečo, čo nemusí byť zrejmé priamo zo zadania,
    a teda nemusí byť pravda (byť špiónom nie je to isté, čo byť Rusom:
    dôkaz tejto úlohy by to zrovna nemalo ovplyvniť, ale to si nemôžeme
    byť vopred istí).

Na ukážku budeme používať tri premenné pre každého z ľudí, ktoré hovoria, či je
dotyčný Rus, Nemec, respektíve špión (keďže zo zadania je zrejmé, že každý je
*buď Nemec alebo Rus*, tak by nám mohla stačiť aj iba jedna premenná namiesto
týchto dvoch).

|    |                   |    |                 |    |                  |
|----|-------------------|----|-----------------|----|------------------|
| RS | Stirlitz je Rus   | RM | Müller je Rus   | RE | Eismann je Rus   |
| NS | Stirlitz je Nemec | NM | Müller je Nemec | NE | Eismann je Nemec |
| SS | Stirlitz je špión | SM | Müller je špión | SE | Eismann je špión |

Táto reprezentácia umožňuje, aby niekto z nich nebol ani Nemec, ani Rus, alebo
bol oboje. Ako prvé teda napíšeme formuly, ktoré zabezpečia, že každý z nich je
buď Nemec, alebo Rus, ale nie oboje. Jednou z možností je napríklad tvrdenie
„<var>X</var> je Rus práve vtedy, keď <var>X</var> nie je Nemec“, čo zapíšeme
ako `RX ↔︎ ¬NX` (inými slovami: povedali sme, že R<var>X</var> je to isté čo
¬N<var>X</var>, a ak zvolíme, či platí jedno, určili sme aj druhé).

Teraz môžeme zapísať všetky podmienky zo zadania:

1. <var>X</var> je buď Rus alebo Nemec: `(RS ↔︎ ¬NS) ∧ (RM ↔︎ ¬NM) ∧ (RE ↔︎ ¬NE)`
2. práve jeden je Rus, ostatní dvaja sú Nemci:
  `(RS ∧ NM ∧ NE) ∨ (NS ∧ RM ∧ NE) ∨ (NS ∧ NM ∧ RE)`
3. každý Rus musí byť špión:
  `(RS → SS) ∧ (RM → SM) ∧ (RE → SE)`
4. Stirlitz: „Müller, ty si taký Nemec, ako som ja Rus“:
  `NM ↔︎ RS`

Samozrejme, aby sme vyrobili vstup pre SAT solver, musíme všetky formuly upraviť
do konjunktívnej normálnej formy:
* Ekvivalencie sa len rozpíšu ako dve implikácie (spojené konjunkciou).
* Implikácie prepíšeme pomocou vzťahu `(a → b) ⇔ (¬a ∨ b)`
* Formulu z bodu 2 musíme „roznásobiť“, čím nám vznikne 27 disjunkcií s tromi
  premennými (z každej zátvorky jedna).

Na vyriešenie úlohy ale potrebujeme dokázať, že *Eismann nie je ruský špión*.
Potrebujeme teda ešte zapísať toto tvrdenie, znegovať ho, previesť do CNF.


**Zapísanú teóriu (so „symbolickými“ slovnými premennými, nie číslami) uložte do
súboru `spyTheory.txt` a cieľové tvrdenie do súboru `spyGoal.txt`. Obidva
súbory si odložte, na budúcich cvičeniach si ukážeme ako ich odovzdať.**

Príklad `spyTheory.txt`:
```
c X je buď Rus alebo Nemec
¬RS ∨ ¬NS
NS ∨ RS
¬RM ∨ ¬NM
NM ∨ RM
¬RE ∨ ¬NE
NE ∨ RE

...
```

Vaše riešienie si môžete odskúšať buď spustením programu [`test.py`](test.py) alebo v
[online editore / testovači](https://dai.fmph.uniba.sk/courses/lpi/russianSpy/).


### Test so SAT solverom

Keď budete chcieť vaše riešenie vyskúšať so SAT solverom, stačí len zmeniť
všetky premenné na čísla (search&replace je váš priateľ :-), negácie na mínus a
zmeniť disjunkcie na nulou ukončené postupnosti čísel.

Môžete použiť priložený pythonovský program [`text2dimacs.py`](text2dimacs.py),
ktorý vám takýto súbor „preloží“ na číselný vstup pre SAT solver.
Rovnako môžete použiť aj
[online konvertor](https://dai.fmph.uniba.sk/courses/lpi/text2dimacs/).

Keď pustíte SAT solver iba s teóriou, nájde možné riešenie, ako by to mohlo
byť. Ak SAT solver povie, že teória je nesplniteľná, tak je niekde problém.
Môžete použiť podobný postup ako v úlohe 1 a získať všetky možnosti (malo by
ich byť 8).

Na dokázanie požadovaného tvrdenia *Eismann nie je ruský špión*, treba negáciu
tohoto tvrdenia pridať k ostatným. Ak SAT solver povie, že teória je už
nesplniteľná, negácia nemôže platiť spolu s predpokladmi, a teda musí určite
platiť pôvodné, nenegované tvrdenie.
