# Progress projektu IFJ a IAL (variant TRP-izp)

Posledná aktualizácia: 16. 11. 2026 (vetva `Code-generator`, commit `c5f9430`)

## Legenda

- [x] Hotové a pokryté aktuálnym kódom alebo testami
- [~] Rozpracované / implementované iba čiastočne
- [ ] Ešte treba dorobiť

## Aktuálny stav

- Prekladač je funkčný celok: scanner → parser (syntax + sémantika) →
  generátor IFJcode26 priamo z parsera → výpis až po úspešnej analýze.
- Build v WSL Ubuntu (gcc 13.3) s `-Wall -Wextra -pedantic -std=c99` je bez
  warningov.
- Unit testy prechádzajú: scanner 56/56, hash tabuľka 26/26, tabuľka
  symbolov 27/27 (`make test`).
- End-to-end testy prechádzajú: 184/184 (`make test_e2e`, `tests/e2e.sh`,
  preklad → `ic26int` → porovnanie výstupu a návratových kódov).
- `valgrind` je čistý na úspešnom preklade aj na chybových cestách (kódy 1, 3,
  4, 5, chyba počas analýzy na požiadanie, chyba vo vnorenom výraze).
- Pri chybe prekladu je `stdout` prázdny; kód nepoužíva súbory, sieť ani
  podprocesy, iba štandardnú knižnicu C.
- Rozšírenie FUNEXP je implementované, ale chýba súbor `rozsireni`, takže by
  sa netestovalo.
- **Pokusné odovzdanie je 19. 11. 2026.** Pred ním treba hlavne: `rozsireni`,
  `rozdeleni`, oprava `readInt` mimo rozsahu Int, hlavičky súborov,
  `clang-format` (pozri „Zoznam úloh“).

## 1. Príprava a architektúra

- [x] Vytvorenie / nastavenie spoločného Git repozitára.
- [x] Dohodnutie pravidiel práce: Conventional Commits, pull requesty a code review.
- [x] `Makefile` s cieľmi `all` (predvolený, `ifj26`), `test`, `test_scanner`,
  `test_ht`, `test_symtable`, `test_e2e`, `check`, `build-check`, `clean`.
- [~] `clang-format` (LLVM, `.clang-format`): `parser.c` má 41 odchýlok,
  `codegen.c` 5, `main.c` 1, `symtable.h` 2 (`clang-format --dry-run`).
  Ostatné súbory sú v poriadku. Treba spustiť `clang-format -i`.
- [x] Architektúra bez AST: parser riadi preklad a generátor vypisuje kód
  priamo pri rozpoznaní konštrukcie (prednáška 9, prístup 3). Na obhajobu
  pripraviť zdôvodnenie (bez AST, dva priechody).
- [x] Dátové štruktúry tokenov, hash tabuľky a tabuľky symbolov.
- [x] Celý tok parser → sémantika → generovanie kódu je prepojený.
- [x] Bez `tmpfile()`: 1. priechod načíta všetky tokeny do poľa v pamäti
  (lexikálna chyba ako zarážka, vráti sa až keď k nej parser dôjde),
  2. priechod ide po tom istom poli. Scanner číta stdin iba raz.
- [x] Uvoľnenie pamäte aj pri chybe (pole tokenov, symbolová tabuľka, buffery
  generátora), overené `valgrind`.
- [ ] Hlavičky zdrojových súborov neobsahujú mená a loginy autorov
  (zadanie 2.5), chýba vo všetkých 14 súboroch `.c/.h`.

## 2. Hash tabuľka a tabuľka symbolov (IAL)

### Hash tabuľka

- [x] Hashovacia funkcia djb2, otvorená adresácia s lineárnym prehľadávaním,
  stavy `EMPTY`, `OCCUPIED`, `DELETED`.
