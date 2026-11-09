

Zadání projektu z předmětů IFJ a IAL
## Ondřej Ondryáš, Zbyněk Křivka
e-mail: {iondryas, krivka}@fit.vut.cz
- září 2026 (revize z 8. října)
## Obsah
1 Obecné informace1
## 2 Zadání3
## 3 Hodnocení6
4 Využití AI nástrojů7
## 5 Dokumentace9
6 Odevzdávaný archiv10
7 Poznámky na závěr11
1 Obecné informace
Název projektu:Implementace překladače imperativního jazyka IFJ26.
Informace:diskuzní fórum a
e-learning(Moodle) předmětu IFJ.
Registrace varianty:do středy 30. září 2026, 23:59.
Pokusné odevzdání:čtvrtek 19. listopadu 2026 (10. týden sem.), 23:59:59.
Hlavní odevzdání:pátek 27. listopadu 2026 (11. týden sem.), 11:59:59.
Obhajoby:12. a 13. týden semestru.
Hlavní cíle projektu:
•Pochopit základní principy překladu zdrojového kódu z vyššího do nižšího jazyka.
•Prakticky využít teorii formálních jazyků.
•Naučit se efektivně a udržitelně pracovat na rozsáhlejším softwarovém projektu v týmu.
•Naučit sevhodným způsobemvyužívat asistenci AI nástrojů (při zachování mozkové činnosti).
Řešitelské týmy:
•Projekt budou řešit čtyřčlenné týmy. Týmy s jiným počtem členů jsou nepřípustné (jen výji-
mečně po předchozí konzultaci tříčlenné).
•Vytváření týmů se provádí funkcionalitou Týmy v IS VUT. Tým vytváří vedoucí a název týmu
bude automaticky generován na základě loginu vedoucího. Vedoucí má kontrolu nad složením
týmu, smí předat vedení týmu jinému členovi a bude odevzdávat výsledný archiv. Rovněž vzá-
jemná komunikace mezi vyučujícími a týmy bude probíhat nejlépe prostřednictvím vedoucích
(ideálně v kopii dalším členům týmu).
•Jakmilebudemíttýmdostatekčlenů,budemuumožněnosizaregistrovatjednuzedvouvariant
zadání (viz sekci2.1) v aktivitě „Projekt – Registrace a odevzdání“.
## 1

