G. Очередная классика

Задано подвешенное дерево, содержащее n (1≤n≤100000) вершин, пронумерованных от 0 до n−1. Требуется ответить на m (1≤m≤10000000) запросов о наименьшем общем предке для пары вершин.

Запросы генерируются следующим образом. Заданы числа a1,a2 и числа x, y и z. Числа a3,…,a2m генерируются следующим образом: ai=(x⋅ai−2+y⋅ai−1+z)modn. Первый запрос имеет вид ⟨a1,a2⟩. Если ответ на i−1-й запрос равен v, то i-й запрос имеет вид ⟨(a2i−1+v)modn,a2i⟩.

Формат ввода
Первая строка содержит два числа: n и m. Корень дерева имеет номер 0. Вторая строка содержит n−1 целых чисел, i-е из этих чисел равно номеру родителя вершины i. Третья строка содержит два целых числа в диапазоне от 0 до n−1: a1 и a2. Четвертая строка содержит три целых числа: x, y и z, эти числа неотрицательны и не превосходят 10^9.

Формат вывода
Выведите в выходной файл сумму номеров вершин — ответов на все запросы.
