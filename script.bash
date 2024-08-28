#!/bin/bash
# Simple script to greet the user
42 -c

42 -brew

42 -c

brew install readline


brew link readline --force

brew --prefix readline


export LDFLAGS="-L/goinfre/rel-mora/homebrew/opt/readline/lib"
export CPPFLAGS="-I/goinfre/rel-mora/homebrew/opt/readline/include"



source ~/.zshrc

#gcc -Wall -Wextra -Werror main.c -lreadline -L/goinfre/rel-mora/homebrew/opt/readline/lib -I/goinfre/rel-mora/homebrew/opt/readline/include