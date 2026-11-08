# Specifikace jazyků IFJ26 a IFJcode26 (IFJ/IAL 2026/2027) 

revize z 4. 10. 2026 

### Ondřej Ondryáš, Zbyněk Křivka 

# **Obsah** 

|**1**|**Pop**|**is jazyka IFJ26**|**2**|
|---|---|---|---|
||1.1|Lexikální jednotky<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>2|
||1.2|Odsazení, konce příkazů a čárky . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>3|
||1.3|Datové typy . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>4|
|**2**|**Stru**|**ktura programu**|**4**|
||2.1|Blok . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>5|
||2.2|Proměnné a rozsahy platnosti . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>5|
||2.3|Definice a volání funkcí . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>6|
||2.4|Podmíněný příkaz . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>7|
||2.5|Cyklus**`while`** . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>7|
|**3**|**Výr**|**azy**|**7**|
|**4**|**Vest**|**avěné funkce**|**8**|
||4.1|Doporučení k testování – kompatibilita se Scalou<br>. . . . . . . . . . . . .|. . . .<br>9|
|**5**|**Roz**|**šíření**|**10**|
||5.1|FUNEXP – funkce ve výrazech . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>10|
||5.2|BOOLTHEN – pravdivostní hodnoty . . . . . . . . . . . . . . . . . . . .|. . . .<br>10|
||5.3|CONTROL – rozšířené řídicí struktury . . . . . . . . . . . . . . . . . . .|. . . .<br>11|
||5.4|VALMEM – členy hodnot<br>. . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>12|
||5.5|ALGEBDT – sjednocení, součiny a**`match`** . . . . . . . . . . . . . . . . .|. . . .<br>12|
||5.6|INTERPOLATEDS – interpolované řetězce . . . . . . . . . . . . . . . .|. . . .<br>13|
||5.7|LAMBDAS – jednoduché anonymní funkce, funkce vyššího řádu . . . . .|. . . .<br>14|
||5.8|LISTS – seznamy . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>15|
||5.9|EXTKW – uživatelské rozšiřující metody<br>. . . . . . . . . . . . . . . . .|. . . .<br>16|
||5.10|PARAMLISTS – funkce s větším množstvím seznamů parametrů . . . . .|. . . .<br>17|
|**6**|**Pře**|**hled chybových návratových kódů**|**18**|
|**7**|**Cílo**|**vý jazyk IFJcode26**|**18**|
||7.1|Hodnoticí interpret`ic26int`. . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>18|
||7.2|Paměťový model. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>19|
||7.3|Datové typy . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>19|
||7.4|Instrukční sada<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . .<br>20|



# **Úvod** 

Vaším cílem v tomto projektu je implementovat překladač z kódu ve zdrojovém jazyce IFJ26 do cílového jazyka IFJcode26. Tento dokument obsahuje specifikaci obou jazyků. 

Při implementaci a odevzdávání se nezapomeňte **řídit pokyny v hlavním zadání** �. 

V tomto dokumentu jsou klíčová slova sázena tučně. 

1 

# **1 Popis jazyka IFJ26** 

Jazyk IFJ26 je zjednodušenou podmnožinou jazyka Scala 3.8.4<sup>1</sup> , což je multiparadigmatický jazyk s prvky objektově orientovaného a funkcionálního programování. IFJ26 je silně a staticky typovaný, podporuje odvozování typů, modifikovatelné i nemodifikovatelné proměnné, uživatelské funkce a základní strukturované řízení toku programu. Na velikosti písmen v identifikátorech a klíčových slovech záleží (tzv. _case-sensitive_ jazyk). 

Není-li výslovně uvedeno jinak, je každá konstrukce IFJ26 současně platnou konstrukcí jazyka Scala 3.8.4 (nedojde-li např. ke kolizi s klíčovým slovem jazyka Scala) a má obdobnou sémantiku. Scala je však výrazně bohatší jazyk; přijetí programu překladačem Scala proto neznamená, že jde o platný program v IFJ26. 

## **1.1 Lexikální jednotky** 

Zdrojové programy a řetězce v testech budou používat pouze znaky ASCII. 

- _Identifikátor_ je neprázdná posloupnost písmen anglické abecedy (malých i velkých), číslic a znaku podtržítka (’ **`_`** ’), která začíná písmenem nebo podtržítkem. Samotné podtržítko není identifikátor a využito bude v rozšířeních. 

Identifikátory zapsané v obrácených apostrofech, operátorové identifikátory ani znaky Unicode v identifikátorech nejsou v IFJ26 podporovány. 

- V jazyce mají speciální význam tato _klíčová slova_ a nelze je použít jako identifikátory: 

|**`def`**|**`do`**|**`Double`**|**`else`**|**`if`**|**`import`**|**`Int`**|**`return`**|
|---|---|---|---|---|---|---|---|
|**`String`**|**`then`**|**`Unit`**|**`val`**|**`var`**|**`while`**|||
|**`Boolean`**|**`case`**|**`class`**|**`extension`**|**`for`**|**`List`**|**`match`**|**`type`**|



Klíčová slova uvedená pod čarou mají speciální význam pouze v určitých rozšířeních; v základním zadání je vhodné je na místě identifikátoru nepřijímat, ale váš překladač na tyto situace nebude testován. 

- _Celočíselný literál_ typu **`Int`** je zápis číselné hodnoty v desítkové soustavě. Kladná část literálu je tvořena číslicemi, mezi dvěma číslicemi smí obsahovat podtržítka, např. **`1_000_000`** . Nenulový literál nesmí začínat nulou. Záporný zápis je tvořen unárním operátorem ’ **`-`** ’ (ASCII 45) a kladnou částí literálu. 

Jiné číselné soustavy a sufix **`L`** nejsou podporovány. Unární ’ **`+`** ’ je možné podporovat, ale nebude testováno. Literál obecně odpovídá svým rozsahem typu _int_ z cílového jazyka IFJcode26, není nutné provádět kontrolu na rozsah literálu, kterou dělá Scala. Chování při pod-/přetečení nebude testováno. 

- _Desetinný literál_ typu **`Double`** má podobu: 

[ _celá část_ ] **`.`** { _desetinná část_ } [ _exponent_ ] nebo { _celá část_ } { _exponent_ } 

_Celá část_ a _desetinná část_ jsou sekvence číslic. [] značí, že daná část může chybět; {} značí, že je povinná. 

_Exponent_ začíná znakem **`e`** nebo **`E`** , za kterým může následovat znaménko a musí následovat alespoň jedna číslice. Číslice mohou být odděleny podtržítky stejně jako u celočíselného literálu. Literál může ve všech případech končit nepovinnou příponou **`d`** nebo **`D`** . Rozsah a přesnost odpovídají typu IEEE 754 binary64, resp. typu _float_ v IFJcode26. Sufixy **`f`** a **`F`** podporovány nejsou. 

> 1Scala 3: `https://docs.scala-lang.org/scala3/` . 

2 

- _Řetězcový literál_ typu **`String`** je ohraničen dvojitými uvozovkami ’ **`"`** ’ (ASCII 34) a nesmí obsahovat skutečný znak konce řádku. Podporovány jsou escape sekvence **`\\`** , **`\"`** , **`\n`** , **`\r`** a **`\t`** . Žádné další escape sekvence nejsou součástí IFJ26. 

- _Víceřádkový řetězcový literál_ je ohraničen trojicí dvojitých uvozovek ’ **`"""`** ’. Obsahuje doslova všechny znaky mezi ohraničeními, včetně znaků nového řádku; escape sekvence se v něm nevyhodnocují. Například v kódu 

```
valx="""A
hojs\nvete
"""
```

bude hodnota **`x`** ekvivalentní s jednořádkovým literálem `"A\n hoj s\\nvete\n "` . 

- Literál hodnoty typu **`Unit`** (viz sekci 1.3 níže) se zapisuje **`()`** . 

- _Řádkový komentář_ začíná dvojicí lomítek **`//`** a končí s koncem řádku. Obsah komentáře je ignorován. Pro účely syntaktické analýzy je komentář posuzován jako jeden konec řádku. 

- _Blokový komentář_ je ohraničen dvojicemi **`/*`** a **`*/`** ; blokové komentáře mohou být **vnořené** . Pokud uvnitř blokového komentáře není žádný znak nového řádku, komentář se chová jako jeden bílý znak (odděluje tokeny). V opačném případě se chová jako jeden konec řádku a za jeho koncem **nesmí** být další tokeny (očekává se zde konec řádku, kterému mohou předcházet jen bílé znaky). 

Neznámý znak, literál mimo povolený rozsah, neukončený řetězec či komentář (vč. vnořeného) a chybná escape sekvence vedou na lexikální chybu 1. 

## **1.2 Odsazení, konce příkazů a čárky** 

_Fyzickým řádkem_ se rozumí sekvence znaků zakončená znakem LF (ASCII 10), příp. koncem souboru (EOF). _Logickým řádkem_ je sekvence znaků zakončená znakem LF (nebo EOF) mimo závorky, víceřádkové řetězcové literály a blokové komentáře. Znak LF uvnitř závorek se považuje za bílý znak, ale nemá funkci konce řádku ve smyslu syntaxe. Fyzické řádky, které jsou pouze prázdné, obsahují jen bílé znaky či komentáře, jsou ignorovány. 

IFJ26 nepodporuje složené závorky pro ohraničení bloků. Bloky jsou vymezeny výhradně _odsazením_ . Pro odsazení se používají pouze mezery (tabulátor na začátku neprázdného řádku je lexikální chyba 1). Prázdné řádky a řádky tvořené jen bílými znaky nemění aktuální úroveň odsazení. Míra odsazení logického řádku se určí jako počet mezer na začátku jeho prvního fyzického řádku. Uvnitř závorek musí po fyzickém konci řádku být následující řádek odsazen více než začátek příslušného logického řádku. 

Každý logický řádek obsahuje jeden příkaz (příp. více příkazů oddělených středníkem), definici funkce, anotaci **`@main`** , prolog, v rozšířeních dále jednu větev **`case`** nebo jeden generátor či stráž příkazu **`for`** . Neukončený výraz nemůže pokračovat na dalším logickém řádku. Logický řádek nemůže začínat operátorem. 

