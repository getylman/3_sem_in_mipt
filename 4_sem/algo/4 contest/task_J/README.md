J*. Англо-китайское расстояние

Расстояние Кринжововной между двумя строками равной длины — это количество индексов, в которых символы этих строк не равны.

Некая Б. решила узнать, насколько похожи предложения на китайском p на их перевод на английский s. Для этого она записала оба предложения в битовой записи. Однако в силу слабого знания что китайского, что английского, она оставила вместо некоторых битов знаки вопроса. Известно, что предложение на китайском требует не больше бит для записи, чем на английском.

Б. решила определить расстояние между предложениями как суммарное расстояние Кринжововны от p до всех подстрок s, имеющих длину |p|.

Ваша задача — заполнить знаки вопросов так, чтобы расстояние от p до s было минимально возможным.

Формат ввода
В первой строке дано предложение на английском в битовой записи s, во второй — битовая запись того же предложения на китайском p. Обе строки непусты, имеют длину не более 1000 и состоят из символов ‘0’, ‘1’ и ‘?’.

Длина строки p не превосходит длины строки s.

Формат вывода
В первой строке выведите минимальное расстояние от p до s после восстановления всех знаков вопроса.

Во второй и третьей строках соответственно выведите s и p, в которых символы ‘?’ заменены на ‘0’ и ‘1’.

Примечания
А как вы думаете, сколько международных границ отделяет Англию от Китая? Автор нашел путь через три границы
