/*
 * rust函数
 * 2025-02-08
 */

// 没有参数和返回值的函数
fn func_no_param() {
    println!("Enter func_no_param");
}

fn test_func() {
    println!("[test_func] ---------------------------------------------------");

    //调用函数
    func_no_param();
}

fn main() {
    test_func();
}
