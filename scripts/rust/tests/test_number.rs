// learning rust int and float number
// 2323-05-31

// i8 i16 i32 i64 i128 isize
fn test_signed_int() {
    println!("[test_signed_int]: --------------------------------------");

    let num_i8:i8 = 123;
    println!("num_i8: {}", num_i8);

    let num_i16:i16 = -123;
    println!("num_i16: {}", num_i16);

    let num_i32:i32 = i32::MIN;
    println!("num_i32: {}", num_i32);

    let num_i64:i64 = 123;
    println!("num_i64: {}", num_i64);

    let num_i128:i128 = 0;
    println!("num_i128: {}", num_i128);

    let num_isize:isize = isize::MAX;
    println!("num_isize: {}", num_isize);
}

// u8 u16 u32 u64 u128 usize
fn test_unsigned_int() {
    println!("[test_unsigned_int]: ------------------------------------");

    let num_u8:u8 = 123;
    println!("num_u8: {}", num_u8);

    let num_u16:u16 = 123;
    println!("num_u16: {}", num_u16);

    let num_u32:u32 = 123;
    println!("num_u32: {}", num_u32);

    let num_u64:u64 = 123;
    println!("num_u64: {}", num_u64);

    let num_u128:u128 = u128::MAX;
    println!("num_u128: {}", num_u128);

    let num_usize:usize = 123;
    println!("num_usize: {}", num_usize);
}

// different base
fn test_different_base() {
    println!("[test_different_base]: ----------------------------------");

    // hex
    let hex:u32 = 0xff;
    println!("hex: 0x{:x}", hex);
    println!("HEX: 0x{:X}", hex);

    // oct
    let oct:u32 = 0o123;
    println!("oct: 0o{:o}", oct);

    // bin
    let bin:u32 = 0b11110000;
    println!("bin: 0b{:b}", bin);
}

//f32 f64
fn test_float() {
    println!("[test_float]: -------------------------------------------");

    let x = 2.0; // f64
    let y:f32 = 3.2; // f32
    let z:f64 = 4.8; // f54
    println!("x: {}, y: {}, z: {}", x, y, z);
}

fn main() {
    test_signed_int();
    test_unsigned_int();
    test_different_base();
    test_float();
}
