# ОПИСАНИЕ КОДА ПРОЕКТА
В данной деректории содержится исходный текст файла описания кода, написанный в latex. 

# ЗАВИСИМОСТИ
Для его сборки требуется следующее окружение:
* ubuntu (минимум v16.04)
* inkscape (минимум v0.92)
* GNU Make (минимум v4.1)
* plantuml
* texlive-full

# УСТАНОВКА НЕОБХОДИМЫХ ЗАВИСИМОСТЕЙ
...
$ sudo apt update
$ sudo apt install make
$ sudo apt install inkscape
$ sudo apt install plantuml
$ sudo apt install texlive-full
...

# СБОРКА ДОКУМЕНТА
...
$ make all
...

# ОЧИСТКА ПРОЕКТА

...
$ make clean
...