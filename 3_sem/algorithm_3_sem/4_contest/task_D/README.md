D. Звезды

Ограничение времени	1 секунда
Ограничение памяти	64Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

В этой задаче используйте дерево Фенвика.
Марк любит наблюдать за звездами над Пантеллерией. Но следить за ними и над Риадом, и над Мединой ему крайне тяжело. Поэтому он наблюдает только за частью пространства, ограниченной кубом размером n×n×n. Этот куб поделен на маленькие кубики размером 1×1×1. Во время его наблюдений могут происходить следующие события:
В каком-то кубике появляются или исчезают несколько звезд.
К нему может заглянуть его друг Рома и поинтересоваться, сколько видно звезд в части пространства, состоящей из нескольких кубиков.

Формат ввода
Первая строка входного файла содержит натуральное число 1≤n≤128. Координаты кубиков — целые числа от 0 до n−1. Далее следуют записи о происходивших событиях по одной в строке. В начале строки записано число m. Если m равно:то за ним следуют 4 числа — x, y, z (0≤x,y,z < N) и k (−20000≤k≤20000) — координаты кубика и величина, на которую в нем изменилось количество видимых звезд;то за ним следуют 6 чисел — x1, y1, z1, x2, y2, z2 (0≤x1≤x2 < N, 0≤y1≤y2 < N, 0 ≤ z1 ≤ z2 < N), которые означают, что Рома попросил подсчитать количество звезд в кубиках (x,y,z) из области: x1≤x≤x2, y1≤y≤y2, z1≤z≤z2;то это означает, что Марку надоело наблюдать за звездами и отвечать на вопросы Ромы. Эта запись встречается во входном файле только один раз и будет последней записью.
Количество записей во входном файле не больше 100002.

Формат вывода
Для каждого вопроса Ромы выведите на отдельной строке одно число — искомое количество звезд.