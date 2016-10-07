
//四边形
int a = 0;
int b = 1;
int c = 2;
int d = 3;

int aa = a;
int bb = b;
int cc = c;
int dd = d;

while (true)
{
    while (true)
    {
        while (true)
        {
            while (area(hull[a], hull[b], hull[c], hull[d])
                <= area(hull[a], hull[b], hull[c], hull[(d+1) % nn]))
            {
                d = (d + 1) % nn;
            }

            if (area(hull[a], hull[b], hull[c], hull[d])
                <= area(hull[a], hull[b], hull[(c+1) % nn], hull[d]))
            {
                c = (c + 1) % nn;
                continue;
            }
            else
            {
                break;
            }
        }

        if (area(hull[a], hull[b], hull[c], hull[d])
            <= area(hull[a], hull[(b+1) % nn], hull[c], hull[d]))
        {
            b = (b + 1) % nn;
            continue;
        }
        else
        {
            break;
        }
    }
    if (area(hull[a], hull[b], hull[c], hull[d])
        > area(hull[aa], hull[bb], hull[cc], hull[dd]))
    {
        aa = a;
        bb = b;
        cc = c;
        dd = d;
    }

    a = (a+1) % nn;
    if (a == b) b = (b+1) % nn;
    if (b == c) c = (c+1) % nn;
    if (c == d) d = (d+1) % nn;
    if (a == 0) break;
}

System.out.printf("%.1f\n", area(hull[aa], hull[bb],
    hull[cc], hull[dd]));
}
