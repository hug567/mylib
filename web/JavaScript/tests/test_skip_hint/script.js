/*
 * 练习：链接跳转是弹出提示窗口
 * 时间：2023-10-05
 */
//页面加载完成时调用函数initAll
window.onload = initAll;

function initAll() {
    //点击id为redirect的链接时调用函数redirect
    document.getElementById("redirect").onclick = initRedirect;
}

function initRedirect() {
    //弹出提示
    alert("将跳转到页面：test_skip_hint2");
    //跳转到原页面
    window.location = this;
    return false;
}