Po hlavičce syntaktické konstrukce, která umožňuje otevřít blok, následuje znak konce řádku. Blok poté začíná na dalším logickém řádku, který musí být odsazen více než logický řádek s hlavičkou. Všechny příkazy uvnitř bloku pak mají stejné odsazení. Bloky nemohou být prázdné a nemohou začínat uvnitř závorek. 

Příkazy jsou odděleny buď tak, že leží na samostatných logických řádcích, nebo uvnitř jednoho logického řádku středníkem (který je tak v roli separátoru). Za posledním příkazem bloku nebo 

3 

před koncem souboru není další oddělovač nutný. 

Za poslední položkou neprázdného seznamu parametrů, argumentů, prvků seznamu nebo atributů datové třídy je povolena _koncová čárka_ , pouze pokud je následujícím tokenem uzavírací závorka a mezi čárkou a touto závorkou je znak konce řádku. Mezi nimi mohou být pouze bílé znaky a komentáře. 

## **1.3 Datové typy** 

Jazyk podporuje v základním zadání právě následující typy: 

- **`Int`** 32bitové celé číslo se znaménkem. Celočíselné operace mají stejnou sémantiku přetečení jako Scala. 

**`Double`** 64bitové desetinné číslo dle IEEE 754. 

**`String`** nemodifikovatelný řetězec znaků; v IFJ26 se uvažují pouze znaky ASCII. 

- **`Unit`** typ s jedinou skutečnou hodnotou **`()`** . Obvykle se využívá jako návratový typ funkce, která nevrací žádnou smysluplnou hodnotu (obdobně jako void v jazyce C). Lze jej však použít i jako typ proměnné či parametru. 

Interně existuje také typ **`Boolean`** , který reprezentuje hodnotu relačních výrazů v podmínkách (viz také sekci 3). V základním zadání jej však nelze použít jako typ proměnné či parametru. Jako plnohodnotný typ jazyka je dostupný až v rozšíření BOOLTHEN. 

IFJ26 provádí jedinou implicitní konverzi: rozšíření **`Int`** na **`Double`** . Opačná implicitní konverze neexistuje (použití hodnoty typu **`Double`** na místě očekávajícím hodnotu typu **`Int`** povede na typovou chybu 6). 

# **2 Struktura programu** 

Program začíná povinným _prologem_ : 

```
importifj26.*
```

Před prologem mohou být pouze bílé znaky a komentáře. Prolog musí být uveden právě jednou a musí mít přesně uvedený tvar (s libovolnými bílými znaky mezi tokeny). Pro překladač IFJ26 nemá tento řádek sémantický význam; při překladu překladačem Scala zpřístupní kompatibilní implementace vestavěných funkcí. Absence prologu povede na syntaktickou chybu 2. 

Za prologem následují pouze definice funkcí na nejvyšší úrovni (viz sekci 2.3). 

**Vstupní funkce:** Právě jedna funkce musí být označena anotací **`@main`** . Znak **`@`** se v jiném kontextu nepoužívá, mezi ním a klíčovým slovem **`main`** nesmí být žádný znak. Anotace může být na samostatném řádku nebo na stejném řádku s klíčovým slovem **`def`** . Identifikátor vstupní funkce je libovolný platný identifikátor. Vstupní funkce nesmí mít žádný parametr a její výsledný typ musí být **`Unit`** . Chybějící vstupní funkce vede na chybu 3, více vstupních funkcí na chybu 4, přítomnost parametru na chybu 5 a jiný návratový typ na chybu 6. 

4 

```
importifj26.*
deffactorial(n:Int):Int=
varresult=1
vari:Int=n//uvedenítypujenepovinné
whilei>1do
result=result*i
i=i-1
result//poslednívýrazvtělefunkceurčínávratovouhodnotu
@maindefrunFoo():Unit=
valn=readInt()
valresult=factorial(n)
print(result)
print("\n")
```

## **2.1 Blok** 

**Blok** je odsazená sekvence otevřená na místě povoleném syntaxí (např. za hlavičkou funkce, podmínky, cyklu). Obsahem bloku jsou **příkazy** . Příkazy se v bloku provádějí postupně shora dolů. Jazyk dle základního zadání obsahuje příkazy definice proměnné, přiřazení, volání funkce, návratu z funkce, podmíněný příkaz **`if`** a cyklus **`while`** . Příkazem je také samostatně stojící vyhodnocení výrazu. 

Blok musí mít vždy tělo. Pro zápis bloku, který neobsahuje žádný efektivní příkaz, je možné jako tělo využít např. výraz tvořený samostatným literálem **`()`** : 

```
ifx<5then
print("prilismalo")
else
()
```

## **2.2 Proměnné a rozsahy platnosti** 

**Příkaz definice proměnné** : Nemodifikovatelná proměnná se definuje klíčovým slovem **`val`** , modifikovatelná klíčovým slovem **`var`** . Inicializace je vždy povinná: 

**`val`** _id_ [ **`:`** _typ_ ] **`=`** _výraz-nebo-volání_ **`var`** _id_ [ **`:`** _typ_ ] **`=`** _výraz-nebo-volání_ 

Proměnnou je v základním zadání možné inicializovat _výrazem_ (viz sekci 3) nebo _voláním funkce_ (viz sekci 2.3). Není-li uveden typ, staticky se odvodí z typu inicializace. Nelze-li jej jednoznačně odvodit, nastane chyba 6. Je-li typ uveden, musí s ním být výsledek inicializace kompatibilní. 

**Příkaz přiřazení** má tvar: 

_id_ **`=`** _výraz-nebo-volání_ 

Levá strana musí označovat dříve definovanou modifikovatelnou proměnnou (jinak chyba 7). 

Typ proměnné je po celou dobu její platnosti neměnný. Pokus o přiřazení hodnoty jiného typu povede na chybu 6. 

Lokální proměnná je viditelná od místa definice do konce bloku a ve všech jeho podblocích. V podbloku lze _překrýt_ (angl. _shadowing_ ) proměnnou nadřazeného bloku novou definicí stejného jména. 

5 

Opakovaná definice ve stejném bloku vede na chybu 4. Použití proměnné před definicí nebo mimo její rozsah vede na chybu 3. 

## **2.3 Definice a volání funkcí** 

Funkce se deklaruje a zároveň definuje buď v jednořádkovém tvaru: 

**`def`** _id_ **`(`** _parametry_ **`)`** [ **`:`** _návratový-typ_ ] **`=`** _výraz-nebo-volání_ 

nebo ve víceřádkovém tvaru: 

**`def`** _id_ **`(`** _parametry_ **`)`** [ **`:`** _návratový-typ_ ] **`=`** _odsazený-blok_ 

Každý formální parametr má tvar _id_ **`:`** _typ_ . Parametry jsou odděleny čárkami (viz také sekci 1.2), jsou předávány hodnotou a v těle se chovají jako nemodifikovatelné lokální proměnné. Návratový typ v některých případech není nutné uvádět (viz níže). 

Přetěžování funkcí (angl. _overloading_ ) není podporováno; dvě definice stejného jména vedou na chybu 4. 

Funkci je možné volat před její lexikální definicí, podporována je i vzájemná rekurze. 

### **Návratový typ a návratová hodnota** 

_Poslední příkaz bloku_ je poslední příkaz zapsaný přímo v daném bloku (nikoli uvnitř jeho podbloků). Platí následující pravidla: 

1. **Příkaz návratu z funkce** **`return`** _výraz-nebo-volání_ ihned ukončí funkci s uvedenou hodnotou, a to i z vnořené větve či cyklu. Samostatný **`return`** vrací **`()`** a je povolen pouze ve funkci s explicitním návratovým typem **`Unit`** . 

2. Není-li proveden **`return`** , funkce vrátí _výsledek svého těla_ . Výsledkem jednořádkového těla je hodnota jeho výrazu či volání; výsledkem bloku zakončeného výrazem či voláním je hodnota tohoto posledního příkazu. Blok zakončený definicí proměnné, přiřazením nebo cyklem má výsledek **`()`** (typu **`Unit`** ). Hodnoty z těla cyklu se nepřenášejí do výsledku nadřazeného bloku. 

3. Není-li **`if`** výrazem (viz rozšíření CONTROL), může jím tělo funkce končit pouze tehdy, pokud: 

   - je návratový typ explicitně **`Unit`** ; 

   - nebo všechny větve končí návratem **`return`** ; 

   - nebo návratový typ není uveden a výsledky všech větví jsou typu **`Unit`** (odvodí se **`Unit`** ). 

Končí-li větev dalším **`if`** , stejná podmínka se ověří rekurzivně v jeho větvích. Chybějící **`else`** v rozšíření BOOLTHEN se pro toto posouzení chová jako větev s **`()`** . 

4. Ve funkci, která má v hlavičce explicitně uvedený návratový typ **`Unit`** , se návratová hodnota (určená dle kteréhokoliv pravidla) běžně vyhodnotí, ale zahodí a funkce vrací **`()`** . (To platí i pro **`return`** !) Jinak musí být každá explicitně i implicitně vracená hodnota kompatibilní s návratovým typem. 

Návratový typ musí být explicitně uveden v hlavičce, pokud dochází k přímé či nepřímé rekurzi nebo pokud se kdekoliv v těle funkce vyskytuje **`return`** . Jinak uveden být nemusí, pak se odvodí z výsledku těla podle pravidel výše. 

6 

Porušení těchto pravidel je typová chyba 6. Kontroly platí i pro nedosažitelný kód. 

### **Příkaz volání funkce** 

Volání funkce má podobu: 

_id_ **`(`** _seznam-argumentů_ **`)`** 

V základním zadání (bez rozšíření FUNEXP) je seznam argumentů tvořen pouze _termy_ , tedy literály nebo identifikátory proměnných (ne výrazy). Jejich počet a typy musí odpovídat signatuře funkce. Volání tedy v základním zadání může: 

- stát samostatně jako příkaz (výsledek se zahodí, příp. použije jako návratová hodnota ve volající funkci, pokud je posledním provedeným příkazem), 

- inicializovat proměnnou, 

