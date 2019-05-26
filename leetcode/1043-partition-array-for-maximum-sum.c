int maxSumAfterPartitioning(int* A, int ASize, int K){
    int k[K+1] = {0}, l[K+1] = {0}, n[K+1] = {0}, edge=0, max = K + 1;
    for(int j = 0; j < ASize; j++)
    {
        for(int i = 0; i < ASize; i++)
        {
            if(A[i] > k[j])
            {
                k[j] = A[i]; 
                l[j] = i;
            }
        }
        A[l[j]] = 0;
        if(l[j] == 0 || l[j] == ASize - 1)
            edge++;
    }

    if (edge == 0)
    {
        max -= 2;
    }
    else if (edge == 1)
    {
        max -= 2;
    }

    for( int i = 0; i < max; i++)
    {
        for(int j = 0; j < max-i; j++)
        {
            if(n[i] < l[j])
        }
    }
}

