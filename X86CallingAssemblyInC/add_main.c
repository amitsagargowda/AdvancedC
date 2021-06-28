/*
 * add_main.c
 *
 * A small program that illustrates how to call the add function we wrote in
 * assembly language.
 */

#include <stdio.h>

int add(int, int);

int main() {
    printf("%d\n", add(1, 2));
    printf("%d\n", add(2, -6));
    printf("%d\n", add(2, 3));
    printf("%d\n", add(-2, 4));
    printf("%d\n", add(2, -6));
    printf("%d\n", add(2, 4));
    return 0;
}