- tvořit pravou stranu příkazu přiřazení, 

- tvořit tělo jednořádkové funkce, 

- vystupovat jako hodnota v příkazu návratu z funkce **`return`** . 

V základním zadání nelze použít volání funkce uvnitř výrazů. Vizte také rozšíření FUNEXP. 

## **2.4 Podmíněný příkaz** 

```
ifpodmínkathen
odsazený-blok-větve-1
else
odsazený-blok-větve-2
```

_Podmínka_ musí být relační výraz s výsledkem typu **`Boolean`** . Pokud je pravdivý, provede se první blok, jinak druhý. Část **`else`** je v základním zadání povinná. Obě větve vytvářejí samostatné rozsahy platnosti. Klíčové slovo **`else`** musí ležet na samostatném logickém řádku, který je odsazen stejně jako otevírající řádek s **`if`** . 

V základním zadání nelze **`if`** použít jako výraz. Vizte také rozšíření BOOLTHEN a CONTROL. 

## **2.5 Cyklus** **`while`** 

```
whilepodmínkado
tělo-cyklu
```

Před každou iterací se vyhodnotí relační výraz _podmínka_ . Je-li pravdivý, provede se tělo a vyhodnocení se opakuje. Tělo tvoří samostatný rozsah platnosti. 

# **3 Výrazy** 

Výrazy jsou tvořeny termy (literály či identifikátory proměnných), kulatými závorkami, unárními a binárními operátory. V základním zadání není možné uvnitř výrazu volat funkce (viz rozšíření FUNEXP). V rámci sémantické analýzy vstupního programu jsou prováděny silné typové kontroly. 

7 

### Podporovány jsou následující operátory (od nejvyšší priority): 

|**Priorita**|**Operátory**<br>|**Asociativita**|
|---|---|---|
|1|unární**`+`**<sup>2</sup>,**`-`**|pravá|
|2|**`*`**,**`/`**|levá|
|3|**`+`**,**`-`**|levá|
|4|**`<`**,**`<=`**,**`>`**,**`>=`**|bez asociativity|
|5|**`==`**,**`!=`**|bez asociativity|



Operandy se vyhodnocují zleva doprava. Při nesouladu typů operandů končí překlad s chybou 6. Celočíselné dělení nulou je běhová chyba cílového jazyka; desetinné dělení nulou se chová v souladu s příslušnou instrukcí jazyka IFJcode26. 

**Aritmetické operátory:** Operátory **`+`** , **`-`** a **`*`** nad dvěma hodnotami **`Int`** vracejí **`Int`** ; je-li alespoň jeden operand **`Double`** , druhý se případně implicitně převede a výsledkem je **`Double`** . Dělení dvou hodnot **`Int`** je celočíselné a zaokrouhluje k nule, dělení s alespoň jedním operandem **`Double`** je desetinné dle IEEE 754. Unární operátory lze použít jen na číselnou hodnotu a nemění její typ. 

**Konkatenace:** Operátor **`+`** nad dvěma hodnotami **`String`** provádí konkatenaci. Automatická konverze jiných operandů na řetězec není v IFJ26 povolena (je nutné nejprve použít funkci **`toStr`** ). 

**Relační (porovnávací) operátory:** Operátory **`<`** , **`<=`** , **`>`** a **`>=`** porovnávají dvě číselné hodnoty (s případnou konverzí **`Int`** na **`Double`** ) nebo dva řetězce lexikograficky. Operátory **`==`** a **`!=`** porovnávají hodnoty stejných typů nebo dvě číselné hodnoty. Řetězení relačních operátorů není povoleno. Bez rozšíření BOOLTHEN lze pravdivostní výsledek použít pouze přímo v podmínce **`if`** nebo **`while`** ; nelze jej uložit, předat ani vrátit. 

# **4 Vestavěné funkce** 

Překladač bude poskytovat několik základních vestavěných funkcí, které bude možné využít v programech v jazyce IFJ26. Pro generování kódu vestavěných funkcí je vhodné (a obvykle nutné) využít specializovaných instrukcí jazyka IFJcode26. Při použití špatného typu termu v parametrech vestavěných funkcí dochází k chybě 5. 

Zástupný typ **_`Any`_** znamená, že je na místě příslušného parametru možné využít hodnotu libovolného typu. 

- **`print(value:`** **_`Any`_** **`): Unit`** Vypíše právě jednu hodnotu na standardní výstup bez oddělovače a bez znaku nového řádku. Hodnoty typu **`Int`** , **`Double`** , **`String`** se vypisují v souladu s instrukcí **WRITE** jazyka IFJcode26; hodnota **`()`** typu **`Unit`** se vypíše jako řetězec `"()"` . 

- **`readLine(): String`** Načte jeden řádek standardního vstupu (čte znaky až do dosažení znaku konce řádku LF nebo konce souboru EOF) a vrátí jej včetně ukončovacího znaku řádku (pokud je použita po dosažení EOF, je vrácen prázdný řetězec). Odpovídá chování instrukce **READ** jazyka IFJcode26. 

- **`readInt(): Int`** Načte celý řádek obdobně jako funkce **`readLine`** . Je-li celý řádek platným zápisem hodnoty **`Int`** v desítkové soustavě, vrátí tuto hodnotu; při EOF, překročení rozsahu nebo chybném formátu vrátí 0. Okolní bílé znaky se neignorují a podtržítka na vstupu nejsou povolena. Chování vychází z instrukce **READ** jazyka IFJcode26 (ta však při chybném vstupu či EOF vrací hodnotu _nil_ ). 

> 2Unární plus není nutné podporovat, nebude testováno. 

8 

**`readDouble(): Double`** Obdobně jako **`readInt`** načte desetinnou hodnotu typu **`Double`** . 

- **`toStr(value:`** **_`Any`_** **`): String`** Vrátí řetězcovou reprezentaci termu _value_ . Do řetězců jsou hodnoty tisknuty obdobně jako ve funkci **`print`** – s rozdílem, že desetinné hodnoty vždy tiskne ve formátu odpovídajícím specifikátoru `"%.2f"` (v souladu s instrukcí **FLOAT2STR** ). 

- **`toInt(value: Double): Int`** Vrátí celé číslo, které vznikne oseknutím desetinné části argumentu převedením výsledku na typ **`Int`** . 

**`strLength(value: String): Int`** Vrátí počet znaků řetězce. 

- **`subStr(value: String, start: Int, end: Int): String`** Vrátí podřetězec zadaného řetězce **`value`** . Parametrem **`start`** je dán index začátku požadovaného podřetězce (počítáno od nuly) a parametr **`end`** určuje index za posledním znakem podřetězce. Program končí s běhovou chybou 40, nastane-li některý z těchto případů: 

   - **`start`** < 0 

   - **`end`** < 0 

   - **`start`** > **`end`** 

   - **`start`** ≥ **`strLength(value)`** 

   - **`end`** > **`strLength(value)`** 

- **`ord(value: String, index: Int): Int`** Vrátí ASCII kód znaku na zadaném indexu. Je-li řetězec prázdný nebo index mimo rozsah, vrátí -1. 

- **`chr(code: Int): String`** Pro hodnotu v intervalu 0 až 127 vrátí jednoznakový řetězec s odpovídajícím ASCII kódem. Jiná hodnota vede na běhovou chybu (dle odpovídající instrukce IFJcode26). 

Špatný počet argumentů nebo nesprávný typ argumentu vestavěné či uživatelské funkce vede na chybu 5. 

## **4.1 Doporučení k testování – kompatibilita se Scalou** 

Programovací jazyk IFJ26 je schválně navržen tak, aby byl (téměř) kompatibilní s podmnožinou jazyka Scala. Pokud si nejste jistí, co by měl cílový kód přesně vykonat pro nějaký zdrojový kód jazyka IFJ26, můžete si to ověřit pomocí překladače `scala` (s dodatečnou konfigurací např. na serveru Merlin). 

Z e-learningu si stáhněte soubor `ifj26.scala` , který obsahuje balíček `ifj26` s výše popsanými funkcemi – doplňuje tak kompatibilitu IFJ26 s překladačem Scala 3.8.4. Program v jazyce IFJ26 pak můžete přeložit, pokud překladači předáte cestu k souboru `ifj26.scala` . Program v jazyce IFJ26 uložený v souboru `prog.scala` lze provést (přeložit a rovnou spustit) pomocí příkazu<sup>3</sup> : 

```
scalarunifj26.scalaprog.scala
```

Tím lze jednoduše zkontrolovat, co by měl provést zadaný zdrojový kód (resp. co by při interpretaci měl vykonávat vygenerovaný cílový kód). Je ale potřeba si uvědomit, že jazyk Scala je nadmnožinou jazyka IFJ26, a tudíž může zpracovat i konstrukce, které nejsou v IFJ26 vyžadované či povolené (např. bohatší syntaxe a sémantika většiny příkazů, či dokonce zpětné nekompatibility). Pokud narazíme na významnou odlišnost, uvedeme ji v e-learningu IFJ. Typicky platí, že oceňujeme podporu různých funkcí a konstrukcí jazyka Scala, které jsou nad rámec zadání IFJ26, ale je vhodné to radši konzultovat na fóru. 

> 3Na serveru Merlin je nutná dodatečná konfigurace JVM, více informací najdete v e-learningu. 

9 

# **5 Rozšíření** 

Rozšíření jsou povinně volitelnou částí projektu (tj. pro získání plného počtu bodů je nutné některá z nich implementovat). Implementovaná rozšíření se uvádějí v dokumentaci způsobem popsaným v hlavním zadání �. Každé rozšíření níže přidává jistou popsanou podmnožinu funkcionality jazyka Scala. Uvedené závislosti mezi rozšířeními jsou závazné. Pokud se překrývá funkcionalita dvou implementovaných rozšíření, musí fungovat i jejich smysluplné kombinace. Pokud není něco jasné, doporučujeme seznámit se nejprve s příslušnou funkcionalitou jazyka Scala a pak případně konzultovat na fóru. 

## **5.1 FUNEXP – funkce ve výrazech** 

### _až 1,5 bodu_ 

