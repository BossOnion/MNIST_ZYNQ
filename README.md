# MNIST_ZYNQ  
  
【说明】    
手写数字识别：MNIST数据集  
平台：xc7z020clg400-2（正点原子领航者V2）  
读取模型参数：Netron——https://netron.app  
  
【内容】  
0-model：训练好的模型（conv1、conv2、fc1、fc2=weight/bias=0/1、2/3、4/5、6/7）可用于测试  
1-origin：参数格式均为float32  
    float32-c++: 卷积池化ip核的C++原代码和性能参数  
    float32-ip.rar： 封装并输出的卷积池化ip核  
soc：本地图片识别片上系统  
