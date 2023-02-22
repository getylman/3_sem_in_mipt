D. Первые k элементов длинной последовательности

Ограничение времени	1 секунда
Ограничение памяти	16Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

Дана длинная последовательность целых чисел длины n. Требуется вывести в отсортированном виде её наименьшие k элементов.
Чтобы не пришлось считывать большую последовательность, её элементы задаются формулой. А именно, во входных данных содержатся числа a0,x,y. Тогда ai=(x⋅ai−1+y) (mod 2^30). Искомая последовательность — a1,a2,…,an.Обратите внимание на ограничение по памяти.

Формат ввода
В первой строке записаны n и k(1≤n≤10^7,1≤k≤1000).
В следующей строке через пробел заданы значения a0,x,y(0≤a0,x,y<2^30).

Формат вывода
Выведите k наименьших элементов последовательности в отсортированном виде.