Termín odevzdávání:
Kompletní implementaci a dokumentaci projektu odevzdejte nejpozději v pátek27. 11. v 11:59:59
(tj. před polednem, ne v noci) do StudISu pod zadání „Projekt – Registrace a odevzdání“. Podrobné
informace ke struktuře archivu jsou uvedeny v sekci6.
Mezi čtvrtkem 26. 11. a úterým 1. 12.8:00zanestevytisknutoudokumentaci
## 1
na fakultu (nejspíše
recepci FIT nebo garantovi projektu, bude upřesněnoaktualitou z předmětu).
V 11. týdnu semestru se v IS VUT objeví také přihlašování na termíny osobní obhajoby – ty pro-
běhnou ve 12. až 13. týdnu semestru. Před svou obhajobou do IS odevzdáte prezentaci ve formátu
PDF (a případně i v původním). Podrobné informace budou uvedeny v e-learningu a upozorníme
na ně formouaktualit z předmětu.
Pokusné odevzdání:
Do konce čtvrtka 19. 11. můžete dobrovolně odevzdat v IS VUT implementaci projektu pod zadání
„Projekt – Pokusné odevzdání“. Do konce týdne vám e-mailem zašleme výsledky běhu automati-
zovaných testů, které vám napoví, které části projektu mají nedostatky. Výsledky budou obsahovat
pouze popisy kategorií testů a procentuální úspěšnost.
Pokusně odevzdává nejvýše jeden člen týmu (nejlépe vedoucí), který se na zadání v rámci pokus-
ného odevzdání registruje v IS VUT, kde projekt odevzdá a následně obdrží jeho vyhodnocení,
o kterém informuje zbytek týmu.
Pokud časové a technické okolnosti dovolí, nabídneme vám možnost pokusně odevzdat podruhé,
a to pravděpodobně do středy 25. 11. 8:00. Tuto možnost však budou (případně) mít pouze týmy,
které využily hlavního pokusného odevzdání.
Pokusné odevzdání je nepovinné. Upozorňujeme však, že v případě reklamací nebo snah o přidání
bodů k dosažení zápočtu po finálním odevzdání projektu budenevyužití pokusného odevzdání
považováno za přitěžující okolnost.
Zdroje informací:
•E-learning(Moodle) předmětu IFJ:
–často kladené otázky (FAQ),
–fórum k projektu.
•Cvičící: Ondřej Ondryáš – konzultace na fóru, na discordu v kanálu#ifj-public, příp.
osobní konzultace po dohoděe-mailemči na discordu.
•Garant projektu: Zbyněk Křivka – konzultace na fóru, na discordu v kanálu#ifj-public,
příp. osobně v konzultačních hodinách (viztewebovou stránku) nebo po dohoděe-mailem
(uvádějte předmět začínajícíIFJ:).
Pokud máte jakékoliv dotazy, problémy či nejasnosti ohledně zadání projektu, tak po přečteníFAQ
a dřívějších dotazů nafóru(využívejte i možnosti vyhledávání!)neváhejte napsatnejlépe na fó-
rum, případně na discord do kanálu#ifj-public. Čas od času si fórum přečtěte, i pokud nemáte
žádné otázky, neboť se zde mohou vyskytnoutzávazná vyjasnění zadání.
V případě individuálních problémů, které nevychází přímo z nejasnosti v zadání, se co nejdříve
ozvětecvičícímu či garantovi projektu. Organizační problémy (tj. týkající se registrací, odevzdá-
## 1
Vytisknutá dokumentace musí být shodná s odevzdaným PDF. Tiskněte na standardní kancelářský papír
(∼80 g/m
## 2
) rozměru A4, nejlépe jednostranně. Jednotlivé papíry spojte v levém horním rohu běžnou sešívačkou.
## 2

vání, hodnocení atp.) řešte s garantem projektu, dr. Křivkou (cvičícího můžete uvést do kopie).
Na problémy zjištěné v řádu hodin až jednotek dní před termínem odevzdání nebude brán zřetel.
Začněte proto projekt řešit s dostatečným předstihem.
## 2 Zadání
Vytvořte program v jazyceC, který načte zdrojový kód zapsaný ve zdrojovém jazyce IFJ26, kte-
rý je specifikován vsamostatném dokumentuŞ, a přeloží jej do cílového jazyka IFJcode26 (tzv.
mezikód), který je specifikován tamtéž. Jestliže proběhne překlad bez chyb, vrací se návratová
hodnota 0 (nula). Pokud došlo k nějaké chybě překladu, vrací se příslušná návratová hodnota dle
sekce specifikace„Přehled chybových návratových kódů“Ş.
Překladač bude načítat řídicí program v jazyce IFJ26 ze standardního vstupu a generovat výsledný
kód v jazyce IFJcode26 na standardní výstup. Všechna chybová hlášení, varování a ladicí výpisy
provádějte na standardní chybový výstup; tj. bude se jednat o konzolovou aplikaci bez grafického
uživatelského rozhraní (tzv. filtr). Pro interpretaci výsledného programu v cílovém jazyce IFJco-
de26 bude v e-learningu předmětu k dispozici interpret.
Návrh implementace překladače je zcela ve vaší režii. Jezakázánootevírat síťová spojení nebo
jinak komunikovat po síti, spouštět další procesy a vytvářet nové či modifikovat existující sou-
bory (ani v adresáři/tmp). Dále jezakázánovyužívat jakékoliv knihovny
## 2
třetích stran (mimo
standardní knihovnu jazyka C).
Poznámka:Dbejte hlavně na to, aby se váš překladač korektně choval v situacích, které přímo
vychází ze zadání (specifikace jazyka). Pokud specifikace nějaký detail chování nespecifikuje,
doporučujeme jej probrat se cvičícími a/nebo ostatními kolegy/-němi řešícími projekt, ale
typicky platí, že je to zcela na vás.
Upozornění:Projekt bude hodnocen pouze jakofunkční celek, a nikoli jako soubor sepa-
rátních, společně nekooperujících modulů. K problémům typu „člen týmu ukončil studium“
přihlížíme (pokud je s námi konzultujete s předstihem), ale i v těchto případech je nutné ode-
vzdat něco, co jsme schopni spustit a otestovat.
2.1 Implementace tabulky symbolů
V rámci projektu bude nutné, abyste implementovali jistou vyhledávací datovou strukturu, a to dle
varianty zadání, kterou si zaregistrujete v IS VUT:
vv-BVS)Výškově vyváženýbinární vyhledávací strom.
TRP-izp)Tabulka s rozptýlenými položkami simplicitním zřetězením položek(TRP s otevře-
nou adresací).
Konkrétní způsob implementace si sami zvolte, typicky dle znalostí z přednášek IAL (např. ve
variantě vv-BVS zvolte libovolný typ stromu, ve variantě TRP-izp zvolte vhodnou/-é hashovací
funkci/-e). Pokud se rozhodnete implementovat strukturu/algoritmus, která/-ý se neprobírá v IAL,
poznačte to v dokumentaci a odůvodněte na obhajobě.
## 2
Výjimkou jsou knihovny/platformy pro automatické testování, které doporučujeme, ale nevyžadujeme a nehodno-
tíme. Projekt musí jít přeložit výchozím cílemMakefile(viz sekci2.7) a poté spustit i v prostředí bez těchto knihoven.
## 3

