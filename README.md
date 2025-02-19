# Курсовой проект «Игра "Жизнь"»

Упрощённая консольная реализация игры «Жизнь», придуманная английским математиком Джоном Конвеем в 1970 году.

## Содержание

### 1. Правила игры
Место действия игры — Вселенная. Это размеченная на клетки ограниченная плоскость.

Каждая клетка на этой плоскости может находиться в двух состояниях: быть «живой», то есть заполненной, или быть «мёртвой», то есть пустой. Клетка имеет восемь соседей, окружающих её.

Распределение живых клеток в начале игры называется первым поколением. Каждое следующее поколение рассчитывается на основе предыдущего по правилам:
1. В пустой (мёртвой) клетке, рядом с которой ровно три живых клетки, зарождается жизнь.
2. Если у живой клетки есть две или три живых соседки, то эта клетка продолжает жить. В противном случае, если соседей меньше двух или больше трёх, клетка умирает «от одиночества» или «от перенаселённости».

Игра прекращается, если:
-   на поле не останется ни одной «живой» клетки;
-   при очередном шаге ни одна из клеток не меняет своего состояния, то есть складывается стабильная конфигурация.
  
Игрок не принимает прямого участия в игре, а только расставляет начальную конфигурацию «живых» клеток, которые затем взаимодействуют согласно правилам уже без его участия. Он является наблюдателем.

### 2. Требования к решению

Реализация должна удовлетворять требованиям и ограничениям:
1. Текущее состояние Вселенной выводится на консоль в виде таблицы из символов, разделённых пробелом. Мёртвая клетка помечается символом `-`, живая клетка помечается символом `*`. Ниже приведены примеры.
2. На каждом шаге на консоль должно выводиться текущее состояние Вселенной, а также информация о номере поколения и количестве живых клеток на текущий момент.
3. При завершении игры на консоли должно присутствовать состояние Вселенной на момент окончания игры, номер поколения, количество живых клеток и причина завершения игры.
4. При расчёте состояния клеток на границах игрового поля учитываются только соседние клетки. У клеток на границе игрового поля соседних клеток будет меньше 8.
5. Для инициализации Вселенной использовать текстовый файл. Файл имеет структуру: первые два числа — это количество строк и количество столбцов в сетке Вселенной. Затем идёт информация о распределении живых клеток. Распределение состоит из неопределённого количества пар чисел, где каждая пара состоит из номера строки и номера столбца живой клетки.

Примеры входного файла, соответствующее ему начальное состояние Вселенной и конечное состояние:

##### Пример 1
```
20 30
2 3
2 4
3 4
3 5
3 6
3 7
5 0
5 1
5 2
6 2
```  
![начальное распределение 1](./images/1_start.png)
![конечное распределение 1](./images/1_end.png)
##### Пример 2
```
10 10
```  
![начальное и конечное распределение 2](./images/2_start_end.png)
##### Пример 3
```
3 3
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
```  
![начальное распределение 3](./images/3_start.png)
![конечное распределение 3](./images/3_end.png)

### 3. Дополнительный материал
1. При выводе на консоль каждого следующего состояния у вас никуда не денутся те состояния, которые вы выводили ранее. Это может быть полезно для сохранения истории развития вашей Вселенной, но при этом может выглядеть не совсем эстетично.
Альтернативный вариант — очищать консоль перед каждым выводом следующего состояния. Для этого можно использовать функцию `std::system` с аргументом `"clear"`, то есть вызвать функцию `std::system("clear");`. Эта функция находится в библиотеке `<cstdlib>`.
2. Компьютеры сейчас работают быстро, поэтому без дополнительных действий состояния будут сменять друг друга практически мгновенно. Для комфортного просмотра разумно добавить задержку примерно в одну секунду перед каждым следующим вычислением нового состояния. Для этого необходимо подключить библиотеку `<unistd.h>` и использовать функцию `sleep`, которая принимает на вход количество секунд, на которое надо задержаться. Для задержки на одну секунду необходимо вызвать `sleep(1);`.

### 4. Пример пошаговой работы программы
Входной файл:
```
20 30
2 3
2 4
3 4
3 5
3 6
3 7
5 0
5 1
5 2
6 2
```
![поколение 1](./images/gen1.png)
![поколение 2](./images/gen2.png)
![поколение 3](./images/gen3.png)
![поколение 4](./images/gen4.png)
![поколение 5](./images/gen5.png)
![поколение 6](./images/gen6.png)
![поколение 7](./images/gen7.png)
![поколение 8](./images/gen8.png)
![поколение 9](./images/gen9.png)
![поколение 10](./images/gen10.png)
![поколение 11](./images/gen11.png)
![поколение 12](./images/gen12.png)
![поколение 13](./images/gen13.png)
![поколение 14](./images/gen14.png)

