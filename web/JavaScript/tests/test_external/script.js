/*
 * 练习：外部JavaScript脚本
 * 时间：2023-10-05
 */
//定义窗口加载事件处理程序，窗口加载完成后，将执行指定的JavaScript函数
window.onload = writeMessage;

function writeMessage() {
    //获取指定id的元素，并改变元素的属性
    document.getElementById("helloMessage").innerHTML = "Hello World!";
}