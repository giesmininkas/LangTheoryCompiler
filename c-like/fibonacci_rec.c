int fibonacci(int iter) {
    int c = 1;
    
    if(iter - 2) {
        if(iter - 1){
            int a = iter - 1;
            int b = iter - 2;
            a = fibonacci(a);
            b = fibonacci(b);
            c = a + b;    
        }
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


int foo(int a) {
    if(a) {
        int tmp = a - 1;
        tmp = foo(tmp);
        a = a + tmp;
    }
    return a;
}

int main() {
    int iter = 40;
    int fib = fibonacci(iter);
    
    print_integer(fib);
    
    //int a = 4;
    //int b = foo(a);
    //print_integer(b);
    return 0;
}
