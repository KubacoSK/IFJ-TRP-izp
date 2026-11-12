# Progress projektu IFJ a IAL (variant TRP-izp)

Posledná aktualizácia: 12. 11. 2026

## Legenda

- [x] Hotové a pokryté aktuálnym kódom alebo testami
- [~] Rozpracované / implementované iba čiastočne
- [ ] Ešte treba dorobiť

## Aktuálny stav

- Základné C moduly existujú: scanner, parser (syntax + sémantika v jednom
  module), hash tabuľka, tabuľka symbolov, pomocné funkcie, chybové kódy a `main`.
- Build bol overený v Linux prostredí (WSL Ubuntu, gcc 13.3) s
  `-Wall -Wextra -pedantic -std=c99`, bez warningov.
- Unit testy prechádzajú: scanner 56/56, hash tabuľka 26/26, tabuľka
  symbolov 19/19 (`make test`).
- Parser je dvojpriechodový: 1. priechod zbiera hlavičky funkcií, 2. priechod
  analyzuje telá. Na vetve `SematickaAnalyza-parser` bolo opravených 9 z 10
  nálezov z `REVIEW_FINDINGS.md` (finding 4 zatiaľ odložený).
- Parser bol ručne otestovaný sadou ~90 malých IFJ26 programov s očakávanými
  návratovými kódmi a cez `valgrind`; sada zatiaľ nie je v repozitári.
- Generovanie IFJcode26 zatiaľ nie je implementované (vetva `CodeGenerator`
  neobsahuje generátor).
- **Pokusné odovzdanie je 19. 11. 2026** – bez generátora kódu prejdú iba
  testy chybových návratových kódov.

## 1. Príprava a architektúra

- [x] Vytvorenie / nastavenie spoločného Git repozitára.
- [x] Dohodnutie pravidiel práce: Conventional Commits, pull requesty a code review.
- [x] Vytvorenie základného `Makefile` s cieľmi `all`, `ifj26`, `test`,
  `test_scanner`, `test_ht`, `test_symtable` a `clean`.
- [x] Doplniť samostatné ciele `check` alebo `build-check`.
- [ ] Nastaviť a overiť `clang-format` pre všetky zdrojové súbory
  (v repozitári chýba `.clang-format`, zadanie to vyžaduje povinne).
- [x] Navrhnutie základných dátových štruktúr tokenov v `scanner.h`.
- [x] Navrhnutie dátových štruktúr hash tabuľky a tabuľky symbolov.
- [~] Základná modulárna architektúra existuje, treba ju ešte prepojiť s
  kompletným tokom parser -> sémantika -> generovanie kódu.
- [ ] **`main.c` používa `tmpfile()` na kópiu stdin – zadanie zakazuje vytvárať
  súbory (ani v `/tmp`).** Treba načítať vstup do pamäte (napr. pole tokenov
  v 1. priechode, čo zároveň vyrieši finding 4).
- [~] Jednotné vlastníctvo pamäte: parametre funkcií majú `free_params`,
  `parse_params` uvoľňuje pri chybe; pri chybe sa ešte neuvoľní `current_tok`
  a symbolová tabuľka v niektorých vetvách.
- [ ] Hlavičky zdrojových súborov neobsahujú mená a loginy autorov
  (zadanie 2.5 to vyžaduje).

## 2. Hash tabuľka a tabuľka symbolov (IAL)

### Hash tabuľka

- [x] Zvolená hashovacia funkcia djb2.
- [x] Implementovaná otvorená adresácia s lineárnym prehľadávaním.
- [x] Implementované stavy `EMPTY`, `OCCUPIED` a `DELETED`.
- [x] Implementované `ht_init`, `ht_insert`, `ht_search`, `ht_delete` a
  `ht_clear`.
- [x] Ošetrené kolízie, aktualizácia duplicitného kľúča a hrobčeky.
- [x] Napísané unit testy pre inicializáciu, vkladanie, vyhľadávanie,
  kolízie, mazanie a čistenie tabuľky (26/26 prechádza).
- [ ] Overiť správanie pri zaplnenej tabuľke a pri zlyhaní alokácie.

