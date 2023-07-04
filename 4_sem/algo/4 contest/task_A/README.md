A. Простой поток

Системы газопроводов устроены достаточно сложно. Вам нужно посчитать, какое максимальное количество газа по заданной сети газопроводов можно передать из страны A с номером 1 в страну B с номером n.

Формат ввода
Первая строка входного файла содержит n и m — количество вершин и количество газопроводов сети (2 ≤ n ≤ 100, 1 ≤ m ≤ 1000). Следующие m строк содержат по три числа: номера вершин, которые соединяет соответствующее ребро сети и его пропускную способность. Пропускные способности не превосходят 10^5.

Формат вывода
В выходной файл выведите одно число — величину максимального потока газа из вершины страны A в страну с номером n. 

Примечания
В этой задаче необходимо реализовать алгоритм Форда-Фалкерсона.