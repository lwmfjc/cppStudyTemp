//如果定义了宏：预处理器会触发 #ifdef STB_IMAGE_IMPLEMENTATION 内部的代码块。这时，头文件里成千上万行的 C 语言源码（解码 JPG、PNG、TGA 的具体算法）才会被“释放”出来
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"