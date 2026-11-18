#!/bin/bash
#
# Project: Implementation of a Compiler for the Imperative Language IFJ26.
#
# End-to-end testy: preklad IFJ26 -> IFJcode26 -> interpret ic26int,
# porovnanie vystupu na stdout a navratovych kodov.
#
# Pouzitie:  make test_e2e   alebo   bash tests/e2e.sh
# Interpret: IC26INT=/cesta/k/ic26int, inak ic26int z PATH,
#            inak ic26int-windows-x86_64.exe v koreni projektu.
# Prekladac: IFJ26=/cesta/k/ifj26, inak ./ifj26 v koreni projektu.
#
# Druhy testov:
#   okm NAZOV 'telo @main' 'vystup' ['vstup']       platny program
#   ok  NAZOV 'program bez prologu' 'vystup' ['vstup']
#   rtm NAZOV KOD 'telo @main' 'vystup' ['vstup']   behova chyba interpretu
#   cem NAZOV KOD 'telo @main'                      chyba prekladu
#   ce  NAZOV KOD 'program bez prologu'
#   codem NAZOV 'telo @main' 'retazec v kode'       kontrola vygenerovaneho kodu
# Vystup a vstup sa zapisuju cez printf %b (\n = novy riadok),
# program sa zapisuje doslovne.

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
COMPILER="${IFJ26:-$ROOT/ifj26}"

if [ -n "$IC26INT" ]; then
  INTERP="$IC26INT"
elif command -v ic26int > /dev/null 2>&1; then
  INTERP="$(command -v ic26int)"
elif [ -f "$ROOT/ic26int-windows-x86_64.exe" ]; then
  INTERP="$ROOT/ic26int-windows-x86_64.exe"
else
  echo "e2e: interpret ic26int nenajdeny (nastav IC26INT=...)" >&2
  exit 2
fi

if [ ! -x "$COMPILER" ]; then
  echo "e2e: prekladac $COMPILER neexistuje (najprv make)" >&2
  exit 2
fi

# pracovny priecinok vnutri projektu: Windows interpret z WSL neotvori /tmp
WORK="$(mktemp -d "$ROOT/tests/.e2e_tmp.XXXXXX")" || exit 2
trap 'rm -rf "$WORK"' EXIT
cd "$WORK" || exit 2

HEADER=$'import ifj26.*\n'
MAIN=$'@main\ndef m() =\n'

total=0
failed=0
group=""
group_total=0
group_failed=0

end_group() {
  [ -n "$group" ] && printf '  %-14s %3d testov, %d zlyhalo\n' "$group" \
    "$group_total" "$group_failed"
}

skupina() {
  end_group
  group=$1
  group_total=0
  group_failed=0
}

fail() {
  failed=$((failed + 1))
  group_failed=$((group_failed + 1))
  echo "FAIL [$group/$1] $2"
}

# zobrazenie retazca so specialnymi znakmi
show() { head -c 120 "$1" | od -An -c | tr -s ' ' | head -3; }

# spolocne jadro: nazov, program, ocakavany kod prekladu, ocakavany kod
# interpretu (prazdny = nespustat), vystup, vstup
run() {
  local name=$1 prog=$2 exp_crc=$3 exp_irc=$4 exp_out=$5 input=$6
  local f="$group-$name"
  total=$((total + 1))
  group_total=$((group_total + 1))

  printf '%s\n' "$prog" > "$f.ifj"
  "$COMPILER" < "$f.ifj" > "$f.code" 2> "$f.cerr"
  local crc=$?
  if [ "$crc" != "$exp_crc" ]; then
    fail "$name" "preklad vratil $crc, ocakavane $exp_crc"
    return
  fi
  if [ "$exp_crc" != 0 ]; then
    # pri chybe prekladu nesmie byt na stdout nic
    [ -s "$f.code" ] && fail "$name" "pri chybe $crc je na stdout kod"
    return
  fi
  [ -z "$exp_irc" ] && return

  printf '%b' "$input" > "$f.in"
  # Windows interpret pise \n ako \r\n, pred porovnanim sa \r odstrani
  "$INTERP" "$f.code" < "$f.in" 2> "$f.ierr" | tr -d '\r' > "$f.out"
  local irc=${PIPESTATUS[0]}
  printf '%b' "$exp_out" > "$f.exp"
  if [ "$irc" != "$exp_irc" ]; then
    fail "$name" "interpret vratil $irc, ocakavane $exp_irc"
    head -3 "$f.ierr"
  elif ! cmp -s "$f.out" "$f.exp"; then
    fail "$name" "iny vystup"
    echo "  ocakavane:"; show "$f.exp"
    echo "  dostal:"; show "$f.out"
  fi
}

