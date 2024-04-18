// 脚本_医院挂号.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Windows.h>
#include <iostream>
#include<fstream>
#include<string>

int main()
{

    HWND hwnd = FindWindowA("WeChatMainWndForPC", NULL);//获取微信窗口句柄
    if (hwnd == NULL) {
       std::cout << "窗口不存在";
        exit(0);
    }
    ShowWindow(hwnd, SW_MAXIMIZE);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, 1000, 700, SWP_SHOWWINDOW);//微信窗口置顶
    SetCursorPos(18, 148);//窗口移动

    /*
    *模拟鼠标键盘按键操作
    */
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    SetCursorPos(18, 100);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

    keybd_event(17, 0, 0, 0);//模拟按下ctrl
    keybd_event('F', 0, 0, 0);//模拟按下F
    keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
    keybd_event('F', 0, KEYEVENTF_KEYUP, 0);

    Sleep(1000); 
    TCHAR szText[] = L"文件传输助手"; //发送联系人

    if (OpenClipboard(hwnd)) {//系统剪切板操作
        EmptyClipboard();
        HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(szText));
        LPWSTR pData = (LPWSTR)GlobalLock(hData);
        CopyMemory(pData, szText, sizeof(szText));
        GlobalUnlock(hData);
        SetClipboardData(CF_UNICODETEXT, hData);
        CloseClipboard();
    }
    keybd_event(17, 0, 0, 0);
    keybd_event('V', 0, 0, 0);
    keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
    keybd_event('V', 0, KEYEVENTF_KEYUP, 0);//ctrl + V

    Sleep(1000);//等待微信搜索联系人
    keybd_event(13, 0, 0, 0);//按下 回车键
    keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
    std::wifstream in(L"test_auto.txt");
    in.imbue(std::locale("")); // 使用系统默认的 locale
    std::wstring s;
    while (std::getline(in, s))//着行读取数据并存于s中，直至数据全部读取
    //TCHAR sendText[] = s.c_str();//发送的消息
    {
        std::wcout << s << std::endl;
        if (OpenClipboard(nullptr)) {
            EmptyClipboard();
            // 计算需要的缓冲区大小，以字节数计算
            size_t bufferSize = (s.length() + 1) * sizeof(wchar_t); // 加1是为了包含结尾的空字符
            HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, bufferSize);
            if (hData != nullptr) {
                LPWSTR pData = (LPWSTR)GlobalLock(hData);
                if (pData != nullptr) {
                    // 将宽字符串转换为 UTF-16 编码
                    memcpy(pData, s.c_str(), bufferSize);
                    GlobalUnlock(hData);
                    SetClipboardData(CF_UNICODETEXT, hData);
                }
            }
            CloseClipboard();
        }
        for (int i = 0; i < 1; i++) {//发送消息次数
            keybd_event(17, 0, 0, 0);
            keybd_event('V', 0, 0, 0);
            keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('V', 0, KEYEVENTF_KEYUP, 0);

            keybd_event(13, 0, 0, 0);
            keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
            Sleep(500);
        }
    }
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