Tato datová struktura bude využita především jakotabulka symbolů(TS), viz přednášky IFJ.
Vytvořte modulsymtable.c+symtable.h, který poskytuje TS jakožtoabstraktní datový
typ(ADT) – modul tedy bude obsahovat funkce, které slouží pro vytvoření TS a práci s ní, přičemž
interní reprezentace je před uživatelem skryta (viz přednášky v IAL).
Co se organizace kódu týče, postupujte jednou z následujících možností:
1.Vybraná datová struktura bude integrální součástí TS, tj. bude mít (obvykle) fixní typ klíčů
a hodnot, implementaci příslušných operací umístíte přímo do modulusymtable. Vhodné,
pokud vyhledávací strukturu nepotřebujete nikde jinde.
2.Vybraná datová struktura bude ADT, který je implementovánobecněpro použití s různý-
mi typy klíčů a/nebo hodnot. TS pak budesamostatnýmADT, kterýinterněvyužívá vaši
datovou strukturu (zbytek překladače, který pracuje s TS, s ní pracuje pouze skrz operace
definované v modulusymtable, tedy nevolá přímo operace datové struktury). V tomto
případě umístěte povinně datovou strukturu do modulubst.c+bst.h(vv-BVS), resp.
hashtable.c+hashtable.h(TRP-izp).
Upozornění:Za účelem vašeho procvičení učiva z IAL je přísnězakázánopro implementaci
vyhledávácí struktury využít nástroje AI (viz sekci4).
2.2 Implementace překladače
Pro implementaci jednotlivých částí překladačepovinněvyužijte následující metody. Všechny bu-
dou probírány na přednáškách předmětu IFJ. Nedodržení těchto metod bude penalizováno značnou
ztrátou bodů!
1.Lexikální analýzu implementujte (v principu) jakokonečný automat. Drobné odchylky od
standardní funkce tohoto modelu jsou povoleny.
2.Při konstrukci syntaktické analýzy založené na LL gramatice (vše kromě výrazů) využij-
te buďmetodu rekurzivního sestupu(doporučeno), nebo prediktivní analýzu řízenou LL
tabulkou.
3.Výrazy (vč. pravdivostních) zpracujte pouze pomocíprecedenčnísyntaktickéanalýzy, kte-
rá odpovídá výkladu v přednáškách (využívá precedenční tabulku).
Při řešení projektu je zakázáno využívat generátory lexerů či parserů (např. lex, flex, yacc, Bison
atp.).
2.3 Vstupy a výstupy překladače
Veškerá chybová hlášení vzniklá v průběhu činnosti překladače budou vždy vypisována na stan-
dardní chybový výstup (stderr). Veškeré texty tištěné řídicím (přeloženým) programem budou
vypisovány na standardní výstup (stdout). Kromě chybových/ladicích hlášení vypisovaných na
standardní chybový výstup nebude generovaný mezikód přikazovat výpis žádných znaků či do-
konce celých textů, které nejsou přímo předepsány řídicím (přeloženým) programem.
Základní testování bude probíhat pomocí skritpů, které budou postupně vaším překladačem kom-
pilovat sadu testovacích příkladů, výsledky interpretovat naším interpretem jazyka IFJcode26 a po-
rovnávat produkované výstupy (na standardním výstupu) s výstupy očekávanými. Pro porovnání
výstupů bude použit programdiff. Proto jediný neočekávaný znak (vč. konců řádku), který bude
při hodnotící interpretaci vámi vygenerovaného kódu svévolně vytisknut, povede k nevyhovující-
mu hodnocení aktuálního výstupu, a tím snížení bodového hodnocení celého projektu.
## 4