okm() { run "$1" "$HEADER$MAIN$2" 0 0 "$3" "$4"; }
ok() { run "$1" "$HEADER$2" 0 0 "$3" "$4"; }
rtm() { run "$1" "$HEADER$MAIN$3" 0 "$2" "$4" "$5"; }
cem() { run "$1" "$HEADER$MAIN$3" "$2" "" "" ""; }
ce() { run "$1" "$HEADER$3" "$2" "" "" ""; }

codem() {
  local f="$group-$1"
  total=$((total + 1))
  group_total=$((group_total + 1))
  printf '%s\n' "$HEADER$MAIN$2" > "$f.ifj"
  "$COMPILER" < "$f.ifj" > "$f.code" 2> /dev/null
  grep -qF -- "$3" "$f.code" || fail "$1" "v kode chyba '$3'"
}

echo "e2e: prekladac $COMPILER"
echo "e2e: interpret $INTERP"

# ---------------------------------------------------------------------------
skupina parser

okm aritmetika '  val a = 1 + 2 * 3 - 4 / 2' ''
okm zatvorky '  val a = ((1 + 2)) * (3)' ''
okm unarne '  val a = -1
  val b = -(a + 2) * +3
  val c = - -a' ''
okm double_mix '  val a: Double = 1
  val b = 1.5 + 2' ''
okm concat '  val s = "a" + "b"' ''
okm relacia_if '  if 1 < 2 then
    print(1)
  else
    print(2)' '1'
okm while '  var i = 0
  while i < 3 do
    i = i + 1' ''
okm unit_literal '  print(())
  val u: Unit = (((())))' '()'
ok volanie_vo_vyraze '@main
def m() =
  val a = 1 + f(2, 3) * 2
def f(a: Int, b: Int): Int =
  a + b' ''
ok vnorene_volanie '@main
def m() =
  print(f(f(1, 2), 3))
def f(a: Int, b: Int): Int =
  a + b' '6'
ok volanie_prikaz '@main
def m() =
  f(1)
def f(a: Int) =
  print(a)' '1'
ok bez_typu_pred_def '@main
def m() =
  val a = g()
  print(a)
def g() =
  1' '1'
ok koncova_ciarka '@main
def m() =
  print(f(1,
  ))
def f(a: Int): Int =
  a' '1'
okm strednik '  val a = 1; val b = a + 1' ''
okm vstavane '  val s = toStr(1)
  val n = strLength(s)
  val c = chr(65)' ''
cem operand_operand 2 '  val a = 1 2'
cem dva_operatory 2 '  val a = 1 + * 2'
cem chyba_operand 2 '  val a = 1 *'
cem prazdne_zatv_op 2 '  val a = (1 +)'
cem riadok_operator 2 '  val a = 1
  -a'
cem relacie_retaz 2 '  if 1 < 2 < 3 then
    print(1)
  else
    print(2)'
cem nedef_premenna 3 '  print(y)'
cem nedef_funkcia 3 '  val a = h(1)'
ce malo_argumentov 5 '@main
def m() =
  val a = f()
def f(a: Int): Int =
  a'
ce vela_argumentov 5 '@main
def m() =
  val a = f(1, 2)
def f(a: Int): Int =
  a'
ce zly_typ_arg 5 '@main
def m() =
  val a = f("x")
def f(a: Int): Int =
  a'
cem string_plus_int 6 '  val a = "a" + 1'
cem unarne_string 6 '  val a = -"a"'
cem unit_plus 6 '  val a = () + 42'
cem bool_mimo_if 6 '  val a = 1 < 2'
cem zapis_do_val 7 '  val a = 1
  a = 2'