Volání vestavěné i uživatelské funkce může být součástí výrazu. Argumentem funkce může být libovolný výraz. Volání lze vnořovat a argumenty se vyhodnocují zleva doprava. Například: 

```
valresult=2*factorial(readInt()+1)
print(toStr(result+strLength(subStr("abcd",1,3))))
```

## **5.2 BOOLTHEN – pravdivostní hodnoty** 

### _až 1 bod_ 

Rozšíření přidává typ **`Boolean`** , literály **`true`** a **`false`** , unární negaci **`!`** a binární operátory **`&&`** a **`||`** . Operátor **`!`** má vyšší prioritu než násobení, **`&&`** má nižší prioritu než relační operátory a **`||`** ještě nižší. Binární booleovské operátory se vyhodnocují zkratově zleva doprava. Jejich operandy musí být typu **`Boolean`** . 

Pravdivostní hodnotu lze ukládat, předávat, vracet, porovnávat operátory **`==`** a **`!=`** . **`toStr`** pro argument typu **`Boolean`** vrací **`"true"`** nebo **`"false"`** , **`print`** obdobným způsobem hodnotu vypíše. Podporujte také vestavěnou funkci **`readBoolean`** (obdoba k ostatním funkcím pro čtení ze vstupu, odpovídá chování instrukce READ v IFJcode26). Podmínkou v příkazech **`if`** a **`while`** může být libovolný výraz typu **`Boolean`** . 

Dále podporujte zkrácený podmíněný příkaz, tj. bez povinné části **`else`** , a rozšířený podmíněný příkaz s větvemi **`else if`** (musí být zarovnáno s **`if`** ): 

```
ifx<0then
print("negative")
elseifx==0then
print("zero")
```

10 

## **5.3 CONTROL – rozšířené řídicí struktury** 

_až 1,5 bodu; vyžaduje BOOLTHEN_ 

Podmíněný příkaz **`if`** lze použít také jako **výraz** ; v tom případě je větev **`else`** povinná a typy výsledků obou větví musí být shodné (příp. s implicitní konverzí). Výsledkem je hodnota provedené větve. Zároveň podporujte použití jednořádkových těl všech větví (tedy místo bloku). 

```
varx=-5
valabsolute=ifx<0then0-xelsex//v'absolute'jehodnota5
//ukázkyrůznýchkombinacíjednořádkovýchtělabloků
valabs2=ifx<0then
0-x
else
x
//
valabs3=ifx<0then0-xelse
x
```

Dále podporujte cyklus **`for`** s jedním _generátorem_ a libovolným počtem _stráží_ ( _guards_ , viz dokumentace Scaly<sup>4</sup> ). Zdrojem generátoru může být celočíselný rozsah: 

- _from_ **`to`** _to_ – oba krajní body jsou zahrnuty, 

- _from_ **`until`** _until_ – pravý krajní bod zahrnut není, 

- _from_ **`to`** _to_ **`by`** _step_ – inkluzivní rozsah s nenulovým krokem (překladač kontroluje nenulovost alespoň pro literály; pokud je na místě kroku složitější výraz, je nutné generovat kód, který při nulovém kroku ukončí program s chybou 40). 

Všechny meze i krok jsou výrazy typu **`Int`** (jinak chyba 6) a vyhodnotí se právě jednou před první iterací. Řídicí proměnná je nová nemodifikovatelná proměnná **`Int`** platná v těle cyklu. Stráž začíná slovem **`if`** a musí být typu **`Boolean`** . Jednořádkový a víceřádkový zápis mají tvar: 

```
fori<-1to10by2do
print(i)
vallimit=10
for
i<-0untillimit
ifi!=3
ifi<8
do
print(i)
```

Ve víceřádkovém zápisu musí být generátor a stráže na větší úrovni odsazení než klíčové slovo **`for`** . Každý generátor musí být na samostatném logickém řádku, všechny musí být zarovnané. Klíčové slovo **`do`** má pak stejnou úroveň odsazení jako **`for`** a otvírá blok s tělem cyklu, případně může v obou variantách následovat přímo jednořádkové tělo (podobně jako u **`if`** ). 

Je-li implementováno rozšíření LISTS, může být zdrojem generátoru hodnota typu **`List[T]`** . 

Více generátorů, definice uvnitř hlavičky a klíčové slovo **`yield`** nejsou podporovány. Stejně tak není nutné podporovat cyklus **`for`** na místě výrazu; ani ukládání generátoru do proměnné. 

> 4 `https://docs.scala-lang.org/scala3/book/taste-control-structures.html# for-loops-and-expressions` 

11 

## **5.4 VALMEM – členy hodnot** 

_až 0,5 bodu_ 

Rozšíření zpřístupňuje alternativní volání bezparametrických vestavěných funkcí na hodnotách s využitím standardní tečkové notace: 

_výraz_ **`.`** _id_ 

Tento zápis tvoří výraz. Podporovány jsou právě následující _členy_ : 

|_příjemce_|_člen_|_typ výsledku_|
|---|---|---|
|libovolná hodnota|**`toString`**|**`String`**|
|hodnota typu**`Double`**|**`toInt`**|**`Int`**|
|hodnota typu**`Double`**|**`floor`**|**`Double`**|
|hodnota typu**`String`**|**`length`**|**`Int`**|



Uvedené členy se zapisují bez prázdného seznamu argumentů, např. **`"abc".length`** . Podporováno je také řetězení: **`number.floor.toInt`** . 

Použití jiného členu není podporováno (mimo případy, kdy to přímo vyplývá z jiného rozšíření, např. LISTS nebo EXTKW). 

**Upozornění:** Pro desetinná čísla má vestavěná funkce **`toStr`** , a tedy i člen **`.toString`** , jiné chování než jazyk Scala – tedy např. hodnota výrazu `(1.2345).toString` bude při překladu Scalou `"1.2345"` , ale při interpretaci výstupu vašeho překladače bude `"1.23"` . 

## **5.5 ALGEBDT – sjednocení, součiny a** **`match`** 

### _až 2 body_ 

Rozšíření přidává základní algebraické datové typy. _Sjednocení typů_ se zapisuje 𝑇1 **`|`** 𝑇2; jeho hodnotou může být hodnota kteréhokoli členského typu: 

```
typeScalar=Int|Double|String
deffoo(x:Double|String):String=
returntoStr(x)
@main
defmain():Unit=
varanything:Scalar=5
anything="hello"
foo(5)//"5"
foo(anything)//typováchyba!
```

Členským typem může být libovolný typ, který vaše implementace překladače podporuje (vč. dříve zadefinovaných sjednocení typů). 

Sjednocení musí být v místě vzniku uvedeno explicitně jako typ proměnné, parametru nebo výsledku funkce; automatické odvození sjednocení se nevyžaduje. Na nejvyšší úrovni (mezi funkcemi, tj. s globálním rozsahem platnosti) je možné definovat alias pro sjednocení typů pomocí klíčového slova **`type`** . 

_Součinový typ_ se definuje syntaxí _datové třídy_ : 

```
caseclassPoint(x:Int,y:Int)
```

12 

Parametry jsou nemodifikovatelné veřejné atributy. Hodnota se vytvoří voláním **`Point(10, 20)`** . Přístup k hodnotě atributu má syntaxi standardní tečkové notace, např. **`point.x`** . 

Vlastní tělo, metoda **`copy`** , metody, modifikovatelné atributy, dědičnost, typové parametry a výchozí hodnoty při definici datové třídy nejsou povoleny (resp. nejsou vyžadovány, nebudou testovány). Chování při použití ve funkcích **`print`** a **`toStr`** není definováno. 

Dále podporujte základní výraz **`match`** , který porovnává hodnotu postupně se _vzory_ ve větvích **`case`** ; vyhodnotí se _výraz_ v první odpovídající větvi a jeho hodnota je výsledkem. Podporovány jsou: 

- literály, 

- vzor _id_ **`:`** _typ_ pro rozlišení členu sjednocení, 

- vzor konstruktoru datové třídy, např. **`Point(x, y)`** , 

- zástupný vzor **`_`** (výchozí větev – vždy uspěje), 

- nepovinná stráž **`if`** _booleovský-výraz_ za vzorem. 

```
defpointToStr(x:Int,y:Int)=
valptA=toStr(x)
valptB=toStr(y)
"point"+ptA+":"+ptB
```

```
defdescribe(value:Int|String|Point):String=
valuematch
case0=>"zero"
casen:Intifn>0=>"positive"
casetext:String=>text
casePoint(a,b)=>pointToStr(a,b)
case_=>"negative"
```

Všechny větve musí být typově kompatibilní. **`match`** musí být vyčerpávající (to znamená, že nemůže nastat situace, kdy by výraz „neměl hodnotu“): postačí implementovat tak, že výraz _vždy_ vyžaduje větev **`case _`** (ale můžete se pokusit i o komplexnější logiku v souladu s chováním Scaly). 

Stráž může být jednoduchý relační výraz i bez rozšíření BOOLTHEN; složené booleovské výrazy vyžadují BOOLTHEN. Tělem větve je běžný výraz dle schopností vašeho překladače. 

Alternativní vzory, interpolované řetězce ve vzorech, regulární výrazy, vnořené typové vzory a další speciální vlastnosti jazyka Scala nejsou podporovány. 

Dále podporujte navíc nové vestavěné funkce **`readIntMaybe`** a **`readDoubleMaybe`** , které fungují obdobně jako běžné vestavěné funkce **`readInt`** a **`readDouble`** s tím rozdílem, že jejich návratová hodnota je typu **`Int | Unit`** (resp. **`Double | Unit`** ) a v případě chybného vstupu (kdy standardní funkce vrací nulu) vrací hodnotu **`()`** . 

## **5.6 INTERPOLATEDS – interpolované řetězce** 

_až 0,5 bodu_ 

Rozšíření přidává pouze interpolátor **`s`** . V řetězci lze použít **`$id`** pro hodnotu proměnné a **`${výraz}`** pro libovolný _výraz_ dle schopností vašeho překladače (tedy např. uvnitř výrazu není nutné podporovat volání funkce, pokud neimplementujete FUNEXP). 

13 

