#include <iostream>

void fun(int nnum, int&container){
    container = nnum;
    //return contain;
}

int fun1(int num){
    int cont = 0;
    //fun(num,cont);
    return num;
}

int main(){
    int contain;
    fun(fun1(5), contain);
    std::cout << contain << std:: endl;
}