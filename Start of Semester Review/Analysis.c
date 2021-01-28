//Diógenes Silva Pedro 11883476

void algoritmo1(int *values, int N){
    int i, j = 0; //a
    int tmp;
    for (i = 0; i < N; i++){               //1. (a+b)  2. n.(2a+b) = a + b + 2an + bn
        for (j = 0; j < N; j++){           //1. n(a+b) 2. n(n.(2a+b)) = an + bn + 2an² + bn²
            if (values[j] > values[j+1]){  //n(n(a + b)) = a.n² + b.n²
                tmp = values[j+1];         //n(n(2a)) = 2a.n²
                values[j+1] = values[j];   //n(n(2a)) = 2a.n²
                values[j] = tmp;           //n(n(a)) = a.n²
            }
        }
    }         
}

//f(n) = a + (a+b) + n.(2a+b) + n(a+b) + n(n.(2a+b)) + n(n(a+b)) + n(n(2a)) + n(n(2a)) + n(n(a))

//f(n) = a + a + b + 2an + bn + an + bn + 2an² + bn² + a.n² + b.n² + 2a.n² + 2a.n² + a.n²

//f(n) = 8an² + 2bn² + 3an + 2bn + 2a + b

//Denotando todas as variáveis com tempos aproximadamente iguais temos a = b = K, logo:

//f(n) = 10Kn² + 5Kn + 3K