Dvojice **`$$`** vloží jeden znak dolaru. Dvojitá uvozovka se v běžném interpolovaném řetězci zapíše jako **`\"`** . Podporovány jsou i interpolované víceřádkové řetězce, kde se dvojitá uvozovka zapisuje doslova. 

```
valname="IFJ"
valn=26
//IFJ27costs$0
print(s"$name${n+1}costs$$0")
//Hesaid"hello",IFJ.[novýřádek]Secondline.
print(s"""Hesaid"hello",$name.
Secondline.""")
```

Každá vložená hodnota se převádí stejným způsobem jako funkcí **`toStr`** . 

**Upozornění:** Pro desetinná čísla má vestavěná funkce **`toStr`** jiné chování než jazyk Scala – tedy např. hodnota výrazu `s"${1.2345}"` bude při překladu Scalou `"1.2345"` , ale při interpretaci výstupu vašeho překladače bude `"1.23"` . 

## **5.7 LAMBDAS – jednoduché anonymní funkce, funkce vyššího řádu** 

_až 2,5 bodu; vyžaduje FUNEXP_ 

Rozšíření zavádí typ funkční hodnoty **`(T1, T2, ...) =>`** _R_ (lze použít kdekoliv, kde se očekává typ). Jako hodnotu takového typu lze pak použít libovolnou běžně definovanou funkci nebo tzv. _lambda_ (anonymní) funkci. 

```
//běžnáfunkce
deffoo(x:Int)=x+5
//běžnáfunkcepřijímajícíjinoufunkcijakosvůjparametr
defbar(a:Int,f:(Int)=>Boolean)=
valresult=f(a)//volánífunkcepřijatézparametru
ifresultthen
print("fuspelo")
else
print("fneuspelo")
//funkce,covracífunkci
defgoo():(Int)=>String=
return(a:Int)=>
valstrA=toStr(a)
"cislo"+strA
@maindefmain():Unit=
valadd:(Int,Int)=>Int=
(left:Int,right:Int)=>left+right//lambda(anonymní)funkce
valpositive=(value:Int)=>value>0//vyžadujeimplementaciBOOLTHEN,
//typemje(Int)=>Boolean
valaddFive:(Int)=>Int=foo//doproměnnéjemožnépřiřaditběžnou
//funkci,alemusíbýtexplicitněotypovaná
//volánífunkcíuloženýchvproměnných
valx=add(10,8)
valy=addFive(x)
bar(y,positive)
```

V zápisu lambda funkce musí být vždy uveden typ a jméno každého parametru. Zástupné zápisy s podtržítkem nejsou vyžadovány. Lambda funkce může mít jako tělo jeden výraz nebo odsaze- 

14 

ný blok. V případě bloku však tělo lambda funkce nesmí obsahovat příkaz **`return`** . Funkce bez parametrů má typ **`() => R`** , odpovídající lambda funkce má hlavičku **`() =>`** **_`tělo`_** . 

Referenci na funkci (běžnou i anonymní) lze uložit do proměnné (běžné funkce však lze takto přiřadit jen do proměnných, které mají explicitně určený typ), předat jako parametr, vrátit z funkce a volat (viz příklad). 

Nejsou podporovány generické, kontextové, závislé ani částečné funkce. Nejsou podporovány ani uzávěry (closures), tedy uvnitř lambda funkcí nelze používat lokální proměnné z funkcí, ve kterých jsou definovány. 

## **5.8 LISTS – seznamy** 

_až 2 body; vyžaduje CONTROL a/nebo LAMBDAS spolu s BOOLTHEN_ 

Přidává nemodifikovatelný homogenní typ **`List[T]`** , kde _T_ je konkrétní typ podporovaný implementovanými rozšířeními. Jde o jediný povolený tvar použití typového argumentu; definice vlastních generických funkcí či typů zůstává zakázána. 

Seznam se vytváří zápisem **`List(v1, v2, ...)`** . Všechny prvky musí mít kompatibilní typ. Prázdný seznam vyžaduje očekávaný typ, např. **`val empty: List[Int] = List()`** . 

K položkám seznamu na jednotlivých indexech je možné přistupovat pomocí syntaxe volání funkce. Pokud je index mimo hranice seznamu, program bude za běhu ukončen s chybou 40. 

Každý seznam podporuje tyto členy: 

**`drop(n): List[T]`** zahodí prvních **`n`** prvků, 

**`take(n): List[T]`** vrátí nejvýše prvních **`n`** prvků, 

**`slice(from, until): List[T]`** vrátí prvky v daném polouzavřeném intervalu indexů, 

**`head: T`** vrátí první prvek; prázdný seznam vede na běhovou chybu, 

**`tail: List[T]`** vrátí seznam bez prvního prvku; prázdný seznam vede na běhovou chybu, 

- **`toString: String`** vrátí řetězec `"List(` _položky_ `)"` , kde _položky_ jsou jednotlivé položky ze seznamu převedené funkcí **`toStr`** na řetězec a oddělené čárkou a mezerou (viz příklad níže). Volání vestavěné funkce **`toStr`** se seznamem jako argumentem vrací totéž jako člen **`toString`** . Stejná řetězcová reprezentace je využita i při výpisu seznamu funkcí **`print`** . 

Podporována je také statická funkce **`List.range(start, end)`** a **`List.range(start, end, step)`** ; vytvoří celočíselný seznam od **`start`** včetně po **`end`** vyjma, krok nesmí být nulový (je nutné generovat kód, který při nulovém kroku ukončí program s chybou 40). 

Dále podporujte operátor **`++`** pro konkatenaci dvou seznamů (priorita stejná jako **`+`** , levá asociativita). 

Syntaxe členských metod je zde součástí LISTS a nevyžaduje VALMEM<sup>5</sup> . 

```
vallst=List.range(1,10)
valx=lst(2)
print(x)//vypíše3
```

Pokud implementujete také LAMBDAS a BOOLTHEN, musí seznam podporovat **`filter((T) => Boolean)`** , **`takeWhile((T) => Boolean)`** a **`dropWhile((T) => Boolean)`** . 

> 5Doporučujeme jej však také implementovat, když už pro to budete mít podporu v syntaxi. 

15 

```
valfoo=List(1,2,6,89,20,1)
valgoo=foo.takeWhile((x:Int)=>x<10)
//goojeseznamsprvky1,2,6
```

S CONTROL lze seznam použít jako zdroj generátoru cyklu **`for`** . Rozsahy vytvořené pomocí syntaxe generátorů **`to`** / **`until`** navíc podporují člen **`toList`** , který vrátí **`List[Int]`** se stejnými prvky: 

```
valitemsList:List[Int]=(1to5).toList
vallstStr=itemsList.toString
//lstStr=="List(1,2,3,4,5)"
```

## **5.9 EXTKW – uživatelské rozšiřující metody** 

_až 0,5 bodu_ 

Rozšíření přidává klíčové slovo **`extension`** . Na nejvyšší úrovni lze definovat jednu nebo více metod pro jeden konkrétní typ. Příjemce má tvar jediného explicitně typovaného parametru. Rozšiřující metoda se definuje stejně jako běžná funkce a volá se výhradně členským zápisem, zde už ale je nutné podporovat také argumenty funkcí. Povoleny jsou i deklarace bezparametrických metod bez závorek (v příkladu výše např. **`twice`** ), které se pak volají bez závorek. Pozor, metoda s prázdným seznamem parametrů zde není totéž jako bezparametrická metoda. 

```
extension(value:Int)
//bezparametrickámetoda
deftwice:Int=value*2
//metodasprázdnýmseznamemparametrů
deffoo():String="foo"+value.toString
//metodasjednímparametrem
defplus(other:Int):Int=value+other
//použití
defsomeFn()=
valx:Int=6
valy=x.twice
valz=x.foo()
valw=x.plus(12)
//pozor,nelze`x.foo`ani`x.twice()`
```

Syntaxe volání rozšiřujících metod je zde součástí EXTKW a nevyžaduje VALMEM<sup>6</sup> . 

Rozšiřující metoda je viditelná v celém programu bez ohledu na pořadí definice. Její jméno nesmí být pro tentýž typ definováno vícekrát. 

Pokud implementujete LISTS, není nutné podporovat `List` na místě rozšiřovaného typu. Dále není nutné podporovat další specifické funkce jazyka Scala ( **`using`** parametry, operátorové a infixové metody, atp.). 

> 6Doporučujeme jej však také implementovat, když už pro to budete mít podporu v syntaxi. 

16 

## **5.10 PARAMLISTS – funkce s větším množstvím seznamů parametrů** 

_až 0,5 bodu_ 

Rozšíření umožňuje definovat běžnou funkci bez seznamu parametrů nebo s více seznamy parametrů. Pravidla pro tělo funkce, návratovou hodnotu, odvození návratového typu a rekurzi zůstávají stejná jako v základním zadání. 

**Funkce bez seznamu parametrů** se definuje bez kulatých závorek za jménem. Volá se pouze uvedením svého jména bez kulatých závorek. Každé takové použití vyhodnotí tělo funkce znovu; nejde o proměnnou ani o uložený výsledek předchozího volání. Tento zápis se liší od funkce s jedním prázdným seznamem parametrů, např. **`def foo(): Int = 42`** , která se nadále volá jako **`foo()`** . 

Funkce s **více seznamy parametrů** se zapisuje tak, že jednotlivé seznamy jdou bezprostředně za sebou (před nepovinnou anotací návratového typu). Každý seznam je ohraničen vlastní dvojicí kulatých závorek a může být i prázdný. Jména parametrů musí být jedinečná napříč všemi seznamy dané funkce (jinak chyba 4). Všechny parametry jsou v těle dostupné jako nemodifikovatelné lokální proměnné. 

Při volání musí být uvedeny všechny seznamy argumentů ve stejném pořadí a se stejným rozdělením jako v definici. Prázdný seznam nelze vynechat. Chybný počet seznamů, chybný počet argumentů v kterémkoli seznamu nebo nekompatibilní typ argumentu vede na chybu 5. Argumenty se vyhodnocují zleva doprava, postupně od prvního seznamu k poslednímu; teprve poté se provede tělo funkce. 

```
importifj26.*
```

