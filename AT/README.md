# AT指令配置蓝牙模块
**工具：串口助手**
## 基本步骤
1.连接蓝牙模块和USB转接头

  注：***TXD,RXD交叉连接！***

2.利用串口助手配置蓝牙模块
  
  常用指令：
      
       AT+NAME=<Param>  //重命名

       AT+NAME？  //查询名称

       AT+PSWD=<Param>  //设置配对密码 

       AT+ PSWD？  //查询密码

       AT+VERSION？  //获取版本号
