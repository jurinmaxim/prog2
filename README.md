# Objektumorientált Lift szimulátor: Programozás Alapjai 2 NHF

## Leírás
A lift szimulátor algoritmusa azon alapszik, hogy az összes működésben levő lift külön van
vezérelve, és ezért nem avatkoznak bele egymás dolgába. Mivel több lift szállít utasokat
egyszerre, ezért nem volt megfelelő az egy liftre illeszkedő liftalgoritmusom.
A liftek működésének kulcsa a lift státusza. A liftek minden szimulált másodpercben
ellenőrzik a lift státuszát, és annak megfelelően végzik el teendőjüket. A lift lehet álló és
mozgó állapotban, továbbá ezek az állapotok megoszlanak arra, hogy melyik irányba ment
illetve megy a lift.
A második fontos eleme az algoritmusnak az, hogy az egyes liftek mi alapján haladnak az
épületben. A lift alapvetően úgy működik, mint manapság a liftek többsége: addig megy az
egyik irányba, amíg a legtávolabbi utasítás történt, utána megfordul.
Mindegyik lift az éppen benne utazó utasok közül kiválaszt egyet, amelyik a célutas lesz, és
annak a célutasnak az emelete felé fog haladni addig, amíg meg érkezik oda. Közben az
elhaladó szinteknél ellenőrzi, hogy van-e hívás, vagy van-e kiszálló azon a szinten, és hogyha
van, akkor beszállnak a lift kapacitásához igazodva, illetve kiszállnak az utasok.
A lift szimuláció minden körben ellenőrzi, hogy kész van-e az összes utas, amit az utas
státusza mutat. Az utas státusza lehet várakozó valamelyik irányba, utazó vagy kész. Ha kész
van az összes utas, akkor számítja ki a statisztikát a program, ami a várakozási idő átlagát és
az utazási idő átlagát írja ki a standard kimenetre.

## Adatszerkezetek
A lift szimulátor megvalósításához hat classt használtam fel, névlegesen a Lift, Emelet, Utas,
Szimuláció, SzimulációIdő és az UtasLista classokat. A program futása során ezek az
objektumok egymással kommunikálnak és kerülnek kölcsönhatásba.
Mivel a bővíthetőség egy fontos szempont volt a program elkészítésében, ezért a Liftek
száma tetszőlegesen megválaszható, továbbá az input file adataitól függ az épület
magassága és az utasok száma is (Az én példámban egy random generátor által generált, 0-
100-ig számozott emeleteket tartalmaz a file).
Így látszik, hogy az Emeletből annyi példány lesz, ahány emelet van, Liftből annyi, ahány lift
van (jelen esetben 4), Utasból annyi, ahány utas van. Szimulációból, mivel egy fut le, ezért
egy darab lesz, továbbá a SzimulációIdő és az UtasListából is 1-1 lesz, mert ezek statikus
pointerek amik egy példányra mutatnak.
A statisztika készítés egyik fő szempontja a programnak, és a lift szimulátor a két
legkézenfekvőbb statisztikát számolja ki: várakozási idő, utazási idő, és ezeknek a az átlagai.

***Készítette: Jurin Maxim, 2017 BME*** 
