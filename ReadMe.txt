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

3,���DALSA����������
3.1 ��Ŀ-����ҳ-C/C++-����-���Ӱ���Ŀ¼
.;C:\Program Files\Teledyne DALSA\Sapera\Include;C:\Program Files\Teledyne DALSA\Sapera\Classes\Basic;C:\Program Files\Teledyne DALSA\Sapera\Classes\Gui;%(AdditionalIncludeDirectories)
3.2 ��Ŀ-����ҳ-C/C++-��������-���п�-���̵߳���DLL
3.3 ��Ŀ-����ҳ-������-����-���ӿ�Ŀ¼ C:\Program Files\Teledyne DALSA\Sapera\Lib\Win64
3.4 ��Ŀ-����ҳ-������-����-�������� SapClassBasic.lib;SapClassGuiD.lib;ZLBImage.lib;ZLBCommon.lib
3.5 ��Ŀ-����ҳ-������-�߼�-Ŀ������-MachineX64
3.6 ��Ŀ-����ҳ-��Դ-����-���Ӱ���Ŀ¼ ..\..\..\..\Classes\Gui;%(AdditionalIncludeDirectories)
3.7 ��Ŀ-����ҳ-�����¼�-Ԥ�������¼�-������ 
if exist %SystemRoot%\SysWOW64 goto end
echo (Sapera LT warning) Compiling a 64-bit configuration under 32-bit Windows
:end

4,CSerialPort���б�����־���
����:warning C4996: 'sprintf': This function or variable may be unsafe. Consider using sprintf_s instead. To disable deprecat
���1:��Ŀ->����->��������->C/C++ -> Ԥ������ -> Ԥ���������壬����_CRT_SECURE_NO_DEPRECATE 



