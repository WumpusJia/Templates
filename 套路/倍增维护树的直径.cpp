/*
���ȶ�����������LCAԤ����
Ȼ��1-n���μ���
���ԭֱ����a-b,������ֱ��Ϊmax(a-b,a-i,b-i)
*/


int cal(int a,int b)//����a-b���ϵĵ���
{
    int t = LCA(a,b);
    return deep[a]+deep[b]-2*deep[t]+1;
}


