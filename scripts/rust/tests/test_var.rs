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

    // start with underline, unused variables will not be warned
    let _num03 = 8;
}

// variable deconstruction
fn test_var_dec() {
    println!("[test_var_dec]: ----------------------------------------");

    let (num01, num02) = (3, 7);
    println!("num02: {}, num02: {}", num01, num02);

    let strs = ("xing", "huang");
    let (fisrt, last) = strs;
    println!("fisrt name: {}, last name: {}", fisrt, last);
}

fn main() {
    test_var();
    test_var_dec();
}
