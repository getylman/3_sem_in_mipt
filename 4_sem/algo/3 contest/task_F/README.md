F. Самый быстрый индплан

Учебный офис ФПМИ по организационной структуре представляет из себя дерево. Это связано с тем, что так число контактирующих пар специалистов оказывается минимальным. При этом для некоторых пар (i, j) известно, что требуется ровно один час, чтобы передать информацию между сотрудниками с номерами i и j. Остальные пары специалистов между собой не контактируют.

Студент знает, что для согласования его заявления на индплан необходимо, чтобы подписи поставили сотрудники с номерами i и j. Заявление он может подать только одному из них (тот сразу ставит подпись и отправляет второму, быть может через промежуточных специалистов). Необходимо для каждого заявления узнать, сколько часов будут его согласовывать.

Формат ввода
В первой строке находится одно целое число N (1 ≤ N ≤ 10^5) — количество специалистов в учебном офисе.

В каждой из следующих N - 1 строк задано по два числа, разделенных пробелом, i, j  — номера специалистов, контактирующих между собой (1 ≤ i, j ≤ N).

В следующей строке задано число Q — количество заявлений на индплан (0 ≤ M ≤ 10^5).

В каждой из следующих Q строк задано по два числа — номера специалистов, чьи подписи нужны на очередном заявлении.

Формат вывода
Выведите Q строк, в каждой из которых содержится одно целое число — ответ на очередной запрос. Ответы необходимо вывести в порядке, соответствующем порядку запросов на входе программы. 