### Tabuľka symbolov

- [x] Navrhnuté typy `DataType`, `SymbolKind`, `Param`, `VarData` a `FuncData`.
- [x] Implementovaná globálna tabuľka funkcií.
- [x] Implementované lokálne scopes s rodičovským scope.
- [x] Implementované pridávanie a vyhľadávanie premenných a funkcií.
- [x] Implementované zatienenie premenných vo vnorenom scope.
- [x] Implementované uvoľnenie symbolov, parametrov a scope-ov.
- [x] Napísané unit testy pre funkcie, premenné, scopes a zatienenie (19/19).
- [x] Redefinícia v rovnakom scope: rieši parser cez
  `symtable_find_var_current_scope` pred vložením (chyba 4).
- [x] Vstavané funkcie (`print`, `readLine`, `readInt`, `readDouble`, `toStr`,
  `toInt`, `strLength`, `subStr`, `ord`, `chr`) sú vložené do tabuľky.
- [ ] Doplniť testy pre chybové stavy a zlyhanie alokácie.

## 3. Lexikálna analýza / scanner

- [ ] Dokončiť a archivovať stavový diagram scanneru.
- [x] Čítanie zo `stdin` aj z nastaveného `FILE *`.
- [x] Reset vnútorného stavu scanneru.
- [x] Tokenizácia identifikátorov, kľúčových slov a samostatného `_`.
- [x] Tokenizácia celočíselných a desatinných literálov vrátane exponentov,
  oddeľovačov `_` a sufixu `d/D`.
- [x] Tokenizácia jedno- a viacriadkových reťazcov s escape sekvenciami.
- [x] Tokenizácia operátorov, porovnania, priradenia a interpunkcie.
- [x] Podpora anotácie `@main`.
- [x] Spracovanie komentárov vrátane vnorených blokových komentárov.
- [x] Spracovanie odsadenia cez tokeny `INDENT` a `DEDENT`.
- [x] Lookahead cez `unget_token` (využíva ho parser pri príkaze s identifikátorom).
- [x] Príznak `had_preceding_newline` sa nastavuje (potrebné pre koncovú čiarku).
- [x] Detekcia lexikálnych chýb a interných chýb alokácie.
- [x] Unit testy scanneru pokrývajúce základné tokeny a chybové vstupy (56/56).
- [x] Spustiť testy na Linux prostredí (WSL Ubuntu).
- [ ] Overiť na serveri Merlin (gcc 14+/clang).
- [ ] Doplniť regresné testy pre hraničné prípady čísel, komentárov,
  odsadenia, konca súboru a `had_preceding_newline`.

## 4. Syntaktická analýza / parser (Dominik)

- [x] Rekurzívny zostup, dvojpriechodový (hlavičky -> telá).
- [x] Povinný prolog `import ifj26.*`, iba definície funkcií na najvyššej úrovni.
- [x] Anotácia `@main` na rovnakom aj samostatnom riadku (oba priechody).
- [x] Parametre a návratové typy funkcií, ľubovoľný počet parametrov
  (dynamické pole namiesto `Param[20]`).
- [x] Koncová čiarka v parametroch a argumentoch iba pred novým riadkom.
- [x] Bloky cez `INDENT` / `DEDENT`, prázdny blok je chyba 2.
- [x] `val` / `var`, priradenie, volanie funkcie ako príkaz.
- [x] Samostatný výraz ako príkaz vrátane výrazu začínajúceho identifikátorom.
- [x] Stredník ako oddeľovač príkazov na jednom logickom riadku.
- [x] `if ... then ... else` (else povinné), `while ... do`, `return [výraz]`.
- [x] Precedenčná analýza výrazov s `+ - * /`, relačnými operátormi a zátvorkami.
- [x] Unárne `+`/`-` vrátane `-( ... )`.
- [x] Vnorené zátvorky vo výrazoch (`((x))`, `1 + (2 * (3))`); prázdne `()`
  sa rozpozná podľa `expect_opd`.
- [x] Precedenčná analýza kontroluje poradie operand/operátor
  (`1 2 +`, `1 + * 2`, `x *` sú chyba 2).