# ---------------------------------------------------------------------------
skupina precedencna

okm plus_minus '  val a = 1 + -2' ''
okm krat_minus '  val a = 2 * -3' ''
okm deleno_plus '  val a = 6 / +3' ''
okm minus_minus '  val a = 1 - -2' ''
okm rel_minus '  if 1 < -2 then
    print(1)
  else
    print(2)' '2'
okm eq_minus '  if 1 == -1.5 then
    print(1)
  else
    print(2)' '2'
okm unarne_retaz '  val a = - - -1' ''
okm unarne_zatv '  val a = -(1 + 2) * -(3)' ''
cem rel_retaz_eq 2 '  val a = 1
  val b = 2
  val c = 3
  if a < b == c then
    print(1)
  else
    print(2)'
cem rel_retaz 2 '  if 1 < 2 < 3 then
    print(1)
  else
    print(2)'
okm print_vyraz '  val a = 1
  val b = 2
  print(a + b)
  print(toStr((a)))' '31'
cem print_bool 6 '  val a = 1
  print(a < 2)'
ce add_bez_ciarky 2 '@main
def m() =
  val a = add(1 2)
def add(x: Int, y: Int): Int =
  x + y'
okm unit_eq '  if () == () then
    print(1)
  else
    print(2)' '1'
okm unit_neq '  val u = ()
  if u != () then
    print(1)
  else
    print(2)' '2'
cem unit_lt 6 '  if () < () then
    print(1)
  else
    print(2)'
cem unit_eq_int 6 '  if () == 1 then
    print(1)
  else
    print(2)'
cem prazdny_vyraz 2 '  val a ='
cem iba_minus 2 '  val a = -'
cem neparova_zatv 2 '  val a = (1 + 2'
cem i_zatvorka 2 '  val a = 1 (2)'

# ---------------------------------------------------------------------------
skupina literaly

okm hello '  print("Hello, world!\n")' 'Hello, world!\n'
okm int '  print(42)' '42'
okm int_nula '  print(0)' '0'
okm int_32bit '  print(2147483647)' '2147483647'
okm int_podtrz '  print(1_000_000)' '1000000'
okm double '  print(1.5)' '0x1.8p+0'
okm double_0 '  print(0.0)' '0x0p+0'
okm double_exp '  print(1e3)' '0x1.f4p+9'
okm double_d '  print(2d)' '0x1p+1'
okm unit '  print(())' '()'
okm unit_zatv '  print(((())))' '()'
okm int_zatv '  print((7))' '7'
okm prazdny '  print("")' ''
okm specialne '  print("a#b\\c d\tx")' 'a#b\\c d\tx'
okm uvodzovky '  print("povedal \"ahoj\"")' 'povedal "ahoj"'
okm viac '  print("a")
  print(1)
  print(2.5)
  print("\n")' 'a10x1.4p+1\n'
okm strednik '  print("x"); print("y")' 'xy'
okm utf8 '  print("čšž á")' 'čšž á'
okm vyraz_arg '  print(("z"))' 'z'
# Windows ic26int oreze int@ literal na 32 bitov, kontroluje sa iba kod
codem int_max '  print(9223372036854775807)' 'PUSHS int@9223372036854775807'

# ---------------------------------------------------------------------------
skupina vyrazy

okm aritm '  print(1 + 2 * 3)' '7'
okm aritm_zatv '  print((1 + 2) * 3 - 4)' '5'
okm lava_asoc '  print(10 - 3 - 2)' '5'
okm idiv '  print(7 / 2)' '3'
okm idiv_neg '  print(-7 / 2)' '-3'
okm div '  print(7.0 / 2)' '0x1.cp+1'
okm konv_pravy '  print(2.5 + 1)' '0x1.cp+1'
okm konv_lavy '  print(1 - 0.5)' '0x1p-1'
okm konv_lavy_d '  print(1 / 2.0)' '0x1p-1'
okm konv_zlozity '  print(1 + 2 * 1.5)' '0x1p+2'
okm concat '  print("a" + "b")' 'ab'
okm concat3 '  print("a" + "b" + "c")' 'abc'
okm unar_int '  print(-5)' '-5'
okm unar_dvoj '  print(- -5)' '5'
okm unar_zatv '  print(-(2 + 3) * 2)' '-10'
okm unar_plus '  print(+3)' '3'
okm minus_nula '  print(-0.0)' '-0x0p+0'
okm unar_double '  print(-1.5)' '-0x1.8p+0'
okm val_double '  val x: Double = 1
  print(x)' '0x1p+0'
