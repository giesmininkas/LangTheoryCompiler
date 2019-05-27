int fibonacci(int iter) {
    int a = 1;
    int b = 1;
    int c = 1;
    
    while(iter - 2) {
        a = b;
        b = c;
        c = a + b;
        iter = iter - 1;
    }
    
    return c;
}

int power(int base, int exp) {
    int tmp = base;
    while(exp - 1) {
        tmp = tmp * base;
        exp = exp - 1;
    }
    
    return tmp;
}

void print_integer(int integer) {
    int tmp1 = integer;
    int tmp2 = 10;
    int count =  0;
    
    while(tmp1) {
        count = count + 1;
        tmp1 = tmp1 / 10;
    }
    
    while(count - 1) {
        count = count - 1;
        tmp1 = integer / power(tmp2, count);
        tmp1 = tmp1 % 10;
        tmp1 = tmp1 + 48;
        putchar(tmp1);
    }
    
    tmp1 = integer;
    tmp1 = tmp1 % 10;
    tmp1 = tmp1 + 48;
    putchar(tmp1);
    
    tmp1 = 10;
    putchar(tmp1);
    return;
}

int main() {
    int iter = 9;
    int fib = fibonacci(iter);
    
    print_integer(fib);
    return 0;
}
