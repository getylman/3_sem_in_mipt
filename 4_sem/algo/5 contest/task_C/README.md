C. Циклическая подстрока

На курсе алгоритмов в ФПМИ есть модуль, посвященный строкам. Преподаватель решил не ограничиться стандартными задачами и предложил своим студентам следующую задачу.

Есть текст T, в котором ищут паттерн (тоже строку) P. Казалось бы, классическая задача, но семинарист решил ее усложнить, а именно, надо искать не только паттерн, но и все его циклические сдвиги. Нужно найти количество позиций вхождений (возможно пересекающихся) всех циклических сдвигов паттерна в тексте.

Отметим, что если паттерн «abс», то его циклическими сдвигами называют следующие строки: «abс», «bca», «cab».

Формат ввода
На первой строке вам дан паттерн P (1 ≤ |P| ≤ 106). На второй дан текст T длиной до 106 символов. Обе строки состоят из латинских строчных букв.

Формат вывода
Выведите ответ на задачу.