# algorithms
### Где используется декартач?
##### Задачи, в которых требуется достаточно сбалансированное дерево поиска (например, эффективная реализация множеств или словарей);
##### Широкий класс задач с запросами на диапазонах (RSQ, RMQ и др.), в том числе с обновлениями на отрезках. В отличие от деревьев отрезков, декартовы деревья позволяют выполнять запросы на изменяющихся множествах;
##### Поиск порядковых статистик (определение k-го по величине элемента) за O(logN). В этом случае нужно поддерживать поля cnt, и далее по этой информации определять, в каком поддереве будет располагаться нужный элемент;
##### Решение обратной задачи (определение номера элемента в отсортированной последовательности) за O(logN). Требуется разрезать дерамиду по заданному ключу и определить количество элементов в левой части;
##### Декартово дерево служит основой для ещё более мощной структуры данных, именуемой декартовым деревом по неявному ключу, которую можно рассматривать как массив, позволяющий производить большое количество различных операций с логарифмическим временем выполнения.
---
### Где используется СНМ?
##### Большинство задач, связанных с системой непересекающихся множеств, относятся к так называемым оффлайн-задачам, когда все запросы и их порядок известны заранее. В этом случае допустимо считать и проанализировать все запросы, а также получать ответы на них в порядке, отличном от порядка поступления запросов.
##### Расчёт различных функций (сумма элементов, максимум и т. п.) на множествах. Достаточно определить отдельные массивы для значений данных функций аналогично массиву size[], должным образом инициализировать их элементы и обновлять их при слиянии множеств;
##### Задача о разрезании графа (запросы об удалении рёбер и принадлежности вершин одной компоненте связности) в оффлайн. Можно считать запросы и выполнять их в обратном порядке (что будет аналогично добавлению рёбер)
##### Определение минимального остовного дерева в оффлайн алгоритмом Крускала;
##### Определение ближайшего общего предка в оффлайн алгоритмом Тарьяна.
---
### Где использовать макс. поток?
##### Минимальный разрез 
Вычисляем максимальный поток.
Далее запускаем из истока dfs, который идёт только по рёбрам с ненулевой остаточной пропускной способностью.
Посещённые dfsом вершины составляют одну долю, непосещённые — другую, рёбра между ними составляют минимальный разрез. Величина минимального разреза равна величине максимального потока.
#### Максимальное паросочетание в двудольном графе
Строим сеть: (исток), (количество вершин первой доли), (количество вершин второй доли), (сток).
Соединяем исток со всеми вершинами первой доли рёбрами пропускной способности 1.
Соединяем вершины первой доли с вершинами второй доли рёбрами пропускной способности 1, если соответствующее ребро было в исходном графе.
Соединяем все вершины второй доли со стоком рёбрами пропускной способности 1.
Размер максимального паросочетания равен величине максимального потока. В паросочетание входят рёбра между вершинами долей, нагруженные потоком.
##### Количество рёберно-непересекающихся путей между a и b
Считаем, что рёбра исходного графа имеют пропускную способность 1.
Вычисляем максимальный поток из a в b, его величина равна ответу.
##### Количество вершинно-непересекающихся путей между a и b
Ставим в соответствие каждой вершине исходного графа две вершины («входную» и «выходную»), соединённые ребром пропускной способности 1.
Если в исходном графе было ребро (x → y), до добавляем ребро (выход_x → вход_y) пропускной способности 1.
Вычисляем максимальный поток из выход_a в вход_b, его величина равна ответу.
##### Есть ли путь из a в b и из b в c, не проходящий по одному ребру дважды.
Считаем, что рёбра исходного графа имеют пропускную способность 1.
Соединяем a и c со стоком рёбрами пропускной способности 1, вычисляем максимальный поток между b и стоком, проверяем, что его величина равна 2.
##### Минимальное количество вершинно-непересекающихся путей, покрывающих все вершины ациклического ориентированного графа
Строим сеть: (исток), (количество вершин графа), (количество вершин графа), (сток).
Соединяем исток со всеми вершинами первой доли рёбрами пропускной способности 1.
Соединяем вершину первой доли x с вершиной второй доли y рёбром пропускной способности 1, если ребро (x → y) было в исходном графе.
Соединяем все вершины второй доли со стоком рёбрами пропускной способности 1.
Минимальное количество путей равно разности количества вершин исходного графа и величины максимального паросочетания в построенном двудольном графе (или, что то же самое, величины потока в построенной сети).
##### Можно ли замостить заданную клетчатую фигуру костями домино 1 × 2
Мысленно раскрашиваем клетки фигуры в шахматном порядке. Строим сеть: (исток), (количество белых клеток), (количество чёрных клеток), (сток).
Соединяем исток со всеми белыми клетками рёбрами пропускной способности 1.
Соединяем белые клетки с соседними чёрными клетками рёбрами пропускной способности 1.
Соединяем все чёрные клетки со стоком рёбрами пропускной способности 1.
Вычисляем максимальный поток, проверяем, что его величина равна количеству клеток, делённому пополам.
##### Покрыть заданную клетчатую фигуру минимальным количеством костей домино 1 × 2
Мысленно раскрашиваем клетки фигуры в шахматном порядке. Строим сеть: (исток), (количество белых клеток), (количество чёрных клеток), (сток).
Соединяем исток со всеми белыми клетками рёбрами пропускной способности 1.
Соединяем белые клетки с соседними чёрными клетками рёбрами пропускной способности 1.
Соединяем все чёрные клетки со стоком рёбрами пропускной способности 1.
Вычисляем максимальный поток, количество костей равно (площадь фигуры - величина потока).
##### Закрасить клетки сетки так, чтобы в i-й строке было закрашено r[i], а в j-м столбце — c[j]
Строим сеть: (исток), (количество строк), (количество столбцов), (сток).
Соединяем исток со всеми вершинами второго слоя рёбрами пропускной способности r[i].
Соединяем каждую вершину второго слоя с каждой вершиной третьего слоя рёбрами пропускной способности 1.
Соединяем все вершины третьего слоя со стоком рёбрами пропускной способности c[j].
Вычисляем максимальный поток, проверяем, что его величина равна сумме r (и сумме c). Клетки, которые нужно закрасить, соответствуют рёбрам между вторым и третьим слоями, по которым идёт поток.
(Также существует более простое жадное решение)
#### Покрыть закрашенные клетки сетки минимальным количеством горизонтальных и вертикальных линий.
Строим сеть: (исток), (количество строк), (количество столбцов), (сток).
Соединяем исток со всеми вершинами второго слоя рёбрами пропускной способности 1.
Соединяем i-ю вершину второго слоя с j-й вершиной третьего слоя рёбром пропускной способности 1, если клетку [i][j] нужно покрыть.
Соединяем все вершины третьего слоя со стоком рёбрами пропускной способности 1.
Вычисляем максимальный поток, количество линий равно его величине. Через какие строки и столбцы проводить линии, определяется минимальным вершинным покрытием.
####
---
### Где используется FFT?
#### Всевозможные суммы. Задача: даны два массива a[] и b[]. Требуется найти всевозможные числа вида a[i]+b[j], и для каждого такого числа вывести количество способов получить его.
Например, для a = (1,2,3) и b = (2,4) получаем: число 3 можно получить 1 способом, 4 — также одним, 5 — 2, 6 — 1, 7 — 1.
Построим по массивам a и b два многочлена A и B. В качестве степеней в многочлене будут выступать сами числа, т.е. значения a[i] (b[i]), а в качестве коэффициентов при них — сколько раз это число встречается в массиве a (b).
Тогда, перемножив эти два многочлена за O(n \log n), мы получим многочлен C, где в качестве степеней будут всевозможные числа вида a[i]+b[j], а коэффициенты при них будут как раз искомыми количествами
#### Всевозможные скалярные произведения
Даны два массива a[] и b[] одной длины n. Требуется вывести значения каждого скалярного произведения вектора a на очередной циклический сдвиг вектора b.
Инвертируем массив a и припишем к нему в конец n нулей, а к массиву b — просто припишем самого себя. Затем перемножим их как многочлены. Теперь рассмотрим коэффициенты произведения c[n...2n-1] (как всегда, все индексы в 0-индексации). Имеем:
$$c[k]=\sum_{i + j = k} a[i]b[j]$$
```
c[k] = for i+j=k ...: a[i]b[j]
```
Поскольку все элементы a[i]=0, i=n...2n-1, то мы получаем:
$$c[k]=\sum_{i = 0}^{n - 1} a[i]b[k - i]$$
```
c[k] = for i=0...n-1: a[i]b[k-i]
```
Нетрудно увидеть в этой сумме, что это именно скалярное произведение вектора a на k-n-1-ый циклический сдвиг. Таким образом, эти коэффициенты (начиная с n-1-го и закачивая 2n-2-ым) — и есть ответ на задачу.
Асимптотика O(nlogn)
#### Две полоски
Даны две полоски, заданные как два булевских (т.е. числовых со значениями 0 или 1) массива a[] и b[]. Требуется найти все такие позиции на первой полоске, что если приложить, начиная с этой позиции, вторую полоску, ни в каком месте не получится \rm true сразу на обеих полосках. Эту задачу можно переформулировать таким образом: дана карта полоски, в виде 0/1 — можно вставать в эту клетку или нет, и дана некоторая фигурка в виде шаблона (в виде массива, в котором 0 — нет клетки, 1 — есть), требуется найти все позиции в полоске, к которым можно приложить фигурку.
Эта задача фактически ничем не отличается от предыдущей задачи — задачи о скалярном произведении. Действительно, скалярное произведение двух 0/1 массивов — это количество элементов, в которых одновременно оказались единицы. Наша задача в том, чтобы найти все циклические сдвиги второй полоски так, чтобы не нашлось ни одного элемента, в котором бы в обеих полосках оказались единицы. Т.е. мы должны найти все циклические сдвиги второго массива, при которых скалярное произведение равно нулю.
Таким образом, эту задачу мы решили за O(nlogn).