- [ ] Zásobníky v `parse_expression` majú pevnú veľkosť 100 bez kontroly –
  101+ vnorených zátvoriek = stack buffer overflow (overené ASan).
- [ ] Logický riadok nesmie začínať operátorom – príkaz `-x` alebo `+x` je
  teraz prijatý (vetva PLUS/MINUS v `parse_statement`).
- [ ] Neznámy názov typu (`val a: Foo`, `a: Foo`, `): Foo`) vracia 2, podľa
  špecifikácie ide o nedefinovaný typ = chyba 3.
- [~] Volanie funkcie vo výraze (`1 + f(x)`) a výraz/volanie v argumentoch sú
  prijímané – v základnom zadaní je to chyba, platné iba s rozšírením FUNEXP.
  Treba rozhodnúť, či FUNEXP implementujeme.
- [ ] Navrhnúť a zdokumentovať kompletnú LL gramatiku a LL tabuľku.
- [~] Vytvoriť samostatné syntaktické testy s očakávanými návratovými kódmi
  (existujú lokálne, treba ich pridať do `tests/` a skriptu).

## 5. Sémantická analýza (Dominik)

- [x] Prepojenie parsera s tabuľkou symbolov pre funkcie, parametre a premenné.
- [x] Nedefinovaná premenná/funkcia (3), redefinícia premennej/funkcie (4).
- [x] Duplicitné mená parametrov (4).
- [x] Inicializácia je povinná syntakticky, čítanie neinicializovanej premennej
  nemôže nastať.
- [x] Typová kontrola výrazov, inicializácie a priradení vrátane `Int -> Double`.
- [x] Zápis do `val` a do parametra (7).
- [x] Počet a typy argumentov pri volaní vstavaných aj užívateľských funkcií (5).
- [x] `@main`: chýbajúci (3), viacnásobný (4), s parametrami (5),
  iný návratový typ ako `Unit` (6).
- [x] Boolean iba v podmienke `if` / `while` (inde chyba 6).
- [x] Explicitný `Unit`: hodnota `return` a jednoriadkového tela sa zahodí.
- [x] `return` vo funkcii bez explicitného návratového typu (6).
- [ ] **Finding 4:** odvodený návratový typ funkcie sa neukladá do symtable a
  funkciu bez typu nemožno správne volať pred jej definíciou (typ `TYPE_UNDEF`).
- [ ] Výsledok viacriadkového tela sa nekontroluje (`parse_block` nevracia typ
  posledného príkazu) – napr. `def f(): Int =` s telom `val x = 1` prejde,
  `@main def run() =` s telom `5` prejde.
- [ ] Pravidlá pre `if` na konci tela funkcie (Unit / všetky vetvy `return`).
- [ ] Rekurzia (priama aj nepriama) bez explicitného návratového typu (6) –
  zatiaľ sa nekontroluje.
- [ ] Porovnanie `==` / `!=` dvoch hodnôt `Unit` vracia 6, špecifikácia
  povoľuje porovnanie hodnôt rovnakého typu.
- [ ] Overiť na fóre: chyba 6 vs. 10 pre nepovolený `return` (samostatný
  `return` mimo `Unit`, `return` vo funkcii bez typu).
- [ ] Overiť na fóre: zreťazenie relačných operátorov (`1 < 2 < 3`) teraz
  vracia 6, môže sa očakávať 2.
- [ ] Overiť: `val x` v tele funkcie s parametrom `x` vracia 4 (parametre sú
  v rovnakom scope ako telo), Scala to povoľuje.
- [ ] Poradie chýb medzi priechodmi: 1. priechod hlási chyby hlavičiek skôr, než
  2. priechod skontroluje prolog (napr. chýbajúci prolog + duplicitná funkcia
  vráti 4 namiesto 2).
- [~] Testy sémantických chybových kódov `3`, `4`, `5`, `6`, `7` existujú
  lokálne; kód `10` zatiaľ nikde nevzniká.

## 6. Generovanie cieľového kódu IFJcode26 (Jakub)

