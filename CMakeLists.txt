cmake_minimum_required(VERSION 3.1)
project(cardlist)
set(SOURCE_FILES  card.c card.h cardlist.h cardlist.c cardmain.c)
add_executable(cards ${SOURCE_FILES})