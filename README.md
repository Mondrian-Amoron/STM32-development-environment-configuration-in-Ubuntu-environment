​
写在前面：
        我是南昌航空大学洪鹰战队22级电控组成员，在学习和备赛的过程中使用过很多开发环境，从Keil到CubeIDE，再到VScode，最后还是觉得VScode使用起来比较方便。在24赛季的备赛过程中，我们接触并使用了湖南大学跃鹿战队的开源电控框架basic_framework，感受到了使用Ozone进行调试的方便性，由此产生了探索的小兴趣。

        在联盟赛结束后我开始探索Ubuntu系统下的STM32开发环境的搭建，并在一次次试错中总结出了一个较为方便的开发环境搭建过程，故写下此篇博客用以记录，方便后面重装系统后能够快速重建开发环境，也为从事相关开发工作的同学们提供一个思路。

在此感谢湖南大学跃鹿战队电控开源框架basic_framework提供的环境搭建思路，附上框架链接：
basic_framework: Hey this is the basic frame work for robomaster standard infantry Robots! enjoy using it, have fun developing Robot with us
https://gitee.com/hnuyuelurm/basic_framework

 一、Ubuntu系统的安装
1、启动盘的制作和双系统的安装
这里推荐一个b站的视频，这个UP主讲的非常细，Ubuntu的启动盘制作可以参考这个视频

（建议：关于内存分布这块，建议至少120G，且直接挂载一个根节点，能提高内存空间利用率）

Windows 和 Ubuntu 双系统的安装和卸载_哔哩哔哩_bilibili
Windows 和 Ubuntu 双系统的安装和卸载共计16条视频，包括：双系统启动效果、下载Ubuntu系统镜像、下载安装镜像工具等，UP主更多精彩视频，请关注UP账号。
https://www.bilibili.com/video/BV1554y1n7zv/?spm_id_from=333.1007.top_right_bar_window_custom_collection.content.click&vd_source=db1d1f91faddd9a92b98355deb2f94a6
（建议：自备一个大容量高速U盘，每隔一段时间将自己重要的资料或工程文件都在U盘里备份一份，因为永远不知道Ubuntu会在什么时候突然崩溃）

2、拯救者BIOS启动
因为我的电脑是拯救者的，所以当时启动安装时，为保险起见专门找了拯救者的BIOS启动相关注意事项，以供大家参考

联想拯救者Y7000P双系统Ubuntu安装记录_哔哩哔哩_bilibili
-, 视频播放量 11288、弹幕量 1、点赞数 98、投硬币枚数 34、收藏人数 131、转发人数 42, 视频作者 Astra-github, 作者简介 谁能赐我一篇SCI，相关视频：Windows11 安装 Ubuntu 避坑指南，手把手教你安装双系统 windows11+ubuntu 22.04(1)，Windows 和 Ubuntu 双系统的安装和卸载，这个双系统太美了！！，一步解决联想拯救者R9000p 5800h安装ubuntu后屏幕无法调节亮度的问题！！！，几分钟让你学会安装Windows双系统，无需U盘和PE，ros安装成功～联想拯救者r7000p win10和Ubuntu双系统，windows+ubuntu双系统详细安装教程，互不冲突，3分钟安装ubuntu20.04显卡驱动（大学生亲试一整个白天），联想Y7000安装ubuntu18.04系统
https://www.bilibili.com/video/BV1j34y1y7iy/?spm_id_from=333.1007.top_right_bar_window_custom_collection.content.click&vd_source=db1d1f91faddd9a92b98355deb2f94a6

3、更改Ubuntu的时间
双系统会导致Ubuntu比Windows的时间快8小时，而Windows的时间比Ubuntu慢8小时，所以需要解决系统时间同步的问题。还是第一次分享的那个视频，后面有一节讲到了时间同步的问题。

（建议：打开字幕观看，因为有些莫名出现的问题，会在弹幕里有解答）

系统时间同步问题_哔哩哔哩_bilibili
系统时间同步问题是Windows 和 Ubuntu 双系统的安装和卸载的第9集视频，该合集共计16集，视频收藏或关注UP主，及时了解更多相关视频内容。
https://www.bilibili.com/video/BV1554y1n7zv?p=9&vd_source=db1d1f91faddd9a92b98355deb2f94a6

