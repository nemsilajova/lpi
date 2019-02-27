Cvičenie 2
==========

Riešenie prvého cvičenia odovzdávajte do **stredy 6.3. 23:59:59**.

Či ste správne vytvorili pull request (PR) si môžete overiť
v [tomto zozname PR pre pu01](https://github.com/pulls?utf8=%E2%9C%93&q=is%3Aopen+is%3Apr+user%3AFMFI-UK-1-AIN-412+base%3Apu01).

Riešenie tohto cvičenia (úloha [Formula](#formula-2b)) odovzdávajte
podľa [pokynov na konci tohoto zadania](#technické-detaily-riešenia)
do **stredy 6.3. 23:59:59**.

Či ste správne vytvorili pull request si môžete overiť
v [tomto zozname PR pre pu02](https://github.com/pulls?utf8=%E2%9C%93&q=is%3Aopen+is%3Apr+user%3AFMFI-UK-1-AIN-412+base%3Apu02).

Všetky ukážkové a testovacie súbory k tomuto cvičeniu si môžete stiahnuť
ako jeden zip súbor
[pu02.zip](https://github.com/FMFI-UK-1-AIN-412/lpi/archive/pu02.zip).

## Odovzdanie cvičenia 1

Podľa návodu na [odovzdávanie riešení](../../docs/odovzdavanie.md) odovzdajte
riešenie prvého cvičenia. Riešenie odovzdajte do vetvy (branch) `pu01`
v adresári `prakticke/pu01`.

Odovzdajte dva súbory: `spyTheory.txt` ktorý obsahuje „textovú“ verziu vstupu pre SAT solver
(s názvami premenných „`NM`“, „`RM`“ atď.) obsahujúcu teóriu a `spyGoal.txt` obsahujúci 
správne znegované tvrdenie, ktoré chcete dokázať.

## Formula (2b)

Vytvorte objektovú hierarchiu na reprezentáciu výrokovologických formúl.
Zadefinujte základnú triedu `Formula` a 6 od nej odvodených tried určených
na reprezentáciu jednotlivých druhov atomických a zložených formúl.

Všetky triedy naprogramujte ako knižnicu podľa
[pokynov na konci tohoto zadania](#technické-detaily-riešenia).

```
Formula
 │    constructor()
 │    Array of Formula subf()       // vrati vsetky priame podformuly ako pole
 │    String toString()             // vrati retazcovu reprezentaciu formuly
 │    Bool isSatisfied(Valuation v) // vrati true, ak je formula splnena
 │                                  // ohodnotenim v
 │    Bool equals(Formula other)    // vrati true ak je tato formula rovnaka
 │                                  // ako other
 │    Int deg()                     // vrati stupen formuly
 │    Set of String vars()          // vrati mnozinu nazvov premennych
 │    Formula substitute(Formula what, Formula replacement)
 │                                  // naharadi vsetky vyskyty what
 │                                  // v tejto formule za replacement
 │
 ├─ Variable
 │      constructor(String name)
 │      String name()   // vrati meno premennej
 │
 ├─ Negation
 │      constructor(Formula originalFormula)
 │      Formula originalFormula()   // vrati povodnu formulu
 │                                  // (jedinu priamu podformulu)
 │
 ├─ Disjunction
 │       constructor(Array of Formula disjuncts)
 │
 ├─ Conjunction
 │       constructor(Array of Formula conjuncts)
 │
 └─ BinaryFormula
      │   constructor(Formula leftSide, Formula rightSide)
      │   Formula leftSide()    // vrati lavu priamu podformulu
      │   Formula rightSide()   // vrati pravu priamu podformulu
      │
      ├─ Implication
      │
      └─ Equivalence
```
Samozrejme použite syntax a základné typy jazyka, ktorý používate (viď
príklady použitia knižnice na konci).

Metódy `toString`, `isSatisfied`, `equals`, `degree` a `substitute` budú
virtuálne metódy. Predefinujte ich v každej podtriede tak, aby robili *správnu
vec*<sup>TM</sup> pre dotyčný typ formuly.

Poznámka: v závislosti od detailov vašej implementácieje je možné, že niektoré
z nich by mali rovnakú imlementáciu vo všetkých podtriedach. Vtedy je samozrejme
v poriadku (priam lepšie) implementovať ich raz v základnej triede.

Metóda `toString` vráti reťazcovú reprezentáciu formuly podľa nasledovných
pravidiel:
- `Variable`: reťazec `a`, kde `a` je meno premennej (môže byť
  viacpísmenkové)
- `Negation`: reťazec `-A`, kde `A` je reprezentácia podformuly
- `Conjunction`:  reťazec `(A&B&C....)`, kde `A`, `B`, `C`, ... sú
  reprezentácie podformúl (konjunktov)
- `Disjunction`:  reťazec `(A|B|C....)`, kde `A`, `B`, `C`, ... sú
  reprezentácie podformúl (disjunktov)
- `Implication`:  reťazec `(A->B)`, kde `A` a `B` sú reprezentácie
  ľavej a pravej podformuly
- `Equivalence`: reťazec `(A<->B)`, kde `A` a `B` sú reprezentácie
  ľavej a pravej podformuly

Teda napríklad v objektovej štruktúre

![GitHub branch](../../images/formula.png)

metóda `toString` koreňového objektu triedy `Implication` vráti reťazec
`(-(A&C)->(--B|(D&F)))`.

Metóda `isSatisfied` vráti `True` alebo `False` podľa toho, či je formula splnená
daným ohodnotením. Ak sa stane, že ohodnotenie neobsahuje nejakú
premennú, ktorá sa vyskytne vo formule, tak môžete buď vygenerovať chybu /
výnimku alebo ju považovať za `False`.

Metóda `equals` vráti `True` ak je formula reprezentovaná touto inštanciou
rovnaká ako tá reprezentovaná inštanciou `other`. Táto metóda je dôležitá,
pretože zabudovaný operátor rovnosti vo väčšine jazykov porovnáva či sa jedná o
tú istú inštanciu objektu. Napríklad `Variable('a') == Variable('a')` v Pythone
vráti `False`, pretože porovnávame dve rôzne inštancie triedy `Variable`.

Metóda `deg` vráti stupeň formuly tak, ako bol zadefinovaný na prednáške.

Metóda `vars` vráti množinu všetkých (názvov) premenných v tejto formule.

Metóda `substitute` vráti **novú** formulu (inštanciu) v ktorej sú všetky výskyty
formuly `what` nahradené **kópiou** formuly `replacement`.

## Ohodnotenie a množina premenných
Ohodnotenie (angl. <i>valuation</i>) je mapa z reťazcov (mien premenných)
do `Bool`. Množina premenných je množina reťazcov (mien premenných).
Použite správne typy podľa vášho jazyka:

### C++
Použite `typedef`y v [FormulaTypes.h](cpp/FormulaTypes.h).

Príklad použitia:
```c++
Valuation v;
v["a"] = true;
Formula *f = new Variable("a");
if (f->isSatisfied(v) != v["a"]) { /* nieco je zle */ }
```
```c++
Variables vs{"a"};
for(const auto &var : {"b", "c"})
	vs.insert(var);
```

### Java
Použite implementácie rozhraní `java.util.Set` a `java.util.Map` (napr. `java.util.HashMap`
na reprezentovanie ohodnotenia).

Príklad použitia:
```java
Map<String,Boolean> v = new HashMap<String,Boolean>();
v.put("a",true);
Formula f = new Variable("a");
if (f.isSatisfied(v) != v.get("a")) { /* nieco je zle */ }
```

## Technické detaily riešenia

Riešenie [odovzdajte](../../docs/odovzdavanie.md) do vetvy `pu02` v podadresári
`prakticke/pu02` podľa jazyka.

Odovzdávanie riešení v iných jazykoch konzultujte s cvičiacimi.

Správne vytvorený pull request sa objaví
v [zozname PR pre `pu02`](https://github.com/pulls?utf8=%E2%9C%93&q=is%3Aopen+is%3Apr+user%3AFMFI-UK-1-AIN-412+base%3Apu02).

### C++
Odovzdajte súbory `Formula.h` a `Formula.cpp` v podadresári [cpp](cpp/).
Testovací program [`FormulaTest.cpp`](cpp/FormulaTest.cpp) musí ísť skompilovať
s vaším riešením a korektne zbehnúť.

*Poznámka:* Formula vždy vlastní svoje podformuly. Príkaz `delete f`
v programe zmaže zároveň aj všetky podformuly.

### Java
Odovzdajte súbor `Formula.java` v podadresári [java](java/).
Testovací program [`FormulaTest.java`](java/FormulaTest.java) musí byť skompilovateľný
a korektne zbehnúť, keď sa k nemu priloží vaša knižnica.
