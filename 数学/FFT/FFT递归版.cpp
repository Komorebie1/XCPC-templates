void FFT(complex<double> *A, int limit, int op)
{
    if (limit == 1)
        return;
    complex<double> A1[limit / 2], A2[limit / 2];
    for (int i = 0; i < limit / 2; i++)
    {
        A1[i] = A[i * 2], A2[i] = A[i * 2 + 1];
    }
    FFT(A1, limit / 2, op), FFT(A2, limit / 2, op);
    complex<double> w1  ({cos(2 * pi / limit), sin(2 * pi / limit) * op});
    complex<double> wk({1, 0});
    for (int i = 0; i < limit / 2; i++)
    {
        A[i] = A1[i] + A2[i] * wk;
        A[i + limit / 2] = A1[i] - A2[i] * wk;
        wk = wk * w1;
    }
}