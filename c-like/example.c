int foo(int f) {
   //int a = 456;
   return 4;
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
    
    //tmp1 = integer / (10 * (count - 1));
    
    //count = count - 1;
    
    tmp1 = 10;
    putchar(tmp1);
    return;
}

int main() {
    int n = '0';
    //char c = 12;
    
    int abcd = 123456;
    
    print_integer(abcd);
    
    //putchar(abcd);
    
    if ( n ) {
        
    }
  
    while ( n - 90 ) {
        /*int abcd = 13456;
        char dfgh = 'a';
        dfgh = 'b';
        
        if(abcd) {
            
        }
        else {
        
        } */
        
        n = n + 1;
        putchar(n);    
    }
    
    char c = 10;
    putchar(c);
    return foo(abcd);
}

