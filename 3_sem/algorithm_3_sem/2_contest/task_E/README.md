E. Минимакс

Ограничение времени	2 секунды
Ограничение памяти	256Mb
Ввод	стандартный ввод или input.txt
Вывод	стандартный вывод или output.txt

Реализуйте структуру данных, способную выполнять операции ниже. Напишите программу, реализовав все указанные здесь методы. Возможные команды для программы:

insert n — добавить в структуру число n (1 ≤ n ≤ 10^9) (значение n задается после команды). Программа должна вывести ok.
extract_min — удалить из структуры минимальный элемент. Программа должна вывести его значение.
get_min — программа должна вывести значение минимального элемента, не удаляя его из структуры.
extract_max — удалить из структуры максимальный элемент. Программа должна вывести его значение.
get_max — программа должна вывести значение миаксимального элемента, не удаляя его из структуры.
size — программа должна вывести количество элементов в структуре.
clear — Программа должна очистить структуру и вывести ok.
Перед исполнением операций extract_min, extract_max, get_min и get_max программа должна проверять, содержится ли в структуре хотя бы один элемент.

Если во входных данных встречается операция extract_min, extract_max, get_min или get_max, и при этом в структуре нет ни одного элемента, то программа должна вместо числового значения вывести строку error.

Формат ввода
В первой строке входных данных записано единственное число M (1 ≤ M ≤ 2 ⋅ 10^5) — количество команд.

В следующих М строках дано по одной команде из тех, что идут выше.

Формат вывода
Для каждой команды выведите одну строчку — результат ее выполнения.

Примечания
Запрещено использовать set!