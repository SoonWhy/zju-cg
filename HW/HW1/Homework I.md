# Homework I

- 姓名：郭炅
- 学号：3170105370
- 班级：计算机科学与技术1701班
- 课程：计算机图形学
- 授课教师：张宏鑫

### Bresenham Algorithm for Drawing Circle

- 此处仿照PPT中线的bresenham算法，进行了简单实现
- 取特殊情况下的圆，即圆心位于原点，经过计算后再移动圆
- 考虑到圆在象限中具有的八分对称性，所以只需要计算一个八分圆即可同时得到另外七个八分圆，此处选取圆弧段 $x=0$ 和 $x=y$
- **使用OpenGL简单地实现了具体算法，工程链接详见附件或者百度网盘链接（相同）**

#### Derivation Detail

- Suppose edge length of pixel is $1$.

- Define a circle function：$f(x,y)=x^2+y^2-r^2$ , for any points$(x,y)$ in coordinate system, we can judge whether they are inside the circle or outside the circle

  - $$
    f(x,y)\left\{
    \begin{aligned}
    &<0, \ (x,y)\ is\ inside\ the\ circle\\
    &=0,\ (x,y)\ is\ on\ the \ circle\ \\
    &>0,\ (x,y)\ is\ outside\ the \ circle\ \\
    \end{aligned}\right.
    $$

- Towards the current eighth circle chosen, suppose that we have draw a pixel at $(x_k,y_k)$, then we need to decide that next pixel is at $(x_k+1,y_k)$ or $(x_k+1,y_k-1)$

- We need to test the midpoint of two candidate pixels, whose position is $(x_k+1,y_k-\cfrac{1}{2})$ , then we have

  - $$
    \begin{aligned}
    p_k&=f(x_k+1,y_k-\cfrac{1}{2})\\
    &=(x_k+1)^2+(y_k-\cfrac{1}{2})^2-r^2
    \end{aligned}
    $$

- If $p_k<0$, then midpoint is inside the circle, which means midpoint is below the circle boundary, so $(x_k+1,y_k)$ is closer to circle boundary.

- If $p_k>0$, then midpoint is outside the circle, which means midpoint is above the circle boundary, so $(x_k+1,y_k - 1)$ is closer to circle boundary.

- Similarly, we can get its recursive equation by considering the next pixel, which means we have just drawn a pixel at $(x_{k+1},y_{k+1})$ , and the midpoint of candidate points is $(x_{k+1}+1,y_{k+1}-\cfrac{1}{2})$ , then we have

  - $$
    \begin{aligned}
    p_{k+1}&=f(x_{k+1}+1,y_{k+1}-\cfrac{1}{2})\\
    &=[(x_{k}+1)+1]^2+(y_{k+1}-\cfrac{1}{2})^2-r^2\\
    &=[(x_k+1)^2+(y_k-\cfrac{1}{2})^2-r^2]+2(x_k+1)+(y_{k+1}^2-y_{k}^2)-(y_{k+1}-y_{k})+1\\
    &=p_{k}+2(x_k+1)+(y_{k+1}^2-y_{k}^2)-(y_{k+1}-y_{k})+1
    \end{aligned}
    $$

  - for $y_{k+1}$ , it may be $y_{k}$ or $y_{k}-1$ according to the signal of $p_k$

- Simplify the recursive equation, we can get:

  - If $y_{k+1}=y_{k}$, then $p_{k+1}=p_{k}+2x_{k+1}+1$

  - If $y_{k+1}=y_{k}-1$ , then $p_{k+1}=p_{k}+2x_{k+1}+1-2y_{k+1}$ , and derivation process is as followed:

    - $$
      \begin{aligned}
      y_{k+1}&=y_{k}-1\\
      (y_{k+1}^2-y_{k}^2)-(y_{k+1}-y_{k})&=2-2y_{k}=-2y_{k+1}
      \end{aligned}
      $$

  - for $x_{k+1}$ and $y_{k+1}$, we can get the specific value of them:

    - $x_{k+1}=x_{k}+1$
    - $y_{k+1}=y_{k}-2$

- As for initial value, the start point$(x_0,y_0)$ is at $(0,r)$ , then we can get the initial $p_0$

  - $$
    \begin{aligned}
    p_{0}&=f(1,r-\cfrac{1}{2})\\
    &=1+(r-\cfrac{1}{2})^2-r^2\\
    &=\cfrac{5}{4}-r
    \end{aligned}
    $$

  - if we define radius as integer, then we can simply round it to $p_{0}=1-r$

#### Concrete Algorithm:

1. Whatever $r$ and $(x_c,y_c)$ is, just make $(x_0,y_0)=(0,r)$
2. Calculate $p_0=\cfrac{5}{4}-r$
3. For every $x_{k}$, from $k=0$ , just test:
   1. if $p_k<0$, then next pixel is at $(x_{k+1},y_{k})$, then $p_{k+1}=p{k}+2x_{k+1}+1$
   2. else, then next pixel is at $(x_{k+1},y_k-1)$, then $p_{k+1}=p_{k}+2x_{k+1}+1-2y_{k+1}$
   3. $x_{k+1}=x_{k}+1$ and $y_{k+1}=y_{k}-2$
4. Get the symmetric points.
5. Move circle to right position, which means center of the circle from $(0,0)$ to $(x_c,y_c)$.

#### Implementation

- Use OpenGL
- Please read the file named **'Readme.md'** to get details.
- running screenshot as followed:

![1568904894682](1568904894682.png)

- core code:

```c++
// core procedure of bresenham algorithm
while (cirPt.getx() < cirPt.gety()) {

    // next point
    cirPt.incrementX();

    // recursive procedure
    if (p < 0) {
        p += 2 * cirPt.getx() + 1;
    }
    else
    {
        cirPt.decrementY();
        p += 2 * (cirPt.getx() - cirPt.gety()) + 1;
    }

    // draw points of eight symmetric circles
    circlePlotPoints(xc, yc, cirPt);
}
```

- main data structure:

```c++
// A class used to represent the current point (x,y)
class Pixel
{
private:
	GLfloat x, y;
	
public:
	Pixel() {
		x = 0;
		y = 0;
	}

	void setCoords(GLfloat xCoordinate, GLfloat yCoordinate) {
		x = xCoordinate;
		y = yCoordinate;
	}

	GLfloat getx() const {
		return x;
	}

	GLfloat gety() const {
		return y;
	}

	// suppose the size of pixel is 1
	// in fact, we can implement a function using input value
	void incrementX() {
		x += 1;
	}

	// suppose the size of pixel is 1
	void decrementY() {
		y -= 1;
	}
};
```

