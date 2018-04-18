#!/bin/bash
# Чистим экран.
clear

# Обновляем основной проект.
git pull

# Инициализируем все submodule.
git submodule update --init --recursive

# Во всех submodule переходим на ветку master.
git submodule foreach --recursive git checkout master

# Обновляем все submodule до актуального состояния.
git submodule foreach --recursive git pull