二、配置C/C++环境
打开终端，以此输入以下命令来安装gcc、g++、gdb

1、安装gcc
sudo apt-get install gcc
2、安装g++
sudo apt-get install g++
3、安装gdb（调试用）
sudo apt-get install gdb
4、运行以下三条命令来看是否安装成功
gcc -v

g++ -v


gdb -v


5、可以使用vim或gedit来编写一段简单的代码运行一下（可跳过）
        对于代码或一个工程，最好是使用专属的文件夹来进行分类管理，这样会显得很有条理，管理起来也方便。例如在此处，我在主目录下创建了/Project/CxC++/test，test即是我的工程文件名，在这里面我们写一个C++程序来进行简单的验证。（以vim为例）

（1）使用vim创建hello.cpp
vim hello.cpp
（2）如果没有vim则先安装vim
sudo apt-get install vim
（3）成功创建hello.cpp后，进行代码编写：
关于vim的操作，感兴趣的同学可以上网搜索相关资料进行学习，在这里我就不班门弄斧了，简单的操作一下：

1、使用vim创建hello.cpp后，可以看到如下的场景



2、按下“i”键，进入编辑模式（左下角也有提示“插入”）



3、进行简单的代码编写



4、编辑完成后，先按一次“ESC”，此时左下角的“插入”会消失，然后同时按下“Shift”和“：”键，待下方出现“：”后，输入wq，然后按下回车。（wq表示保存并退出）



5、编写完成后，执行下面的命令对cpp文件进行编译

g++ -o hello hello.cpp

6、执行编译好的.o文件，验证运行效果



三、安装、配置VScode
1、前往VScode的官网进行下载，注意选择下载.deb
Visual Studio Code - Code Editing. Redefined
Visual Studio Code is a code editor redefined and optimized for building and debugging modern web and cloud applications.  Visual Studio Code is free and available on your favorite platform - Linux, macOS, and Windows.
https://code.visualstudio.com/




2、下载完成之后，在所属文件夹打开终端（一般默认是在“下载”里的）


3、执行如下命令，安装VScode，注意后面的.deb文件版本要对应自己所下载的版本，我这里以1.89为例（dpkg是Debian 系统中的软件包管理工具，感兴趣的可以自己去了解，这里就不多赘述了）
sudo dpkg -i code_1.89.0-1714530869_amd64.deb


4、打开VScode，安装必要的插件
（1）简体中文插件，一般首次进入后都会在右下角提示你安装的，如果没有提示就自己去搜索安装（注：安装完后需要重启软件才会生效）



(2)在左侧扩展商店中搜索“C/C++”，选择第一个进行安装



5、 创建一个新工程，并使用VScode打开，创建第一个.cpp文件进行测试
（1）我这里以创建一个test1文件夹为例（新建“test1”文件夹，右键选择“使用其它程序打开”，选择使用VScode打开）




（2）创建一个main.cpp


（3）编写测试代码
#include<iostream>
using namespace std;

int main()
{
    cout << "Hello VScode ubder Ubuntu!!" << endl;
    return 0;
}


（4）配置.vscode里的相关.json文件，可以选择右键新建名为“.vscode”的文件夹，然后手动创建以下三个.json文件