okm var_prirad '  var x = 1
  x = x + 1
  print(x)' '2'
okm var_dbl_konv '  var d: Double = 1.5
  d = 2
  print(d)' '0x1p+1'
okm premenne '  val a = 5
  val b = a * a
  print(b)' '25'
okm str_var '  val s = "x"
  print(s + s)' 'xx'
okm unit_var '  val u = ()
  print(u)' '()'
okm strednik '  val a = 2; val b = a + 1; print(a * b)' '6'
rtm nula_delenie 57 '  print(1 / 0)' ''

# ---------------------------------------------------------------------------
skupina riadenie

okm if_true '  if 1 < 2 then
    print("a")
  else
    print("b")' 'a'
okm if_false '  if 2 < 1 then
    print("a")
  else
    print("b")' 'b'
okm rel_vsetky '  val a = 2
  if a <= 2 then
    print("1")
  else
    print("0")
  if a >= 3 then
    print("1")
  else
    print("0")
  if a != 2 then
    print("1")
  else
    print("0")
  if a == 2.0 then
    print("1")
  else
    print("0")
  if 1 < 1.5 then
    print("1")
  else
    print("0")
  if "abc" < "abd" then
    print("1")
  else
    print("0")
  if () == () then
    print("1")
  else
    print("0")
  if a > 1 then
    print("1")
  else
    print("0")' '10011111'
okm while_3 '  var i = 0
  while i < 3 do
    print(i)
    i = i + 1' '012'
okm while_0 '  var i = 5
  while i < 3 do
    print(i)
    i = i + 1
  print("koniec")' 'koniec'
okm vnorene '  var i = 0
  while i < 3 do
    var j = 0
    while j < i do
      print(j)
      j = j + 1
    print(";")
    i = i + 1' ';0;01;'
okm val_v_cykle '  var i = 0
  while i < 3 do
    val x = i * 10
    print(x)
    print(" ")
    i = i + 1' '0 10 20 '
okm zatienenie '  val x = 1
  if x < 2 then
    val x = "a"
    print(x)
  else
    val x = 2.5
    print(x)
  print(x)' 'a1'
okm zatien_else '  val x = 1
  if x > 2 then
    val x = "a"
    print(x)
  else
    val x = 2.5
    print(x)
  print(x)' '0x1.4p+11'
okm if_vnoreny '  val a = 5
  if a > 3 then
    if a > 4 then
      print("vela")
    else
      print("stred")
  else
    print("malo")' 'vela'
okm zahadzovanie '  1 + 2
  "x"
  print("ok")
  ()
  print("!")' 'ok!'
okm strednik '  var i = 0; while i < 2 do
    print(i); i = i + 1
  print("e")' '01e'
okm faktorial '  var n = 5
  var f = 1
  while n > 0 do
    f = f * n
    n = n - 1
  print(f)' '120'
okm if_v_cykle '  var i = 0
  while i < 5 do
    if i / 2 * 2 == i then
      print("p")
    else
      print("n")
    i = i + 1' 'pnpnp'
okm double_cyklus '  var x = 0.0
  while x < 1 do
    x = x + 0.25
  print(x)' '0x1p+0'
okm concat_cyklus '  var s = ""
  var i = 0
  while i < 3 do
    s = s + "ab"
    i = i + 1
  print(s)' 'ababab'

# ---------------------------------------------------------------------------
skupina funkcie

ok poradie_arg '@main
def m() =
  print(sub(10, 3))
def sub(a: Int, b: Int): Int =
  a - b' '7'
ok faktorial_rek '@main
def m() =
  print(fact(5))
def fact(n: Int): Int =
  if n < 2 then
    return 1
  else
    return n * fact(n - 1)' '120'