- [x] `ht_init`, `ht_insert`, `ht_search`, `ht_delete`, `ht_clear`.
- [x] Unit testy (26/26).
- [ ] Pevná kapacita `HT_CAPACITY 2039` bez zväčšovania: viac ako 2039
  premenných v jednom bloku alebo viac ako ~2029 funkcií vráti 99, hoci 99 má
  byť iba chyba neovplyvnená vstupom. Rozhodnúť v tíme (zväčšovanie tabuľky).

### Tabuľka symbolov

- [x] Typy `DataType`, `SymbolKind`, `Param`, `VarData` (s jedinečným `id`),
  `FuncData`.
- [x] Globálna tabuľka funkcií, lokálne scopes s rodičom, zatienenie.
- [x] Jedinečné ID premennej z počítadla (`next_var_id`) pre premenovanie
  `LF@meno$ID`.
- [x] Vstavané funkcie vložené do tabuľky.
- [x] Unit testy (27/27) vrátane jedinečných ID.
- [ ] Návratové hodnoty pri zlyhaní alokácie sa nekontrolujú všade:
  `symtable_add_builtins` v `main.c`, `symtable_push_scope` v `parser.c`,
  `str_dup` mena parametra v `symtable_add_func`.
- [ ] Parser pri analýze na požiadanie priamo mení `symtab->current_scope`
  (Symtable nie je úplne skrytý ADT); zvážiť funkciu na odpojenie/obnovenie
  rozsahov v `symtable`.

## 3. Lexikálna analýza / scanner

- [ ] Dokončiť a archivovať stavový diagram scanneru.
- [x] Identifikátory, kľúčové slová, `_`, celé a desatinné literály
  (exponent, `_`, sufix `d/D`), jedno- a viacriadkové reťazce s escape
  sekvenciami, operátory, `@main`, vnorené komentáre, `INDENT` / `DEDENT`,
  `had_preceding_newline`.
- [x] Unit testy scanneru (56/56).
- [ ] Desatinný literál mimo rozsahu Double (`1e999`) prejde a vygeneruje
  `float@inf` → interpret skončí 51; má byť lexikálna chyba 1 (kontrola
  `ERANGE` / `HUGE_VAL` po `strtod`).
- [ ] Odsadenie hlbšie ako 127 úrovní vráti 99 (`MAX_INDENT_LEVELS`);
  zásobník odsadenia zmeniť na dynamický.
- [ ] Skutočný tabulátor v jednoriadkovom reťazci a `"""a""""` vrátia 1,
  Scala ich prijme (nízka priorita).
- [ ] Kľúčové slová rozšírení (`Boolean`, `case`, `for`, …) sa berú ako
  identifikátory (netestuje sa); `val a: Boolean` vráti 3.
- [ ] Overiť na serveri Merlin (gcc 14+/clang).

## 4. Syntaktická analýza / parser (Dominik)

- [x] Rekurzívny zostup, dvojpriechodový (hlavičky → telá).
- [x] Prolog `import ifj26.*` (aj s bielymi znakmi medzi tokenmi), iba
  definície funkcií na najvyššej úrovni, `@main` na rovnakom aj samostatnom
  riadku.
- [x] Parametre, návratové typy, koncová čiarka iba pred novým riadkom.
- [x] Bloky cez `INDENT` / `DEDENT`, prázdny blok je chyba 2.
- [x] `val` / `var`, priradenie, volanie ako príkaz, samostatný výraz,
  stredník, `if … then … else`, `while … do`, `return [výraz]`.
- [x] Precedenčná analýza podľa prednášky 8: jeden zásobník s terminálmi,
  `E` a značkami `<`, `i` v tabuľke, redukcia hľadá pravidlo
  (`E → i`, `E → u E`, `E → ( E )`, `E → ( )`, `E → E op E`).
- [x] Unárne `+` / `-`, zátvorky, `()` ako literál `Unit`.
- [x] Logický riadok nesmie začínať operátorom (za `;` je povolené).
- [x] FUNEXP: volania vo výrazoch a výrazy v argumentoch, vnorené volania,
  vyhodnocovanie zľava doprava.
