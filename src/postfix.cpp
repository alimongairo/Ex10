// Copyright 2021 by idpas
#include "postfix.h"
#include "MyStack.h"
#include <malloc.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int N = 1000;

std::string infix2prefix(std::string str) {
    MyStack<char> head_v(1000);
    MyStack<char> head_o(1000);
    MyStack<char> head(1000);
    char strout[N] = "";
    char c = ' ';
    int n = 0;
    int i = 0;
    float a[26] = { 0 };
    int lvl = 0;
    int lvl_o = 0;
    int v_cnt = 0;
    int o_cnt = 0;

    n = str.length();
    for (; i < n; i++) {
        lvl = get_level(str[i]);
        switch (lvl) {

        case 0:
            head_v.push(str[i]);
            a[get_letter_code(str[i])] = 1;
            v_cnt++;
            break;

        case 21:
        case 22:
            if (!head_o.isEmpty()) {
                lvl_o = get_level(head_o.get());
                if (lvl_o >= lvl) {
                    while (!head_o.isEmpty() && (get_level(head_o.get()) >= lvl)) {
                        head_v.push(head_o.get());
                        head_o.pop();
                    }
                }
                head_o.push(str[i]);
            }
            else {
                head_o.push(str[i]);
            }
            o_cnt++;
            break;

        case 10:
            head_o.push(str[i]);
            break;

        case 11:
            while (!head_o.isEmpty() && (get_level(head_o.get()) != 10)) {
                head_v.push(head_o.get());
                head_o.pop();
            }
            if (head_o.isEmpty()) {
                printf("missing '('\n");
                exit(0);
            }
            else {
                head_o.pop();
            }
            break;

        default:
            printf("wrong symbol");
            exit(0);
        }
    }
    if (v_cnt != o_cnt + 1) {
        printf("expression is not valid");
        exit(0);
    }
    while (!head_o.isEmpty()) {
        if (head_o.get() == 10) {
            printf("missing ')'\n");
            exit(0);
        }
        head_v.push(head_o.get());
        head_o.pop();
    }

    while (!head_v.isEmpty()) {
        head.push(head_v.get());
        head_v.pop();
    }
    i = 0;
    while (!head.isEmpty()) {
        strout[i] = head.get();
        head.pop();
        i++;
    }

    return strout;
}

//
int get_level(char c) {
    int code = (unsigned char)c;
    if ((code > 96) && (code < 123)) {
        return 0;
    }
    else if (code == 40) {
        return 10;
    }
    else if (code == 41) {
        return 11;
    }
    else if ((code == 43) || (code == 45)) {
        return 21;
    }
    else if ((code == 42) || (code == 47)) {
        return 22;
    }
    else {
        return -1;
    }
}

int get_letter_code(char c) {
    return (unsigned char)c - 97;
}

char get_letter(int a) {
    return (char)(a + 97);
}