ok fib '@main
def m() =
  var i = 0
  while i < 10 do
    print(fib(i))
    print(" ")
    i = i + 1
def fib(n: Int): Int =
  if n < 2 then
    return n
  else
    return fib(n - 1) + fib(n - 2)' '0 1 1 2 3 5 8 13 21 34 '
ok jednoriadkova '@main
def m() =
  print(dvakrat(21))
def dvakrat(x: Int): Int = x * 2' '42'
ok bez_typu_pred_def '@main
def m() =
  val a = g()
  print(a + 1)
def g() =
  41' '42'
ok odvodeny_string '@main
def m() =
  print(meno("svet"))
def meno(s: String) =
  "ahoj " + s' 'ahoj svet'
ok double_konv_arg '@main
def m() =
  print(polovica(3))
def polovica(x: Double): Double =
  x / 2' '0x1.8p+0'
ok double_konv_ret '@main
def m() =
  print(f())
def f(): Double =
  return 2' '0x1p+1'
ok double_konv_telo '@main
def m() =
  print(f())
def f(): Double =
  val a = 1
  a + 2' '0x1.8p+1'
ok double_konv_1r '@main
def m() =
  print(f())
def f(): Double = 5' '0x1.4p+2'
ok unit_explicit '@main
def m() =
  print(f())
def f(): Unit =
  1 + 2' '()'
ok unit_return_hodnota '@main
def m() =
  print(f())
def f(): Unit =
  return 5' '()'
ok unit_return_holy '@main
def m() =
  print(f())
def f(): Unit =
  print("x")
  return' 'x()'
ok unit_1r '@main
def m() =
  print(f())
def f(): Unit = 42' '()'
ok return_v_cykle '@main
def m() =
  print(prvy_vacsi(10))
def prvy_vacsi(limit: Int): Int =
  var i = 0
  while i < 100 do
    if i * i > limit then
      return i
    else
      ()
    i = i + 1
  return -1' '4'
ok vyraz_s_volaniami '@main
def m() =
  print(1 + sq(2) * sq(3) - sq(1))
def sq(x: Int): Int = x * x' '36'
ok vnorene_volania '@main
def m() =
  print(add(add(1, 2), add(3, add(4, 5))))
def add(a: Int, b: Int): Int = a + b' '15'
ok volanie_prikaz '@main
def m() =
  pozdrav("A")
  pozdrav("B")
  print("!")
def pozdrav(s: String) =
  print(s)' 'AB!'
ok param_zatienenie '@main
def m() =
  val x = 100
  print(f(1))
  print(x)
def f(x: Int): Int =
  if x < 5 then
    val y = x + 1
    return y
  else
    return x' '2100'
ok vzajomna_rek '@main
def m() =
  print(parne(10))
  print(parne(7))
def parne(n: Int): String =
  if n == 0 then
    return "T"
  else
    return neparne(n - 1)
def neparne(n: Int): String =
  if n == 0 then
    return "F"
  else
    return parne(n - 1)' 'TF'
ok unit_arg '@main
def m() =
  f(())
def f(u: Unit) =
  print(u)' '()'
ok main_neskor '
def a(): Int = 1
@main
def m() =
  print(a() + b())
def b(): Int = 2' '3'
ok if_koniec_unit '@main
def m() =
  f(1)
  f(2)
def f(x: Int) =
  if x == 1 then
    print("jeden")
  else
    print("iny")' 'jedeniny'

# ---------------------------------------------------------------------------
skupina vstavane

okm tostr_int '  print(toStr(42) + "|")' '42|'
okm tostr_double '  print(toStr(3.14159) + "|" + toStr(2))' '3.14|2'
okm tostr_double2 '  print(toStr(-0.5))' '-0.50'
okm tostr_str '  print(toStr("ab"))' 'ab'
okm tostr_unit '  print(toStr(()))' '()'
okm tostr_vyraz '  print("a" + toStr(1 + 2))' 'a3'
okm toint '  print(toInt(3.99))' '3'
okm toint_neg '  print(toInt(-3.99))' '-3'
okm toint_int_arg '  print(toInt(7))' '7'
okm chr '  print(chr(65) + chr(97))' 'Aa'
okm chr_0 '  print(strLength(chr(0)))' '1'
rtm chr_128 58 '  print(chr(128))' ''
rtm chr_neg 58 '  print(chr(-1))' ''
okm strlen '  print(strLength("hello"))' '5'
okm strlen_prazdny '  print(strLength(""))' '0'
okm strlen_vyraz '  print(strLength("ab" + "cd") * 2)' '8'
okm ord '  print(ord("A", 0))
  print(" ")
  print(ord("abc", 2))' '65 99'