- [x] Hlboké výrazy: 100 000 vnorených zátvoriek aj výraz s 200 000 členmi
  prejdú.
- [ ] Hlboko vnorené volania `f(f(…))` (~50 000 úrovní) spadnú na
  segfault (rekurzia); 20 000 prejde. Obmedziť hĺbku.
- [ ] `1 < 2 == 3 < 4` vráti 2 (v tabuľke `E` medzi úrovňami 4 a 5),
  podľa priorít by mohla byť skôr 6 → fórum.
- [ ] Navrhnúť a zdokumentovať LL gramatiku a LL tabuľku.

## 5. Sémantická analýza (Dominik)

- [x] Nedefinovaná premenná/funkcia/typ (3), redefinícia premennej/funkcie,
  duplicitné parametre (4).
- [x] Typová kontrola výrazov, inicializácie, priradení, argumentov a návratu
  vrátane `Int → Double`.
- [x] Zápis do `val` a do parametra (7).
- [x] Počet a typy argumentov vstavaných aj užívateľských funkcií (5).
- [x] `@main`: chýbajúci (3), viacnásobný (4), s parametrami (5), iný
  návratový typ ako `Unit` (6).
- [x] Boolean iba v podmienke `if` / `while` (inde 6).
- [x] Explicitný `Unit`: hodnota `return` a tela sa zahodí.
- [x] `return` vo funkcii bez explicitného typu (6).
- [x] Odvodený návratový typ, analýza na požiadanie pri volaní pred
  definíciou, rekurzia bez typu (6) cez stav „prebieha“ a graf volaní.
- [x] Pravidlá pre `if` na konci tela funkcie, rekurzívne pre vnorený `if`.
- [x] `() == ()` a `() != ()` prechádzajú.
- [x] Zreťazenie `1 < 2 < 3` vráti 2.
- [ ] Poradie chýb: 1. priechod nájde lexikálnu chybu a duplicitnú funkciu
  skôr než 2. priechod (syntaktická chyba pred neukončeným reťazcom vráti 1;
  chýbajúci prolog + duplicitná funkcia vráti 4 namiesto 2).
- [ ] Kód 10 nikde nevzniká; samostatný `return` vo funkcii s typom iným ako
  `Unit` vráti 6 → fórum (6 podľa kap. 2.3 vs. 10 podľa kap. 6).
- [ ] Boolean ako argument (`print(1 < 2)`, `f(1 < 2)`) vráti 6, môže sa
  čakať 5 → fórum.
- [ ] `val x` v tele funkcie s parametrom `x` vráti 4 (parametre sú v rovnakom
  scope ako telo), Scala to povoľuje → fórum.

## 6. Generovanie cieľového kódu IFJcode26 (Jakub)

Rozhodnutia (implementované):

- [x] Priame generovanie z parsera, zásobníkové inštrukcie.
- [x] Argumenty aj návratová hodnota cez dátový zásobník, rámec vytvára volaná
  funkcia (`CREATEFRAME`, `PUSHFRAME` v prológu).
- [x] Premenné `LF@meno$ID`, všetky `DEFVAR` na začiatku funkcie (buffer
  `defs`), žiadna chyba 52 pri premenných v cykloch.
- [x] Pomocné premenné lokálne `LF@%t1`, `LF@%t2`.
- [x] Vstupný bod `CALL $f$<main>`, `CLEARS`, `EXIT int@0`; výpis až na konci.
- [x] Každý príkaz nechá na zásobníku 1 hodnotu, pred ďalším sa zahodí.
- [x] `Unit` = `nil@nil`, `print(())` vypíše `()`.
- [x] Statická konverzia `Int → Double`, `<=` / `>=` ako `(a < b) OR (a == b)`,
  `Int / Int` cez `IDIVS`, `+` reťazcov cez `CONCAT`.
