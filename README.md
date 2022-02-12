# Hydro Paintboard Painter

Hydro 冬日绘板自动绘制脚本。

## 使用前准备

1. 在使用此工具之前，确保你的电脑上安装了 curl，python，bandizip 以及 python 的 PIL 库。

2. 用 GIMP 处理好你需要绘制的图片。方法如下：

    1. 将 `HydroPaintboard.gpl` 放入 `<GIMP安装路径>/share/gimp/<GIMP 版本号>/palettes` 中。
    2. 用 GIMP 打开图片，选择顶栏的 `图像>模式>索引`，颜色表选择 `使用自定义色板`，下面填入 `HydroPaintboard.gpl`。下面的递色自选，建议小图片不要用。
    3. 选择顶栏的 `文件>导出为`，选择 `bmp` 格式（可能要找一会）。
    4. 确保你在下面填入 `ImagesToData.cfg` 的图片的最后一次处理都是按照上述方法。

## 使用步骤

1. 在本文件夹下创建一个文件 `ImagesToData.cfg`，每行填入一个需要画的图片，格式为 `图片路径 左上角x 左上角y`。注意图片路径中不能有空格。
2. 编译并运行 `ImagesToData.cpp`。这时应该会生成一个文件 `tasks.txt`。
3. 在本文件夹下创建一个文件 `cookies.txt`，每行填入一个 cookie。
4. 编译并运行 `Paint.cpp`。可能会生成不少文件，不要管它们，并且在本工具运行时不要删除它们。
5. 请在本工具运行时不要关闭电脑或使之睡眠，否则本工具可能会无法工作。

## 其他

感谢 ouuan 的 [LuoguPaintBoard](https://github.com/ouuan/LuoguPaintBoard)，本项目部分由此改编。  
本工具还很不完善，欢迎在 `Issues` 页面提出，或者直接开 `Pull request`。
