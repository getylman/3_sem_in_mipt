D*. Лондон и его окрестности

Ограничение времени	2 секунды
Ограничение памяти	512Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

«London is the capital of Great Britain» (с) Ваш Учитель английского

Как известно, Лондон делится на несколько зон. Между ними разная стоимость проезда, в них разные цены на жилье и в принципе уровень жизни в них различный. Лондонское метро London ungerground старейшее в мире и одно из крупнейших на нашей планете. По большей части зоны современного Лондона определялись именно расположением станций.

Вам дан набор из N достопримечательностей с их координатами (x, y), при этом множество этих мест таково, что если построить их выпуклую оболочку, то все, что попадет внутрь, будет нулевой зоной. Если же выбросить из набора точки, образующие нулевую оболочку (или попавшую на ее контур), то все, что лежит внутри выпуклой оболочки оставшихся точек является уже первой зоной. По индукции можно построить разбиение города на «концентрированные» выпуклые оболочки. Номер зоны, в которой лежит заданная точка, определяется максимальным номером выпуклой оболочки, в которой она еще лежит внутри либо на ее границе.

Историк Боб хочет узнать номер зоны, в которой расположена каждая из K станций метро Лондона из своего списка.

Формат ввода
В первой строке вам дается число N (3 ≤ N ≤ 10^3) — количество достопримечательностей для разбиения города на зоны.

Далее идут N строк по два целых числа через пробел (xi, yi) (-10^9 ≤ xi, yi ≤ 10^9) — координаты достопримечательностей. Гарантируется, что одинаковых точек нет.

На следующей строке идет число K (1 ≤ K ≤ 5 ⋅ 10^4) — количество станций станций London tube, номер зоны которых хочет узнать Боб.

Далее идут K строк по два целых числа через пробел (xi, yi) (-10^9 ≤ xi, yi ≤ 10^9) — координаты станций.

Формат вывода
Выведите K строк из одного целого числа, где на i-й строке номер зоны i-й станции на вводе. Если станция лежит вне нулевой зоны, то для нее выводите ноль.
