int InverseMatrix_GaussianJordan(const float** &fMat, float **&invMat)
{
    int k, l, m, n;
    int iTemp;
    float dTemp;

    for (l = 0; l < 6; l++)
    {
        for (m = 0; m < 6; m++)
        {
            if (l == m)
                invMat[l][m] = 1;
            else
                invMat[l][m] = 0;
        }
    }

    for (l = 0; l < 6; l++)
    {
        //Find pivot (maximum lth column element) in the rest (6-l) rows
        iTemp = l;
        for (m = l + 1; m < 6; m++)
        {
            if (fMat[m][l] > fMat[iTemp][l])
            {
                iTemp = m;
            }
        }
        if (fabs(fMat[iTemp][l]) == 0)
        {
            return 1;
        }
        // Swap the row which has maximum lth column element
        if (iTemp != l)
        {
            for (k = 0; k < 6; k++)
            {
                dTemp = fMat[l][k];
                fMat[l][k] = fMat[iTemp][k];
                fMat[iTemp][k] = dTemp;

                dTemp = invMat[l][k];
                invMat[l][k] = invMat[iTemp][k];
                invMat[iTemp][k] = dTemp;
            }
        }
        // Perform row operation to form required identity matrix out of the Hessian matrix
        for (m = 0; m < 6; m++)
        {
            dTemp = fMat[m][l];
            if (m != l)
            {
                for (n = 0; n < 6; n++)
                {
                    invMat[m][n] -= invMat[l][n] * dTemp / fMat[l][l];
                    fMat[m][n] -= fMat[l][n] * dTemp / fMat[l][l];
                }
            }
            else
            {
                for (n = 0; n < 6; n++)
                {
                    invMat[m][n] /= dTemp;
                    fMat[m][n] /= dTemp;
                }
            }
        }
    }
    return 0;
}
