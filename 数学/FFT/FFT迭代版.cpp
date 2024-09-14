void change(complex<double> *A, int len)
{
    for (int i = 0; i < len; i++)
        R[i] = R[i / 2] / 2 + ((i & 1) ? len / 2 : 0);
    for (int i = 0; i < len; i++)
        if (i < R[i]) swap(A[i], A[R[i]]);
}

void FFT(complex<double> *A, int limit, int op)
{
    change(A, limit);
    for (int k = 2; k <= limit; k <<= 1)
    {
        complex<double> w1  ({cos(2 * pi / k), sin(2 * pi / k) * op});
        for (int i = 0; i < limit; i += k)
        {
            complex<double> wk({1, 0});
            for (int j = 0; j < k / 2; j++)
            {
                complex<double> x = A[i + j], y = A[i + j + k / 2] * wk;
                A[i + j] = x + y;
                A[i + j + k / 2] = x - y;
                wk = wk * w1;
            }
        }
    }
}