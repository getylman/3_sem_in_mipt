E. Гонка с дозарядкой

Ограничение времени	2 секунды
Ограничение памяти	256Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

Деккард Шоу планирует наказать семью. Для этого он решил, что, выиграв у них гонку, расскажет всему миру, что банда Доминика творила раньше. Однако семья Доминика не дремлет. Узнав про планы Шоу, они решили помешать ему. Для этого они выкрали планы «маршрута», по которому они будут гоняться. Они решили поделиться этим планом с вами.

Есть Y+1 гоночная трасса. i-я трасса – горизонтальный отрезок (0, i) – (X, i).

Есть n заправок. j-я заправка представляет собой вертикальный отрезок (xj, yj1) – (xj, yj2). Проезжая по i-й трассе, машина начинает в точке (0, i) и двигается прямолинейно равномерно к точке (X, i), тратя на каждую единицу расстояния одну единицу бензина. Если в какой-то момент машина проезжает заправку (точка-машина лежит на отрезке-заправке), то бак машины мгновенно заполняется до максимума. Если в какой-то момент бензин закончился, а машина не находится в точке заправки или точке (X, i), трасса считается не пройденной.

Доминик прекрасно понимает, что чем больше бак у машины, тем она тяжелее, а значит медленнее едет. Поэтому он просит вас узнать для каждого i от 0 до Y, какой минимальный объём бака должна иметь машина, чтобы пройти i-ю трассу. Машина начинает с полным баком.

Помогите Доминику, и он примет вас в семью.

Формат ввода
На первой строке целые числа n, Y, X (1 ≤ n, Y, X ≤ 2 ⋅ 10^5).

Следующие n строк содержат по три целых числа xi, yi1, yi2 — описания заправок (0 < xi < X, 0 ≤ yi1 < yi2 ≤ Y).

Формат вывода
Выведите Y + 1 целое число — ответы для всех трасс.

