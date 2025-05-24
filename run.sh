#!/bin/bash

cd "$(dirname "$0")" # Переход в корень проекта

# Автоматическая сборка если нет бинарника
if [ ! -f build/avltree_app ]; then
    ./build.sh
fi

# Запуск программы
exec ./build/avltree_app
