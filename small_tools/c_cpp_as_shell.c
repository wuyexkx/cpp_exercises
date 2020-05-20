#if 0	// C不编译以下内容	#同时也是shell的注释
filename="$0"				            # 获取整个文件名
name="${filename%.*}"			        # 去除后缀
CC="gcc"
if [ "${filename##*.}"x = "cpp"x ];then # 判断后缀名 cpp
CC="g++"
fi
$CC -o $name "$0" 						
./$name "$@"	                        # 为可执行文件传递参数      	
rm $name
exit 
#endif

#include<stdio.h>
int main()
{
    printf("hello world!\n");
    return 0;
}
