/*
第一类Stirling数 s(p,k)
　　
s(p,k)的一个的组合学解释是：将p个物体排成k个非空循环排列的方法数。

s(p,k)的递推公式： s(p,k)=(p-1)*s(p-1,k)+s(p-1,k-1) ,1<=k<=p-1
边界条件：s(p,0)=0 ,p>=1  s(p,p)=1  ,p>=0

递推关系的说明：
考虑第p个物品，p可以单独构成一个非空循环排列，这样前p-1种物品构成k-1个非空循环排列，方法数为s(p-1,k-1)；
也可以前p-1种物品构成k个非空循环排列，而第p个物品插入第i个物品的左边，这有(p-1)*s(p-1,k)种方法。


第二类Stirling数 S(p,k)
　　
S(p,k)的一个组合学解释是：将p个物体划分成k个非空的不可辨别的（可以理解为盒子没有编号）集合的方法数。
k!S(p,k)是把p个人分进k间有差别(如：被标有房号）的房间(无空房）的方法数。
　　
S(p,k)的递推公式是：S(p,k)=k*S(p-1,k)+S(p-1,k-1) ,1<= k<=p-1
边界条件：S(p,p)=1 ,p>=0    S(p,0)=0 ,p>=1
　　
递推关系的说明：
考虑第p个物品，p可以单独构成一个非空集合，此时前p-1个物品构成k-1个非空的不可辨别的集合，方法数为S(p-1,k-1)；
也可以前p-1种物品构成k个非空的不可辨别的集合，第p个物品放入任意一个中，这样有k*S(p-1,k)种方法。


x^k = \sum_{i=0}^{k}   Stirling2(k,i)*C(x,i)*i!

解释:
将k个球放入x个不同盒子的方案数 = k个球放入i个无标号的盒子中 * 从x中选择i个盒子 * i个盒子的顺序

*/