- [ ] Navrhnúť rozhranie a dátové štruktúry generátora.
- [ ] Implementovať výpis hlavičky a základných inštrukcií IFJcode26.
- [ ] Implementovať tvorbu a rušenie rámcov.
- [ ] Implementovať prácu s premennými, parametrami a dočasnými hodnotami.
- [ ] Implementovať generovanie výrazov a konverzií typov.
- [ ] Implementovať generovanie volaní funkcií a návratových hodnôt.
- [ ] Implementovať generovanie `if` / `else` a `while` cez návestia a skoky.
- [ ] Implementovať požadované vstavané funkcie (vrátane chyby 40 pri `subStr`).
- [ ] Otestovať výstup cez referenčný interpret IFJcode26.
- [ ] Overiť, že diagnostika ide na `stderr` a generovaný kód na `stdout`.

## 7. Testovanie, kvalita a ladenie

- [x] Existujú unit testy hash tabuľky, tabuľky symbolov a scanneru.
- [ ] Doplniť end-to-end testovací skript pre preklad a návratové kódy.
- [ ] Pridať validné vstupy s očakávaným výstupom.
- [~] Lexikálne, syntaktické a sémantické chybové vstupy existujú lokálne,
  treba ich pridať do `tests/`.
- [ ] Pridať testy generovaného IFJcode26.
- [~] Build overený cez gcc 13 (WSL); treba ešte gcc 14+/clang 19+ (Merlin).
- [ ] Overiť kompatibilitu s požiadavkami servera Merlin.
- [~] Parser skontrolovaný cez `valgrind` na testovacích vstupoch – bez únikov
  a neplatných prístupov; ASan odhalil overflow pri hlbokých zátvorkách.
- [ ] Pridať testy hraničných prípadov a regresné testy po každej väčšej zmene.
- [x] Warning-free build s `-Wall -Wextra -pedantic -std=c99`.

## 8. Dokumentácia a odovzdanie

- [~] Zdrojové súbory obsahujú základné komentáre k verejným rozhraniam.
- [ ] Priebežne zapisovať použitie AI podľa požiadaviek predmetu.
- [ ] Vytvoriť súbor `rozdeleni` (LF konce riadkov, súčet 100 %).
- [ ] Vytvoriť súbor `rozsireni` (identifikátory rozšírení, LF konce riadkov).
- [ ] Dokončiť `dokumentace.pdf`:
  - [ ] Úvodná strana, členovia tímu, varianta, rozdelenie bodov, rozšírenia,
    odkaz na repozitár.
  - [ ] Diagram architektúry a dátových tokov.
  - [ ] Diagram konečného automatu scanneru.
  - [ ] LL gramatika/tabuľka a precedenčná tabuľka.
  - [ ] Popis tabuľky symbolov a generovania kódu.
  - [ ] Zhodnotenie použitia AI a rozdelenia práce.
- [ ] Doplniť a aktualizovať `README.md` o build, testy a použitie prekladača.
- [ ] Spustiť `is_it_ok.sh` nad finálnym archívom.
- [ ] Skontrolovať obsah archívu a odstrániť objektové, dočasné a testovacie súbory.
- [ ] **POKUSNÉ ODOVZDANIE** do 19. novembra 2026 23:59:59.
- [ ] **FINÁLNE ODOVZDANIE** do 27. novembra 2026 11:59:59.

## Odporúčané poradie ďalšej práce

1. Odstrániť `tmpfile()` z `main.c` – načítať tokeny do pamäte v 1. priechode
   (rieši zákaz vytvárania súborov aj finding 4).
2. Opraviť chyby precedenčnej analýzy (vnorené zátvorky, poradie
   operand/operátor, kontrola veľkosti zásobníka).
3. Doplniť výsledok bloku a pravidlá návratovej hodnoty (posledný príkaz, `if`,
   rekurzia).
4. Navrhnúť a implementovať generátor IFJcode26 – bez neho nepôjdu validné testy.
5. Pridať end-to-end testy a skript do `tests/`.
6. Spustiť build a testy na Merlin, `clang-format`, hlavičky súborov.
7. Dokončiť dokumentáciu, `rozdeleni`, `rozsireni`, `is_it_ok.sh` a archív.
