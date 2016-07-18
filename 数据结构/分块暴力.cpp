
///////////////////分块暴力/////////////////////
 for(int i = L;i <= R;)
    {
        if(i%BLOCK == 0 && i + BLOCK -1 <= R)
        {
            diff[i/BLOCK] += x;
            i += BLOCK;
        }
        else
        {
            save[i] += x;
            i++;
        }
    }
