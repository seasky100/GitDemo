1,其中使用CSerialPort类添加后提示 
错误:error C2664: “CreateFileW”: 不能将参数 1 从“char *”转换为“LPCWSTR”
解决1:项目属性—〉配置属性—〉常规—〉字符集—〉多字节字符集
解决2:利用类型强制转换，即在参数1前加上(LPCWSTR)或reinterpret_cast<LPCWSTR>(表达式)
      扩展：C++ 新的类型转换操作符 static_cast, const_cast, dynamic_cast, 和reinterpret_cast。

2,CSerialPort类中出错
错误:Run-Time Check Failure #3 - The variable 'comstat' is being used without being initialized.
解决1:一种解决方案是改变基本运行时检查（changing the runtime checks in project settings）：在菜单Project－>Project properties-> C/C++ -> Code generation-> Basic Runtime checks --> change to 'Default'，在中文版中是：项目-〉属性-〉配置属性-〉C/C++-〉代码生成-〉基本运行时检查-〉设置为默认，当将基本运行时检查改为默认之后，编译自然顺利通过了，向串口调试助手发送消息正常了，再从串口调试助手向SerialPortTest发送消息时，也正常了。
解决2:另一种解决方案是将CSerialPort.CPP中的COMSTAT comstat;改为static COMSTAT comstat;这样改了之后，debug顺利通过，然后调试，与串口调试助手相互发消息都ＯＫ了。为什么这样就能解决呢？其实当你使用debug解决方案时，它的基本运行时检查初始设置为：两者(/RTC1，等同于 /RTCsu)，这个两者是指：堆栈帧(/RTCs)，未初始化的变量(/RTCu)。由于它要检查未初始化的变量，所以将SerialPort.cpp中的COMSTAT comstat;改为static COMSTAT comstat;就可以正常使用CSerialPort类了。
     以上是在debug下的解决方案，当在Release编译状态时，你会发现并不需要将COMSTAT comstat;改为static COMSTAT comstat;就能编译成功并且发送接收消息正常。其实，在Release下，它的基本运行时检查初始设置已为默认。这应该也算是第一种解决方案之内。