launch.json:
{
    "version": "0.2.0",
    "configurations": [
    {
        "name": "(gdb) Launch",
        "type": "cppdbg",
        "request": "launch",
        "program": "${workspaceFolder}/${fileBasenameNoExtension}.out",
        "args": [],
        "stopAtEntry": false,
        "cwd": "${workspaceFolder}",
        "environment": [],
        "externalConsole": true,
        "MIMode": "gdb",
        "preLaunchTask": "build",
        "setupCommands": [
            {
            "description": "Enable pretty-printing for gdb",
            "text": "-enable-pretty-printing",
            "ignoreFailures": true
            }
        ]
    }
    ]
}
settings.json:
{
    "files.associations": {
        "ostream": "cpp",
        "iostream": "cpp",
        "array": "cpp",
        "atomic": "cpp",
        "bit": "cpp",
        "*.tcc": "cpp",
        "cctype": "cpp",
        "clocale": "cpp",
        "cmath": "cpp",
        "compare": "cpp",
        "concepts": "cpp",
        "cstdarg": "cpp",
        "cstddef": "cpp",
        "cstdint": "cpp",
        "cstdio": "cpp",
        "cstdlib": "cpp",
        "cwchar": "cpp",
        "cwctype": "cpp",
        "deque": "cpp",
        "string": "cpp",
        "unordered_map": "cpp",
        "vector": "cpp",
        "exception": "cpp",
        "algorithm": "cpp",
        "functional": "cpp",
        "iterator": "cpp",
        "memory": "cpp",
        "memory_resource": "cpp",
        "numeric": "cpp",
        "random": "cpp",
        "string_view": "cpp",
        "system_error": "cpp",
        "tuple": "cpp",
        "type_traits": "cpp",
        "utility": "cpp",
        "initializer_list": "cpp",
        "iosfwd": "cpp",
        "istream": "cpp",
        "limits": "cpp",
        "new": "cpp",
        "numbers": "cpp",
        "stdexcept": "cpp",
        "streambuf": "cpp",
        "typeinfo": "cpp"
    }
}
tasks.json:
{
    "version": "2.0.0",
    "tasks": [
    {
    "label": "build",
    "type": "shell",
    "command": "g++",
    "args": ["-g", "${file}", "-std=c++11", "-o", "${fileBasenameNoExtension}.out"]
    }
    ]
}
（5）回到main.cpp，按下F5进行编译运行（实际上是调试，如果打了断点的话会停在断点）


四、安装、配置arm-none-eabi-gcc交叉编译工具链
关于交叉编译工具链的下载，有很多种方法，可以前往官网下载

Downloads | GNU Arm Embedded Toolchain Downloads – Arm Developer
Download the GNU Embedded Toolchain for ARM, an open-source suite of tools for C, C++, and Assembly programming for 32-bit ARM Cortex-A, ARM Cortex-M and Cortex-R families
https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

（推荐）或者直接使用我上传在天翼云盘的资源（因为百度网盘没有会员的话下载会非常慢）访问码：pgn6
arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi编译工具链下载
天翼云盘是中国电信推出的云存储服务，为用户提供跨平台的文件存储、备份、同步及分享服务，是国内领先的免费网盘，安全、可靠、稳定、快速。天翼云盘为用户守护数据资产。
https://cloud.189.cn/web/share?code=nMv6Bn67b2Az%EF%BC%88%E8%AE%BF%E9%97%AE%E7%A0%81%EF%BC%9Apgn6%EF%BC%89
再附上百度网盘的下载链接：（访问码m9vi）

arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi编译工具链下载
http://xn--gzu811i//pan.baidu.com/s/17r_5awLRDtE-ehpPEQuJ2w?pwd=m9vi%20%E6%8F%90%E5%8F%96%E7%A0%81:%20m9vi%20%E5%A4%8D%E5%88%B6%E8%BF%99%E6%AE%B5%E5%86%85%E5%AE%B9%E5%90%8E%E6%89%93%E5%BC%80%E7%99%BE%E5%BA%A6%E7%BD%91%E7%9B%98%E6%89%8B%E6%9C%BAApp%EF%BC%8C%E6%93%8D%E4%BD%9C%E6%9B%B4%E6%96%B9%E4%BE%BF%E5%93%A6
下载结束后，打开所在文件夹终端（建议将该压缩包转移到一个不常更改的文件夹里，可以新建），输入以下命令进行解压：

tar -xvf arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz
解压后得到一个同名文件夹


复制可执行文件“bin”的路径，操作如下：

（1）进入“arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi”文件夹

（2）进入“bin”文件夹

（3）在空白处右键，选择“在终端打开”

（4）输入以下指令查看路径

pwd
如图白色部分所示就是bin文件的路径，选择后按住“Shift”+“Ctrl”+“c”进行复制



