# 公交车调度系统
北邮2022年大一计导期末大作业公交车调度系统，包含控制台版与GUI版

## **如果你是北邮计院大一学生，请勿以任何形式抄袭或挪用这份代码！！！** 

&emsp;

~~特别是2021届的赵玉宁，贺孟涵~~
***
&emsp;

## 预览

![截图](https://github.com/ZYL-DF/Pic_res/raw/main/2.png?raw=true)
![截图](https://github.com/ZYL-DF/Pic_res/raw/main/1.png?raw=true)
![截图](https://github.com/ZYL-DF/Pic_res/raw/main/3.png?raw=true)

&emsp;
***
## 特点
* 独特UI设计，摒弃传统按钮控件，界面更美观
* 输入操作方便，符合正常人类使用需求
* 三条轨道的设计，要去哪，车在哪，一目了然
* 精选动感洋气bgm，开车更有范儿
* 11款主题皮肤，原批原黑自己当!


&emsp;
***
## 更新说明

* 修复了主窗口名称错误的问题
* 更新了一首精心制作的bgm

&emsp;
***
## 已知BUG
## 公交车出发时，有一定的卡顿
&nbsp;&nbsp;&nbsp;&nbsp;这其实是根本上的程序设计问题，公交车从空闲状态转到移动状态时，是没有延时一秒的；也就是说，公交车何时出发，绘图层不知道。&emsp;

&nbsp;&nbsp;&nbsp;&nbsp;因此，在绘图时运用了大量_fix变量来修补这个bug,具体体现为:绘图层在公交车由空闲态出发时，从起点到第一个位置的动画是没有根据output来绘制的，完全是由绘图层自己操作的。&emsp;

&nbsp;&nbsp;&nbsp;&nbsp;但这同时也带来一个问题：逻辑层可能在延时过程之中。所以，程序进行了一个操作，让逻辑层退出当前延时，再重新进行一次延时，才能让绘图层完成第一步的动画。但是Qt的动画系统重复播放短时间内会引起卡顿，这就是bug的原因 。
&emsp;

(另外，延时间隔设置的越长，这个卡顿越明显）。