2.4 Verzování kódu
Protože jde o rozsáhlý týmový projekt, je nutností při vývoji využívat verzovací systém. Pro spo-
lupráci na projektu povinně využijte systémGit. Repozitář si můžete vytvořit na libovolné veřejné
platformě (např.GitHub,GitLab,Codeberg) nebo na fakultním Git serverugit.fit.vut.cz(pozor, je
dostupný jen ze sítě VUT nebo přesVPN).
Povinně se řiďte (alespoň) následujícími pravidly:
•Vytvářejte větší množství menších commitů – jeden commit má řešit jeden problém.
•Po aplikaci každého commitu by mělo být možné kódpřeložit.
•Nepřidávejtecommity přímo dohlavnívětve–pracujte na samostatnýchvětvícha vevhodných
chvílích vytvářejtepull (merge) requests(PR). Domluvte se v týmu na vhodných pravidlech
code review a pravidlech pro schvalování PR.
•První řádek commitu by měl obsahovat stručnou informaci o charakteru změn a uvádět, které
části projektu se změna dotýká.
Cosezprávcommitůtýče,proinspiracidoporučujemeseznámitsenapř.skonceptemConventional
Commitsnebo s doporučeními pro vývojářelinuxového jádra.
Během vývoje mějte repozitáře nastavené jakosoukromé. Ažpo termínu finálního odevzdá-
níprojektu nastavte repozitáře jako veřejné, příp. na fakultním Git serveru stačí do soukromého
repozitáře přidat uživateleiondryass právy administrátora. Odkaz na repozitář uveďte do doku-
mentace odevzdaného projektu. Repozitáře budounamátkově kontrolovány. Nevhodné použití
gitu (např. několik obřích commitů s celými hotovými kusy projektu) může být penalizováno.
2.5 Udržení kvality kódu
V každém rozsáhlejším projektu je dobrým zvykem využívat tzv.formatter– nástroj, který zajiš-
ťuje konzistentní formátování (styl zápisu) kódu, obvykle na základě nakonfigurovaných pravidel.
Povinněvyužijte pro formátování kódu nástroj
clang-format, vybrat si můžete libovolný
## 3
z vesta-
věných stylů formátování (hodnota parametru--style).
## Dáledoporučujeme:
•využívat při překladu přepínače-Walla-Wextraa řešit reportovaná varování,
•využívat nástrojeCppchecka/neboclang-tidypro dodatečnou statickou analýzu zdrojového
kódu (příklady použití budou v e-learningu),
•průběžně kontrolovat, zda nedochází k únikům paměti, např. pomocí nástroje Valgrind.
Důsledné využití těchto nástrojů vám pomůže předejít bodovým srážkám za nízkou kvalitu kódu,
nevhodnou práci s pamětí atp. Doporučujeme kontrolu zmíněnými nástroji zabudovat přímo do
procesu překladu (tj. do vašehoMakefile) – pozor však, aby bylo možné překlad možné provést
i na stroji, kde nástroje nejsou k dispozici (viz sekci
## 2.7).
Úvodvšechzdrojových textůmusíobsahovat zakomentovaný název projektu, přihlašovací jména
a jména studujících, kteří se na daném souboru skutečně autorsky podíleli. Dále nezapomeňte kód
komentovat– minimálně každá funkce by měla obsahovat stručný popis svého rozhraní a význa-
mu.
## 3
Samozřejmě je nutné, aby všichni členové týmu používali stejný styl formátování.
## 5

## 2.6 Testování
V projektu nevyžadujeme žádnou konkrétní formu testování, ale neobejdete se bez něj.Doporu-
čujemekombinovat dva přístupy:
•Jednotkové (unit) testování dílčích komponent – např. s využitím testovacího rámceGoogle-
## Test;
•End-to-end black-box testování celého překladače – pište si vlastní miniaturní programy v ja-
zyce IFJ26, které zkoušejí konkrétní chybové i nechybové stavy a chování. Po každé změně
v projektu všechny tyto programy přeložte, spusťte (napište si/nechte AI napsat vám skript,
který to bude dělat automaticky) a ověřte, zda mají správný výstup. Obdobným způsobem
budeme vaše řešení testovat i my.
Svétestyidoprovodnénástrojeverzujtevgitu.Nepovinnějemůžeteodevzdatidofinálníhoarchivu
(vhodné, pokud se jimi chcete „pochlubit“ u obhajoby), vaše testy však spouštět nebudeme.
## 2.7 Překlad
Váš projekt musí jít přeložit překladačemgccve verzích 14/15/16 neboclangve verzích 19/23,
a to alespoň na architektuře x86_64 – odpovídá konfiguraci serveru Merlin. K projektu dodejte
Makefile(pro nástroj GNU Make), který po prostém spuštění v adresáři s rozbaleným projektem
(příkazemmake) vytvoří právě jeden spustitelný binární soubor libovolného jména. VášMakefile
musí bez úprav fungovat v prostředí odpovídajícím serveru Merlin (zejm. co se týče cest k překla-
dači).Makefilemůže obsahovat i jiné cíle, ty však spouštět nebudeme.
Před použitím nějaké vyspělé konstrukce jazyka C je vhodné si ověřit, že jí disponuje i zvolený
překladač ve zvolené verzi a že vášMakefilena serveru Merlin korektně využívá právě tento pře-
kladač. Využít můžete libovolný standard jazyka C, který je podporovaný zvoleným překladačem.
Vzhledem k rozsahu projektu platí, že by přeložený projekt měl správně fungovat na libovolném
moderním systému unixového typu, kde bude přeložen. Server Merlin lze považovat za „referenční
stroj“ ve smyslu překladového prostředí, alenepro samotný běh vašeho řešení. Pokud váš program
špatně pracuje s pamětí, je možné, že na Merlinovi to „projde“, zatímco na jiných systémech ne. „It
works on my machine“nenívhodná vývojová strategie ani pádný důvod k reklamaci bez bodové
srážky. Nezaručujeme, že vaše řešení bude skutečně překládáno či spouštěno na serveru Merlin
(důkladněji popsáno v
e-learningu). Zároveň však garantujeme, že vyhodnotíme každý projekt,
kterýlzena Merlinovipřeložit.
Pozor, na serveru Merlin nejsou k dispozici všechny doporučené nástroje pro kontrolu kódu. Pokud
je chcete integrovat přímo do svéhoMakefile, doporučujeme vytvořit si např. třicíle:build(vý-
chozí – jen překlad),check(jen kontrola) abuild-check(spustí nejprvecheck, pakbuild).
Při vývoji budete pak vždy překládat pomocímake build-check, ale my při vyhodnocování
spustíme jen výchozí cílbuild.
## 3 Hodnocení
Do předmětu IFJ získá každý maximálně 28 bodů:
•18 b programová část projektu (za základní funkčnost lze získat nejvýše 12 b, zbylých 6 b je
nutné nasbírat za povinně volitelná rozšíření) – váš překladač bude ohodnocen pomocí auto-
matických testů, dále mohou proběhnout srážky na základě hodnocení kvality kódu či souladu
se zadáním a dokumentací,
## 6

•10 b osobní obhajoba + dokumentace.
Do předmětu IAL získá každý maximálně 15 bodů: 5 b za programovou část projektu, 10 b za ob-
hajobu a dokumentaci. Za povinně volitelná rozšíření je možné získat i více než 6 b (lze jimi dohnat
ztráty v základní funkčnosti nebo budou zapsány jako bonusové body).
Podrobnější informace o způsobu automatického i manuálního hodnocení (jakož i různé tipy pro
prácisjazykemC)najdeteve-learninguIFJnastránce„Jakseprojektyhodnotí,nacosidátpozor“.
Bonusové body
Lze získat až 5 bonusových bodů do předmětu IFJ, a to (mj.) za implementaci většího množství
rozšíření, implementaci vhodných testů, tvůrčí přístup, zajímavé řešení nebo aktivitu na fóru. Jako
bonusové nelze získat více než 50 % bodů z vašeho individuálního hodnocení základní funkčnosti.
Za programovou část projektu (na základě automatických testů) je možné v případě výborného ře-
šení získat více než 18 bodů. V těchto případech budou také připsány jako bonusové body v před-
mětu IFJ.
Upozornění:Udělení zápočtu z IFJ je podmíněno získáním min. 20 bodů v průběhu semestru,
udělení zápočtu z IAL je podmíněno získáním min. 15 bodů. Navíc v IFJ z těchto 20 bodů
musíte získat nejméně 4 body za programovou část projektu.
Osobní obhajoba projektu
Osobní obhajoba se bude skládat z vaší prezentace, kde náhodně vybraný člen týmu v cca 5 minu-
tách představí řešení a popíše nejdůležitější implementační detaily. Dále proběhne cca 15minutová
rozprava, kde se vás budeme ptát na konkrétní otázky týkající se řešení jednotlivých částí projek-
tu. Během obhajoby už budeme mít k dispozici ohodnocenou dokumentaci (kterou musíte předem
odevzdat, viz sekci
1) i předhodnocenou implementaci.
Cílem obhajoby je ověřit, že zvládnete vysvětlit detaily svého řešení a že se dostatečně orientujete
v problematice. Otázky mohou mít charakter silně technický („Proč se na tomto místě předává
tato konkrétní datová struktura?“) i teoretičtější („Jaké třídy je jazyk přijímaný vaším lexikálním
analyzátorem a proč?“).
Detailnější pokyny a seznam otázek, na které se doporučujeme připravit, zveřejníme v e-learningu
před odevzdáním projektu.
Upozornění:Hodnocení obhajoby má implicitní souvislost s kvalitou implementace: za sotva
fungující řešení pravděpodobně nezískáte plné množství bodů za obhajobu. Pokud během ob-
hajoby neprokážetedokonalé pochopení vlastního řešení, může dojít k významné bodové
srážce i za programovou část, v krajních případech může být celý projekt hodnocen0body
nebo mohou být jednotlivci či celý tým posláni k posouzení disciplinární komisí.
4 Využití AI nástrojů
Záměrem projektu je, abystevyrozšířili své dovednosti a znalosti, projekt má vznikat díkyvaší
inteligenci. Nástroje „umělé inteligence“, např. generativní jazykové modely a na nich založené
agentní systémy, mají v tomto procesu samozřejmě své místo. Vhodným a povoleným použitím je:
## 7

•dovysvětlení nejasných částí zadání (preferujte však vyhledávání konkrétních informací, ne
„shrň toto zadání v jednom odstavci“; nezapomeňte, že máte k dispozici také fórum a discord),
•zapojení do procesu návrhu architektury řešení (na základě vlastních znalostí z přednášek vy-
užijte AI pro diskuzi o vaší vlastní představě, ne „řekni mi, jak mám tohle celé udělat“; přistu-
pujte k návrhům AI kriticky),
•vysvětlení použití některých nástrojů či konkrétních funkcí,
•hledáníproblémůachyb(nejlépekonkrétních)veváminapsanémkódu–zapojteAIdoprocesu
code review, ale nevypouštějte z něj člověka,
•implementace konkrétních, ohraničených, perfektně specifikovaných částí kódu,
•vytváření testů na základě přesného popisu testované situace.
V každém případě je nutné, abyste projekt stále řešilivy, a ne AI nástroj. Je důležité, abyste si sa-
mi pečlivě pročetli celé zadání a na jeho základě sami uvážili, jakým směrem při návrhu řešení
postupovat. Na projektech na FIT byste se měli naučit především vyvíjetinženýrskou činnost:
programátorem může být AI, ale softwarovými inženýry*inženýrkami máte být vy.
Poznámka:Domluvte se na kultuře používání AI v týmu hnedze začátkuřešení projektu
a vzájemně se v níprůběžně kontrolujte.
Explicitně zakazujeme použití AI pro:
•Generování či úpravu textu závěrečné dokumentace – ta je letos velmi stručná, vychází zvaší
činnosti, má zachycovatvašemyšlenky a způsob řešení, který jstevynavrhli. Nechceme číst
AI slop.
•Faktickou přípravu gramatiky, LL tabulky, konečného automatu, precedenční tabulky a příp.
jiných podkladových formalismů – zaprvé to modelům přílišnejde, zadruhé vám budou tyto
znalosti chybět u zkoušek.
•Generování kódu vyhledávací datové struktury.
Nenípřípustnéprojekt řešit způsobem „tady máš zadání, celé to naprogramuj,make no mistakes“.
Při posuzování vhodnosti použití prostředků AI klademe důraz natransparentnost:
•V dokumentaci uveďte, jaké konkrétní AI nástroje a modely jste používali, a stručně popište,
jaký byl váš typický pracovní postup při jejich použití.
•Stručně popište také problémy, na které jste při využití AI narazili, a situace, ve kterých jste
návrhy AInevyužilinebo značně upravili.
•Každý segment kódu, který vytvoří AI,označte komentářema uvedťe do tohoto komentáře
taképrompt, který jste využili.
Upozorňujeme, že kontroly týkající se nepřiznaného či nadměrného využití AI nebo plagiátorství
mohou proběhnout i na pokusném odevzdání nebo na jakékoliv části historie projektu ve vašem
git repozitáři.
Přečtěte si zásady uvedené v dokumentuUžívání generativní AI na VUT v Brněvč.Doporučení
pro oblast vzdělávání
. Tyto zásady považujeme pro účely projektu za závazné. Upozorňujeme, že
nedovolené a nepřiznané použití nástrojů AI, jakož ivydávání cizího díla za vlastní, popřípadě
převzetí části cizí práce bez uvedení použitých zdrojů [...]jsoudisciplinární přestupky.
## 8

## 5 Dokumentace
Dokumentace projektu je stručným a výstižným popisem vašeho způsobu řešení projektu. Cílem
dokumentace obecně je rychle přiblížit implementaci člověku, který ji nikdy neviděl, aby se v ní
zorientoval např. pro účely dalšího vývoje, oprav chyb atp.
Dokumentaci je možné psát česky, slovensky (v obou případech s diakritikou) nebo anglicky. Hod-
notíme jak obsahovou stránku, tak i stylistiku, pochopitelnost, strukturu a sazbu. V dokumentaci
nechceme čístomáčku, ale podstatné informace o vašem řešení v ucelené a stručné podobě!
Dokumentace musí obsahovat následující části:
•Na začátku (první straně) budou:
–jména, příjmení, VUT loginy a osobní čísla všech řešitelů (vedoucí bude označen tučně),
–zvolená varianta (vv-BVS/TRP-izp),
–informace o rozdělení bodů (viz sekci6),
–identifikátory implementovaných rozšíření,
–odkaz na git repozitář;
•stručný popis rozdělení práce mezi členy týmu (uveďte výčtem nebo několika větami, kdo a jak
se podílel na jednotlivých částech projektu; povinně zdůvodněte odchylky od rovnoměrného
rozdělení bodů);
•stručný popis způsobu spolupráce, kultury code review a schvalování PR (max. jednotky vět
či odrážek); stručný popis využitých forem testování (max. jednotky vět či odrážek); zvolený
styl formátování kódu;
•blokové schémaarchitektury vašeho řešení, které bude obsahovat jednotlivé moduly překla-
dače (např. lexikální, syntaktická, sémantická analýza atp.) a musí zobrazovat i datové toky
mezi jednotlivými komponentami – specifikujte, v jakých strukturách (např. tokeny, AST, me-
zikód) si komponenty předávají informace. Z diagramu a jeho textového popisu musí být jasné
vstupy, výstupy, význam komponent a jejich propojení;
•diagramautomatu, který specifikuje lexikální analyzátor (podle konvencí přednášených v IFJ;
s případným slovním popisem odchylek od standardního modelu konečného automatu);
•LL gramatiku a z ní vycházející LL tabulku; a precedenční tabulku, podle kterých jste imple-
mentovali syntaktický analyzátor;
•stručný popis každého modulu (informačně obohacující věta na dvojici.c/.h);
•bibliografické citace všech převzatých zdrojů (vč. kódu, algoritmů);
•popis využití prostředků AI (viz sekci4).
V dokumentaci je zbytečné projekt představovat či vysvětlovat,coprojekt dělá – rovnou vysvět-
lete,jaktoho docílil, případně co neumí. Dbejte na správnost použitéterminologie. Obvykle není
vhodné do dokumentace kopírovat úryvky zdrojového kódu. Identifikátory je vhodné sázet fontem
s pevnou šířkou znaků.
Diagramy,tabulky, obrázky musí býtčitelné(i po vytisknutí dokumentace na standardnípapír A4).
Dokumentaci ve formátuPDF(doporučujeme využít L
## A
## T
## E
X nebo Markdown vyrenderovaný do
PDF např. pomocí nástroje Pandoc) pojmenujtedokumentace.pdfa zahrňte v odevzdávaném
archivu.Zdrojovýtextdokumentaceverzujtevgituspolusprojektem(alenedávejtejejdoarchivu).
## 9

6 Odevzdávaný archiv
Do StudISu odevzdáte jeden archiv zkomprimovaný ve formátuZIP. V kořeni budou pouze:
•zdrojový kód implementace (případně může být v podsložcesrc/) – zdrojové soubory by
neměly být rozřazeny v žádné další adresářové struktuře,
## •soubordokumentace.pdf,
•souborrozdeleni(viz níže),
•souborrozsireni(viz níže),
•souborMakefile(viz sekci2.7),
•nepovinněsložkatests/se všemi zdrojovými soubory využívanými při vašem procesu au-
tomatizovaného testování
Názvy všech souborů a adresářů mohou obsahovat pouze písmena anglické abecedy, číslice, tečku,
podtržítko (a pouze v nezbytných případech spojovník).
Archivnesmíobsahovat žádné binární spustitelné soubory nebo jiné přeložené artefakty, skryté
adresáře (s tečkou na začátku) vč. adresáře.git, adresář(e)__MACOSXnebo.DS_Store.
Ve-learninguIFJ najdete skriptis_it_ok.sh, který kontroluje většinu formálních požadavků
odevzdávaného archivu. Využijte jej.
6.1 Dělení bodů
Odevzdaný archiv bude povinně obsahovat souborrozdeleni, ve kterém zohledníte dělení bo-
dů mezi jednotlivé členy týmu (i při požadavku na rovnoměrné dělení). Na každém řádku je pro
jednoho člena týmu uvedeno:
VUT ID (osobní číslo),dvojtečka, odpovídající FIT login (xlogin),dvojtečka, požadovaný
celočíselný počet procent bodů bez uvedení znaku %
Každý řádek (i poslední) je poté ihned ukončen jednímunixovým znakem nového řádku(známý
také jako „line feed“,⟨LF⟩, ASCII hodnota 10 nebo\n, tj. unixové ukončení řádku LF,newin-
dowsovské CRLF!).
Obsah souboru bude tedy vypadat například takto (
## LF
zastupuje unixové odřádkování):
## 123456:xnovaka01:67
## LF
## 117890:xnovakh02:03
## LF
## 124567:xnovako03:30
## LF
## 115678:xnovakj04:00
## LF
Formát odevzdaného souboru musí být správný a obsahovat všechny registrované členy týmu (i ty
hodnocené 0 %). Součet všech procent musí být roven 100. Pokud soubor nesplňuje uvedené po-
žadavky, bude použito rovnoměrné rozdělení.
Vedoucí týmu je před odevzdáním projektu povinen celý tým informovat o rozdělení bodů. Kaž-
dý člen týmu je navíc povinen rozdělení bodů zkontrolovat po odevzdání do StudIS a případně
rozdělení bodů reklamovat u cvičícího ještě před obhajobou projektu.
6.2 Implementovaná rozšíření
Odevzdaný archiv bude dále obsahovat souborrozsireni, ve kterém na každém řádku uvedete
jeden identifikátor implementovaného povinně volitelného rozšíření. Pokud soubor nebude nale-
## 10

zen, implementovaná rozšíření nebudou testována (a přijdete o body). Identifikátorem se myslí
pouze řetězec FUNEXP, BOOLTHEN atp., viztespecifikaciŞ. Každý řádek (i poslední) je ukon-
čen jednímunixovým znakem nového řádku(obdobně jako v souborurozdeleni).
7 Poznámky na závěr
Teoretické znalosti potřebné pro vytvoření projektu získáte během semestru na přednáškách a také
v e-learningu IFJ (nezapomeňte sledovat diskuzní fórum k projektu). Postupuje-li vaše realizace
projektu rychleji než probírání témat na přednášce, doporučujeme využít samostudium (viz zve-
řejněné záznamy z minulých let a detailnější pokyny v e-learningu).
Jenezbytné, aby na řešení projektu spolupracoval celý tým. Návrh překladače, základních rozhraní
a rozdělení práce lze vytvořit již v první čtvrtině semestru. Je dobré, když se celý tým domluví
na pravidelných schůzkách a komunikačních kanálech, které bude během řešení projektu využívat
(instant messaging, video konference, verzovací systém, štábní kultura atd.).
Situaci, kdy je projekt ignorován částí týmu, lze řešit prostřednictvím souborurozdeleni. Ex-
trémní případy řešte přímo se cvičícími conejdříve. Je ale nutné, abyste si vzájemně (nespoléhejte
pouze na vedoucího), nejlépe na pravidelných schůzkách týmu,ověřovaliskutečnýpokrokv práci
na projektu a případně včas přerozdělili práci. Jako tým nesete všichni stejným dílem zodpovědnost
za celý projekt – nelze říct: „Já jsem si svou část udělal a zbytek mě nezajímá.“ Pokud vám člen
týmu v průběhu semestru „zmizí“, budete muset jeho část dopracovat bez něj (také za to získáte
patřičný počet bodů „navíc“).
Pokud využíváte editor Visual Studio Code (nebo nějaký jeho derivát), doporučujeme využít
roz-
šířenípro podporu jazyka Scala arozšířenípro podporu cílového jazyka IFJcode26.
Maximální počet bodůzískatelný na jednu osobu za programovou implementaci je23včetně
bonusových bodů.
Nenechávejte řešení projektu až na poslední týden.Projekt je tvořen z několika částí (např. le-
xikální analýza, syntaktická analýza, sémantická analýza, tabulka symbolů, vnitřní reprezentace,
generování cílového kódu, dokumentace, testování!) a dimenzován tak, aby jednotlivé části bylo
možno navrhnout a implementovat již v průběhu semestru na základě znalostí získaných na před-
náškách předmětů IFJ a IAL a samostudiem ze zdrojů uvedených v e-learningu IFJ.
Opravy zadání
2026-10-08: Doplněn požadavek na souborrozsireniv archivu. Přidány konkrétní odkazy do
e-learningu.
## 11