打开终端，输入下面的指令，打开profile文件（不加sudo的话只能以“只读”打开）

sudo vim /etc/profile
在打开的文件末尾输入以下内容（注：$PATH:后面的链接为我们刚复制的bin的链接，配置时需要根据实际情况进行修改）

步骤：

（1）输入“i”进入插入模式

（2）将光标移动到末行后，回车另起一行

（3）输入前面的export PATH=$PATH:

（4）按住“Shift”+“Ctrl”+“v”进行粘贴

（5）按下Esc，然后按下“Shift”+“：”，输入“wq”，保存修改并退出

export PATH=$PATH:/home/yml/mondrian/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin


执行如下命令，然后重启电脑/虚拟机使环境变量生效

source profile
重启完成后执行以下命令看是否配置成功



五、安装JLink驱动
1、安装libreadline库
我们烧录会用到JLinkExe的命令，而JLinkExe会用到libreadline库，所以要安装libreadline库，执行如下命令安装：

sudo apt-get install libreadline-dev
2、进入SEGGER的官网，下载JLink驱动（选择Linux下的64-bit DEB Installer）
SEGGER - The Embedded Experts - Downloads - J-Link / J-Trace
Download the latest SEGGER trial versions, eval packages and user manuals!
https://www.segger.com/downloads/jlink/



点击Download



左下角勾选同意，然后“Download software”



速度应该会特别慢，这里可以选择我上传到云盘的资源（v792o版本）：

天翼云盘（访问码b4oi）：

JLink驱动
天翼云盘是中国电信推出的云存储服务，为用户提供跨平台的文件存储、备份、同步及分享服务，是国内领先的免费网盘，安全、可靠、稳定、快速。天翼云盘为用户守护数据资产。
https://cloud.189.cn/web/share?code=FzyMRvYFz2ye%EF%BC%88%E8%AE%BF%E9%97%AE%E7%A0%81%EF%BC%9Ab4oi%EF%BC%89
百度网盘（访问码k365）：

JLink驱动
https://pan.baidu.com/s/1DZm-yv6eYUxakmD4R5_kBA?pwd=k365

3、安装JLink驱动
下载好后，打开.deb文件所在的文件夹，打开终端，执行以下命令进行安装：

sudo dpkg -i JLink_Linux_V792o_x86_64.deb
因为我之前已经安装过了，所以这里显示“覆盖”



4、查看JLink版本
执行如下命令来查看Jlink版本，验证是否安装成功

jlink --version


5、进入SEGGER查看相关可执行文件
输入以下命令，然后执行“ls”查看相关的可执行文件（一般默认安装位置都是在/opt下的）

cd /opt/SEGGER/JLink


六、J-Link Commander交互模式初体验
1、直接执行JLinkExe命令
主要是为了验证一下是否安装成功，执行以下命令，进入J-Link Commander交互模式

JLinkExe
此时如果没有链接Jlink的话会出现这个界面：



我们点击No，然后会进入Commander交互模式，在这种模式下，我们可以执行各种 J-Link Commander 提供的命令来连接、配置调试器，下载程序或文件到目标设备等操作，感兴趣的同学可自行学习。

执行“q”指令退出该模式。



2、初次尝试使用JLinkExe来与设备建立连接
连接A板（XH2.54转MX1.25的转接线需要自己焊接，注意查看手册，对上线序）



当然，如果我们接入Jlink设备后，再执行这个命令会提示你执行“connect”来与设备进行链接，或者输入“?”来查看更多的指令帮助。



我们输入“connect”后，会返回我们连接的开发板芯片的信息，并让我们确认。

我们输入芯片型号来设置Device（这里以STM32F427IIH6为例）



选择连接接口为SWD（或JTAG，根据实际需求来看）



选择传输速度，默认4000kHz，我们可以自行修改，比如我这里设置2000kHz



按下回车后，等待几毫秒便会提示连接成功了（会打印检测到的芯片以及寄存器信息等，例如我们可以找到熟悉的“Cortex-M4”）



