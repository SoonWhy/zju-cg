# Homwork5

- 姓名：郭炅
- 学号：3170105370
- 专业：计算机科学与技术
- 授课老师：张宏鑫

## Requirement

- Render a car with POVRAY
- Resolution: > 640 $\times$ 480

## Result

### 1st Method

![image-20191226104527993](image-20191226104527993.png)

- A red car with inside space
- Four wheels combined with some basic solid figures
- draw by use some CSG method with basic graphes

### 2nd Method

![image-20191226114543038](image-20191226114543038.png)

- A blue car with more details
- The geometric relationship is normal and surface is more smooth

## Details

### 1st Structure

graph

|--ground

​		|--plane with grass texture

<img src="image-20191226112308375.png" alt="image-20191226112308375" style="zoom:25%;" />

|--car

​		|--Top part of car

<img src="image-20191226112452679.png" alt="image-20191226112452679" style="zoom:25%;" />

​				|--entity combined by two intersected round boxes

<img src="image-20191226113210353.png" alt="image-20191226113210353" style="zoom:25%;" />

​				|--(difference) front and back axles

<img src="image-20191226113139655.png" alt="image-20191226113139655" style="zoom:25%;" />

​				|--(difference) inside space in entity combined by two intersected round boxes(all in the inside space, so pic cannot show this procedure until next step)

<img src="image-20191226113335816.png" alt="image-20191226113335816" style="zoom:25%;" />

​				|--(difference, then intersection)side windows

​						|--two prisms intersected with inside space

<img src="image-20191226113621154.png" alt="image-20191226113621154" style="zoom:25%;" />

<img src="image-20191226112645464.png" alt="image-20191226112645464" style="zoom:25%;" />

​				|--(difference, then intersection)font and back windows

​						|--two round boxes intersected with inside space

<img src="image-20191226113451159.png" alt="image-20191226113451159" style="zoom:25%;" />

<img src="image-20191226113531630.png" alt="image-20191226113531630" style="zoom:25%;" />

<img src="image-20191226112602811.png" alt="image-20191226112602811" style="zoom:25%;" />

​		|--Middle part of car

<img src="image-20191226113739498.png" alt="image-20191226113739498" style="zoom:25%;" />

​				|--base entity, a round box

<img src="image-20191226113835119.png" alt="image-20191226113835119" style="zoom:25%;" />

​				|--(difference)space for wheels

<img src="image-20191226113953008.png" alt="image-20191226113953008" style="zoom:25%;" />

​				|--(difference)inside space in entity combined by two intersected round boxes

<img src="image-20191226114045135.png" alt="image-20191226114045135" style="zoom:25%;" />

​				|--(plus) front and back axles, part of two cylinders(intersected with inside sapce). The reason is that simple difference will poduce hole, so must front and back axles.

<img src="image-20191226114114134.png" alt="image-20191226114114134" style="zoom:25%;" />

​		|--wheels

<img src="image-20191226111959109.png" alt="image-20191226111959109" style="zoom:25%;" />

​				|--single wheel

<img src="image-20191226112033855.png" alt="image-20191226112033855" style="zoom:25%;" />

​						|--tire, intersection combined by torus and cylinder

​																								<img src="image-20191226112136151.png" alt="image-20191226112136151" style="zoom:25%;" />			

​						|--wheel hub, which is sphere

<img src="image-20191226112229231.png" alt="image-20191226112229231" style="zoom:25%;" />

### 2nd Structure

This method uses obj's data and draws the many meshes to construct smooth surfaces. Towards different meshes, give them different color. 