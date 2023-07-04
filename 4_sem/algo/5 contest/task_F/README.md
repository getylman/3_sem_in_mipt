F. Ахо 

Это интерактивная задача.

Каждый раз, когда Маргарет и Альфред посещают кафе «У Дональда», они играют в странную игру про угадывание строк.

Её правила таковы:

    Первый игрок пишет строку S фиксированной длины N. Также у первого игрока есть строка T, изначально пустая. Обе строки состоят только из маленьких букв английского алфавита.
    Второй игрок не знает эти строки в течение всей игры. Однако ему разрешено спрашивать про любые две позиции (в обеих строках), правда ли, что символы в них равны. Например, вопрос может выглядеть так “Равны ли второй символ строки S и пятый символ строки T?” Обратите внимание, что можно спрашивать про два символа одной строки.
    Игра состоит из M раундов. В начале каждого раунда первый игрок добавляет один символ в конец строки T.
    После добавления символа второй игрок может задать не более пяти вопросов. После этого он должен сказать, какое число подстрок строки T равно строки S.

Маргарет быстро заметила, что Альфред всегда преуспевает в роли втрого игрока. Она подозревает наличие стратегии, позволяющей второму игроку выигрывать независимо от S и T. А вы так сможете?

Формат ввода
При запуске ваша программа должна считывать два целых числа N и M (1≤N,M≤20000) из стандартного потока ввода.

Далее следуют M раундов игры. В i-м раунде вы можете задать не более пяти вопросов в формате “<позиция1> <позиция2>”. Описание любой позиции выглядит как “s x” где 1≤x≤N (если это x-й символ строки S) или как “t y” где 1≤y≤i (если это y-й символ строки T). Ответ программы жюри будет “Yes”, если символы на этих позициях равны и “No” иначе.

Формат вывода
В конце любого раунда вы должны вывести ответ в формате “$ k”, где k равно числу вхождений строки S в строки T. После этого в строку T будет автоматически добавлен новый символ (если это не последний раунд).

Не забудьте делать flush после каждого вопроса. После того, как вы вывели все m чисел, ваша программа должна автоматически завершиться, иначе ваш вердикт может быть каким угодно.

Примечания
В примере, строка S изначально равна “aba”, а строка T получается добавлением символов “a”, “b”, “a”, “c”, “a”, “b”, “a”. 