假设这里我们已经编译得到了一个test.bin或test.hex文件，那么到这一步后，我们就可以使用下面两条命令来实现烧录.bin文件或.hex文件了（这里不做演示，只做说明）

loadbin ./test.bin,0x08000000
loadfile ./test.hex
然后执行“q”退出Commander模式。

七、安装CubeMX
1、安装Java环境
打开终端，输入下面的指令安装Java运行环境

sudo apt install default-jre
安装完成后，输入下面的指令验证是否安装成功

java --version


2、安装CubeMX
前往官网下载CubeMX软件包（点击获取软件）

STM32CubeMX软件下载
https://www.st.com/zh/development-tools/stm32cubemx.html#overview


选择第一个下载（Linux版本）



之后会弹出一个许可协议，我们选择同意后，会弹出选择下载身份的界面，可以右下角选择访客下载，也可以注册一个ST账号后再登录下载，这里建议注册一个账号后再下载

（注：无论是选择访客下载还是注册后下载，软件的下载链接都会发送到你填写的邮箱里，所以请确保你的邮箱是在电脑上打开的）



将下载好的包解压后，进入，双击运行“SetupSTM32CubeMX-6.11.1”（以实际下载的版本为主）



然后根据向导一步步进行安装，注意选择一个能容得下的盘



安装完成后，打开刚刚选择的安装位置（例如我这里是/home/yml/STM32CubMX），双击“STM32CubeMX”启动程序



登录之后，点击右边栏的"INSTALL/REMOVE"或“Help”->“Manage embedded sofeware packages”



选择自己需要的芯片型号的HAL库包，选好之后点击“INSTALL”，想移除某软件包也可以在这个界面选择，然后点“REMOVE”



（关于工程的创建过程，可以自行搜索学习，这里就不赘述了，只需注意一点：Project Maneger那里的Toolchain/IDE要选择Makefile）



八、编写JLink烧录脚本并修改Makefile
1、打开工程
使用VScode打开一个新建好的工程



2、编写代码
打开main.c，随便写点什么，比如这里来个经典点灯



3、编译
在底部的终端栏里执行以下指令进行编译（"-j16"这里的16对应电脑核心数，我的是16核的，所以是-j16，根据电脑实际硬件配置进行修改，例如CPU是20核的就改为-j20）

make -j16


执行后可以看到编译好的.elf、.hex、.bin文件



4、编写JLinkScript脚本
在工程主目录下创建一个.JLinkScript脚本文件，并编写以下内容

speed 2000
device STM32F103C8
r
loadfile ./build/Jlink_test.hex
q
解释：
speed 2000： 设置J-Link与目标设备之间的通信速度为2000 kHz（这个速率可自行修改）。
device STM32F103C8： 指定目标通信设备的型号为STM32F103C8，如果是其他芯片需要修改为对应的型号。
r： 通过DEMCR.VC_CORERESET来在复位后暂停核心的执行。在ARM Cortex-M系列微控制器中，DEMCR是一个调试与监控寄存器，而VC_CORERESET是其中的一个位（bit）。将这个位设置为1会导致在复位后暂停核心的执行。
loadfile ./build/Jlink_test.hex： 加载指定的hex文件（位于"./build/Jlink_test.hex"路径下）到目标设备的Flash存储器中。（注：这里的Jlink_test.hex是上一步“编译”后得到的，工程名称不一样，所得到的.hex文件名也不一样，需要根据实际情况进行修改）。
q： 退出J-Link调试工具，一次烧录结束。



修改（只是举例，可跳过不看）：
如果想要修改生成的.elf、.hex、.bin文件名，可以打开Makefile文件，在Target这里进行修改（例如，把Jlink_test修改为test1后，再次编译就会生成test1.elf、test1.hex、test1.bin）





注：修改名称后，记得将STM32.JLinkScript里的.hex文件名也修改了。

5、修改Makeflie
打开Makefile后，滑动至最底下，添加下面这条命令

Flash:
	JLinkExe -if SWD -CommanderScript STM32.JLinkScript
解释：调用JLinkExe（J-Link调试工具），选择SWD接口（当然你也可以设置为JTAG）与目标设备进行通信，然后执行名为"STM32.JLinkScript"的J-Link脚本文件。



