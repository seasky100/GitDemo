1,����ʹ��CSerialPort����Ӻ���ʾ 
����:error C2664: ��CreateFileW��: ���ܽ����� 1 �ӡ�char *��ת��Ϊ��LPCWSTR��
���1:��Ŀ���ԡ����������ԡ������桪���ַ����������ֽ��ַ���
���2:��������ǿ��ת�������ڲ���1ǰ����(LPCWSTR)��reinterpret_cast<LPCWSTR>(���ʽ)
      ��չ��C++ �µ�����ת�������� static_cast, const_cast, dynamic_cast, ��reinterpret_cast��

2,CSerialPort���г���
����:Run-Time Check Failure #3 - The variable 'comstat' is being used without being initialized.
���1:һ�ֽ�������Ǹı��������ʱ��飨changing the runtime checks in project settings�����ڲ˵�Project��>Project properties-> C/C++ -> Code generation-> Basic Runtime checks --> change to 'Default'�������İ����ǣ���Ŀ-������-����������-��C/C++-����������-����������ʱ���-������ΪĬ�ϣ�������������ʱ����ΪĬ��֮�󣬱�����Ȼ˳��ͨ���ˣ��򴮿ڵ������ַ�����Ϣ�����ˣ��ٴӴ��ڵ���������SerialPortTest������Ϣʱ��Ҳ�����ˡ�
���2:��һ�ֽ�������ǽ�CSerialPort.CPP�е�COMSTAT comstat;��Ϊstatic COMSTAT comstat;��������֮��debug˳��ͨ����Ȼ����ԣ��봮�ڵ��������໥����Ϣ���ϣ��ˡ�Ϊʲô�������ܽ���أ���ʵ����ʹ��debug�������ʱ�����Ļ�������ʱ����ʼ����Ϊ������(/RTC1����ͬ�� /RTCsu)�����������ָ����ջ֡(/RTCs)��δ��ʼ���ı���(/RTCu)��������Ҫ���δ��ʼ���ı��������Խ�SerialPort.cpp�е�COMSTAT comstat;��Ϊstatic COMSTAT comstat;�Ϳ�������ʹ��CSerialPort���ˡ�
     ��������debug�µĽ������������Release����״̬ʱ����ᷢ�ֲ�����Ҫ��COMSTAT comstat;��Ϊstatic COMSTAT comstat;���ܱ���ɹ����ҷ��ͽ�����Ϣ��������ʵ����Release�£����Ļ�������ʱ����ʼ������ΪĬ�ϡ���Ӧ��Ҳ���ǵ�һ�ֽ������֮�ڡ�

