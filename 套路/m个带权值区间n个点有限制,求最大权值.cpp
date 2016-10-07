/*
如果每个点限制都是 <= X
S->1 cost = 0,cap = X.
1->2->3->...->n  cost = 0,cap = INF
n->T cost = 0,cap = X;

对于[L,R]权值为w,
L->R+1 cost = -w cap = 1
跑最小费用流
*/