到这一步后，你就可以使用“make”指令来进行编译，然后插上开发板，使用“make Flash”指令来进行烧录了。

make Flash
部分烧录日志的截图：





6、创建烧录task
配置.vscode里的相关.json文件，可以选择右键新建名为“.vscode”的文件夹，然后手动创建“tasks.json”文件，添加下面的内容：

{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "jlink_Flash", 
            "type": "shell",
            "command":"make Flash",
            "group": {
                "kind": "build",
                "isDefault": false,
            }
        }
    ]
}


保存之后，就可以点击“终端->运行任务->jlink_Flash”来进行烧录操作了




当然，也可以配置的更加方便一点，比如使用快捷键“F5”实现一键烧录下载，可以自行去尝试。

九、安装Ozone
        Ozone是一款功能强大的调试和系统分析工具，也是SEGGER开发的，支持多种微处理器架构和调试接口，并与SEGGER的J-Link调试器兼容。

1、下载Ozone的软件包
官网：Ozone – The Performance Analyzer
The SEGGER Ozone J-Link Debugger & Performance Analyzer is an “All-In-One” software solution for debugging and performance analysis.
https://www.segger.com/products/development-tools/ozone-j-link-debugger/
进去官网后点击“Downloads”



进去之后等一等，网页加载完成后会下滑到“ Ozone - The J-Link Debugger”这一栏，在“Linux”那一栏选择下载“64-bit DEB Installer”



同意SEGGER的软件安装协议（忘记的可以回看第五节里安装JLink驱动那块的流程），然后就开始下载了



老样子，官网下载比较慢，我在云盘也上传了相关软件包（V326版本），需要的可以下载

天翼云盘（提取码：tv8u）：

Ozone_Linux_V326
天翼云盘是中国电信推出的云存储服务，为用户提供跨平台的文件存储、备份、同步及分享服务，是国内领先的免费网盘，安全、可靠、稳定、快速。天翼云盘为用户守护数据资产。
https://cloud.189.cn/web/share?code=aINf6rmaUnye%EF%BC%88%E8%AE%BF%E9%97%AE%E7%A0%81%EF%BC%9Atv8u%EF%BC%89
百度网盘（提取码：np6y）：

Ozone_Linux_V326
https://pan.baidu.com/s/1Lq2iSv_zSqz_0Q9vOcYNRA?pwd=np6y

2、安装Ozone
打开包含软件包的文件夹



从这里打开终端，执行以下命令进行安装（注：这里的软件包版本要修改为自己实际下载的）

sudo dpkg -i Ozone_Linux_V326_x86_64.deb


十、Ozone的配置及初次体验
1、基础调试配置
打开终端，执行下面的命令，打开Ozone

ozone


在弹出的小框中，配置Device为自己开发板的芯片型号（首次打开应该是不会显示的，需要手动搜索，我这里显示C8是因为之前配置过）





选择好芯片型号后，Register Set会自动设置好，我们需要设置的是Peripherals，选择对应芯片的.svd文件



（插曲）.svd文件的寻找
这个文件可以在ST的官网下载到，流程如下：

进入官网，在搜索栏里搜索想要寻找的芯片型号

ST意法半导体官网
https://www.st.com/content/st_com/zh.html


点击搜索出来的芯片，进去后点击“CAD资源”这一栏



在全部资源里可以找到SVD（System View Description）文件包



下载解压后就可以得到这一系列的各种型号的.svd文件了



选择好.svd文件后，点击右下角的“Next”，在这个界面，我们需要选择“Target Interface”为“SWD”,点击识别到的JLink设备，然后点“Next”。



在这一步需要选择.elf文件，这是由Makefile生成的（第八节的第3小节里提到过）。这个文件通常在我们的工程文件的build目录下。



点击“Open”进行选择，选择好后我们点击“Next”进行下一步配置。



这一步我们保持默认就好，点击“Finish”



下面这个界面就是配置完成后的界面了，我们可以点击左上角的绿色按钮开始启动调试



2、常用调试配置
Ozone中提供了非常多的控件，在这里介绍两个调参常用的，其它控件的功能大家可以自行探索

（1）Watched Data
单击左上角的“View”，在“General”一栏找到“Watched Data”，选择“New Watched Data Window”，就会生成一个下图所示的小窗口，我们可以在这个窗口里查看变量的值。



例如：我们定义一个静态全局变量Test_Data，然后把它添加进来，看看它的值



注：watch里的变量不会实时更新，只有在暂停或遇到断点的时候才会更新，如果想让它自动刷新的话，可以右键变量名->将“Refresh Rate”设置为“5Hz”（一秒刷新5次），或者添加到Graph里实时更新（刷新率更高）

（2）Break&Tracepoints
单击左上角的“View”，在“General”一栏找到“Break&Tracepoints”，单击后就会生成一个下图所示的小窗口，我们可以在这个窗口里查看和管理设置的断点。



（3）Timeline
单击左上角的“View”，在“Advanced”一栏找到“Timeline”，单击后就会生成一个下图所示的小窗口，我们可以在这个窗口里查看变量随时间的变化过程，并且可以自行设置采样频率（PID调参神器）。



我们可以简单写一个小例子看看效果：

    HAL_Delay(1000);
    Test_Data = Test_Data + 20;
    HAL_Delay(1000);
    Test_Data = Test_Data - 20;
将Watchd Data窗口里的“Test_Data”右键，选择“Graph”后，就能在“Timeline”窗口看见它的变化了，我们将时间滚动设置的慢一点（比如设置为1秒钟），就能看到“Test_Data”的可视化变化情况了。



（4）Data Sampling
单击左上角的“View”，在“Advanced”一栏找到“Data Sampling”，单击后就会生成一个下图所示的小窗口。这也是一个类似于“Watched Data”的变量监视窗口，它的优点在于可以自行设置更高的采样频率，例如这里设置了采样频率为1kHz。



3、调试文件的保存
        完成一次调试后，可以将这次调试的文件保存起来，下次再打开的时候，就可以紧接着上次调试的工程继续调试了（就不用每次都繁琐的添加变量设置采样时间了）

点击左上角的“File”，然后点击“Save Project as...”，此时会弹出一个会话框，让你选择调试工程保存的位置以及名称。（建议单独创建一个文件夹用来保存调试文件，文件夹命名最好加上芯片名称用以区分，找起来也方便找）



当你没有保存的时候，点击右上角的红色“X”退出时也会提示你让你进行保存的。



4、调试文件的加载
再次启动Ozone时，会弹出小对话框让你选择，我们点击“Open Existing Project”后就会弹出一个对话框，选择上次保存的“.jdebug”文件打开，就能恢复上次调试时的场景。







当我们选择“Create New Project”后，就会弹出熟悉的配置界面了，当我们想要调试其它工程或其它芯片的时候可以选择这个。



5、关于代码修改与调试
        在这个环境下，我们是使用VScode来编写代码，使用Ozone来进行调试，当我们在调试过程中发现了问题，想要修改代码的时候，可以直接暂停Ozone中正在调试的进程，然后打开VScode进行修改。在修改完执行make指令进行编译后，Ozone会检测到代码发生了改变并重新加载.elf文件。

如下图，在VScode中做了修改后，Ozone会检测到变化，并提示你加载新的修改，点击“Yes”即可将新修改的内容加载进来。



结束语：
        本想着是作为一次配置流程的记录，以方便日后如果系统出了问题，需要重装时，我能快速的重新搭建起来开发环境。但是在慢慢记录的过程中，我想到或许发表了后会有其他小伙伴也来看，所以重头又详细的补充了一些，最后发现洋洋洒洒的写了1万2千多字。这样配置可能不是最优的，会有人觉得又臭又长，网上有更多更好的配置流程，我只是摸索着把自己总结出来的东西进行了一个记录，并且尽量详细的说明每一个步骤。不仅是给自己看吧，也希望能够帮到有需要的人。

最后，再次感谢湖南大学跃鹿战队的电控开源框架basic_framework提供的开发环境搭建思路！

​