```
defanswer:Int=42
defanswerWithParens():Int=42
defadd(a:Int)(b:Int)(c:Int):Int=a+b+c
defoffset()(value:Int):Int=value+1
@maindefrun():Unit=
valx=answer
valy=answerWithParens()
valsum=add(x)(y)(1)
valresult=offset()(sum)
print(result)//vypíše86
```

Volání v obou nových tvarech je povoleno na stejných místech jako běžné volání funkce, nicméně funkce bez seznamu parametrů mohou být součástí výrazu či argumentem jiného volání i **bez** rozšíření FUNEXP. 

V kombinaci s EXTKW lze více seznamů použít také u rozšiřujících metod. 

Částečná aplikace, tedy volání s vynechanými koncovými seznamy argumentů, není součástí tohoto rozšíření. Neuvažujte žádnou kombinaci s rozšířením LAMBDAS. 

17 

# **6 Přehled chybových návratových kódů** 

Překladač provádí všechny typové kontroly staticky. Pokud lze pro jednu chybu rozumně použít více kategorií, má přednost konkrétnější kód uvedený níže. 

- 1 chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému, komentáře nebo odsazení). 

- 2 chyba v programu v rámci syntaktické analýzy (chybná syntaxe, chybějící prolog, nepovolená konstrukce nebo porušení struktury odsazených bloků). 

- 3 sémantická chyba – použití nedefinované funkce, proměnné nebo typu; chybějící funkce s anotací **`@main`** . 

- 4 sémantická chyba – nepovolená redefinice funkce, proměnné, typu. 

- 5 sémantická chyba – nesprávný počet nebo typ argumentů při volání funkce, nepovolené parametry funkce s anotací **`@main`** . 

- 6 sémantická chyba typové kompatibility nebo odvození typu ve výrazu, přiřazení, inicializaci, návratové hodnotě či řídicí konstrukci. 

- 7 sémantická chyba – pokus o zápis do nemodifikovatelné proměnné nebo formálního parametru funkce. 

- 10 ostatní sémantické chyby (např. nepovolený **`return`** , nevyčerpávající **`match`** nebo nulový krok rozsahu). 

- 99 interní chyba překladače neovlivněná vstupním programem (např. chyba alokace paměti). 

Celočíselné dělení nulou neošetřujte (program skončí s příslušnou chybou interpretu). Pro běhové chyby, které nelze obecně rozhodnout při překladu (index mimo řetězec, **`head`** prázdného seznamu), generujte kód, který při interpretaci skončí s návratovým kódem 40 (běhová sémantická chyba). 

# **7 Cílový jazyk IFJcode26** 

