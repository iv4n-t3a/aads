# Персистентный массив

Массив с поддержкой версионности

## Формат входных данных

На первой строке идет количество запросов, далее запросы вида

* `create i j x` создать новую версию от версии `i` с `array[j] = x`
* `get i j` получить значение `j`-го элемента в `i`-й версии

## Выходные данные

Ответы на запросы `get`

## Ассимптотика операций

* `create` - `O(log n)`
* `get` - `O(log n)`

## Примечание(Сборка)

Используйте флаг `-std=c++20`, чтобы скомпилировать с 20ми плюсами.
