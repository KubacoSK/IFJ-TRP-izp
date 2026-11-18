# Prompty pouzite na vygenerovanie testov pre codegen (Gemini)

## 01_normal_valid

1. `01_header_and_print_literals`
Prompt: "potrebujem zakladny test na code generator kde sa vypise cez print cele cislo zaporne cislo string a tiez hodnota () typu Unit ktora sa ma podla zadania vypisat ako ()"

2. `02_arithmetic_int_and_double`
Prompt: "sprav mi test na generovanie aritmetiky pre Int a Double scitanie odcitanie nasobenie delenie a unarny minus nech viem ci funguju instrukcie ADD SUB MUL IDIV a DIV"

3. `03_implicit_int_to_double_conversion`
Prompt: "v zadani je ze IFJ26 robi implicitnu konverziu Int na Double tak mi sprav test kde sa miesa Int a Double v scitani v deleni pri priradeni do Double premennej pri volani funkcie s Double parametrom a pri navrate z funkcie"

4. `04_string_concatenation_and_relations`
Prompt: "sprav mi test na spajanie stringov cez + pomocou CONCAT aj s prazdnym stringom a porovnavanie stringov cez < <= > >= == !="

5. `05_if_else_and_all_comparisons`
Prompt: "potrebujem otestovat generovanie navesti a skokov pre viacero if else za sebou so vsetkymi porovnavacimi operatormi a aj porovnanie dvoch Unit premennych cez =="

6. `06_while_loops_and_variables_in_loop`
Prompt: "sprav mi test na while cyklus kde je vo vnutri tela cyklu definovana premenna val lebo v IFJcode26 keby bol DEFVAR priamo v cykle tak to v druhej iteracii padne na chybu 52"

7. `07_functions_frames_and_recursion`
Prompt: "potrebujem test na volanie funkcii ramce a rekurziu daj tam faktorial a potom aj vzajomnu rekurziu dvoch funkcii isEven a isOdd kde sa jedna vola pred svojou definiciou"

8. `08_builtin_string_and_conversion_functions`
Prompt: "sprav mi test na vstavane funkcie toStr pre vsetky typy toInt pre kladne aj zaporne desatinne cislo strLength subStr ord a chr"

9. `09_builtin_input_functions`
Prompt: "potrebujem test na citacie vstavane funkcie readLine readInt a readDouble s normalnym vstupom"

10. `10_funexp_nested_calls_and_eval_order`
Prompt: "mame spravene aj rozsirenie FUNEXP tak mi sprav test na codegen kde sa volaju funkcie priamo vo vyrazoch vnoruju sa do seba a argumenty su vyrazy vyhodnocovane zlava doprava"

## 02_edge_cases_valid

11. `01_variable_shadowing_and_scopes`
Prompt: "a teraz edgecase pre codegen v zadani je ze v podbloku sa da prekryt shadowing premenna rovnakym menom tak sprav test kde je vonku var x Int vo vnutri ifu val x String a v dalsom ife val x Int a na konci sa vypise to vonkajsie x"

12. `02_int_division_truncation_towards_zero`
Prompt: "v revizii specifikacie pisu ze celociselne delenie IDIV zaokruhluje k nule takze -5 / 2 je -2 sprav mi test na kladne a zaporne kombinacie delenia Int"

13. `03_function_return_rules_and_unit_discard`
Prompt: "v sekcii 2.3 je ze ked ma funkcia explicitne navratovy typ Unit tak sa navratova hodnota vyhodnoti ale zahodi a vrati sa () aj ked je tam return 999 a ze blok koncovany while cyklom vracia () sprav mi na vsetky tieto pravidla test"

14. `04_substr_and_ord_boundary_cases`
Prompt: "sprav mi edgecase na subStr a ord ked je start rovne end napr subStr abc 0 0 alebo end rovne dlzke stringu a pri ord ked je prazdny string alebo zaporny index alebo index mimo rozsah kedy to ma vratit -1 a nie zhodit interpret"

15. `05_read_invalid_and_eof_fallbacks`
Prompt: "podla specifikacie instrukcia READ v IFJcode26 vracia pri chybe alebo EOF hodnotu nil ale funkcie readInt a readDouble musia vtedy vratit 0 a readLine prazdny string sprav na to test so zlym vstupom a EOF"

16. `06_ifjcode26_string_escaping_special_chars`
Prompt: "v IFJcode26 sa musia v stringoch znaky do 032 mriezka 035 a lomitko 092 escapovat cez \xyz inak to interpret neprelozi sprav test kde je v stringu medzera mriezka # lomitko \ a tabulator"

17. `07_tostr_vs_print_double_formatting`
Prompt: "v zadani je upozornenie ze toStr pre Double vypisuje format %.2f cez FLOAT2STR takze 1.2345 da 1.23 sprav na to test"

## 03_runtime_errors

18. `01_err40_substr_start_negative`
Prompt: "teraz potrebujem behove chyby pri subStr kde prekladac musi vygenerovat kod co skonci s navratovym kodom 40 sprav prvy test kde je start zaporny"

19. `02_err40_substr_end_negative`
Prompt: "sprav druhy test na subStr chybu 40 kde je parameter end zaporny"

20. `03_err40_substr_start_gt_end`
Prompt: "sprav test na subStr chybu 40 kde je start vacsi ako end"

21. `04_err40_substr_start_ge_length`
Prompt: "v zadani je ze subStr konci chybou 40 aj ked je start vacsi alebo rovny strLength tak sprav test pre string dlzky 5 kde je start 5 a end 5"

22. `05_err40_substr_end_gt_length`
Prompt: "sprav test na subStr chybu 40 kde je end vacsi ako dlzka stringu"

23. `06_err40_substr_empty_string`
Prompt: "ked zavolam subStr na prazdny string "" s 0 a 0 tak start 0 je rovny dlzke 0 cize start >= strLength a musi to tiez hodit chybu 40 sprav na to test"

24. `07_err_chr_negative`
Prompt: "funkcia chr funguje len pre 0 az 127 a ina hodnota vedie na behovu chybu sprav test na chr(-1)"

25. `08_err_chr_above_127`
Prompt: "sprav este test na chr(128) co je tiez mimo interval ASCII a ma skoncit behovou chybou"

26. `09_err_div_by_zero_int`
Prompt: "celociselne delenie nulou sa v prekladaci neosetruje a ma skoncit chybou interpretu 57 pri instrukcii IDIV sprav na to test"