okm ord_prazdny '  print(ord("", 0))' '-1'
okm ord_za '  print(ord("abc", 3))' '-1'
okm ord_neg '  print(ord("abc", -1))' '-1'
okm substr '  print(subStr("abcdef", 1, 4))' 'bcd'
okm substr_cely '  print(subStr("abc", 0, 3))' 'abc'
okm substr_prazdny '  print("[" + subStr("abc", 1, 1) + "]")' '[]'
okm substr_posl '  print(subStr("abc", 2, 3))' 'c'
rtm substr_e_33 40 '  print(subStr("abc", 3, 3))' ''
rtm substr_e_00 40 '  print(subStr("", 0, 0))' ''
rtm substr_e_neg 40 '  print(subStr("abc", -1, 2))' ''
rtm substr_e_negk 40 '  print(subStr("abc", 0, -1))' ''
rtm substr_e_obr 40 '  print(subStr("abc", 2, 1))' ''
rtm substr_e_za 40 '  print(subStr("abc", 0, 4))' ''
okm substr_cyklus '  val s = "ahoj"
  var i = 0
  while i < strLength(s) do
    print(subStr(s, i, i + 1) + ".")
    i = i + 1' 'a.h.o.j.'
okm readline '  val a = readLine()
  print("[" + a + "]")' '[ab\n]' 'ab\n'
okm readline_eof '  val a = readLine()
  print("[" + a + "]")' '[]' ''
okm readline_bez_lf '  print(readLine())
  print("|")
  print(readLine())' 'x\n|y' 'x\ny'
okm readline_dlzka '  print(strLength(readLine()))' '4' 'abc\n'
okm readint '  val a = readInt()
  val b = readInt()
  print(a + b)' '42' '40\n2\n'
okm readint_zly '  print(readInt())
  print(readInt())
  print(readInt())' '000' ' 7\nabc\n1_0\n'
okm readint_eof '  print(readInt())' '0' ''
okm readint_neg '  print(readInt())' '-5' '-5\n'
okm readdouble '  print(readDouble())' '0x1.8p+0' '1.5\n'
okm readdouble_zly '  print(readDouble())' '0x0p+0' 'x\n'
okm readdouble_eof '  print(readDouble() + 1)' '0x1p+0' ''
okm ako_prikazy '  toStr(1)
  readLine()
  strLength("x")
  print("ok")' 'ok' 'riadok\n'
okm vnorene '  print(subStr(toStr(12345), ord("b", 0) - 97, strLength("abcd")))' '234'

# ---------------------------------------------------------------------------
skupina specifikacia

# priklad z kap. 2 specifikacie
ok faktorial 'def factorial(n: Int): Int =
    var result = 1
    var i: Int = n // uvedeni typu je nepovinne
    while i > 1 do
        result = result * i
        i = i - 1
    result // posledni vyraz v tele funkce urci navratovou hodnotu
@main def runFoo(): Unit =
    val n = readInt()
    val result = factorial(n)
    print(result)
    print("\n")' '120\n' '5\n'
# priklad z kap. 5.1 (FUNEXP)
ok funexp 'def factorial(n: Int): Int =
    var result = 1
    var i: Int = n
    while i > 1 do
        result = result * i
        i = i - 1
    result
@main
def m() =
    val result = 2 * factorial(readInt() + 1)
    print(toStr(result + strLength(subStr("abcd", 1, 3))))' '50' '3\n'
okm readint_pretecenie '  print(readInt())
  print("|")
  print(readInt())' '0|3000000000' '99999999999999999999\n3000000000\n'

# ---------------------------------------------------------------------------
end_group
echo "e2e: $total testov, $failed zlyhalo"
[ "$failed" = 0 ]