- [x] Literály `int@`, `float@%a`, `string@` s escape `\xyz`.
- [x] Vstavané funkcie: inline `print`, `toStr`, `toInt`, `chr`, `strLength`,
  `readLine`; knižnica `$b$` `readInt`, `readDouble`, `ord`, `subStr`
  (chyba 40 vo všetkých 5 prípadoch).
- [x] Otestované cez `ic26int` (e2e), kód iba na `stdout`.

Otvorené:

- [ ] `readInt` pre hodnotu mimo rozsahu Int (`3000000000`, `2147483648`)
  vráti túto hodnotu namiesto 0 (kap. 4). Opraviť `$b$readInt` a test
  `readint_pretecenie` v `tests/e2e.sh` (dnes očakáva nesprávny výstup).
- [ ] `readLine` pri EOF: Windows `ic26int` vráti `""`, ale podľa kap. 7.4.4
  `READ` vráti `nil`. Pridať kontrolu `nil` (napr. presunúť do `$b$readLine`).
- [ ] Pretečenie Int nemá 32-bitovú sémantiku Scaly (`2147483647 + 1` →
  `2147483648`, `toInt(1e20)` → 64-bitová hodnota) → najprv fórum.
- [ ] Aktualizovať `Generator postup.md`: R10/R12 uvádzajú `GF@%t1` a
  `POPS GF@%t1`, R16 `<=` ako `GTS NOTS`; kód používa `LF@%t1`, `CLEARS`
  a `OR`.

## 7. Testovanie, kvalita a ladenie

- [x] Unit testy hash tabuľky, tabuľky symbolov a scanneru (109).
- [x] End-to-end skript `tests/e2e.sh` (184 testov): parser, precedenčná
  analýza, literály, výrazy, riadenie toku, funkcie, vstavané funkcie,
  príklady zo špecifikácie.
- [ ] Doplniť e2e testy chybových kódov, ktoré chýbajú alebo sú slabo pokryté:
  - 1: neukončený reťazec, tabulátor v odsadení, neukončený komentár,
    neplatný escape, `1e999` (dnes 0 e2e testov);
  - 2: chýbajúci a dvojitý prolog;
  - 3: chýbajúci `@main`;
  - 4: redefinícia premennej, funkcie, parametra, dva `@main` (dnes 0 testov);
  - 5 a 6: `@main` s parametrom, `@main` s typom `Int`;
  - 6: rekurzia bez typu, telo s typom končiace `if` bez `return`;
  - 7: zápis do parametra;
  - `readInt` so vstupom `2147483648` → `0`;
  - 100 úrovní vnorenia → preklad bez chyby.
- [x] Warning-free build, `valgrind` čistý.
- [~] Build overený cez gcc 13 (WSL); treba gcc 14+/clang 19+ (Merlin).
- [ ] Drobné výnimky v pomenovaní: `Token_type`, `Token_attribute`
  v `scanner.h`, `p_toStr`, `p_toInt`, `p_strLength`, `p_subStr`
  v `symtable.c`, makro `current_tok` v `parser.c`.

### Overiť na Merline / Linux `ic26int`

- [ ] `READ string` pri EOF (`nil` alebo `""`).
- [ ] Literály `int@` mimo 32 bitov (`-2147483648` vo Windows verzii vypíše
  `-2147483647`).
- [ ] `READ int` so vstupmi `+5`, ` 5`, `3000000000`.
- [ ] `float@` s `-0x0p+0` a subnormálnymi číslami, výpis `\n` ako LF.
- [ ] Návratové kódy 40, 57, 58; čas behu pri veľkých vstupoch.

## 8. Dokumentácia a odovzdanie

- [~] Zdrojové súbory obsahujú komentáre k funkciám; dokumentácia rozhraní
  v `.h` (ideálne Doxygen) – prejsť všetky `.h`.
- [ ] Pripraviť odpovede na obhajobu: prečo bez AST, prečo dva priechody,
  scanner s vnorenými komentármi, parametre hash tabuľky (djb2, 2039 slotov,
  lineárny krok), tvar precedenčnej analýzy, volacia konvencia a zásobník.
