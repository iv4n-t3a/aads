# Алгоритм Косорайю

Построение графа конденсации

## Ассимптотика операций

Время работы - `O(|V| + |E|)`

## Формат входных данных

На первой строке количество веришин и ребер в графе,
далее идут ребра как пары номеров вершин.

## Выходные данные

Для каждой вершины на строке с номером `i` будет выведена пара чисел
`i` и `c`, где `i` - номер вершины, а `c` - номер компоненты связности,
которой она принадлежит.