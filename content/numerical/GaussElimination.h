/**
* Author: IDK
* Description: Gauss Elimination. Requires global matrix a, with size n by n.
* Stores answer in ans matrix.
*/
#pragma once

void gauss() {
    FOR(j,1,n+1) {
        if (a[j][j]==0) {
            FOR(i,j+1,n+1) {
                if (a[i][j]!=0) {
                    FOR(k,j+1,n+2) swap(a[i][k],a[j][k]);
                    break;
                }
            }
        }
        FOR(i,j+1,n+1) {
            double x=a[i][j]/a[j][j];
            FOR(k,j+1,n+2) a[i][k]-=x*a[j][k];
        }
    }
    for (int i=n;i;i--) {
        ans[i]=a[i][n+1]/a[i][i];
        FOR(j,1,i) a[j][n+1]-=ans[i]*a[j][i];
    }
}
