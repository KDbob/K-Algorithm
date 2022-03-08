1. 计算适应度比例，即每个个体的选择概率：


$$
p\left( x_i \right)=\frac{f\left( x_j \right)}{\sum_{j=1}^{N}{f\left( x_i \right)}}
$$

2. 计算每个个体的累积概率，相当于轮盘上的“跨度”，“跨度”越大越容易选到：

$$
q_i=\sum_{j=1}^{i}f\left(x_j\right)
$$

​	