- [ ] Vytvoriť súbor `rozdeleni` (LF konce riadkov, súčet 100 %).
- [ ] Vytvoriť súbor `rozsireni` s riadkom `FUNEXP` (LF koniec riadku).
- [ ] Dokončiť `dokumentace.pdf`:
  - [ ] Úvodná strana, členovia tímu, varianta, rozdelenie bodov, rozšírenia,
    odkaz na repozitár.
  - [ ] Diagram architektúry a dátových tokov.
  - [ ] Diagram konečného automatu scanneru.
  - [ ] LL gramatika/tabuľka a precedenčná tabuľka.
  - [ ] Popis tabuľky symbolov a generovania kódu.
  - [ ] Rozdelenie práce, spolupráca, testovanie.
  - [ ] Štýl formátovania kódu (`clang-format`, LLVM).
- [ ] Doplniť `README.md` o build, testy a použitie prekladača.
- [ ] Archív vytvoriť z gitu (pracovná kópia na Windows má CRLF), spustiť
  `is_it_ok.sh`, odstrániť objektové a dočasné súbory.
- [ ] **POKUSNÉ ODOVZDANIE** do 19. novembra 2026 23:59:59.
- [ ] **FINÁLNE ODOVZDANIE** do 27. novembra 2026 11:59:59.

## Otázky na fórum

1. Musí generovaný kód pretekať na 32 bitoch ako Scala? Vracia `readInt`
   0 pre hodnoty mimo rozsahu Int?
2. Boolean ako argument (`print(1 < 2)`): chyba 5 alebo 6? `a < b == c < d`:
   chyba 2 alebo 6?
3. Samostatný `return` vo funkcii s typom iným ako `Unit`: chyba 6 alebo 10?
4. Smie premenná na najvyššej úrovni tela funkcie zatieniť parameter?
5. Nezarovnaný DEDENT, zlé odsadenie v zátvorkách, tabulátor v reťazci:
   chyba 1 alebo 2?

## Zoznam úloh

**Pred pokusným odovzdaním (19. 11. 2026):**

- [ ] Vytvoriť `rozsireni` (`FUNEXP`) a `rozdeleni` (časť 8).
- [ ] Opraviť `readInt` mimo rozsahu Int a test `readint_pretecenie` (časť 6).
- [ ] Kontrola `nil` v `readLine` pri EOF (časť 6).
- [ ] `1e999` ako lexikálna chyba 1 (časť 3).
- [ ] Hlavičky zdrojových súborov s autormi a loginmi (časť 1).
- [ ] `clang-format -i` na `parser.c`, `codegen.c`, `main.c`, `symtable.h`
  (časť 1).

**Do finálneho odovzdania (27. 11. 2026):**

- [ ] Otázky na fórum a podľa odpovedí upraviť kódy chýb a pretečenie Int.
- [ ] Limity vracajúce 99 (kapacita tabuľky, hĺbka odsadenia) a segfault pri
  hlbokom vnorení volaní (časti 2, 3, 4).
- [ ] Kontroly zlyhania alokácie v `main.c`, `parser.c`, `symtable.c` (časť 2).
- [ ] Poradie chýb medzi priechodmi (časť 5).
- [ ] Doplniť e2e testy chybových kódov 1, 4 a ďalších (časť 7).
- [ ] Build a testy na serveri Merlin (časť 7).
- [ ] Aktualizovať `Generator postup.md` (časť 6).
- [ ] Drobné výnimky v pomenovaní (časť 7), dokumentácia funkcií v `.h`.
- [ ] LL gramatika a LL tabuľka, stavový diagram scanneru (časti 3, 4).
- [ ] `dokumentace.pdf`, `README.md`, odpovede na obhajobu (časť 8).
- [ ] `is_it_ok.sh` a kontrola archívu (časť 8).
