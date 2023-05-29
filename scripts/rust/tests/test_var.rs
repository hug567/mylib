// learning rust variable
// 2323-05-29

//use std::io;

fn test_var() {
    println!("[test_var]: --------------------------------------------");

    // cannot be changed after it has been assigned
    let num01 = 5;
    println!("num01: {}", num01);

    // can be changed after it has been assigned
    let mut num02 = 6;
    println!("num02: {}", num02);
    num02 = 7;
    println!("new num02: {}", num02);
}

fn main() {
    test_var();
}