Cílový jazyk IFJcode26 je mezikódem, který zahrnuje instrukce tříadresné (typicky se třemi argumenty) a zásobníkové (typicky bez parametrů a pracující s hodnotami na datovém zásobníku). Každá instrukce se skládá z operačního kódu (klíčové slovo s názvem instrukce), u kterého nezáleží na velikosti písmen (tj. case insensitive). Zbytek instrukcí tvoří operandy, u kterých na velikosti písmen záleží (tzv. case sensitive) – to platí i pro označení datových typů a rámců (viz dále). Operandy oddělujeme libovolným nenulovým počtem mezer či tabulátorů. Odřádkování slouží pro oddělení jednotlivých instrukcí, takže na každém řádku je maximálně jedna instrukce a není povoleno jednu instrukci zapisovat na více řádků. Každý operand je tvořen proměnnou, konstantou nebo návěštím. V IFJcode26 jsou podporovány jednořádkové komentáře začínající mřížkou (#). Kód v jazyce IFJcode26 začíná úvodním řádkem s tečkou následovanou jménem jazyka: 

```
.IFJcode26
```

## **7.1 Hodnoticí interpret** **`ic26int`** 

Pro hodnocení a testování mezikódu v IFJcode26 je k dispozici interpret pro příkazovou řádku ( `ic26int` ): 

```
ic26intprg.code<prg.in>prg.out
```

Chování interpretu lze upravovat pomocí přepínačů/parametrů příkazové řádky. Nápovědu k nim získáte pomocí přepínače `--help` . 

18 

Proběhne-li interpretace bez chyb, vrací se návratová hodnota `0` (nula). Chybovým případům odpovídají následující návratové hodnoty: 

- 50 chybně zadané vstupní parametry na příkazovém řádku při spouštění interpretu. 

- 51 chyba při analýze (lexikální, syntaktické) vstupního kódu v IFJcode26. 

- 52 chyba při sémantických kontrolách vstupního kódu v IFJcode26 (redefinice symbolu či návěští; neexistující návěští vč. nenalezení při interpretaci). 

- 53 běhová chyba interpretace – špatné typy operandů. 

- 54 běhová chyba interpretace – přístup k neexistující proměnné (rámec existuje). 

- 55 běhová chyba interpretace – rámec neexistuje (např. čtení z prázdného zásobníku rámců). 

- 56 běhová chyba interpretace – chybějící hodnota (v proměnné, na datovém zásobníku, v prvku pole nebo v zásobníku volání). 

- 57 běhová chyba interpretace – špatná hodnota operandu (např. dělení nulou, špatná návratová hodnota instrukce EXIT). 

- 58 běhová chyba interpretace – chybná práce s řetězcem či polem. 

- 60 interní chyba interpretu tj. neovlivněná vstupním programem (např. chyba alokace paměti, chyba při otvírání souboru s řídicím programem atd.). 

## **7.2 Paměťový model** 

Hodnoty během interpretace nejčastěji ukládáme do pojmenovaných proměnných, které jsou sdružovány do tzv. rámců, což jsou v podstatě slovníky proměnných s jejich hodnotami. IFJcode26 nabízí tři druhy rámců: 

- globální, značíme GF (Global Frame), který je na začátku interpretace automaticky inicializován jako prázdný; slouží pro ukládání globálních proměnných; 

- lokální, značíme LF (Local Frame), který je na začátku nedefinován a odkazuje na vrcholový/aktuální rámec na zásobníku rámců; slouží pro ukládání lokálních proměnných funkcí (zásobník rámců lze s výhodou využít při zanořeném či rekurzivním volání funkcí); 

- dočasný, značíme TF (Temporary Frame), který slouží pro chystání nového nebo úklid starého rámce (např. při volání nebo dokončování funkce), jenž může být přesunut na zásobník rámců a stát se aktuálním lokálním rámcem. Na začátku interpretace je dočasný rámec nedefinovaný. 

K překrytým (dříve vloženým) lokálním rámcům v zásobníku rámců nelze přistoupit dříve, než vyjmeme později přidané rámce. 

Další možností pro ukládání nepojmenovaných hodnot je datový zásobník využívaný zásobníkovými instrukcemi. 

## **7.3 Datové typy** 

Interpret IFJcode26 pracuje s typy operandů dynamicky, takže je typ proměnné (resp. paměťového místa) dán obsaženou hodnotou. Není-li řečeno jinak, jsou implicitní konverze zakázány. Interpret podporuje speciální hodnotu/typ nil a čtyři základní datové typy (int, bool, float a string), jejichž rozsahy i přesnosti jsou kompatibilní s jazykem IFJ26. Dále podporuje heterogenní typ pole (array) fixní velikosti. Prvky pole mohou obsahovat hodnoty všech podporovaných typů (včetně referencí na stejné či jiná pole). 

Zápis každé konstanty v IFJcode26 se skládá ze dvou částí oddělených zavináčem (znak `@` ; bez bílých znaků): označení typu konstanty (int, bool, float, string, nil) a samotné konstanty (číslo, literál, nil). Příklady: `float@0x1.2666666666666p+0` , `bool@true` , `nil@nil` nebo `int@-5` . 

19 

Typ int reprezentuje 64-bitové celé číslo (rozsah C-long long int). Typ bool reprezentuje pravdivostní hodnotu (true nebo false). Typ float popisuje desetinné číslo (rozsah C-double) a v případě zápisu konstant používejte v jazyce C formátovací řetězec `'%a'` pro funkci **`printf`** . Literál pro typ string je v případě konstanty zapsán jako sekvence tisknutelných ASCII znaků (vyjma bílých znaků, mřížky `#` a zpětného lomítka `\` ) a escape sekvencí, takže není ohraničen uvozovkami. Escape sekvence, která je nezbytná pro znaky s ASCII kódem 000–032, 035 a 092, je tvaru \𝑥𝑦𝑧, kde 𝑥𝑦𝑧 je dekadické číslo v rozmezí 000–255 složené právě ze tří číslic; např. konstanta 

```
string@retezec\032s\032lomitkem\032\092\032a\010novym\035radkem
```

reprezentuje řetězec 

`retezec s lomitkem` \ `a novym#radkem` 

Pokus o práci s neexistující proměnnou (čtení nebo zápis) vede na chybu 54. Pokus o čtení hodnoty neinicializované proměnné vede na chybu 56. Pokus o interpretaci instrukce s operandy nevhodných typů dle popisu dané instrukce vede na chybu 53. 

## **7.4 Instrukční sada** 

U popisu instrukcí sázíme operační kód tučně a operandy zapisujeme pomocí neterminálních symbolů v úhlových závorkách. Neterminál ⟨ _var_ ⟩ značí proměnnou, ⟨ _symb_ ⟩ konstantu nebo proměnnou. ⟨ _label-literal_ ⟩ značí návěští (v podobě literálu). ⟨ _label_ ⟩ značí literál návěští _nebo_ řetězcový literál _nebo_ proměnnou, která obsahuje řetězec – v tomto případě daná instrukce použije hodnotu řetězce (s interpretovanými escape sekvencemi) jako cílové návěští. 

Identifikátor proměnné se skládá ze dvou částí oddělených zavináčem (znak `@` ; bez bílých znaků), označení rámce LF, TF nebo GF a samotného jména proměnné (sekvence libovolných alfanumerických a speciálních znaků bez bílých znaků začínající písmenem nebo speciálním znakem, kde speciální znaky jsou: `_` , `-` , `$` , `&` , `%` , `*` , `!` , `?` ). Např. `GF@_x` značí proměnnou `_x` uloženou v globálním rámci. 

Na zápis návěští se vztahují stejná pravidla jako na jméno proměnné (tj. část identifikátoru za zavináčem). 

Instrukční sada nabízí instrukce pro práci s proměnnými v rámcích, různé skoky, operace s datovým zásobníkem, aritmetické, operace s poli, řetězcové, logické a relační operace, dále také konverzní, vstupně/výstupní a ladicí instrukce. 

Pole (typ array) je reprezentováno referencí (obdoba ukazatele). Referenci lze ukládat na zásobník nebo kopírovat mezi proměnnými pomocí instrukce MOVE. Pomocí EQ nebo podmíněných skoků lze porovnat, zda dvě reference ukazují na stejné pole. Nad referencí jinak není možné provádět žádné aritmetické operace či porovnání LT/GT. Pole zůstávají v paměti, dokud jsou dosažitelná z datového zásobníku či z proměnných, a to i přes reference v prvcích jiných polí. Nedosažitelná pole jsou automaticky uvolňována. 

### **7.4.1 Práce s rámci, volání funkcí** 

**MOVE** ⟨ _var_ ⟩⟨ _symb_ ⟩ Přiřazení hodnoty do proměnné Zkopíruje hodnotu ⟨ _symb_ ⟩ do ⟨ _var_ ⟩. Např. `MOVE LF@par GF@var` provede zkopírování hodnoty proměnné `var` v globálním rámci do proměnné `par` v lokálním rámci. 

20 

### **CREATEFRAME** 

Vytvoř nový dočasný rámec 

Vytvoří nový dočasný rámec a zahodí případný obsah původního dočasného rámce. 

**PUSHFRAME** Přesun dočasného rámce na zásobník rámců 

Přesune TF na zásobník rámců. Rámec bude k dispozici přes LF a překryje původní rámce na zásobníku rámců. TF bude po provedení instrukce nedefinován a je třeba jej před dalším použitím vytvořit pomocí CREATEFRAME. Pokus o přístup k nedefinovanému rámci vede na chybu 55. 

**POPFRAME** Přesun aktuálního rámce do dočasného 

Přesune vrcholový rámec LF ze zásobníku rámců do TF. Pokud žádný rámec v LF není k dispozici, dojde k chybě 55. 

**DEFVAR** ⟨ _var_ ⟩ Definuj novou proměnnou v rámci 

Definuje proměnnou v určeném rámci dle ⟨ _var_ ⟩. Tato proměnná je zatím neinicializovaná a bez určení typu, který bude určen až přiřazením nějaké hodnoty. 

### **CALL** ⟨ _label_ ⟩ 

Skok na návěští s podporou návratu 

Uloží inkrementovanou aktuální pozici z interního čítače instrukcí do zásobníku volání a provede skok na zadané návěští (případnou přípravu rámce musí zajistit jiné instrukce). 

### **RETURN** 

Návrat na pozici uloženou instrukcí CALL 

Vyjme pozici ze zásobníku volání a skočí na tuto pozici nastavením interního čítače instrukcí (úklid lokálních rámců musí zajistit jiné instrukce). Provedení instrukce při prázdném zásobníku volání vede na chybu 56. 

### **7.4.2 Práce s datovým zásobníkem** 

Operační kód zásobníkových instrukcí je zakončen písmenem „S“. Zásobníkové instrukce načítají chybějící operandy z datového zásobníku a výslednou hodnotu operace ukládají zpět na datový zásobník. 

**PUSHS** ⟨ _symb_ ⟩ Vlož hodnotu na vrchol datového zásobníku 

Uloží hodnotu ⟨ _symb_ ⟩ na datový zásobník. 

**POPS** ⟨ _var_ ⟩ Vyjmi hodnotu z vrcholu datového zásobníku 

Vyjme hodnotu ze zásobníku a uloží ji do proměnné ⟨ _var_ ⟩. Pokud je zásobník prázdný, dojde k chybě 56. 

**CLEARS** Vymazání obsahu celého datového zásobníku 

Smaže celý obsah datového zásobníku (např. aby neobsahoval zapomenuté hodnoty z předchozích výpočtů). 

### **7.4.3 Aritmetické, relační, booleovské a konverzní instrukce** 

V této sekci jsou popsány tříadresné i zásobníkové verze instrukcí pro klasické operace pro výpočet výrazu. Zásobníkové verze instrukcí z datového zásobníku vybírají operandy se vstupními hodnotami dle popisu tříadresné instrukce od konce (tj. typicky nejprve ⟨ _symb_ 2⟩ a poté ⟨ _symb_ 1⟩). 

21 

**ADD** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ 

Součet dvou číselných hodnot 

Sečte ⟨ _symb_ 1⟩ a ⟨ _symb_ 2⟩ (musí být stejného číselného typu int nebo float) a výslednou hodnotu téhož typu uloží do proměnné ⟨ _var_ ⟩. 

**SUB** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Odečítání dvou číselných hodnot 

Odečte ⟨ _symb_ 2⟩ od ⟨ _symb_ 1⟩ (musí být stejného číselného typu int nebo float) a výslednou hodnotu téhož typu uloží do proměnné ⟨ _var_ ⟩. 

**MUL** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Násobení dvou číselných hodnot Vynásobí ⟨ _symb_ 1⟩ a ⟨ _symb_ 2⟩ (musí být stejného číselného typu int nebo float) a výslednou hodnotu téhož typu uloží do proměnné ⟨ _var_ ⟩. 

**DIV** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Dělení dvou desetinných hodnot Podělí hodnotu ze ⟨ _symb_ 1⟩ druhou hodnotou ze ⟨ _symb_ 2⟩ (oba musí být typu float) a výsledek přiřadí do proměnné ⟨ _var_ ⟩ (též typu float). Dělení nulou způsobí chybu 57. 

**IDIV** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Dělení dvou celočíselných hodnot 

Celočíselně podělí hodnotu ze ⟨ _symb_ 1⟩ druhou hodnotou ze ⟨ _symb_ 2⟩ (musí být oba typu int) a výsledek (zaokrouhlený k nule) přiřadí do proměnné ⟨ _var_ ⟩ typu int. Dělení nulou způsobí chybu 57. 

**ADDS/SUBS/MULS/DIVS/IDIVS** Zásobníkové verze aritmetických instrukcí 

**LT/GT/EQ** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Relační operátory menší, větší, rovno Instrukce vyhodnotí relační operátor mezi ⟨ _symb_ 1⟩ a ⟨ _symb_ 2⟩ (stejného typu; int, bool, float nebo string) a do booleovské proměnné ⟨ _var_ ⟩ zapíše false při neplatnosti nebo true v případě platnosti odpovídající relace. Řetězce jsou porovnávány lexikograficky a false je menší než true. Pro výpočet neostrých nerovností lze použít AND/OR/NOT. S operandem typu nil (druhý operand je libovolného typu) lze porovnávat pouze instrukcí EQ, jinak chyba 53. EQ navíc umožňuje porovnávat, zda dvě hodnoty typu array (reference) ukazují na stejné pole. 

**LTS/GTS/EQS** Zásobníkové verze relačních instrukcí 

**AND/OR/NOT** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ 

Základní booleovské operátory 

Aplikuje konjunkci (logické A)/disjunkci (logické NEBO) na operandy typu bool ⟨ _symb_ 1⟩ a ⟨ _symb_ 2⟩ nebo negaci na ⟨ _symb_ 1⟩ (NOT má pouze 2 operandy) a výsledek typu bool zapíše do ⟨ _var_ ⟩. 

**ANDS/ORS/NOTS** Zásobníkové verze booleovských instrukcí 

**INT2FLOAT** ⟨ _var_ ⟩⟨ _symb_ ⟩ Převod celočíselné hodnoty na desetinnou Převede celočíselnou hodnotu ⟨ _symb_ ⟩ na desetinné číslo a uloží jej do ⟨ _var_ .⟩ 

**FLOAT2INT** ⟨ _var_ ⟩⟨ _symb_ ⟩ Převod desetinné hodnoty na celočíselnou (oseknutí) Převede desetinnou hodnotu ⟨ _symb_ ⟩ na celočíselnou oseknutím desetinné části a uloží ji do ⟨ _var_ .⟩ 

22 

**INT2CHAR** ⟨ _var_ ⟩⟨ _symb_ ⟩ 

Převod celého čísla na znak 

Číselná hodnota ⟨ _symb_ ⟩ je dle ASCII převedena na znak, který tvoří jednoznakový řetězec přiřazený do ⟨ _var_ ⟩. Je-li ⟨ _symb_ ⟩ mimo interval ⟨0; 127⟩, dojde k chybě 58. 

**STRI2INT** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Ordinální hodnota znaku 

Do ⟨ _var_ ⟩ uloží ordinální hodnotu znaku (dle ASCII) v řetězci ⟨ _symb_ 1⟩ na pozici ⟨ _symb_ 2⟩ (indexováno od nuly). Indexace mimo daný řetězec vede na chybu 58. 

**FLOAT2STR** ⟨ _var_ ⟩⟨ _symb_ ⟩ Převod desetinné hodnoty na řetězec Převede desetinnou hodnotu ⟨ _symb_ ⟩ na řetězec a uloží jej do ⟨ _var_ .⟩ Hodnota je převedena v souladu s chováním vestavěné funkce **`toStr`** jazyka IFJ26. 

**INT2STR** ⟨ _var_ ⟩⟨ _symb_ ⟩ Převod celočíselné hodnoty na řetězec 

Převede celočíselnou hodnotu ⟨ _symb_ ⟩ na řetězec a uloží jej do ⟨ _var_ .⟩ Hodnota je převedena v souladu s chováním vestavěné funkce **`toStr`** jazyka IFJ26. 

**INT2FLOATS/FLOAT2INTS/** Zásobníkové verze konverzních instrukcí **INT2CHARS/STRI2INTS/ FLOAT2STRS/INT2STRS** 

### **7.4.4 Vstupně-výstupní instrukce** 

**READ** ⟨ _var_ ⟩⟨ _type_ ⟩ Načtení hodnoty ze standardního vstupu 

Načte jednu hodnotu dle zadaného typu ⟨ _type_ ⟩∈{int, float, string, bool} a uloží tuto hodnotu do proměnné ⟨ _var_ ⟩. Podporované hodnoty typu float odpovídají funkci `strtod` jazyka C (kromě nan, inf; i se znaménkem). Formát hodnot je kompatibilní s chováním vestavěných funkcí **`readLine`** , **`readInt`** , **`readDouble`** (a příp. **`readBoolean`** ) jazyka IFJ26. Platný zápis čísel musí zabírat celý vstupní řádek bez okolních bílých znaků. Při chybném číselném vstupu nebo EOF vrací hodnotu nil. 

**WRITE** ⟨ _symb_ ⟩ Výpis hodnoty na standardní výstup Vypíše hodnotu ⟨ _symb_ ⟩ na standardní výstup. Hodnota typu float je vypsána pomocí formátovacího řetězce `%a` (pozor, rozdíl proti instrukci FLOAT2STR), hodnota typu int je vypsána pomocí řetězce `%d` . Tento formát výpisu je v souladu s vestavěnou funkcí **`print`** jazyka IFJ26 pro hodnoty typů int, bool, float, string. Hodnota nil se vypíše jako `nil` ; operand typu array vede na chybu 53. 

### **7.4.5 Práce s řetězci** 

**CONCAT** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Konkatenace dvou řetězců 

Do proměnné ⟨ _var_ ⟩ uloží řetězec vzniklý konkatenací dvou řetězcových operandů ⟨ _symb_ 1⟩ a ⟨ _symb_ 2⟩ (jiné typy nejsou povoleny). 

**STRLEN** ⟨ _var_ ⟩⟨ _symb_ ⟩ Zjisti délku řetězce 

Zjistí délku řetězce v ⟨ _symb_ ⟩ a délka je uložena jako celé číslo do ⟨ _var_ .⟩ 

**GETCHAR** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ 

Vrať znak řetězce 

Do ⟨ _var_ ⟩ uloží řetězec z jednoho znaku v řetězci ⟨ _symb_ 1⟩ na pozici ⟨ _symb_ 2⟩ (indexováno celým číslem od nuly). Indexace mimo daný řetězec vede na chybu 58. 

23 

**SETCHAR** ⟨ _var_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Změň znak řetězce Zmodifikuje znak řetězce uloženého v proměnné ⟨ _var_ ⟩ na pozici ⟨ _symb_ 1⟩ (indexováno celočíselně od nuly) na znak v řetězci ⟨ _symb_ 2⟩ (první znak, pokud obsahuje ⟨ _symb_ 2⟩ více znaků). Výsledný řetězec je opět uložen do ⟨ _var_ .⟩ Při indexaci mimo řetězec ⟨ _var_ ⟩ nebo v případě prázdného řetězce v ⟨ _symb_ 2⟩ dojde k chybě 58. 

### **7.4.6 Práce s poli** 

**NEWARRAY** ⟨ _var_ ⟩⟨ _symb_ 𝑠⟩ Vytvoření pole 

Vytvoří pole o velikosti ⟨ _symb_ 𝑠⟩ a uloží referenci na něj do proměnné ⟨ _var_ ⟩. ⟨ _symb_ 𝑠⟩ musí mít typ int (jinak chyba 53) a kladnou hodnotu (jinak chyba 57). Prvky vytvořeného pole jsou neinicializované (neobsahují žádnou hodnotu). 

**ARRAYGET** ⟨ _var_ 𝑡⟩⟨ _var_ 𝑎⟩⟨ _symb_ 𝑖𝑑𝑥⟩ Čti prvek pole 

Přečte prvek z pole odkazovaného z proměnné ⟨ _var_ 𝑎⟩ na indexu ⟨ _symb_ 𝑖𝑑𝑥⟩ do proměnné ⟨ _var_ 𝑡⟩ (indexováno celým číslem od nuly). Indexace mimo velikost pole vede na chybu 58. 

**ARRAYSET** ⟨ _var_ 𝑎⟩⟨ _symb_ 𝑖𝑑𝑥⟩⟨ _symb_ 𝑣𝑎𝑙⟩ Zapiš prvek pole 

Do pole odkazovaného z proměnné ⟨ _var_ 𝑎⟩ uloží na index ⟨ _symb_ 𝑖𝑑𝑥⟩ prvek ⟨ _symb_ 𝑣𝑎𝑙⟩ (indexováno celým číslem od nuly). Indexace mimo velikost pole vede na chybu 58. 

### **7.4.7 Práce s typy** 

**TYPE** ⟨ _var_ ⟩⟨ _symb_ ⟩ Zjisti typ daného symbolu 

Dynamicky zjistí typ symbolu ⟨ _symb_ ⟩ a do ⟨ _var_ ⟩ zapíše řetězec značící tento typ (int, bool, float, string, nil, array). Je-li ⟨ _symb_ ⟩ neinicializovaná proměnná, označí její typ prázdným řetězcem. 

**ISINT** ⟨ _var_ ⟩⟨ _symb_ ⟩ Urči celočíselnost symbolu Určí, jestli je číslo v symbolu ⟨ _symb_ ⟩ celé (tj. typu int nebo typu float s nulovou desetinnou částí), a výsledek typu bool zapíše do ⟨ _var_ ⟩. Operand ⟨ _symb_ ⟩ musí být typu int nebo float. 

Urči celočíselnost symbolu 

**TYPES/ISINTS** Zásobníkové verze instrukcí pro práci s typy 

### **7.4.8 Instrukce pro řízení toku programu** 

Neterminál ⟨ _label_ ⟩ označuje návěští, které slouží pro označení pozice v kódu IFJcode26. Ve skokových instrukcích může být cíl skoku určen přímo dle literálu návěští nebo přečtením hodnoty symbolu typu string. V případě skoku na neexistující návěští dojde k chybě 52. Cíl podmíněného skoku se ověřuje před vyhodnocením podmínky (i před čtením jejích operandů nebo odebráním hodnot z datového zásobníku), a to i tehdy, když by podmínka nebyla splněna. 

**LABEL** ⟨ _label-literal_ ⟩ 

Definice návěští 

Speciální instrukce označující pomocí návěští ⟨ _label-literal_ ⟩ důležitou pozici v kódu jako potenciální cíl libovolné skokové instrukce. Pokus o redefinici existujícího návěští je chybou 52. 

**JUMP** ⟨ _label_ ⟩ 

Nepodmíněný skok na návěští 

Provede nepodmíněný skok na zadané návěští ⟨ _label_ ⟩. 

24 

**JUMPIFEQ** ⟨ _label_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Podmíněný skok na návěští při rovnosti Pokud jsou ⟨ _symb_ 1⟩ a ⟨ _symb_ 2⟩ stejného typu nebo je některý operand nil (jinak chyba 53) a zároveň se jejich hodnoty rovnají, tak provede skok na návěští ⟨ _label_ ⟩. 

**JUMPIFNEQ** ⟨ _label_ ⟩⟨ _symb_ 1⟩⟨ _symb_ 2⟩ Podmíněný skok na návěští při nerovnosti Jsou-li ⟨ _symb_ 1⟩ a ⟨ _symb_ 2⟩ stejného typu nebo je některý operand nil (jinak chyba 53), ale různé hodnoty, tak provede skok na návěští ⟨ _label_ ⟩. 

Podmíněný skok na návěští při nerovnosti 

**JUMPIFEQS/JUMPIFNEQS** ⟨ _label_ ⟩ Zásobníkové verze podmíněných skoků Zásobníkové skokové instrukce mají jeden operand mimo datový zásobník, a to návěští ⟨ _label_ ⟩, na které se případně provede skok. 

**EXIT** ⟨ _symb_ ⟩ Ukončení interpretace s návratovým kódem 

Ukončí vykonávání programu a ukončí interpret s návratovým kódem ⟨ _symb_ ⟩, kde ⟨ _symb_ ⟩ je celé číslo v intervalu 0 až 49 (včetně). Nevalidní celočíselná hodnota ⟨ _symb_ ⟩ vede na chybu 57. 

### **7.4.9 Ladicí instrukce** 

**BREAK** Výpis stavu interpretu na `stderr` Na standardní chybový výstup (stderr) vypíše stav interpretu v danou chvíli (tj. během vykonávání této instrukce). Stav se mimo jiné skládá z pozice v kódu, výpisu globálního, aktuálního lokálního a dočasného rámce a počtu již vykonaných instrukcí. 

**DPRINT** ⟨ _symb_ ⟩ Výpis hodnoty na `stderr` Vypíše diagnostický zápis dané hodnoty ⟨ _symb_ ⟩ na standardní chybový výstup (stderr). Umožňuje vypsat i pole a neinicializované proměnné. Výpisy touto instrukcí bude možné vypnout pomocí volby interpretu (viz nápověda interpretu). 

25 

# **Revize specifikace** 

2026-09-21: První úplná verze specifikace jazyků IFJ26 a IFJcode26. 

2026-10-03: Upřesnění IFJcode26 a vestavěných čtecích funkcí: 

- **upřesnění** : IFJcode26 + IFJ26: chování READ v chybových stavech (vestavěné funkce **`readInt`** a **`readDouble`** vrací při chybě nulu, ale instrukce READ vrací nil); 

- **oprava** : IFJcode26 + IFJ26: instrukce FLOAT2STR a vestavěná funkce **`toStr`** pro typ **`Double`** vždy vypíšou textovou reprezentaci ve formátu `%.2f` (toto je formátovací řetězec pro funkci `sprintf` jazyka C, který použije interpret při vykonání instrukce FLOAT2STR); 

- **vylepšení** : IFJcode26: reference na pole je nyní možné porovnávat (pomocí EQ i podmíněných skoků); 

- **upřesnění** : IFJcode26: chybové stavy při práci s poli (nekladná velikost, čtení neinicializovaných prvků). 

2026-10-04: **Vylepšení** IFJcode26: instrukce IDIV nyní zaokrouhluje k nule (tzn. −5/2 = −2), lze tak přímo použít pro realizaci dělení stejným způsobem, jako to dělá Scala. (Dříve zaokrouhlovala k −∞, tzn. −5/2 = −3.) 

26 

