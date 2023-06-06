#include <bits/stdc++.h>
using namespace std;

int main() 
{
    int n, m;
    cin >> n;
    m = n;
    int c[n], c2[3*n];
    int rps[n][3], rps2[3*n][3], changed[3*n][3];
    for(int i = 0; i < n; i++)
    {
        char temp;
        cin >> temp >> rps[i][0] >> rps[i][1] >> rps[i][2];
        if(temp == 'R')                 // R - 0
        {
            c[i] = 0;
            c2[i] = 1;
        }
        else if(temp == 'P')            // P - 1
        {
            c[i] = 1;
            c2[i] = 2;
        }
        else if(temp == 'S')            // S - 2
        {
            c[i] = 2;
            c2[i] = 0;
        }
        rps2[i][c[i]] = rps[i][c2[i]];
        for(int j = 0; j < 3; j++)
        {
            if(j != c[i])
            {
                rps2[i][j] = 0;
            }
        }
        changed[i][0] = changed[i][1] = changed[i][2] = 0;
    }

    int pos = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(rps2[i][j] != 0)
                continue;

            int k = pos, count = 0;;
            while(1)
            {
                if(count == n)
                    break;

                if(c[k] == j)
                {
                    rps2[i][j] = rps[k][c2[i]];
                    break;
                }
                k++;
                k %= n;
                count++;
            }
            if(count == n)
                rps2[i][j] = 1;
            pos = k;
        }
    }

    int state1 = 1, state2 = 1, play1, play2, prevstate1 = 1, prevstate2 = 1, maxlosscount = 1, loopcount = 0, maxloopcount = 1;

    for(int k = 0; k < 3; k++)
    {
        for(int i = 1; i < n; i++)
        {
            loopcount = 0;
            state2 = 1;
            state1 = i+1;
            play1 = c[state1-1];
            play2 = c2[state2-1];
            prevstate1 = state1;
            prevstate2 = state2;
            int losscount = 0;
            for(int j = 0; j < 100; j++)
            {
                state1 = rps[state1-1][play2];
                state2 = rps2[state2-1][play1];
                play1 = c[state1-1];
                play2 = c2[state2-1];

                if(state1 == state2)
                    break;

                if(play1 == play2 || (play2+1)%3 == play1)
                {
                    losscount++;
                    if((c[prevstate1-1]+1)%3 == c2[prevstate2-1]) // do not modify a winning transition
                    {
                        loopcount++;
                    }
                    else if(losscount >= maxlosscount && changed[prevstate2-1][c[prevstate1-1]] == 1)
                    {
                        m++;
                        c2[m-1] = c2[state2-1];
                        rps2[m-1][0] = rps2[state2-1][0];
                        rps2[m-1][1] = rps2[state2-1][1];
                        rps2[m-1][2] = rps2[state2-1][2];
                        rps2[prevstate2-1][c[prevstate1-1]] = m;
                        rps2[m-1][c[state1-1]] = rps[state1-1][c2[state2-1]];
                        changed[prevstate2-1][c[prevstate1-1]] = 2;
                        changed[m-1][0] = changed[m-1][1] = changed[m-1][2] = 0;
                        maxlosscount++;
                        break;
                    }
                    else if(losscount >= maxlosscount && (c[prevstate1-1]+1)%3 != c2[prevstate2-1]) 
                    {
                        rps2[prevstate2-1][c[prevstate1-1]] = rps[prevstate1-1][c2[prevstate2-1]];
                        changed[prevstate2-1][c[prevstate1-1]] = 1;
                        state1 = prevstate1;
                        state2 = prevstate2;
                        maxlosscount++;
                        break;
                    }
                }

                if(loopcount > maxloopcount)
                {
                    m++;
                    maxloopcount++;
                    c2[m-1] = c2[state2-1];
                    rps2[m-1][0] = rps2[state2-1][0];
                    rps2[m-1][1] = rps2[state2-1][1];
                    rps2[m-1][2] = rps2[state2-1][2];
                    rps2[prevstate2-1][c[prevstate1-1]] = m;
                    rps2[m-1][c[state1-1]] = rps[state1-1][c2[state2-1]];
                    changed[prevstate2-1][c[prevstate1-1]] = 2;
                    changed[m-1][0] = changed[m-1][1] = changed[m-1][2] = 0;
                    break;
                }

                prevstate1 = state1;
                prevstate2 = state2;
            }
        }
    }

    cout << m << endl;
    for(int i = 0; i < m; i++)
    {
        char temp;
        if(c2[i] == 0)
            temp = 'R';
        else if(c2[i] == 1)
            temp = 'P';
        else if(c2[i] == 2)
            temp = 'S';

        cout << temp << " " << rps2[i][0] << " " << rps2[i][1] << " " << rps2[i][2] << endl;
    }
}
